
#ifndef GRANULAR_ANNBFIS_REGRESSION_H
#define GRANULAR_ANNBFIS_REGRESSION_H

#include "../neuro-fuzzy/granular_nfs_regression.h"
#include "../neuro-fuzzy/annbfis.h"

namespace ksi
{
   class granular_annbfis_regression : virtual public granular_nfs_regression, virtual public annbfis 
   {
    public:
      granular_annbfis_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
   
      /** A constructor with implication.
            @param imp implication
            @date 2018-03-29
          */
        granular_annbfis_regression (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate,
            const ksi::implication & imp);
      granular_annbfis_regression (const granular_annbfis_regression & wzor);
      granular_annbfis_regression (granular_annbfis_regression && wzor);
      granular_annbfis_regression & operator= (const granular_annbfis_regression & wzor);
      granular_annbfis_regression & operator= (granular_annbfis_regression && wzor);
      virtual ~granular_annbfis_regression ();
   
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
