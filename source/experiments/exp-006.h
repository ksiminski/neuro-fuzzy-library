/** @file */

#ifndef EXP_006_H
#define EXP_006_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** Experiment 006: three-way decision experiments for classification.
    *  The experiment includes:
    *  1. Meta-classifier cascade variants.
    *  2. Widening noncommitment variants.
    *  3. Single-system ANNBFIS and TSK baselines.
    *  4. Nested cross-validation for width selection.
    */
   class exp_006 : virtual public experiment
   {
   public:
      virtual void execute () override;
      virtual void execute_nested_cv_for_width_selection();
      virtual void execute_single_system_cv();
   };
}

#endif 
