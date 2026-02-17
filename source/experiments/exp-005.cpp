/** @file */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

#include "../auxiliary/roc.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/to_string.h"
#include "../auxiliary/utility-math.h"
#include "../implications/imp-reichenbach.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/annbfis_prototype.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis_classification.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis_regression.h"
#include "../neuro-fuzzy/fac_prototype_minkowski_classification.h"
#include "../neuro-fuzzy/fac_prototype_minkowski_regression.h"
#include "../neuro-fuzzy/fubi-annbfis.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../neuro-fuzzy/three_way_decision_nfs.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/tsk_prototype.h"
#include "../partitions/gk.h"
#include "../service/debug.h"
#include "../tnorms/t-norm-product.h"
#include "../readers/cross_validation_reader.h"
#include "../readers/reader-complete.h"
#include "../experiments/exp-005.h"
#include <cassert>

#define NO_ITERATIONS 1
using cascade = std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>;
const std::vector<std::string> datasets = 
   {
     	"banana", 
      "blood",
      "fire",
      "heart",
      "ilpd",
      "magic",
      "parkinsons",
      "ring",
      "banknote",
      "bupa",
      "haberman",
      "htru",
      "wisconsin",
      "ionosphere",
      "phoneme",
      "vertebral",
      "ring",
      "magic"
   };

ksi::exp_005::exp_005()
{
}

void ksi::exp_005::classification(const std::string& dataset_name)
{
   std::cout << "classification" << std::endl;
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   std::string RESULT_EXTENSION {".txt"};


   std::vector<ksi::roc_threshold> thresholds { //ksi::roc_threshold::mean,
      //ksi::roc_threshold::minimal_distance, 
      ksi::roc_threshold::youden
   };

   const std::string EXPERIMENT           ("exp-005");
   const std::string TYPE                 ("classification");
   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
   const std::string RESULTS_DIRECTORY    ("../results/" + EXPERIMENT + "/" + TYPE);

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;

   // dataset
   //std::string dataset_name { "htru" };

   std::cout << "data set: " << dataset_name << std::endl;
   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
   std::string TEST    (dataset + "/" + dataset_name + ".test");
   std::string RESULTS (results_dir + "/results-" + dataset_name);

   // THREE-WAY DECISION NEURO-FUZZY CLASSIFIER (single noncommitment value)
   {
      double noncommitment_value = 0.1; // half of width of the noncommitment interval

      for (auto th : thresholds)  // for all thresholds
      {
         // We compose several types of cascades built of neuro-fuzzy systems:
         std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> systems 
         {
            // ANNBFIS
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th)),
            // TSK 
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::tsk (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th)),
         };


         // for all systems we compose cascades:
         for (auto & nfs : systems)
         {
            std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> cascade_of_nfs 
            { 
               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
                  std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
                  std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone())
            };

            std::string threshold_name;
            switch(th)
            {
               case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
               case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
               case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
               default                                   : threshold_name = "something-wrong-has-happened"; break;
            }

            // And we run experiments:
            std::string cascade_name;
            for (const auto & p : cascade_of_nfs)
               cascade_name += std::string{"-"} + p->get_nfs_name();
            cascade_name += std::string{"-"} + std::to_string(noncommitment_value);

            std::string result_file { RESULTS + "-3WDNFS-" + cascade_name + "-" + threshold_name + RESULT_EXTENSION }; 
            ksi::three_way_decision_nfs system (cascade_of_nfs, TRAIN, TEST, result_file, noncommitment_value);
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;


         }
      }
   }

   // THREE-WAY DECISION NEURO-FUZZY CLASSIFIER (separate noncommitment values)
   {

      for (auto th : thresholds)  // for all thresholds
      {
         // We compose several types of cascades built of neuro-fuzzy systems:
         std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> systems 
         {
            // ANNBFIS
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th)),

            // TSK 
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::tsk (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th)),
         };


         std::vector<double> noncommitment_values = {0.2, 0.1, 0.0}; // half of width of the noncommitment interval
         // for all systems we compose cascades:
         for (auto & nfs : systems)
         {
            std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> cascade_of_nfs 
            { 
               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
                  std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
                  std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone())
            };

            std::string threshold_name;
            switch(th)
            {
               case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
               case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
               case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
               default                                   : threshold_name = "something-wrong-has-happened"; break;
            }

            // And we run experiments:
            std::string cascade_name;
            for (const auto & p : cascade_of_nfs)
               cascade_name += std::string{"-"} + p->get_nfs_name();
            cascade_name += std::string{"-"} + ksi::to_string(noncommitment_values);

            std::string result_file { RESULTS + "-3WDNFS-" + cascade_name + "-" + threshold_name + RESULT_EXTENSION }; 
            ksi::three_way_decision_nfs system (cascade_of_nfs, TRAIN, TEST, result_file, noncommitment_values);
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;


         }
      }
   }
}

void ksi::exp_005::regression()
{
   std::cout << std::endl;
   std::cout <<  "regression" << std::endl;

   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   std::string RESULT_EXTENSION {".txt"};

   const std::string EXPERIMENT           ("exp-005");
   const std::string TYPE                 ("regression");
   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
   const std::string RESULTS_DIRECTORY    ("../results/" + EXPERIMENT + "/" + TYPE);

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;

   const bool NORMALISATION = false;

   const double ETA = 0.001;

   std::string dataset_name { "leukocytes" };

   std::cout << "data set: " << dataset_name << std::endl;
   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
   std::string TEST    (dataset + "/" + dataset_name + ".test");
   std::string RESULTS (results_dir + "/results-" + dataset_name);

   // MA
   {
      ksi::ma system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // TSK
   {
      ksi::tsk system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // ANNBFIS
   {
      ksi::annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // SUBSPACE_ANNBFIS
   {
      ksi::subspace_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // FUBI_ANNBFIS
   {
      ksi::fubi_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // MINKOWSKI PROTOTYPE TSK
   {
      const double minkowski_coefficient { 2.0 };
      ksi::fac_prototype_minkowski_regression factory (minkowski_coefficient);
      ksi::tsk_prototype system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, factory);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }

   // MINKOWSKI PROTOTYPE ANNBFIS
   {
      const double minkowski_coefficient { 2.0 };
      ksi::fac_prototype_minkowski_regression factory (minkowski_coefficient);
      ksi::annbfis_prototype system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, ksi::imp_reichenbach(), factory);
      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }
   // MAHALANOBIS PROTOTYPE TSK
   {
      //const int NUMBER_OF_RULES = 3;
      ksi::gk algorithm;
      algorithm.setNumberOfIterations(NUMBER_OF_CLUSTERING_ITERATIONS);
      algorithm.setNumberOfClusters(NUMBER_OF_RULES);

      ksi::fac_prototype_mahalanobis_regression factory;
      ksi::tsk_prototype system (algorithm, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, factory);

      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }
   // MAHALANOBIS PROTOTYPE ANNBFIS
   {
      //const int NUMBER_OF_RULES = 3;
      ksi::gk algorithm;
      algorithm.setNumberOfIterations(NUMBER_OF_CLUSTERING_ITERATIONS);
      algorithm.setNumberOfClusters(NUMBER_OF_RULES);

      ksi::imp_reichenbach impl;
      ksi::fac_prototype_mahalanobis_regression factory;
      ksi::annbfis_prototype system (algorithm, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, impl, factory);

      std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
      std::string result_file { RESULTS + "-" + system.get_nfs_name() + RESULT_EXTENSION }; 
      system.experiment_regression(TRAIN, TEST, result_file);
      std::cout << "\tResults saved to file " << result_file << std::endl;
      std::cout << std::endl;
   }
}


//void ksi::exp_005::WP_classification_CV(const std::string& dataset_name)
//{
//   std::cout << "classification CV" << std::endl;
//   ksi::imp_reichenbach implication;
//   ksi::t_norm_product Tnorm;
//   std::string RESULT_EXTENSION {".txt"};

//   const std::string EXPERIMENT           ("exp-005");
//   const std::string TYPE                 ("classification");
//   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
//   const std::string RESULTS_DIRECTORY    ("../results/" + EXPERIMENT + "/" + TYPE);

//   const int NUMBER_OF_RULES = 5;
//   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
//   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

//   const bool NORMALISATION = false;

//   const double ETA = 0.001;
//   const double POSITIVE_CLASS_LABEL = 1.0;
//   const double NEGATIVE_CLASS_LABEL = 0.0;

 
//   std::cout << "data set: " << dataset_name << std::endl;
//   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

//   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
//   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
//   std::string TEST    (dataset + "/" + dataset_name + ".test");
//   std::string RESULTS (results_dir + "/results-" + dataset_name);
//   // THREE-WAY DECISION NEURO-FUZZY CLASSIFIER (separate noncommitment values)
//   {
//      // We compose several types of cascades built of neuro-fuzzy systems:
//      std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> systems 
//      {
//         // ANNBFIS
//         std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, ksi::roc_threshold::youden)),
//         // TSK 
//         std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::tsk (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, ksi::roc_threshold::youden)),
//      };

//      auto functions = {WP::get_noncommitment, WP::get_noncommitment_based_on_threshold};
//      auto func_names = {"noncommitment", "noncommitment_based_on_threshold"};
//      // for all systems we compose cascades:
      
//      for (auto & nfs : systems)
//      {
//         std::map<std::string, double> statistics {
//            {std::string("no_rules"), 0.},
//            {std::string("f1_test_score"), 0.}
//         };
//         for(auto i = 0; i < NO_ITERATIONS; ++i)
//         {
//            std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> cascade_of_nfs 
//            { 
//               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()),
//               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
//               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone())
//            };

//            // And we run experiments:
//            std::string cascade_name;
//            for (const auto & p : cascade_of_nfs)
//               cascade_name += std::string{"-"} + p->get_nfs_name();
//            cascade_name += std::string{"-based_on_threshold"};
//            cascade_name += std::string{"-"} + std::to_string(i);

//            std::string result_file { RESULTS + "-3WDNFS-" + cascade_name + RESULT_EXTENSION }; 
//            ksi::three_way_decision_nfs_WP system(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
//            WP::get_noncommitment_based_on_threshold);
//            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
//            system.experiment_classification(TRAIN, TEST, result_file);    
//            std::cout << "\tResults saved to file " << result_file << std::endl;
//            std::cout << std::endl;
         
//            statistics["no_rules"] = system.get_number_of_rules();
//            for(auto j = 0; j < 3;++j)
//            {
//               statistics["f1_test_score"] += system.get_test_F1score_for_part_of_the_cascade(j);
//            }
//            statistics["f1_test_score"] = statistics["f1_test_score"]/3;
//         }

//         for(auto it = statistics.begin(); it != statistics.end(); ++it)
//         {
//            it->second = it->second/NO_ITERATIONS;
//            std::cout << it->first << " : " << it->second << std::endl;
//         }
//      }
//   }
//}

void ksi::exp_005::WP_classification(const std::string& dataset_name)
{
   std::cout << "classification" << std::endl;
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   std::string RESULT_EXTENSION {".txt"};

   const std::string EXPERIMENT           ("exp-005");
   const std::string TYPE                 ("classification");
   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
   const std::string RESULTS_DIRECTORY    ("../results/" + EXPERIMENT + "/" + TYPE);

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;

   // dataset
   //std::string dataset_name { "haberman" };

   std::cout << "data set: " << dataset_name << std::endl;
   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
   std::string TEST    (dataset + "/" + dataset_name + ".test");
   std::string RESULTS (results_dir + "/results-" + dataset_name);


   // THREE-WAY DECISION NEURO-FUZZY CLASSIFIER (separate noncommitment values)
   {

         // We compose several types of cascades built of neuro-fuzzy systems:
         std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> systems 
         {
            // ANNBFIS
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::annbfis  (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, ksi::roc_threshold::youden)),
            // TSK 
            std::shared_ptr<ksi::neuro_fuzzy_system> (new ksi::tsk      (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, ksi::roc_threshold::youden)),
         };


         // for all systems we compose cascades:
         for (auto & nfs : systems)
         {
            std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> cascade_of_nfs 
            { 
               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()),
               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone()), 
               std::shared_ptr<ksi::neuro_fuzzy_system> (nfs->clone())
            };

            auto fitness_func = WP::get_noncommitment;
            // And we run experiments:
            std::string cascade_name;
            for (const auto & p : cascade_of_nfs)
               cascade_name += std::string{"-"} + p->get_nfs_name();
            cascade_name += std::string{"-custom_fitness_func"};

            std::string result_file { RESULTS + "-3WDNFS-" + cascade_name + RESULT_EXTENSION }; 
            ksi::three_way_decision_nfs_WP system(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
            WP::get_noncommitment);
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
      }
   }
}

double f1_score(const ksi::result& result)
{
   return 2.0 * result.TestPositive2Positive / (2.0 * result.TestPositive2Positive + result.TestPositive2Negative + result.TestNegative2Positive);
}

void save_to_file(const std::string& file_path, const std::vector<double>& f1_scores, const std::vector<double>& avg_num_samples)
{
   using namespace std::string_literals;
   assert(f1_scores.size() == avg_num_samples.size());
   std::ofstream file(file_path);
   if (!file) throw std::runtime_error("Cannot open file: "s + file_path);
   for(auto i = 0; i < f1_scores.size(); ++i)
   {
      file << i << " " << f1_scores.at(i) << " " << avg_num_samples.at(i) << std::endl;
   }
}
std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_one_noncommitment(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
{
   return std::make_unique<ksi::three_way_decision_nfs>(cascade_of_nfs, TRAIN, TEST, result_file, 0.1);
}

std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_stairs(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
{
   std::vector vec{0.3, 0.2, 0.1, 0.1};
   return std::make_unique<ksi::three_way_decision_nfs>(cascade_of_nfs, TRAIN, TEST, result_file, vec);
}

std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_meta(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
{
   cascade meta_classifiers;
   for(const auto& nfs : cascade_of_nfs)
   {
      meta_classifiers.push_back(std::shared_ptr<ksi::neuro_fuzzy_system>(nfs->clone()));
   }
   meta_classifiers.pop_back();

   return std::make_unique<ksi::three_way_decision_nfs_meta>(cascade_of_nfs, meta_classifiers, TRAIN, TEST, result_file);
}

std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_algorithm(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
{
   return std::make_unique<ksi::three_way_decision_nfs_WP>(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
            WP::get_noncommitment_based_on_threshold);
}

std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_algorithm_penalize(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
{
   return std::make_unique<ksi::three_way_decision_nfs_WP>(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
            WP::get_noncommitment_based_on_threshold_hard_penalize);
}
cascade create_anbfis()
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   auto x = std::make_shared<ksi::annbfis> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   return cascade{
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone())
   };
}

cascade create_anbfis_increasing_no_rules()
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   auto x = std::make_shared<ksi::annbfis> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   return cascade{
      std::make_shared<ksi::annbfis> (NUMBER_OF_RULES-3, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::annbfis> (NUMBER_OF_RULES-1, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::annbfis> (NUMBER_OF_RULES+1, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::annbfis> (NUMBER_OF_RULES+3, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold)
   };
}



cascade create_tsk()
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   auto x = std::make_shared<ksi::tsk> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   return cascade{
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone()),
      std::shared_ptr<ksi::neuro_fuzzy_system>(x->clone())
   };
}

cascade create_tsk_increasing_no_rules()
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = 5;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   auto x = std::make_shared<ksi::tsk> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   return cascade{
      std::make_shared<ksi::tsk> (NUMBER_OF_RULES-3, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::tsk> (NUMBER_OF_RULES-1, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::tsk> (NUMBER_OF_RULES+1, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold),
      std::make_shared<ksi::tsk> (NUMBER_OF_RULES+3, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold)
   };
}


void save_depth_to_file(const std::string& file_path, const std::vector<std::tuple<std::vector<double>, std::size_t, std::size_t>>& answers)
{
   using namespace std::string_literals;
   std::ofstream file(file_path);
   if (!file) throw std::runtime_error("Cannot open file: "s + file_path);
   for(const auto& answer : answers)
   {
      for(const auto& val : std::get<0>(answer))
      {
         file << val << ",";
      }
      file << std::get<1>(answer) << "," << std::get<2>(answer) << std::endl;
   }
}

void test_algorithm_simple(const std::string& dataset_name, const int repetitions, cascade cascade_of_nfs, std::function<std::unique_ptr<ksi::three_way_decision_nfs> (const cascade&, const std::string&, const std::string&, const std::string&)> func, std::string name = "")
{
   std::string RESULT_EXTENSION {".txt"};

   const std::string EXPERIMENT           ("exp-005");
   const std::string TYPE                 ("classification");
   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
   const std::string RESULTS_DIRECTORY    ("../results/");

   std::cout << "data set: " << dataset_name << std::endl;
   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
   std::string TEST    (dataset + "/" + dataset_name + ".test");
   std::string RESULTS (results_dir +"/" + name );

   std::vector<double> f1_scores(repetitions), avg_num_of_samples(repetitions);
   for(auto i = 0; i < repetitions; ++i)
   {
      // And we run experiments:
      std::string cascade_name;
      for (const auto & p : cascade_of_nfs)
         cascade_name += std::string{"-"} + p->get_nfs_name();
      cascade_name += name;
      cascade_name += std::string{"-"} + std::to_string(i);


      std::string result_file { RESULTS + "/" + std::to_string(i) +"/results-" + dataset_name + cascade_name + RESULT_EXTENSION }; 
      
      auto system = func(cascade_of_nfs, TRAIN, TEST, result_file);
      std::cout << "\tmethod:    " << system->get_nfs_name() << std::endl;
      auto result = system->experiment_classification(TRAIN, TEST, result_file);
      auto second_result = system->get_answers_for_test_classification_depth();
      auto train_data_set_result = system->get_answers_for_test_classification_depth(false);
      save_depth_to_file(RESULTS + "/" + std::to_string(i) +"/depth-" + dataset_name + cascade_name + RESULT_EXTENSION, second_result);
      save_depth_to_file(RESULTS + "/" + std::to_string(i) +"/depth-train-" + dataset_name + cascade_name + RESULT_EXTENSION, train_data_set_result);
      std::cout << "\tResults saved to file " << result_file << std::endl << std::endl;
      f1_scores.at(i) = f1_score(result);
      avg_num_of_samples.at(i) = system->get_number_of_rules();
   }
   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples);
   std::cout << "Main results saved to file " << RESULTS + RESULT_EXTENSION << std::endl;
}

void ksi::exp_005::execute()
{
   try
   {
      for(auto dataset : datasets)
      {
         {
            auto annbfis_increasing_stairs = [=](){
               test_algorithm_simple(dataset, 23, create_anbfis_increasing_no_rules(), create_3WDNFS_meta, "ANNBFIS-increasing_no_rules_meta_classifier");
            };
            auto annbfis_simple_one = [=](){
               test_algorithm_simple(dataset, 23, create_anbfis(), create_3WDNFS_meta, "ANNBFIS_steady_no_rules_meta_classifier");
            };

            auto tsk_simple_one = [=]() {
               test_algorithm_simple(dataset, 23, create_tsk(), create_3WDNFS_meta, "TSK-steady_no_rules_meta_classifier");
            };
            auto tsk_increasing_one = [=](){
               test_algorithm_simple(dataset, 23, create_tsk_increasing_no_rules(), create_3WDNFS_meta, "TSK-increasing_no_rules_meta_classifier");
            };
            auto x =    std::thread(annbfis_increasing_stairs); 
            auto x2 =    std::thread(annbfis_simple_one); 
            auto x4 =    std::thread(tsk_simple_one); 
            auto x5 =    std::thread(tsk_increasing_one); 
            x.join(); 
            x2.join();
            x4.join();
            x5.join();
         }
         {
            //auto annbfis_increasing_stairs = [=](){
            //   test_algorithm_simple(dataset, 23, create_anbfis_increasing_no_rules(), create_3WDNFS_algorithm, "ANNBFIS-increasing_no_rules_soft_penalization");
            //};
            //auto annbfis_increasing_one = [=](){
            //   test_algorithm_simple(dataset, 23, create_anbfis_increasing_no_rules(), create_3WDNFS_algorithm_penalize, "ANNBFIS-increasing_no_rules_hard_penalization");
            //};
            //auto annbfis_simple_one = [=](){
            //   test_algorithm_simple(dataset, 23, create_anbfis(), create_3WDNFS_algorithm_penalize, "ANNBFIS_steady_no_rules_hard_penalization");
            //};
            //auto annbfis_simple_stairs = [=](){
            //   test_algorithm_simple(dataset, 23, create_anbfis(), create_3WDNFS_algorithm, "ANNBFIS_steady_no_rules_soft_penalization");   
            //};
            //auto tsk_simple_one = [=]() {
            //   test_algorithm_simple(dataset, 23, create_tsk(), create_3WDNFS_algorithm_penalize, "TSK-steady_no_rules_hard_penalization");
            //};
            //auto tsk_increasing_one = [=](){
            //   test_algorithm_simple(dataset, 23, create_tsk_increasing_no_rules(), create_3WDNFS_algorithm_penalize, "TSK-increasing_no_rules_hard_penalization");
            //};
            //auto tsk_simple_stairs = [=]() {
            //   test_algorithm_simple(dataset, 23, create_tsk(), create_3WDNFS_algorithm, "TSK-steady_no_rules_soft_penalization");
            //};
            //auto tsk_increasing_stairs = [=](){
            //   test_algorithm_simple(dataset, 23, create_tsk_increasing_no_rules(), create_3WDNFS_algorithm, "TSK-increasing_no_rules_soft_penalization");   
            //};
            //auto x =    std::thread(annbfis_increasing_stairs); 
            //auto x1 =    std::thread(annbfis_increasing_one);
            //auto x2 =    std::thread(annbfis_simple_one); 
            //auto x3 =    std::thread(annbfis_simple_stairs);
            //auto x4 =    std::thread(tsk_simple_one); 
            //auto x5 =    std::thread(tsk_increasing_one); 
            //auto x6 =    std::thread(tsk_simple_stairs); 
            //auto x7 =    std::thread(tsk_increasing_stairs);
            //x.join(); 
            //x1.join();
            //x2.join();
            //x3.join();
            //x4.join();
            //x5.join();
            //x6.join();
            //x7.join();
         }
      }
   } CATCH;

   return;
}
