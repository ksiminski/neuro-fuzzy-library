/** @file GrIMP regression tests; no external test framework or datasets needed. */

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../source/common/data-modifier-imputer-granular.h"
#include "../source/descriptors/descriptor-gaussian.h"
#include "../source/descriptors/descriptor-triangular.h"
#include "../source/partitions/fcm.h"
#include "../source/service/exception.h"
#include "../source/tnorms/t-norm-min.h"
#include "../source/tnorms/t-norm-product.h"

namespace
{
   using matrix = std::vector<std::vector<double>>;
   using imputer = ksi::data_modifier_imputer_granular;

   void require(bool condition, const std::string& message)
   {
      if (!condition)
         throw std::runtime_error(message);
   }

   void near(double actual, double expected, const std::string& message)
   {
      require(std::isfinite(actual) && std::abs(actual - expected) <=
         1e-10 * std::max(1.0, std::abs(expected)), message);
   }

   template<typename Action>
   void throws(Action action, const std::string& message)
   {
      try
      {
         action();
      }
      catch (const ksi::exception& error)
      {
         require(std::string(error.what()).find(message) != std::string::npos,
            "Unexpected exception: " + std::string(error.what()));
         return;
      }
      throw std::runtime_error("Expected ksi::exception: " + message);
   }

   struct partition_trace
   {
      int calls = 0;
      ksi::dataset training;
   };

   // A known partition makes the numerical oracle independent of random FCM.
   class fixed_partitioner : public ksi::partitioner
   {
   public:
      matrix centers, spreads;
      std::shared_ptr<partition_trace> trace = std::make_shared<partition_trace>();
      bool gaussian = true;
      bool incremental = false;
      int local_calls = 0;

      fixed_partitioner(matrix c, matrix s) : centers(std::move(c)), spreads(std::move(s)) {}

      ksi::partitioner* clone() const override { return new fixed_partitioner(*this); }

      ksi::partition doPartition(const ksi::dataset& ds) override
      {
         ++trace->calls;
         ++local_calls;
         trace->training = ds;
         ksi::partition result;
         for (std::size_t c = 0; c < centers.size(); ++c)
         {
            ksi::cluster cluster;
            for (std::size_t a = 0; a < centers[c].size(); ++a)
            {
               const double center = centers[c][a] +
                  (incremental && a + 1 == centers[c].size() ? local_calls : 0);
               if (gaussian)
                  cluster.addDescriptor(ksi::descriptor_gaussian(center, spreads[c][a]));
               else
                  cluster.addDescriptor(ksi::descriptor_triangular(center - 1, center, center + 1));
            }
            result.addCluster(cluster);
         }
         // Deliberately do not populate the optional V/S matrices.
         return result;
      }
   };

   class recording_modifier : public ksi::data_modifier
   {
   public:
      std::shared_ptr<int> calls = std::make_shared<int>(0);
      recording_modifier() { description = "recording modifier"; }
      ksi::data_modifier* clone() const override { return new recording_modifier(*this); }
      void modify(ksi::dataset& ds) override
      {
         for (std::size_t r = 0; r < ds.size(); ++r)
            for (std::size_t a = 0; a < ds.getNumberOfAttributes(); ++a)
               require(ds.exists(r, a), "The next modifier received incomplete data");
         ++*calls;
      }
   };

   class invalid_tnorm : public ksi::t_norm_product
   {
   public:
      double value;
      explicit invalid_tnorm(double v) : value(v) {}
      ksi::t_norm* clone() const override { return new invalid_tnorm(*this); }
      double tnorm(double, double) const override { return value; }
   };

   ksi::dataset sample(double observed = 0.0)
   {
      ksi::dataset ds(matrix{{0, 10}, {observed, -999}});
      ds.getDatumNonConst(1)->make_attribute_incomplete(1);
      return ds;
   }

   void same(const ksi::dataset& actual, const ksi::dataset& expected)
   {
      require(actual.size() == expected.size(), "Dataset size changed");
      for (std::size_t r = 0; r < actual.size(); ++r)
      {
         require(actual.getDatum(r)->getNumberOfAttributes() ==
            expected.getDatum(r)->getNumberOfAttributes(), "Row width changed");
         for (std::size_t a = 0; a < actual.getDatum(r)->getNumberOfAttributes(); ++a)
         {
            require(actual.exists(r, a) == expected.exists(r, a), "Missingness changed");
            near(actual.get(r, a), expected.get(r, a), "Value changed");
         }
      }
   }

   void weighted_imputation_and_metadata()
   {
      fixed_partitioner partitioner({{0, 0, 10, 100}, {2, 2, 30, 300}},
                                    {{1, 1, 1, 1}, {1, 1, 1, 1}});
      ksi::t_norm_product product;
      imputer modifier(partitioner, product);
      ksi::dataset ds(matrix{{0, 0, 10, 100}, {2, 2, 30, 300}, {0, 1, -999, 999}});
      auto row = ds.getDatumNonConst(2);
      row->make_attribute_incomplete(2);
      row->make_attribute_incomplete(3);
      row->setID(42);
      row->setIDincomplete(7);
      row->setWeight(0.4);
      row->setTypicality(0.75);
      row->switchTypicality(true);
      row->addLabel("keep");
      row->setDecision(ksi::number(5.0));
      ds.setMaximalNumericalLabel(100);
      const auto original = ds;
      modifier.modify(ds);
      const double q = std::exp(-2.0);
      near(ds.get(2, 2), (10 + 30 * q) / (1 + q), "Weighted centre (first missing axis)");
      near(ds.get(2, 3), (100 + 300 * q) / (1 + q), "Weighted centre (second missing axis)");
      require(ds.exists(2, 2) && ds.exists(2, 3), "Imputed values must exist");
      for (std::size_t r = 0; r < ds.size(); ++r)
         for (std::size_t a = 0; a < 4; ++a)
            if (original.exists(r, a))
               near(ds.get(r, a), original.get(r, a), "Observed values must be unchanged");
      row = ds.getDatumNonConst(2);
      require(row->getID() == 42 && row->getIDincomplete() == 7, "IDs must be preserved");
      near(row->getWeight(), 0.4, "Weight must be preserved");
      near(row->getTypicality(), 0.75, "Typicality must be preserved");
      require(row->isTypicalityOn() && row->getLabel(0) == "keep", "Metadata must be preserved");
      near(row->getDecision()->getValue(), 5, "Decision must be preserved");
      require(ds.getMaximalNumericalLabel() == 100, "Dataset metadata must be preserved");
      require(partitioner.trace->training.size() == 2, "Train on complete rows only");
      require(modifier.get_number_of_complete_items_in_dataset() == 2 &&
              modifier.get_number_of_incomplete_items_in_dataset() == 1, "Input counts");
      require(modifier.getName() == "imputer_granular" &&
              modifier.print().find("GrIMP") != std::string::npos, "Modifier description");

      ksi::t_norm_min minimum;
      imputer min_modifier(partitioner, minimum);
      ds = original;
      min_modifier.modify(ds);
      const double q_min = std::exp(-1.5);
      near(ds.get(2, 2), (10 + 30 * q_min) / (1 + q_min), "Use the supplied t-norm");
   }

   void fully_missing_row()
   {
      fixed_partitioner p({{0, 10}, {2, 30}}, {{1, 1}, {1, 1}});
      ksi::t_norm_product t;
      imputer m(p, t);
      auto ds = sample();
      ds.getDatumNonConst(1)->make_attribute_incomplete(0);
      m.modify(ds);
      near(ds.get(1, 0), 1, "All missing: equal granule weights");
      near(ds.get(1, 1), 20, "All missing: mean of granule centres");
   }

   void passthrough_and_reuse()
   {
      fixed_partitioner p({{0, 10}}, {{1, 1}});
      ksi::t_norm_product t;
      imputer m(p, t);
      recording_modifier next;
      m.addModifier(next);
      auto ds = sample();
      m.modify(ds);
      require(p.trace->calls == 1 && *next.calls == 1, "First call and chain");
      auto original = ds;
      m.modify(ds);
      same(ds, original);
      require(p.trace->calls == 1 && *next.calls == 2, "Complete input skips clustering");
      require(m.get_number_of_incomplete_items_in_dataset() == 0, "Clear old incomplete indices");
      ksi::dataset empty;
      m.modify(empty);
      require(empty.empty() && p.trace->calls == 1 && *next.calls == 3, "Empty input and chain");
      require(m.get_number_of_complete_items_in_dataset() == 0, "Clear old training rows");
      ds = sample(0.5);
      m.modify(ds);
      require(p.trace->training.size() == 1 && *next.calls == 4, "Refit on each incomplete input");
   }

   void copy_clone_move_and_lifetime()
   {
      auto owned = [] {
         fixed_partitioner p({{0, 10}}, {{1, 1}});
         p.incremental = true;
         ksi::t_norm_product t;
         return std::make_unique<imputer>(p, t);
      }();
      recording_modifier next;
      owned->addModifier(next);
      imputer copied(*owned);
      auto first = sample();
      owned->modify(first);
      near(first.get(1, 1), 11, "Dependencies outlive constructor arguments");
      first = sample();
      owned->modify(first);
      near(first.get(1, 1), 12, "Original partitioner state");
      auto second = sample();
      copied.modify(second);
      near(second.get(1, 1), 11, "Copy owns an independent partitioner");
      require(*next.calls == 3, "Copied modifier chain");
      std::unique_ptr<ksi::data_modifier> cloned(copied.clone());
      imputer assigned(*owned);
      assigned = copied;
      assigned = assigned;
      imputer moved(std::move(assigned));
      imputer move_assigned(*owned);
      move_assigned = std::move(moved);
      for (ksi::data_modifier* m : {cloned.get(), static_cast<ksi::data_modifier*>(&move_assigned)})
      {
         auto ds = sample();
         m->modify(ds);
         near(ds.get(1, 1), 12, "Clone/assignment/move preserves independent state");
      }
      // A moved-from object may be copied, destroyed, or assigned again.
      imputer moved_from_copy(moved);
      auto ds = sample();
      throws([&] { moved_from_copy.modify(ds); }, "partitioner and a t-norm");
      moved_from_copy = copied;
      moved_from_copy.modify(ds);
      near(ds.get(1, 1), 12, "Reuse after move");
   }

   void zero_spreads()
   {
      fixed_partitioner p({{0, 10}, {2, 30}}, {{0, 0}, {0, 0}});
      ksi::t_norm_product t;
      imputer m(p, t);
      auto ds = sample();
      m.modify(ds);
      near(ds.get(1, 1), 10, "Singleton matching and zero spread on missing axis");
      ds = sample(1);
      const auto original = ds;
      throws([&] { m.modify(ds); }, "sum of weights is zero");
      same(ds, original);
   }

   void atomic_failure_and_no_complete_rows()
   {
      fixed_partitioner p({{0, 10}}, {{1, 1}});
      ksi::t_norm_product t;
      imputer m(p, t);
      recording_modifier next;
      m.addModifier(next);
      auto ds = sample();
      ksi::datum far(std::vector<double>{1000, -123});
      far.make_attribute_incomplete(1);
      ds.addDatum(far);
      const auto original = ds;
      throws([&] { m.modify(ds); }, "sum of weights is zero");
      same(ds, original);
      require(*next.calls == 0, "Do not run next modifier on failure");
      ds = sample();
      ds.getDatumNonConst(0)->make_attribute_incomplete(0);
      const auto incomplete = ds;
      throws([&] { m.modify(ds); }, "at least one complete");
      same(ds, incomplete);
      require(p.trace->calls == 1, "Do not cluster a dataset with no complete rows");
   }

   void invalid_data()
   {
      fixed_partitioner p({{0, 10}}, {{1, 1}});
      ksi::t_norm_product t;
      imputer m(p, t);
      auto ds = sample();
      ds.addDatum(ksi::datum(std::vector<double>{1}));
      throws([&] { m.modify(ds); }, "rectangular");
      for (const double value : {std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::quiet_NaN()})
      {
         ds = sample();
         ds.set(1, 0, value);
         throws([&] { m.modify(ds); }, "finite observed values");
      }
      ds = sample();
      ds.set(1, 1, std::numeric_limits<double>::quiet_NaN());
      ds.getDatumNonConst(1)->make_attribute_incomplete(1);
      m.modify(ds);
      near(ds.get(1, 1), 10, "Ignore payload of missing values");
   }

   void invalid_partitions_and_tnorms()
   {
      ksi::t_norm_product t;
      auto check = [&](fixed_partitioner p, const std::string& message) {
         imputer m(p, t);
         auto ds = sample();
         const auto original = ds;
         throws([&] { m.modify(ds); }, message);
         same(ds, original);
      };
      check(fixed_partitioner({}, {}), "nonempty Gaussian partition");
      check(fixed_partitioner({{0}}, {{1}}), "dimensions");
      fixed_partitioner triangular({{0, 10}}, {{1, 1}});
      triangular.gaussian = false;
      check(triangular, "Gaussian cluster descriptors");
      for (const double value : {-1.0, std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::quiet_NaN()})
         check(fixed_partitioner({{0, 10}}, {{value, 1}}), "nonnegative spreads");
      check(fixed_partitioner({{0, std::numeric_limits<double>::infinity()}}, {{1, 1}}), "finite centres");
      fixed_partitioner p({{0, 10}}, {{1, 1}});
      for (const double value : {-0.1, 1.1, std::numeric_limits<double>::quiet_NaN()})
      {
         invalid_tnorm invalid(value);
         imputer m(p, invalid);
         auto ds = sample();
         throws([&] { m.modify(ds); }, "finite membership");
      }
   }

   void small_weights_and_large_centres()
   {
      fixed_partitioner p({{0, 10}, {0, 30}}, {{1, 1}, {1, 1}});
      ksi::t_norm_product t;
      imputer m(p, t);
      auto ds = sample(38);
      m.modify(ds);
      near(ds.get(1, 1), 20, "Retain subnormal nonzero weights");
      fixed_partitioner large({{0, 1e308}, {0, 1e308}}, {{1, 1}, {1, 1}});
      imputer large_modifier(large, t);
      ds = sample();
      large_modifier.modify(ds);
      near(ds.get(1, 1), 1e308, "Finite weighted average of large centres");
   }

   void actual_fcm_integration()
   {
      ksi::fcm p(1, 10);
      ksi::t_norm_product t;
      imputer m(p, t);
      ksi::dataset ds(matrix{{0, 10}, {2, 20}, {5, 30}, {1, -999}});
      ds.getDatumNonConst(3)->make_attribute_incomplete(1);
      m.modify(ds);
      near(ds.get(3, 1), 20, "FCM one-cluster centroid");
      near(ds.get(3, 0), 1, "FCM leaves observed input unchanged");
      require(ds.exists(3, 1), "FCM result is complete");
   }
}

int main()
{
   const std::vector<std::pair<std::string, std::function<void()>>> tests{
      {"weighted imputation and metadata", weighted_imputation_and_metadata},
      {"fully missing row", fully_missing_row},
      {"passthrough, chaining and reuse", passthrough_and_reuse},
      {"copy, clone, move and lifetime", copy_clone_move_and_lifetime},
      {"zero spreads", zero_spreads},
      {"atomic failure and no complete rows", atomic_failure_and_no_complete_rows},
      {"invalid data", invalid_data},
      {"invalid partitions and t-norms", invalid_partitions_and_tnorms},
      {"small weights and large centres", small_weights_and_large_centres},
      {"actual FCM integration", actual_fcm_integration}
   };
   int failures = 0;
   for (const auto& [name, run] : tests)
   {
      try
      {
         run();
         std::cout << "PASS: " << name << '\n';
      }
      catch (const std::exception& error)
      {
         ++failures;
         std::cerr << "FAIL: " << name << ": " << error.what() << '\n';
      }
   }
   std::cout << tests.size() - failures << '/' << tests.size() << " GrIMP tests passed\n";
   return failures == 0 ? 0 : 1;
}
