
#ifndef GRANULAR_NFS_REGRESSION_H
#define GRANULAR_NFS_REGRESSION_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/granular_nfs.h"
#include "../common/dataset.h"
#include "../common/result.h"
#include "../granules/granule.h" 
#include "../granules/set_of_granules.h" 
#include "../partitions/partitioner.h"

namespace ksi
{
   class granular_nfs_regression : public granular_nfs
   {

    public:
      granular_nfs_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
      
      granular_nfs_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate,
            const ksi::partitioner & partitioner);
      
      
      granular_nfs_regression (const granular_nfs_regression & wzor);
      granular_nfs_regression (granular_nfs_regression && wzor);
      granular_nfs_regression & operator= (const granular_nfs_regression & wzor);
      granular_nfs_regression & operator= (granular_nfs_regression && wzor);
      
      virtual ~granular_nfs_regression ();
            
      void createFuzzyRulebase(  
          int nClusteringIterations, 
          int nTuningIterations, 
          double dbLearningCoefficient, 
          const ksi::set_of_granules & train_granules,
          const ksi::set_of_granules & validation_granules);
      

      
      virtual ksi::result experiment_regression(
          const std::string & trainDataFile, 
          const std::string & testDataFile, 
          const std::string & outputFile, 
          const int nNumberOfRules, 
          const int nNumberOfClusteringIterations, 
          const int nNumberofTuningIterations, 
          const double dbLearningCoefficient, 
          const bool bNormalisation) override;

     virtual ksi::result experiment_regression() override;
     
          
          
      /** This function is not implemented in this class and will not be implemented, because the class is responsible for regression and not for classification.
       @throw ksi::exception the method always throws an exception */
      virtual ksi::result experiment_classification(
          const std::string & trainDataFile, 
          const std::string & testDataFile, 
          const std::string & outputFile, 
          const int nNumberOfRules, 
          const int nNumberOfClusteringIterations, 
          const int nNumberofTuningIterations, 
          const double dbLearningCoefficient, 
          const bool bNormalisation, 
          const double dbPositiveClass, 
          const double dbNegativeClass, 
          ksi::roc_threshold threshold_type) override;
      
      ksi::dataset generate_dataset_from_granules(
          const ksi::set_of_granules & granules, 
          const int NUMBER_OF_TRAIN_DATA);
      
      
   };
}


#endif
