/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 

#include "../readers/reader-complete.h"
#include "../readers/reader-incomplete.h"
#include "../common/data-modifier-normaliser.h"
#include "../common/data-modifier-standardiser.h"
#include "../common/data-modifier-marginaliser.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-imputer-average.h"
#include "../common/data-modifier-imputer-median.h"
#include "../common/data-modifier-imputer-knn-average.h"
#include "../common/data-modifier-imputer-knn-median.h"
#include "../common/dataset.h"
#include "../common/error-RMSE.h"
#include "../partitions/partitioner.h"
#include "../partitions/rfcm.h"
#include "../partitions/fcm.h"
#include "../partitions/fcm-conditional.h"
#include "../partitions/fcm-possibilistic.h"
#include "../partitions/sfcm.h"
#include "../descriptors/descriptor-triangular.h"
#include "../descriptors/descriptor-semitriangular.h"
#include "../descriptors/descriptor-trapezoidal.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../descriptors/descriptor-gaussian-subspace.h"
#include "../descriptors/descriptor-sigmoidal.h"
#include "../descriptors/descriptor-singleton.h"
#include "../neuro-fuzzy/premise.h"
#include "../tnorms/t-norm-product.h"
#include "../tnorms/t-norm-min.h"
#include "../tnorms/t-norm-lukasiewicz.h"
#include "../tnorms/t-norm-drastic.h"
#include "../tnorms/t-norm-fodor.h"
#include "../tnorms/t-norm-einstein.h"
#include "../implications/imp-lukasiewicz.h"
#include "../implications/imp-fodor.h"
#include "../implications/imp-goedel.h"
#include "../implications/imp-goguen.h"
#include "../implications/imp-kleene-dienes.h"
#include "../implications/imp-reichenbach.h"
#include "../implications/imp-rescher.h"
#include "../implications/imp-zadeh.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/logicalrule.h"
#include "../neuro-fuzzy/consequence-MA.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../neuro-fuzzy/random-neuro-fuzzy-forest.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/ma.h"
#include "../auxiliary/matrix.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"

#include "../experiments/exp-001.h"

#include <fstream>

void ksi::exp_011::execute()
{
   ksi::imp_reichenbach implikacja;
   std::vector<ksi::neuro_fuzzy_system *> systemy { new ksi::annbfis(implikacja),
      new ksi::tsk, new ksi::ma };
   
   try
   {  
      std::vector<std::string> regresja { "CH4", "CO2", "concrete"/*, "death"*/ };
      std::vector<std::string> klasyfikacja { "pima", "parkinsons" };
      
      std::string PATH    ("../../../datasets");
      std::string LOMITKO ("/");
      std::string REGRESSION ("regression");
      std::string CLASSIFICATION ("classification");
      std::string RESULTS ("./results");
      std::string TRAIN   (".data");
      std::string TEST    (".test");
      std::string LACZNIK ("-");
      std::string ANNBFIS ("annbfis");
      std::string TSK     ("tsk");
      std::string MA      ("ma");
      std::string FOREST  ("forest");
      
      const int NUMBER_OF_RULES = 5;
      const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
      const int NUMBER_OF_TUNING_ITERATIONS = 100;
      const bool NORMALISATION = true;
      const double POSITIVE = 1.0;
      const double NEGATIVE = 0.0;
      
      const double ETA = 0.1;      
      
      // najpierw regresja
      std::vector<int> liczebnosci_lasow { 5, 10, 20, 50 };
      std::vector<ksi::roc_threshold> kryteria_roc { ksi::roc_threshold::mean,
                                       ksi::roc_threshold::minimal_distance,
                                       ksi::roc_threshold::youden };
      
                                       
      for (const auto & nazwa : regresja)
      {
         std::string plik = PATH + LOMITKO + REGRESSION + LOMITKO + nazwa + LOMITKO + nazwa;
         std::string plikTrain = plik + TRAIN;
         std::string plikTest  = plik + TEST;         
         
         for (auto & pSystem : systemy)
         {
            // eksperyment dla systemu
            
            std::string plikWynik = RESULTS + LOMITKO + nazwa + LACZNIK + 
                                    pSystem->get_nfs_name();
            pSystem->experiment_regression(plikTrain, plikTest, plikWynik,
                                          NUMBER_OF_RULES,
                                          NUMBER_OF_CLUSTERING_ITERATIONS,
                                          NUMBER_OF_TUNING_ITERATIONS,
                                          ETA, NORMALISATION);
            
            // eksperyment dla lasu systemow: 
            
            for (const int ILE_DRZEW : liczebnosci_lasow)
            {
               std::string plikWynikLas = RESULTS + LOMITKO + nazwa + LACZNIK + 
                                    nazwa + LACZNIK + FOREST + pSystem->get_nfs_name() + LACZNIK + std::to_string(ILE_DRZEW);
               ksi::random_neuro_fuzzy_forest las;
               las.experiment_regression(plikTrain, plikTest, plikWynikLas,
                  NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS,
                  ILE_DRZEW, ETA, NORMALISATION, *pSystem);
            }            
         } 
      }
       
      
      for (const auto & nazwa : klasyfikacja)
      {
         std::string plik = PATH + LOMITKO + CLASSIFICATION + LOMITKO + nazwa + LOMITKO + nazwa;
         std::string plikTrain = plik + TRAIN;
         std::string plikTest  = plik + TEST;
         
         for (auto & pSystem : systemy)
         {
            // eksperyment dla systemu
            std::string nazwa_kryterium;
            for (auto & kryterium : kryteria_roc)
            {
               switch (kryterium)
               {
                  case ksi::roc_threshold::mean:
                     nazwa_kryterium = "mean";
                     break;
                  case ksi::roc_threshold::minimal_distance:
                     nazwa_kryterium = "minimaldistance";
                     break;
                  case ksi::roc_threshold::youden:
                     nazwa_kryterium = "youden";
                     break;                 
               }
                  
                  
               std::string plikWynik = RESULTS + LOMITKO + nazwa + LACZNIK + 
                                       pSystem->get_nfs_name() + LACZNIK + nazwa_kryterium;
               pSystem->experiment_classification(plikTrain, plikTest, plikWynik,
                                             NUMBER_OF_RULES,
                                             NUMBER_OF_CLUSTERING_ITERATIONS,
                                             NUMBER_OF_TUNING_ITERATIONS,
                                             ETA, NORMALISATION,
                                             POSITIVE, NEGATIVE, kryterium);
               
               // eksperyment dla lasu systemow: 
               for (const int ILE_DRZEW : liczebnosci_lasow)
               {
                  std::string plikWynikLas = RESULTS + LOMITKO + nazwa + LACZNIK + 
                                       nazwa + LACZNIK + FOREST + pSystem->get_nfs_name() + LACZNIK + std::to_string(ILE_DRZEW) + LACZNIK + nazwa_kryterium;
               
                  ksi::random_neuro_fuzzy_forest las;
                  las.experiment_classification(plikTrain, plikTest, plikWynikLas,
                     NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS,
                     ILE_DRZEW, ETA, NORMALISATION, 
                     POSITIVE, NEGATIVE, kryterium,
                     *pSystem);
               }
            }
         }
      }
   }
   catch (...)
   {
      for (auto & pSystem : systemy)
         delete pSystem;
      
      throw;
   }
   
   for (auto & pSystem : systemy)
         delete pSystem;   

   return;
}
