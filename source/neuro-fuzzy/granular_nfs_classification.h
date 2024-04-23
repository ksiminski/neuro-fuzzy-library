
#ifndef GRANULAR_NFS_CLASSIFICATION_H
#define GRANULAR_NFS_CLASSIFICATION_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/granular_nfs.h"
#include "../common/dataset.h"
#include "../common/result.h"
#include "../granules/granule.h" 
#include "../granules/set_of_granules.h" 

namespace ksi
{
   class granular_nfs_classification : public granular_nfs
   {
   protected:
//        double _positive_class; ///< value of a positive class
//        double _negative_class; ///< value of a negative class
//        ksi::roc_threshold _threshold; ///< threshold_type
       double threshold_value;  ///< threshold value: default (set in constructor): mean
       
       /** a method for copying class fields */
       void copy_fields(const granular_nfs_classification & wzor);  
       /** a method for swapping class fields */
       void swap_fields(granular_nfs_classification & wzor);
       
    public:
      granular_nfs_classification (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate,
            const double dbPositiveClass, 
            const double dbNegativeClass, 
            ksi::roc_threshold threshold_type);
      
      
      granular_nfs_classification (const granular_nfs_classification & wzor);
      granular_nfs_classification (granular_nfs_classification && wzor);
      granular_nfs_classification & operator= (const granular_nfs_classification & wzor);
      granular_nfs_classification & operator= (granular_nfs_classification && wzor);
      virtual ~granular_nfs_classification ();
      
      virtual void createFuzzyRulebase(  
          int nClusteringIterations, 
          int nTuningIterations, 
          double dbLearningCoefficient, 
          const ksi::set_of_granules & train_granules,
          const ksi::set_of_granules & validation_granules) override;        
          
      
      /** This function is not implemented in this class and will not be implemented, because the class is responsible for classification and not for regression.
       @throw ksi::exception the method always throws an exception */
      virtual ksi::result experiment_regression(
          const std::string & trainDataFile, 
          const std::string & testDataFile, 
          const std::string & outputFile, 
          const int nNumberOfRules, 
          const int nNumberOfClusteringIterations, 
          const int nNumberofTuningIterations, 
          const double dbLearningCoefficient, 
          const bool bNormalisation) override;
      

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
