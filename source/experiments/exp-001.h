/** @file */

#ifndef EXP_001_H
#define EXP_001_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 001  <br/>
    
   Algorithms for handling complete datasets:
   1. normalisation
   2. standardisation
   
   Algorithms for handling incomplete datasets:   
   1. marginalisation
   2. imputation with constant
   3. imputation with averages of the attribute
   4. imputation with medians of the attribute
   5. imputation with averages of k nearest neighbours 
   6. imputation with medians of k nearest neighbours 
   7. imputation with values from k nearest neighbours
   
   and finally an example of a chain of modifiers:
   1. imputation with values from k nearest neighbours + standardisation
   
   @date 2018-07-29
    
    */
   class exp_001 : virtual public experiment
   {
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
