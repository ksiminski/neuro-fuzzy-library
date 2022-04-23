/** @file */

#ifndef EXP_LAB_H
#define EXP_LAB_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** LABORATORY EXPERIMENT  <br/>
    */
   class exp_lab : virtual public experiment
   {
      void fuzzy_system();
      void neuro_fuzzy_system();
      
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
