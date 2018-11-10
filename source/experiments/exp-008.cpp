/** @file */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric> // std::iota
#include <random> 
#include <chrono>
 
#include "../service/debug.h"
#include "../auxiliary/utility-string.h"
#include "../implications/imp-reichenbach.h"
 
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../auxiliary/roc.h"

#include "../experiments/exp-008.h"

#include <fstream>
#include <map>

void ksi::exp_008::execute()
{
   try
   { 
       /*
      {
         // classification 
         
         ksi::imp_reichenbach implication;
         
         ksi::ma MA;
         ksi::tsk TSK;
         ksi::annbfis ANNBFIS (implication);
         ksi::subspace_annbfis SUBSPACE_ANNBFIS (implication);
         
         std::vector<ksi::neuro_fuzzy_system *> systems 
//          {  & ANNBFIS};
         { & MA, & TSK, & ANNBFIS, & SUBSPACE_ANNBFIS };
         
         const std::string DIRECTORY ("dane/");
         const std::string SUBDIRECTORY ("jw-norm/parkinson/");
         const std::string TRAIN   (DIRECTORY + SUBDIRECTORY + "parkinson.train"), 
                           TEST    (DIRECTORY + SUBDIRECTORY + "parkinson.test"),
                           RESULTS (DIRECTORY + "/parkinson-results");
         const std::vector<int> NUMBER_OF_RULES = { 3, 4, 5, 7, 10, 15 };
         const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
         const int NUMBER_OF_TUNING_ITERATIONS = 100; 
//          const double ETA = 0.1;
         const std::vector<double> ETA = { 0.0001, 0.001, 0.01, 0.1};
         const bool NORMALISATION = false;
         const double POSITIVE = 1.0;
         const double NEGATIVE = 0.0;
         
         
         const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::youden;
         //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::mean;
         //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::minimal_distance;
         
         for (auto number_of_rules : NUMBER_OF_RULES)
         {
            for (auto eta : ETA)
            {
               for (auto p : systems)
                  p->experiment_classification(TRAIN, TEST, 
                      RESULTS + "-" + std::to_string(number_of_rules) 
                              + "-" + std::to_string(eta)
                              + "-" + p->get_nfs_name(),
                                             number_of_rules,
                                             NUMBER_OF_CLUSTERING_ITERATIONS,
                                             NUMBER_OF_TUNING_ITERATIONS,
                                             eta, NORMALISATION,
                                             POSITIVE, NEGATIVE,
                                             THRESHOLD_TYPE);    
            }
         }
      }
      
       {
          // classification 
          
          ksi::imp_reichenbach implication;
          
          ksi::ma MA;
          ksi::tsk TSK;
          ksi::annbfis ANNBFIS (implication);
          ksi::subspace_annbfis SUBSPACE_ANNBFIS (implication);
          
          std::vector<ksi::neuro_fuzzy_system *> systems 
          //          {  & ANNBFIS};
          { & MA, & TSK, & ANNBFIS, & SUBSPACE_ANNBFIS };
          
          const std::string DIRECTORY ("dane/");
          const std::string SUBDIRECTORY ("jw-norm/banknote/");
          const std::string TRAIN   (DIRECTORY + SUBDIRECTORY + "banknote.train"), 
          TEST    (DIRECTORY + SUBDIRECTORY + "banknote.test"),
          RESULTS (DIRECTORY + "/banknote-results");
          const std::vector<int> NUMBER_OF_RULES = { 3, 4, 5, 7, 10, 15 };
          const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
          const int NUMBER_OF_TUNING_ITERATIONS = 100; 
          //          const double ETA = 0.1;
          const std::vector<double> ETA = { 0.0001, 0.001, 0.01, 0.1};
          const bool NORMALISATION = false;
          const double POSITIVE = 1.0;
          const double NEGATIVE = 0.0;
          
          
          const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::youden;
          //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::mean;
          //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::minimal_distance;
          
          for (auto number_of_rules : NUMBER_OF_RULES)
          {
             for (auto eta : ETA)
             {
                for (auto p : systems)
                   p->experiment_classification(TRAIN, TEST, 
                                                RESULTS + "-" + std::to_string(number_of_rules) 
                                                + "-" + std::to_string(eta)
                                                + "-" + p->get_nfs_name(),
                                                number_of_rules,
                                                NUMBER_OF_CLUSTERING_ITERATIONS,
                                                NUMBER_OF_TUNING_ITERATIONS,
                                                eta, NORMALISATION,
                                                POSITIVE, NEGATIVE,
                                                THRESHOLD_TYPE);    
             }
          }
       }
       
       */
      {
         // regression 
         
         ksi::imp_reichenbach implication;
         
         ksi::ma MA;
         ksi::tsk TSK;
         ksi::annbfis ANNBFIS (implication);
         ksi::subspace_annbfis SUBSPACE_ANNBFIS (implication);
         
         
         std::vector<ksi::neuro_fuzzy_system *> systems 
         { & MA, & TSK, & ANNBFIS, & SUBSPACE_ANNBFIS };
         
         const std::vector<int> NUMBER_OF_RULES = { 3, 4, 5, 7, 10, 15 };
         const std::vector<double> ETA = { 0.0001, 0.001, 0.01, 0.1};
         const std::vector<std::string> DATASETS { "methane", "leukocytes", "concrete" };
         
         const std::string DIRECTORY ("dane/");
         const std::string DATA_SUBDIRECTORY ("jw-norm/");
         
         const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
         const int NUMBER_OF_TUNING_ITERATIONS = 100;  
         const bool NORMALISATION = false; 
         
         for (auto dataset_name : DATASETS)
         {
            const std::string SUBDIRECTORY (dataset_name + "/");
            const std::string TRAIN   (DIRECTORY + DATA_SUBDIRECTORY + SUBDIRECTORY + dataset_name +  ".train"); 
            const std::string TEST    (DIRECTORY + DATA_SUBDIRECTORY + SUBDIRECTORY + dataset_name +  ".test");
            const std::string RESULTS (DIRECTORY + dataset_name + "-results");
            
            debug(dataset_name);
            for (auto number_of_rules : NUMBER_OF_RULES)
            {
               debug(number_of_rules);
               for (auto eta : ETA)
               {
                  debug(eta);
                  for (auto p : systems)
                  {
                     debug(p->get_nfs_name());
                     p->experiment_regression(TRAIN, TEST, 
                                             RESULTS + "-" + std::to_string(number_of_rules) 
                                             + "-" + std::to_string(eta)
                                             + "-" + p->get_nfs_name(),
                                             number_of_rules,
                                             NUMBER_OF_CLUSTERING_ITERATIONS,
                                             NUMBER_OF_TUNING_ITERATIONS, eta,
                                             NORMALISATION);
                  }
               }
            }
         }
      }
       
       
       
       
       // 
   }
   catch (...)
   {
         
      throw;
   }
   
   return;
}

