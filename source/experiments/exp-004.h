/** @file */

#ifndef EXP_004_H
#define EXP_004_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 004  <br/>
 
    An example of a fuzzy system:
    1. Mamdami-Assilan paradigm
    2. triangular descriptiors in premises
 
    @date 2018-07-30 
    */
   class exp_004 : virtual public experiment
   {
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
