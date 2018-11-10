/** @file */

#ifndef EXP_011_H
#define EXP_011_H



#include "../experiments/experiment.h"


 

namespace ksi
{
   /** EXPERIMENT 011  <br/>
    An experiment with a random neuro-fuzzy forest both for regression and classification.
    @date 2018-04-08
    
    */
   class exp_011 : virtual public experiment
   {
   public:
      /** The method executes an experiment. */
      void execute ();
   };
}

#endif 
