/** @file */

#ifndef EXP_002_H
#define EXP_002_H

#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 002  <br/>
    
    An experiment with clustering with various clustering algorithms. 
    1. fuzzy C-means (FCM)
    2. possibilistic FCM
    3. conditional FCM 
    4. subspace FCM (SFCM)
    5. fuzzy biclustering (FuBi) 
    6. fuzzy C-ordered means (FCOM)
    7. dbscan
    
    @date 2018-07-28, 2021-07-03, 2022-04-11
    
    */
   class exp_002 : virtual public experiment
   {
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
