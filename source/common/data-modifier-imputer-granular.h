/** @file */

#ifndef DATA_MODIFIER_IMPUTER_GRANULAR_H
#define DATA_MODIFIER_IMPUTER_GRANULAR_H

#include <memory>
#include <utility>
#include <vector>

#include "../common/data-modifier-imputer.h"
#include "../common/dataset.h"
#include "../common/datum.h"
#include "../partitions/partitioner.h"
#include "../tnorms/t-norm.h"

namespace ksi
{
   /** GrIMP: granular imputation using Gaussian clusters and a t-norm.
    *
    * Complete rows define the granules. Missing values are replaced by
    * membership-weighted granule centres; observed values and row metadata
    * (including IDs and weights) are preserved. Zero spreads denote singletons.
    * See docs/grimp.md for the algorithm, preconditions and examples.
    *
    * @author Konrad Wnuk
    * @author Krzysztof Simiński
    * @date 2024-08-08
    */
   class data_modifier_imputer_granular : public data_modifier_imputer
   {
   protected:
      std::shared_ptr<ksi::partitioner> _pPartitioner;
      std::shared_ptr<ksi::t_norm> _pTnorm;
      ksi::dataset complete_dataset;
      std::vector<std::size_t> incomplete_indices;
      std::vector<std::vector<double>> granules_fuzzifications;
      std::size_t cluster_numbers = 0;
      std::vector<std::vector<double>> granules_centers;
      std::size_t number_of_tuple_attributes = 0;

   public:
      /** Clones the partitioner and t-norm; neither needs to outlive the imputer.
       * @param Partitioner A partitioner producing Gaussian descriptors with
       * finite centres and finite, nonnegative spreads.
       * @param Tnorm The t-norm used to aggregate attribute memberships.
       */
      data_modifier_imputer_granular(const partitioner& Partitioner, const t_norm& Tnorm);
      data_modifier_imputer_granular(const data_modifier_imputer_granular& other);
      // The base imputer copies its modifier chain on move and can allocate.
      data_modifier_imputer_granular(data_modifier_imputer_granular&& other);
      data_modifier_imputer_granular& operator=(const data_modifier_imputer_granular& other);
      data_modifier_imputer_granular& operator=(data_modifier_imputer_granular&& other);
      virtual ~data_modifier_imputer_granular();

      /** @return A deep copy, including the partitioner, t-norm and modifier chain. */
      virtual data_modifier* clone() const override;

      /** Imputes a copy, replaces ds on success, then calls the next modifier.
       * Empty/complete datasets skip partitioning and still reach the next
       * modifier. Each call fits granules to its own complete rows.
       * @param ds A rectangular dataset with finite observed values.
       * Missingness is represented by number::exists(), not a NaN sentinel.
       * @throws ksi::exception On invalid data/partition, no complete training
       * rows, or zero total membership (including floating-point underflow).
       * GrIMP failures leave ds unchanged; a subsequent modifier follows its
       * own exception semantics.
       */
      virtual void modify(dataset& ds) override;

      /** Concrete-class convenience accessors retained from the fcm branch.
       * The upstream base interface describes modifier chains with print().
       */
      virtual std::string getDescription() const;
      virtual std::string getName() const;

      /** @return Number of complete rows before the last successful imputation.
       * Undefined after a failed modify call.
       * @author Krzysztof Simiński
       * @date 2024-10-24
       */
      std::size_t get_number_of_complete_items_in_dataset() const;
      /** @return Number of incomplete rows before the last successful imputation.
       * Undefined after a failed modify call.
       * @author Krzysztof Simiński
       * @date 2024-10-24
       */
      std::size_t get_number_of_incomplete_items_in_dataset() const;

   protected:
      /** @return A copy with all missing values filled; never modifies ds.
       * @author Konrad Wnuk
       * @date 2024-08-20
       */
      ksi::dataset granular_imputation(const dataset& ds);

   private:
      void extract_complete_dataset_and_incomplete_indices(const dataset& ds);
      void set_granules_attributes(const ksi::partition& partitioned_data);
      std::pair<std::vector<double>, std::vector<std::size_t>>
         handle_incomplete_tuple(const datum& incomplete_tuple);
      std::vector<std::size_t>
         get_incomplete_attributes_indices(const ksi::datum& incomplete_tuple) const;
      std::pair<std::vector<std::vector<double>>, std::vector<double>>
         calculate_granule_imputations_and_memberships(
            const std::vector<double>& incomplete_tuple_attributes,
            const std::vector<std::size_t>& incomplete_attributes_indices);
      std::vector<double> impute_granule_attributes(
         const std::vector<std::size_t>& incomplete_attributes_indices,
         const std::vector<double>& granule_centers);
      std::vector<double> insert_missing_attributes(
         const std::vector<double>& incomplete_tuple_attributes,
         const std::vector<double>& imputed_granule_attributes,
         const std::vector<std::size_t>& incomplete_attributes_indices);
      double calculate_granule_membership(
         const std::vector<double>& estimated_tuple_attributes,
         const std::vector<double>& granule_centers,
         const std::vector<double>& granule_fuzzifications);
      std::vector<double> weighted_average(
         const std::vector<std::vector<double>>& estimated_values,
         const std::vector<double>& weights);
   };
}

#endif
