/** @file */

#ifndef EXP_006_H
#define EXP_006_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 006  <br/>
    An experiment with a neuro-fuzzy systems:
    1. Mamdani-Assilan                                    (classification and regression tasks)
    2. Takagi-Sugeno-Kang                                 (classification and regression tasks)
    3. ANNBFIS                                            (classification and regression tasks)
    4. subspace ANNBFIS                                   (classification and regression tasks)
    5. FuBiNFS: fuzzy biclustering subspace annbfis       (classification and regression tasks)
    6. Proto-NFS: prototype based neuro-fuzzy systems     (regression task)
    7. Proto-NFS: prototype based neuro-fuzzy systems     (classification task)
    7. Three way decision neuro-fuzzy system              (classification task)
    
    
    @date 2023-04-22
    
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
