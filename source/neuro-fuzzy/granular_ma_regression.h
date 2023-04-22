
#ifndef GRANULAR_MA_REGRESSION_H
#define GRANULAR_MA_REGRESSION_H

#include "../neuro-fuzzy/granular_nfs_regression.h"
#include "../neuro-fuzzy/ma.h"

namespace ksi
{
   class granular_ma_regression : virtual public granular_nfs_regression, virtual public ma 
   {
    public:
      granular_ma_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
      granular_ma_regression (const granular_ma_regression & wzor);
      granular_ma_regression (granular_ma_regression && wzor);
      granular_ma_regression & operator= (const granular_ma_regression & wzor);
      granular_ma_regression & operator= (granular_ma_regression && wzor);
      virtual ~granular_ma_regression ();
   
   protected:
       /** @todo niezaimplementowane
           @warning niezaimplementowane
           */
       virtual void createFuzzyNonGranularRulebase(
//             const int nRules, 
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
