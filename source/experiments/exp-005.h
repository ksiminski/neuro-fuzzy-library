/** @file */

#ifndef EXP_005_H
#define EXP_005_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 005  <br/>
    An experiment with a neuro-fuzzy systems:
    1. Mamdani-Assilan
    2. Takagi-Sugeno-Kang
    3. ANNBFIS
    4. subspace ANNBFIS
    5. fuzzy biclustering subspace annbfis
    for classification and regression tasks.
    
    
    @date 2018-07-30
    
    */
   class exp_005 : virtual public experiment
   {
      virtual void classification();
      virtual void regression ();
    
   public:
      /** The method executes an experiment. */
      virtual void execute ();
      
      exp_005 ();
    
   };
}

#endif 
