/** @file */

#include <algorithm>
#include <cmath>
#include <format>

#include "../descriptors/descriptor-gaussian.h"
#include "../common/data-modifier-imputer-granular.h"

#include "../common/data-modifier-imputer.h"
#include "../common/dataset.h"
#include "../common/datum.h"
#include "../partitions/partitioner.h"
#include "../service/exception.h"

ksi::dataset ksi::data_modifier_imputer_granular::granular_imputation(const dataset& ds)
{
   try
   {
      number_of_tuple_attributes = ds.getNumberOfAttributes();
      extract_complete_dataset_and_incomplete_indices(ds);
      granules_centers.clear();
      granules_fuzzifications.clear();
      cluster_numbers = 0;

      // Empty and already complete datasets need no partitioning.
      if (incomplete_indices.empty())
         return ds;
      if (complete_dataset.empty())
         throw ksi::exception("GrIMP requires at least one complete data item.");
      if (!_pPartitioner || !_pTnorm)
         throw ksi::exception("GrIMP requires a partitioner and a t-norm.");

      const auto partitioned_data = _pPartitioner->doPartition(complete_dataset);
      set_granules_attributes(partitioned_data);

      // Commit results only after every missing value has been imputed.
      auto result(ds);
      for (const auto tup_index : incomplete_indices)
      {
         const auto [values, indices] = handle_incomplete_tuple(*ds.getDatum(tup_index));
         for (std::size_t i = 0; i < indices.size(); ++i)
            result.set(tup_index, indices[i], values[i]);
      }
      return result;
   }
   CATCH;
}

void ksi::data_modifier_imputer_granular::extract_complete_dataset_and_incomplete_indices(const dataset& ds)
{
   complete_dataset = ksi::dataset();
   incomplete_indices.clear();
   for (std::size_t i = 0; i < ds.size(); ++i)
   {
      const auto data_item = ds.getDatum(i);
      if (data_item->getNumberOfAttributes() != number_of_tuple_attributes)
         throw ksi::exception("GrIMP requires a rectangular dataset.");

      bool complete = true;
      for (std::size_t a = 0; a < number_of_tuple_attributes; ++a)
      {
         if (!ds.exists(i, a))
            complete = false;
         else if (!std::isfinite(ds.get(i, a)))
            throw ksi::exception("GrIMP requires finite observed values.");
      }
      if (complete)
         complete_dataset.addDatum(*data_item);
      else
         incomplete_indices.push_back(i);
   }
}

void ksi::data_modifier_imputer_granular::set_granules_attributes(const ksi::partition& partitioned_data)
{
   cluster_numbers = partitioned_data.getNumberOfClusters();
   if (cluster_numbers == 0)
      throw ksi::exception("GrIMP requires a nonempty Gaussian partition.");

   // Upstream stores centres and spreads in the cluster descriptors.
   // getGranule() would clamp small/zero spreads to 1e-6.
   for (std::size_t c = 0; c < cluster_numbers; ++c)
   {
      const auto cluster = partitioned_data.getCluster(c);
      if (!cluster || cluster->getNumberOfDescriptors() != number_of_tuple_attributes)
         throw ksi::exception("GrIMP granule dimensions must match the dataset.");

      std::vector<double> centers, spreads;
      for (std::size_t a = 0; a < number_of_tuple_attributes; ++a)
      {
         const auto descriptor = dynamic_cast<const ksi::descriptor_gaussian*>(
            cluster->getAddressOfDescriptor(a));
         if (!descriptor)
            throw ksi::exception("GrIMP requires Gaussian cluster descriptors.");
         const double center = descriptor->getCoreMean();
         const double spread = descriptor->getFuzzification();
         if (!std::isfinite(center) || !std::isfinite(spread) || spread < 0.0)
            throw ksi::exception("GrIMP requires finite centres and finite, nonnegative spreads.");
         centers.push_back(center);
         spreads.push_back(spread);
      }
      granules_centers.push_back(std::move(centers));
      granules_fuzzifications.push_back(std::move(spreads));
   }
}

std::pair<std::vector<double>, std::vector<std::size_t>> ksi::data_modifier_imputer_granular::handle_incomplete_tuple(const datum& incomplete_tuple)
{
   auto incomplete_tuple_attributes = incomplete_tuple.getVector();
   auto incomplete_attributes_indices = get_incomplete_attributes_indices(incomplete_tuple);

   auto [imputed_attributes, granule_membership] = calculate_granule_imputations_and_memberships(incomplete_tuple_attributes, incomplete_attributes_indices);

   auto imputed_average_attributes = weighted_average(imputed_attributes, granule_membership);

   return std::make_pair(imputed_average_attributes, incomplete_attributes_indices);
}

std::vector<std::size_t> ksi::data_modifier_imputer_granular::get_incomplete_attributes_indices(const ksi::datum& incomplete_tuple) const
{
   std::vector<std::size_t> incomplete_attributes_indices;

   for (std::size_t attr = 0; attr < number_of_tuple_attributes; ++attr) // for each attribute in the incomplete tuple
    {
        if (!incomplete_tuple.at(attr)->exists())
        {
            incomplete_attributes_indices.push_back(attr);
        }
    }

    return incomplete_attributes_indices;
}

std::pair<std::vector<std::vector<double>>, std::vector<double>> ksi::data_modifier_imputer_granular::calculate_granule_imputations_and_memberships(const std::vector<double>& incomplete_tuple_attributes, const std::vector<std::size_t>& incomplete_attributes_indices)
{
    std::vector<std::vector<double>> imputed_attributes;
    imputed_attributes.reserve(cluster_numbers);

    std::vector<double> granule_membership;
    granule_membership.reserve(cluster_numbers);

    for (std::size_t gran = 0; gran < cluster_numbers; ++gran) // for each granule
    {
       auto imputed_granule_attributes = impute_granule_attributes(incomplete_attributes_indices, granules_centers[gran]);
       imputed_attributes.push_back(imputed_granule_attributes);

       auto imputed_tuple_attributes = insert_missing_attributes(incomplete_tuple_attributes, imputed_granule_attributes, incomplete_attributes_indices);

       granule_membership.push_back(calculate_granule_membership(imputed_tuple_attributes, granules_centers[gran], granules_fuzzifications[gran]));
    }

    return std::make_pair(imputed_attributes, granule_membership);
}

std::vector<double> ksi::data_modifier_imputer_granular::impute_granule_attributes(const std::vector<std::size_t>& incomplete_attributes_indices, const std::vector<double>& granule_centers)
{
   std::vector<double> imputed_granule_attributes;

   for (const auto& attr_index: incomplete_attributes_indices) // for each missing attribute in the incomplete tuple
   {
      imputed_granule_attributes.push_back(granule_centers[attr_index]);
   }

    return imputed_granule_attributes;
}

std::vector<double> ksi::data_modifier_imputer_granular::insert_missing_attributes(const std::vector<double>& incomplete_tuple_attributes, const std::vector<double>& imputed_granule_attributes, const std::vector<std::size_t>& incomplete_attributes_indices)
{
   auto imputed_tuple_attributes = incomplete_tuple_attributes;

   for (std::size_t index = 0; index < imputed_granule_attributes.size(); ++index) // for each missing attribute in the incomplete tuple
   {
        auto attr_index = incomplete_attributes_indices[index];
      imputed_tuple_attributes[attr_index] = imputed_granule_attributes[index];
   }

   return imputed_tuple_attributes;
}

double ksi::data_modifier_imputer_granular::calculate_granule_membership(const std::vector<double>& estimated_tuple_attributes, const std::vector<double>& granule_centers, const std::vector<double>& granule_fuzzifications)
{
   double membership = 1.0;
   for (std::size_t a = 0; a < estimated_tuple_attributes.size(); ++a)
   {
      const double spread = granule_fuzzifications[a];
      double attribute_membership;
      if (spread == 0.0)
      {
         // The zero-spread limit is a singleton, including on imputed axes.
         attribute_membership = estimated_tuple_attributes[a] == granule_centers[a] ? 1.0 : 0.0;
      }
      else
      {
         const long double distance = (static_cast<long double>(estimated_tuple_attributes[a])
            - granule_centers[a]) / spread;
         attribute_membership = static_cast<double>(std::exp(-0.5L * distance * distance));
      }
      membership = _pTnorm->tnorm(membership, attribute_membership);
      if (!std::isfinite(membership) || membership < 0.0 || membership > 1.0)
         throw ksi::exception("GrIMP t-norm must return a finite membership in [0, 1].");
   }
   return membership;
}

std::vector<double> ksi::data_modifier_imputer_granular::weighted_average(const std::vector<std::vector<double>>& estimated_values, const std::vector<double>& weights)
{
   const double largest_weight = *std::max_element(weights.begin(), weights.end());
   if (largest_weight == 0.0)
      throw ksi::exception(std::format(
         "GrIMP sum of weights is zero (complete data items {}, granules {}).",
         complete_dataset.size(), cluster_numbers));

   // Scale before summing to retain small nonzero weights. Long double also
   // avoids overflowing the numerator when finite centres have large values.
   std::vector<long double> numerator(estimated_values.front().size(), 0.0L);
   long double denominator = 0.0L;
   for (std::size_t c = 0; c < weights.size(); ++c)
   {
      const long double weight = static_cast<long double>(weights[c]) / largest_weight;
      denominator += weight;
      for (std::size_t a = 0; a < numerator.size(); ++a)
         numerator[a] += weight * estimated_values[c][a];
   }
   std::vector<double> result;
   for (const auto value : numerator)
   {
      const double average = static_cast<double>(value / denominator);
      if (!std::isfinite(average))
         throw ksi::exception("GrIMP produced a non-finite imputed value.");
      result.push_back(average);
   }
   return result;
}

ksi::data_modifier_imputer_granular::data_modifier_imputer_granular(
   const partitioner& Partitioner, const t_norm& Tnorm)
   : data_modifier_imputer(), _pPartitioner(Partitioner.clone()), _pTnorm(Tnorm.clone())
{
   description = "granular imputation (GrIMP)";
   if (!_pPartitioner || !_pTnorm)
      throw ksi::exception("GrIMP requires a partitioner and a t-norm.");
}

ksi::data_modifier_imputer_granular::data_modifier_imputer_granular(
   const data_modifier_imputer_granular& other)
   : data_modifier_imputer(other),
     _pPartitioner(other._pPartitioner ? other._pPartitioner->clone() : nullptr),
     _pTnorm(other._pTnorm ? other._pTnorm->clone() : nullptr),
     complete_dataset(other.complete_dataset), incomplete_indices(other.incomplete_indices),
     granules_fuzzifications(other.granules_fuzzifications), cluster_numbers(other.cluster_numbers),
     granules_centers(other.granules_centers), number_of_tuple_attributes(other.number_of_tuple_attributes)
{
}

ksi::data_modifier_imputer_granular::data_modifier_imputer_granular(
   data_modifier_imputer_granular&& other)
   : data_modifier_imputer(std::move(other)), _pPartitioner(std::move(other._pPartitioner)),
     _pTnorm(std::move(other._pTnorm)), complete_dataset(std::move(other.complete_dataset)),
     incomplete_indices(std::move(other.incomplete_indices)),
     granules_fuzzifications(std::move(other.granules_fuzzifications)), cluster_numbers(other.cluster_numbers),
     granules_centers(std::move(other.granules_centers)), number_of_tuple_attributes(other.number_of_tuple_attributes)
{
}

ksi::data_modifier_imputer_granular& ksi::data_modifier_imputer_granular::operator=(
   const data_modifier_imputer_granular& other)
{
   if (this != &other)
   {
      data_modifier_imputer::operator=(other);
      _pPartitioner.reset(other._pPartitioner ? other._pPartitioner->clone() : nullptr);
      _pTnorm.reset(other._pTnorm ? other._pTnorm->clone() : nullptr);
      complete_dataset = other.complete_dataset;
      incomplete_indices = other.incomplete_indices;
      granules_fuzzifications = other.granules_fuzzifications;
      cluster_numbers = other.cluster_numbers;
      granules_centers = other.granules_centers;
      number_of_tuple_attributes = other.number_of_tuple_attributes;
   }
   return *this;
}

ksi::data_modifier_imputer_granular& ksi::data_modifier_imputer_granular::operator=(
   data_modifier_imputer_granular&& other)
{
   if (this != &other)
   {
      data_modifier_imputer::operator=(std::move(other));
      _pPartitioner = std::move(other._pPartitioner);
      _pTnorm = std::move(other._pTnorm);
      complete_dataset = std::move(other.complete_dataset);
      incomplete_indices = std::move(other.incomplete_indices);
      granules_fuzzifications = std::move(other.granules_fuzzifications);
      cluster_numbers = other.cluster_numbers;
      granules_centers = std::move(other.granules_centers);
      number_of_tuple_attributes = other.number_of_tuple_attributes;
   }
   return *this;
}

ksi::data_modifier_imputer_granular::~data_modifier_imputer_granular() = default;

ksi::data_modifier* ksi::data_modifier_imputer_granular::clone() const
{
   return new data_modifier_imputer_granular(*this);
}

void ksi::data_modifier_imputer_granular::modify(dataset& ds)
{
   ds = granular_imputation(ds);
   if (pNext)
      pNext->modify(ds);
}

std::string ksi::data_modifier_imputer_granular::getDescription() const
{
   return description;
}

std::string ksi::data_modifier_imputer_granular::getName() const
{
   return "imputer_granular";
}

std::size_t ksi::data_modifier_imputer_granular::get_number_of_complete_items_in_dataset() const
{
   return complete_dataset.size();
}

std::size_t ksi::data_modifier_imputer_granular::get_number_of_incomplete_items_in_dataset() const
{
   return incomplete_indices.size();
}
