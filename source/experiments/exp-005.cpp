/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 
 
#include "../service/debug.h"
#include "../implications/imp-reichenbach.h"
 
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../auxiliary/roc.h"

#include "../experiments/exp-005.h"


void ksi::exp_005::execute()
{
   try
   {
      goto dalej;
      {
         // classification 
         
         ksi::imp_reichenbach implication;
         
         ksi::ma MA;
         ksi::tsk TSK;
         ksi::annbfis ANNBFIS (implication);
         ksi::subspace_annbfis SUBSPACE_ANNBFIS (implication);
         
         std::vector<ksi::neuro_fuzzy_system *> systems 
         { & MA, & TSK, & ANNBFIS, & SUBSPACE_ANNBFIS };
         
         std::vector<ksi::roc_threshold> thresholds { ksi::roc_threshold::mean,
            ksi::roc_threshold::minimal_distance, ksi::roc_threshold::youden };
         
         const std::string DIRECTORY ("data/exp-005");
         const std::string TRAIN   (DIRECTORY + "/hab.train"), 
                           TEST    (DIRECTORY + "/hab.test"),
                           RESULTS (DIRECTORY + "/hab.results");
         const int NUMBER_OF_RULES = 5;
         const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
         const int NUMBER_OF_TUNING_ITERATIONS = 100;
         const double ETA = 0.1;
         const bool NORMALISATION = false;
         const double POSITIVE = 2.0;
         const double NEGATIVE = 1.0;
         
         for (auto th : thresholds)
         {
            std::string threshold_name;
            switch(th)
            {
               case ksi::roc_threshold::mean             : threshold_name = "mean"; break;
               case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance"; break;
               case ksi::roc_threshold::youden           : threshold_name = "youden"; break;
               default : threshold_name = "something-wrong-has-happened"; break;
            }
            
            for (auto p : systems)
            {
               p->experiment_classification(TRAIN, TEST, 
                                          RESULTS + "-" + p->get_nfs_name() + "-" + threshold_name,
                                          NUMBER_OF_RULES,
                                          NUMBER_OF_CLUSTERING_ITERATIONS,
                                          NUMBER_OF_TUNING_ITERATIONS,
                                          ETA, NORMALISATION,
                                          POSITIVE, NEGATIVE,
                                          th);    
            }
         }
      }
      dalej: 
      {
         // regression 
         
         ksi::imp_reichenbach implication;
         
         ksi::ma MA;
         ksi::tsk TSK;
         ksi::annbfis ANNBFIS (implication);
         ksi::subspace_annbfis SUBSPACE_ANNBFIS (implication);
         
         std::vector<ksi::neuro_fuzzy_system *> systems 
         { & MA, & TSK, & ANNBFIS, & SUBSPACE_ANNBFIS };
         
         const std::string DIRECTORY ("data/exp-005");
         const std::string TRAIN   (DIRECTORY + "/leukocytes.train"), 
                           TEST    (DIRECTORY + "/leukocytes.test"),
                           RESULTS (DIRECTORY + "/leukocytes.results");
         const int NUMBER_OF_RULES = 5;
         const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
         const int NUMBER_OF_TUNING_ITERATIONS = 100;
         const double ETA = 0.1;
         const bool NORMALISATION = false;
         
         for (auto p : systems)
            p->experiment_regression(TRAIN, TEST, 
                                     RESULTS + "-" + p->get_nfs_name(),
                                     NUMBER_OF_RULES,
                                     NUMBER_OF_CLUSTERING_ITERATIONS,
                                     NUMBER_OF_TUNING_ITERATIONS, ETA,
                                     NORMALISATION);
         
      }
      
      return ;
       
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
