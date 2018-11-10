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
#include "../common/data-modifier-imputer-values-from-knn.h"
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

#include "../experiments/exp-000.h"

void ksi::exp_000::execute()
{
   
      /*
      const int NUMBER_OF_TREES = 100;
      ksi::random_neuro_fuzzy_forest las;
      las.set_number_of_trees(NUMBER_OF_TREES);
      */
      
      
       ksi::imp_reichenbach implikacja;
            
//       ksi::ma system_neuronowo_rozmyty;
       ksi::annbfis system_neuronowo_rozmyty (implikacja);
//       ksi::subspace_annbfis system_neuronowo_rozmyty (implikacja);
      
      //const std::string train ("male.data"), 
      //                  test  ("male.test");
      
//       const std::string TRAIN   ("male.data"), 
//                         TEST    ("male.test"),
//                         RESULTS ("male.results");
//       const int NUMBER_OF_RULES = 2;
            
       const std::string TRAIN   ("parkinsons.data"), 
                         TEST    ("parkinsons.test"),
                         RESULTS ("parkinsons.results"),
                         FOREST  (".forest"),
                         ANNBFIS (".annbfis");
      const int NUMBER_OF_RULES = 5;
      
//       const std::string TRAIN   ("MG.data"), 
//                         TEST    ("MG.test"),
//                         RESULTS ("MG.results"),
//                         FOREST (".forest"),
//                         ANNBFIS (".annbfis");
//       const int NUMBER_OF_RULES = 5;      
       
      const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
      const int NUMBER_OF_TUNING_ITERATIONS = 100;
      const int NUMBER_OF_NFS = 10;
      const double ETA = 0.1;
      const bool NORMALISATION = false;
      const double POSITIVE = 1.0;
      const double NEGATIVE = 0.0;
      
      //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::mean;
      //const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::minimal_distance;
      const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::youden;
      
     
      
//        system_neuronowo_rozmyty.experiment_classification(TRAIN, TEST, RESULTS,
//                                      NUMBER_OF_RULES,
//                                      NUMBER_OF_CLUSTERING_ITERATIONS,
//                                      NUMBER_OF_TUNING_ITERATIONS,
//                                      ETA, NORMALISATION,
//                                      POSITIVE, NEGATIVE,
//                                      THRESHOLD_TYPE);

//       system_neuronowo_rozmyty.experiment_classification(TRAIN, TEST, RESULTS,
//                                     NUMBER_OF_RULES,
//                                     NUMBER_OF_CLUSTERING_ITERATIONS,
//                                     NUMBER_OF_TUNING_ITERATIONS,
//                                     ETA, implikacja, NORMALISATION,
//                                     POSITIVE, NEGATIVE,
//                                     THRESHOLD_TYPE);
      
      
      // MA
//       system_neuronowo_rozmyty.experiment_regression(TRAIN, TEST, RESULTS,
//          NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS,
//          NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION);

      // ANNBFIS, SUBSPACE ANNBFIS
      
      
       std::cout << "zaczynam annbfis ... " << std::flush;
       
//       system_neuronowo_rozmyty.experiment_regression(TRAIN, TEST,
//          RESULTS + ANNBFIS, NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS,
//          NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION);
         system_neuronowo_rozmyty.experiment_classification(TRAIN, TEST, 
                                     RESULTS,
                                     NUMBER_OF_RULES,
                                     NUMBER_OF_CLUSTERING_ITERATIONS,
                                     NUMBER_OF_TUNING_ITERATIONS,
                                     ETA, NORMALISATION,
                                     POSITIVE, NEGATIVE,
                                     THRESHOLD_TYPE);

       std::cout << "skonczone" << std::endl;
   
      
      
      
      std::cout << "zaczynam las ...     "  << std::flush;
      ksi::random_neuro_fuzzy_forest las;
//       las.experiment_regression(TRAIN, TEST, RESULTS + FOREST,
//          NUMBER_OF_CLUSTERING_ITERATIONS,
//          NUMBER_OF_TUNING_ITERATIONS, NUMBER_OF_NFS,
//          ETA, NORMALISATION, system_neuronowo_rozmyty
//       );
      
      las.experiment_classification(TRAIN, TEST, RESULTS + FOREST,
         NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS,
         NUMBER_OF_NFS, ETA, NORMALISATION, POSITIVE, NEGATIVE,
         THRESHOLD_TYPE, system_neuronowo_rozmyty
      );
      std::cout << "skonczone" << std::endl;
      
      
      return ;
     
      /*
        
      ksi::annbfis ANNBFIS;
      
      const std::string TRAIN   ("parkinsons.data"), 
                        TEST    ("parkinsons.test"),
                        RESULTS ("parkinsons.results-minimal-distance");
      const int NUMBER_OF_RULES = 5;
      const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
      const int NUMBER_OF_TUNING_ITERATIONS = 10;
      const double ETA = 3e-9;
      const ksi::imp_reichenbach IMPLIKACJA;
      const bool NORMALISATION = false;
      const double POSITIVE = 1.0;
      const double NEGATIVE = 0.0;
      const ksi::roc_threshold THRESHOLD_TYPE = ksi::roc_threshold::minimal_distance;
      
      
      ANNBFIS.experiment_classification(TRAIN, TEST, RESULTS,
                                    NUMBER_OF_RULES,
                                    NUMBER_OF_CLUSTERING_ITERATIONS,
                                    NUMBER_OF_TUNING_ITERATIONS,
                                    ETA, IMPLIKACJA, NORMALISATION,
                                    POSITIVE, NEGATIVE,
                                    THRESHOLD_TYPE);
      
      */
      
      
      /*
      ksi::annbfis ANNBFIS;
      
      const std::string TRAIN   ("MG.data"), 
                        TEST    ("MG.test"),
                        RESULTS ("MG.results");
      const int NUMBER_OF_RULES = 5;
      const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
      const int NUMBER_OF_TUNING_ITERATIONS = 10;
      const double ETA = 3e-9;
      const ksi::imp_reichenbach IMPLIKACJA;
      const bool NORMALISATION = true;
      
      ANNBFIS.experiment_regression(TRAIN, TEST, RESULTS,
                                    NUMBER_OF_RULES,
                                    NUMBER_OF_CLUSTERING_ITERATIONS,
                                    NUMBER_OF_TUNING_ITERATIONS,
                                    ETA, IMPLIKACJA, NORMALISATION);
      */
      
      
      /*
      //const std::string train ("CH4.data"), 
      //                  test  ("CH4.test");
      const std::string train ("MG.data"), 
                        test  ("MG.test");
      
      //const std::string train ("male.data"), 
      //                  test  ("male.test");
      
      //const std::string train ("gauss.data"), 
      //                  test  ("gauss.test");                  
                        
      const int NUMBER_OF_RULES = 5;
      const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
      const int NUMBER_OF_TUNING_ITERATIONS = 10;
      ksi::imp_reichenbach implikacja;
      ksi::reader_complete czytacz;
      ksi::annbfis ANNBFIS;
      ksi::data_modifier_normaliser normaliser;
      
      auto zbiorTrain = czytacz.read(train);
      auto zbiorTest  = czytacz.read(test);
      
      normaliser.modify(zbiorTrain);
      normaliser.modify(zbiorTest);   
      
      
     
      
      //debug(zbiorTrain.getNumberOfData());
      //debug(zbiorTrain.getNumberOfAttributes());
      //debug(zbiorTest.getNumberOfData());
      const double ETA = 3e-9;
      ANNBFIS.createFuzzyRulebase(NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS,
                                  NUMBER_OF_TUNING_ITERATIONS, ETA,
                                  zbiorTrain, implikacja);
      auto XY = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      
      std::size_t nX = zbiorTest.getNumberOfData();
      
      std::vector<double> wYexpected, wYelaborated;
      for (std::size_t i = 0; i < nX; i++)
      {
         wYexpected.push_back(XY.second.get(i, 0));
         wYelaborated.push_back(ANNBFIS.answer(*(XY.first.getDatum(i))));
      }
      
      ksi::error_RMSE rmse;
      double blad_rmse = rmse.getError(wYelaborated, wYexpected);
      
      std::ofstream model ("model");
      model << "RMSE for test data: ";
      model << blad_rmse << std::endl; 
      model << std::endl << std::endl;      
      model << "excepted\telaborated" << std::endl;
      model << "===========================" << std::endl;
      
      
      for (std::size_t i = 0; i < nX; i++)
      {
         model << wYexpected[i] << '\t' << wYelaborated[i] << std::endl;
      }
      
      model << std::endl << std::endl;      
          
      
      ANNBFIS.printRulebase (model);
      model.close();
      */
      
      /*   
         
         
         std::vector<std::vector<double>> X
         {
            {  3, 4, 5 },
            { -1, 3, 0 },
            {  8, 3, 1 },
            {  0, 0, 0 }
         };
         
         std::vector<double> Y { 11, 4, -3, 0 };
         
         auto simple = ksi::least_square_error_regression::linear_regression(X, Y);
         auto recursive = ksi::least_square_error_regression::recursive_linear_regression(X, Y);
         
         for (auto & d : simple)
            std::cout << d << "  ";
         std::cout << std::endl;
         
         for (auto & d : recursive)
            std::cout << d << "  ";
         std::cout << std::endl;
         
         // teraz krokami:
         
         ksi::least_square_error_regression lser (X[0].size());
         
         for (std::size_t i = 0; i < X.size(); i++)
            lser.read_data_item(X[i], Y[i]);
         
         auto krok_za_krokiem = lser.get_regression_coefficients();
         
         for (auto & d : krok_za_krokiem)
            std::cout << d << "  ";
         std::cout << std::endl;
         
      */ 
         /*
         ksi::Matrix<std::complex<double>> m (10, 2);
         
         m(1,1) = 3.14;
         m(5,0) = 2.71;
         
         std::cout << m << std::endl;
         std::cout << !m << std::endl;
         */
     
      
      /*
      //ksi::descriptor_gaussian S ( 0, 0.5);
      //ksi::descriptor_gaussian_subspace S ( 0, 0.5, 0.7);
      //ksi::descriptor_semitriangular S (1.0, 2.0);
      //ksi::descriptor_triangular S (-2.0, 0.0, 3.0);
      //ksi::descriptor_sigmoidal S (0, 2);
      //ksi::descriptor_singleton S (0.0);
      ksi::descriptor_trapezoidal S (-2, -0.5, 0.1, 1.5);
     
      
      for (double x : { -1, 0 , 1} )
      {
         std::cout << "x     == " << x << std::endl;
         std::cout << "mi(x) == " << S.getMembership(x) << std::endl;
         auto diffs = S.getDifferentials(x);
         std::cout << "differentials:" << std::endl;
         debug(diffs.size());        
         for (const auto & d : diffs)
            std::cout << "  " << d << std::endl;
         std::cout << std::endl;
      }
      
      
      */
      
      /*
      std::vector<double> wagi {0.96, 0.84, 0.70, 0.82, 0.21,
         0.12, 0.18, 0.96, 0.84, 0.70, 0.82, 0.21, 0.12, 0.18}; 
      //std::string plik ("cl4in5d");
      std::string plik ("pedrycz");
      ksi::reader_complete czytacz;
      auto dane = czytacz.read(plik);
      
      
      for (std::size_t i = 0; i < wagi.size(); i++)
         dane.getDatum(i)->setWeight(wagi[i]);
      
      //ksi::fcm_conditional grupator;
      ksi::fcm_possibilistic grupator;
      grupator.setFuzzification(2.0);
      grupator.setNumberOfClusters(2);
      grupator.setNumberOfIterations(100);
      //grupator.setWeigthExponent(2.0);
      
      auto podzial = grupator.doPartition(dane);
      
      std::cout << podzial << std::endl;
      
      
      */
      /*
      
      {
         std::string plik ("possibilistic");
         ksi::reader_complete czytacz;
         auto dane = czytacz.read(plik);
         
         ksi::fcm grupator;
         grupator.setFuzzification(2.0);
         grupator.setNumberOfClusters(2);
         grupator.setNumberOfIterations(100);
         
         auto podzial = grupator.doPartition(dane);
         
         std::cout << "FCM" << std::endl;
         std::cout << podzial << std::endl;
      }

      {
         std::string plik ("possibilistic");
         ksi::reader_complete czytacz;
         auto dane = czytacz.read(plik);
         
         ksi::fcm_possibilistic grupator;
         grupator.setFuzzification(2.0);
         grupator.setNumberOfClusters(2);
         grupator.setNumberOfIterations(100);
         
         auto podzial = grupator.doPartition(dane);
         
         std::cout << "FCM possibilistic" << std::endl;
         std::cout << podzial << std::endl;
      }

      */
      /*
      std::string plik ("dane");
      std::string braki ("wieksze-braki");
   
      ksi::reader_incomplete czytacz;
      auto dane = czytacz.read(braki);
      std::cout << "dane oryginalne" << std::endl;
      std::cout << dane << std::endl;
      std::cout << std::endl;
      
      {
         auto marg = dane;
         ksi::data_modifier_marginaliser marginaliser;
         marginaliser.modify(marg);
         std::cout << "dane zmarginalizowane" << std::endl;
         std::cout << marg << std::endl;
         std::cout << std::endl;
      }

      {
         auto marg = dane;
         int k = 3;
         ksi::data_modifier_imputer_knn_average imputer(3);
         imputer.modify(marg);
         std::cout << "dane uzupelnione srednimi " << k << " najblizszych sasiadow" << std::endl;
         std::cout << marg << std::endl;
         std::cout << std::endl;
      }
      
      {
         auto marg = dane;
         int k = 3;
         ksi::data_modifier_imputer_knn_median imputer (k);
         imputer.modify(marg);
         std::cout << "dane uzupelnione medianami " << k << " najblizszych sasiadow" << std::endl;
         std::cout << marg << std::endl;
         std::cout << std::endl;
      }
      
      {
         auto marg = dane;
         int k = 3;
         ksi::data_modifier_imputer_values_from_knn imputer (k);
         imputer.modify(marg);
         std::cout << "dane uzupelnione wartosciami " << k << " najblizszych sasiadow" << std::endl;
         std::cout << marg << std::endl;
         std::cout << std::endl;
      }
       
      /*
      ksi::reader_complete czytacz;
      auto dane = czytacz.read(plik);
      std::cout << "dane oryginalne" << std::endl;
      std::cout << dane << std::endl;
      std::cout << std::endl;
      
      {
         auto data = dane;
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(data);
         std::cout << "dane znormalizowane" << std::endl;
         std::cout << data << std::endl;
         std::cout << std::endl;
      }

      {
         auto data = dane;
         std::cout << data << std::endl;
         std::cout << std::endl;
         ksi::data_modifier_standardiser standardiser;
      
         standardiser.modify(data);
         std::cout << "dane ustandardyzowane" << std::endl;
         std::cout << data << std::endl;
         std::cout << std::endl;
      }
      */
     
   /*
    double x = 0.1; 
      
      ksi::dis_huber huber (0.3);
      ksi::dis_log   logarithmic  ;
      ksi::dis_linear linear  ;
      
      std::cout << huber.dis(x) << std::endl;
      std::cout << logarithmic.dis(x) << std::endl;
      std::cout << linear.dis(x) << std::endl;
      
      
      std::vector<ksi::dissimilarity * > disoj;
      disoj.push_back(& huber);
      disoj.push_back(& logarithmic);
      disoj.push_back(& linear);
      
      for (auto p : disoj)
         std::cout << p->dis(x) << std::endl;
      
      std::vector<ksi::dissimilarity *> disoj_2;
      for (auto p : disoj)
         disoj_2.push_back(p->clone());
      
      for (auto p : disoj_2)
         std::cout << p->dis(x) << std::endl;
      
      for (auto p : disoj_2)
         delete p;
     
      const int W = 4;
      const int K = 5;
      ksi::Matrix<double> macierz(W, K);
      
      for (int w = 0; w < W; w++)
      {
         for (int k = 0; k < K; k++)
            macierz (w, k) = w - k;
      }
      
      std::cout << macierz << std::endl;
      
      debug(macierz.Frobenius_norm());
      
    
    */
   
}
