
#ifndef GRANULAR_TSK_REGRESSION_H
#define GRANULAR_TSK_REGRESSION_H

#include "../neuro-fuzzy/granular_nfs_regression.h"
#include "../neuro-fuzzy/tsk.h"

namespace ksi
{
   class granular_tsk_regression : public granular_nfs_regression, 
                                   public tsk 
   {
    public:
      granular_tsk_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
      
      granular_tsk_regression (const int nNumberOfRules,
                               const int nNumberOfClusteringIterations,
                               const int nNumberofTuningIterations,
                               const double dbLearningCoefficient,
                               const bool bNormalisation,
                               const int number_of_data_to_read,
                               const int minimal_number_of_granules_in_set,
                               const int maximal_number_of_granules_in_set,
                               const int number_of_data_to_generate);
      
      
      granular_tsk_regression (const std::string & trainDataFile,
                               const std::string & testDataFile,
                               const std::string & resultsFile,
                               const int nNumberOfRules,
                               const int nNumberOfClusteringIterations,
                               const int nNumberofTuningIterations,
                               const double dbLearningCoefficient,
                               const bool bNormalisation,
                               const int number_of_data_to_read,
                               const int minimal_number_of_granules_in_set,
                               const int maximal_number_of_granules_in_set,
                               const int number_of_data_to_generate);
      
      granular_tsk_regression (const granular_tsk_regression & wzor);
      granular_tsk_regression (granular_tsk_regression && wzor);
      granular_tsk_regression & operator= (const granular_tsk_regression & wzor);
      granular_tsk_regression & operator= (granular_tsk_regression && wzor);
      virtual ~granular_tsk_regression ();
   
   protected:
       
       virtual void createFuzzyNonGranularRulebase(
            const int nClusteringIterations, 
            const int nTuningIterations, 
            const double dbLearningCoefficient, 
            const dataset & train);
      
    public:
      virtual ksi::neuro_fuzzy_system * clone() const;
        
      /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      virtual double answer (const datum & item) const;
        
   };
}


#endif
