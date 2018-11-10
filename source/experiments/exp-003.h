/** @file */

#ifndef EXP_003_H
#define EXP_003_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 003  <br/>
    * 
    An experiment with clustering of incomplete data with various clustering algorithms. 
    1. rough fuzzy C-means (RFCM)
    2. rough subspace fuzzy C-means (RSFCM)
    3. rough fuzzy C-ordered means (RFCM)
    
    @date 2018-07-29
    
    */
   class exp_003 : virtual public experiment
   {
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 