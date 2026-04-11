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
#include <functional>

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
#include "../neuro-fuzzy/meta_classifier_three_way_decision_nfs.h"
#include "../partitions/gk.h"
#include "../service/debug.h"
#include "../tnorms/t-norm-product.h"
#include "../readers/cross_validation_reader.h"
#include "../readers/reader-complete.h"
#include "../experiments/exp-006.h"
#include "../readers/train_validation_test_model.h"
#include <cassert>

#define NO_ITERATIONS 1
using cascade = std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>;
const std::map<std::string, int> datasets_rules = 
   {
      {"banana", 7},
      {"banknote", 7},
      {"blood", 10},
      {"bupa", 2},
      {"fire", 2},
      {"haberman", 5},
      {"heart", 2},
      {"htru", 2},
      {"ilpd", 2},
      {"ionosphere", 2},
      {"magic", 2},
      {"phoneme", 5},
      {"ring", 7},
      {"vertebral", 2},
      {"wisconsin", 2}
   };



double f1_score(const ksi::result& result)
{
   return 2.0 * result.TestPositive2Positive / (2.0 * result.TestPositive2Positive + result.TestPositive2Negative + result.TestNegative2Positive);
}

double accuracy(const ksi::result& result)
{
   return (result.TestPositive2Positive + result.TestNegative2Negative) / (result.TestPositive2Positive + result.TestPositive2Negative + result.TestNegative2Positive + result.TestNegative2Negative);
}

void test_algorithm_simple(const std::string& dataset_name, const int repetitions, cascade cascade_of_nfs, std::function<std::unique_ptr<ksi::three_way_decision_nfs> (const cascade&, const std::string&, const std::string&, const std::string&)> func, std::string name = "");

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

//std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_meta(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
//{
//   cascade meta_classifiers;
//   for(const auto& nfs : cascade_of_nfs)
//   {
//      meta_classifiers.push_back(std::shared_ptr<ksi::neuro_fuzzy_system>(nfs->clone()));
//   }
//   meta_classifiers.pop_back();

//   return std::make_unique<ksi::three_way_decision_nfs_meta>(cascade_of_nfs, meta_classifiers, TRAIN, TEST, result_file);
//}

//std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_algorithm(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
//{
//   return std::make_unique<ksi::three_way_decision_nfs_WP>(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
//            WP::get_noncommitment_based_on_threshold);
//}

//std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_algorithm_penalize(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file)
//{
//   return std::make_unique<ksi::three_way_decision_nfs_WP>(cascade_of_nfs, TRAIN, TEST, TEST, result_file,
//            WP::get_noncommitment_based_on_threshold_hard_penalize);
//}


//std::unique_ptr<ksi::three_way_decision_nfs> create_3WDNFS_algorithm_lambda(const cascade& cascade_of_nfs, const std::string& TRAIN, const std::string& TEST, const std::string& result_file, const double lambda)
//{
//   auto lambda_fitness = [lambda](const std::vector<std::tuple<double, double, double>> & data, const double& threshold)
//   {
//      return WP::get_noncommitment_based_on_threshold_custom_lambda(data, threshold, lambda);
//   };

//   return std::make_unique<ksi::three_way_decision_nfs_WP>(cascade_of_nfs, TRAIN, TEST, TEST, result_file, lambda_fitness);
//}

//void test_algorithm_lambda_sweep(
//   const std::string& dataset_name,
//   const int repetitions,
//   const cascade& cascade_of_nfs,
//   const std::string& base_name,
//   const std::vector<double>& lambda_values)
//{
//   for (const auto lambda : lambda_values)
//   {
//      auto wp_lambda_factory = [lambda](const cascade& c, const std::string& train, const std::string& test, const std::string& result_file)
//      {
//         return create_3WDNFS_algorithm_lambda(c, train, test, result_file, lambda);
//      };

//      const std::string experiment_name = base_name + "-WP-lambda-" + lambda_to_tag(lambda);
//      test_algorithm_simple(dataset_name, repetitions, cascade_of_nfs, wp_lambda_factory, experiment_name);
//   }
//}

cascade create_anbfis_constant_number_of_rules(const int number_of_rules)
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = number_of_rules;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   cascade to_return(10);
   for(int i = 0; i < 10; ++i)   {
      to_return.at(i) = std::make_shared<ksi::annbfis> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   }
   return to_return;
}

cascade create_anbfis_increasing_no_rules(const int initial_number_of_rules)
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = initial_number_of_rules;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   cascade to_return(10);
   for (int i = 0; i < 10; ++i)
   {
      to_return.at(i) = std::make_shared<ksi::annbfis> (NUMBER_OF_RULES + 2*i, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   }
   return to_return;
}



cascade create_tsk_constant_number_of_rules(const int number_of_rules)
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = number_of_rules;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   cascade to_return(10);
   for(int i = 0; i < 10; ++i)
   {
      to_return.at(i) = std::make_shared<ksi::tsk> (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   }
   return to_return;
}

cascade create_tsk_increasing_no_rules(const int initial_number_of_rules)
{
   ksi::imp_reichenbach implication;
   ksi::t_norm_product Tnorm;
   ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   const int NUMBER_OF_RULES = initial_number_of_rules;
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;  

   const bool NORMALISATION = false;

   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   cascade to_return(10);
   for (int i = 0; i < 10; ++i)
   {
      to_return.at(i) = std::make_shared<ksi::tsk> (NUMBER_OF_RULES + 2*i, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   }
   return to_return;
}

void ksi::exp_006::classification()
{
}

void ksi::exp_006::regression()
{
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
struct experiment_result{
   double f1_score;
   double accuracy;
   double avg_num_of_samples;
};
experiment_result run_cross_validation_for_dataset(const std::string& dataset_name, std::function<cascade()> cascade_factory, std::function<std::shared_ptr<ksi::three_way_decision_nfs> (const std::function<cascade()>, const ksi::dataset&, const ksi::dataset&, const ksi::dataset&, const std::string&)> func, std::string name)
{
   std::string RESULT_EXTENSION {".txt"};

   const std::string DATA_DIRECTORY       ("../merged-data/");
   const std::string RESULTS_DIRECTORY    ("../results_preeliminary_one_width/");

   std::cout << "data set: " << dataset_name << std::endl;
   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string RESULTS (results_dir +"/" + name );
   ksi::reader_complete cr;
   ksi::train_validation_test_model tvt(cr, 4); 

   const int chunks { 9 };
   tvt.read_and_split_file("../merged-data/" + dataset + ".csv", chunks);

   int counter { 0 };
   std::vector<double> f1_scores(chunks), avg_num_of_samples(chunks), accuracies(chunks);
   for (const auto & [train, validate, test] : tvt)
   {
      // And we run experiments:
      std::string cascade_name;
      cascade_name += std::string{"-"} + std::to_string(counter);


      std::string result_file { RESULTS + "/" + std::to_string(counter) +"/results-" + dataset_name + cascade_name + RESULT_EXTENSION }; 
      
      auto system = func(cascade_factory, train, test, validate, result_file);
      auto result = system->experiment_classification_core();
      auto second_result = system->get_answers_for_test_classification_depth();
      auto train_data_set_result = system->get_answers_for_test_classification_depth(false);
      save_depth_to_file(RESULTS + "/" + std::to_string(counter) +"/depth-" + dataset_name + cascade_name + RESULT_EXTENSION, second_result);
      save_depth_to_file(RESULTS + "/" + std::to_string(counter) +"/depth-train-" + dataset_name + cascade_name + RESULT_EXTENSION, train_data_set_result);
      f1_scores.at(counter) = f1_score(result);
      avg_num_of_samples.at(counter) = system->get_number_of_rules();
      accuracies.at(counter) = accuracy(result);

      counter++;
   }
   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples);
   std::cout << "Main results saved to file " << RESULTS + RESULT_EXTENSION << std::endl;

   experiment_result to_return;
   to_return.f1_score = std::accumulate(f1_scores.begin(), f1_scores.end(), 0.0)/f1_scores.size();
   to_return.accuracy = std::accumulate(accuracies.begin(), accuracies.end(), 0.0)/accuracies.size();
   to_return.avg_num_of_samples = std::accumulate(avg_num_of_samples.begin(), avg_num_of_samples.end(), 0.0)/avg_num_of_samples.size();
   return to_return;
}

//void test_algorithm_simple(const std::string& dataset_name, const int repetitions, cascade cascade_of_nfs, std::function<std::unique_ptr<ksi::three_way_decision_nfs> (const cascade&, const std::string&, const std::string&, const std::string&)> func, std::string name)
//{
//   std::string RESULT_EXTENSION {".txt"};

//   const std::string EXPERIMENT           ("exp-006");
//   const std::string TYPE                 ("classification");
//   const std::string DATA_DIRECTORY       ("../data/" + EXPERIMENT + "/" + TYPE);
//   const std::string RESULTS_DIRECTORY    ("../results_lambda_testing/");

//   std::cout << "data set: " << dataset_name << std::endl;
//   std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

//   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
//   std::string TRAIN   (dataset + "/" + dataset_name + ".train");
//   std::string TEST    (dataset + "/" + dataset_name + ".test");
//   std::string RESULTS (results_dir +"/" + name );

//   std::vector<double> f1_scores(repetitions), avg_num_of_samples(repetitions);
//   for(auto i = 0; i < repetitions; ++i)
//   {
//      // And we run experiments:
//      std::string cascade_name;
//      for (const auto & p : cascade_of_nfs)
//         cascade_name += std::string{"-"} + p->get_nfs_name();
//      cascade_name += name;
//      cascade_name += std::string{"-"} + std::to_string(i);


//      std::string result_file { RESULTS + "/" + std::to_string(i) +"/results-" + dataset_name + cascade_name + RESULT_EXTENSION }; 
      
//      auto system = func(cascade_of_nfs, TRAIN, TEST, result_file);
//      std::cout << "\tmethod:    " << system->get_nfs_name() << std::endl;
//      auto result = system->experiment_classification(TRAIN, TEST, result_file);
//      auto second_result = system->get_answers_for_test_classification_depth();
//      auto train_data_set_result = system->get_answers_for_test_classification_depth(false);
//      save_depth_to_file(RESULTS + "/" + std::to_string(i) +"/depth-" + dataset_name + cascade_name + RESULT_EXTENSION, second_result);
//      save_depth_to_file(RESULTS + "/" + std::to_string(i) +"/depth-train-" + dataset_name + cascade_name + RESULT_EXTENSION, train_data_set_result);
//      std::cout << "\tResults saved to file " << result_file << std::endl << std::endl;
//      f1_scores.at(i) = f1_score(result);
//      avg_num_of_samples.at(i) = system->get_number_of_rules();
//   }
//   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples);
//   std::cout << "Main results saved to file " << RESULTS + RESULT_EXTENSION << std::endl;
//}
void ksi::exp_006::execute()
{
   std::vector<double> stop_criterion_percentages {0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05};
   const std::vector<double> non_commitment_widths{0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5};
   const std::string dataset_name{"bupa"};
   const int number_of_rules = datasets_rules.at(dataset_name);

   double best_f1_annbfis_increasing = 0.0;
   double best_stop_annbfis_increasing = 0.0;
   double best_width_annbfis_increasing = 0.0;

   double best_f1_annbfis_steady = 0.0;
   double best_stop_annbfis_steady = 0.0;
   double best_width_annbfis_steady = 0.0;

   double best_f1_tsk_increasing = 0.0;
   double best_stop_tsk_increasing = 0.0;
   double best_width_tsk_increasing = 0.0;

   double best_f1_tsk_steady = 0.0;
   double best_stop_tsk_steady = 0.0;
   double best_width_tsk_steady = 0.0;

   for (const auto & percentage : stop_criterion_percentages)
   {
      for (const auto & width : non_commitment_widths)
      {
         std::cout << "dataset: " << dataset_name
                   << ", stop percentage: " << percentage
                   << ", noncommitment width: " << width << std::endl;

         auto system_factory = [percentage, width](const std::function<cascade()> c,
                                                   const ksi::dataset& train,
                                                   const ksi::dataset& test,
                                                   const ksi::dataset& validate,
                                                   const std::string& result_file)
         {
            (void) validate;
            return std::make_shared<ksi::three_way_decision_nfs>(c(), train, test, result_file, width, percentage);
         };

         experiment_result annbfis_increasing_result {};
         experiment_result annbfis_steady_result {};
         experiment_result tsk_increasing_result {};
         experiment_result tsk_steady_result {};

         std::thread annbfis_increasing_thread([&]() {
            annbfis_increasing_result = run_cross_validation_for_dataset(
               dataset_name,
               [=](){ return create_anbfis_increasing_no_rules(number_of_rules); },
               system_factory,
               "ANNBFIS-INCREASING-SINGLE-WIDTH-stop-" + std::to_string(percentage) + "-width-" + std::to_string(width)
            );
         });

         std::thread annbfis_steady_thread([&]() {
            annbfis_steady_result = run_cross_validation_for_dataset(
               dataset_name,
               [=](){ return create_anbfis_constant_number_of_rules(number_of_rules); },
               system_factory,
               "ANNBFIS-STEADY-SINGLE-WIDTH-stop-" + std::to_string(percentage) + "-width-" + std::to_string(width)
            );
         });

         std::thread tsk_increasing_thread([&]() {
            tsk_increasing_result = run_cross_validation_for_dataset(
               dataset_name,
               [=](){ return create_tsk_increasing_no_rules(number_of_rules); },
               system_factory,
               "TSK-INCREASING-SINGLE-WIDTH-stop-" + std::to_string(percentage) + "-width-" + std::to_string(width)
            );
         });

         std::thread tsk_steady_thread([&]() {
            tsk_steady_result = run_cross_validation_for_dataset(
               dataset_name,
               [=](){ return create_tsk_constant_number_of_rules(number_of_rules); },
               system_factory,
               "TSK-STEADY-SINGLE-WIDTH-stop-" + std::to_string(percentage) + "-width-" + std::to_string(width)
            );
         });

         annbfis_increasing_thread.join();
         annbfis_steady_thread.join();
         tsk_increasing_thread.join();
         tsk_steady_thread.join();

         std::cout << "average f1 score (annbfis increasing): " << annbfis_increasing_result.f1_score << std::endl;
         std::cout << "average f1 score (annbfis steady): " << annbfis_steady_result.f1_score << std::endl;
         std::cout << "average f1 score (tsk increasing): " << tsk_increasing_result.f1_score << std::endl;
         std::cout << "average f1 score (tsk steady): " << tsk_steady_result.f1_score << std::endl;

         if (annbfis_increasing_result.f1_score > best_f1_annbfis_increasing)
         {
            best_f1_annbfis_increasing = annbfis_increasing_result.f1_score;
            best_stop_annbfis_increasing = percentage;
            best_width_annbfis_increasing = width;
         }

         if (annbfis_steady_result.f1_score > best_f1_annbfis_steady)
         {
            best_f1_annbfis_steady = annbfis_steady_result.f1_score;
            best_stop_annbfis_steady = percentage;
            best_width_annbfis_steady = width;
         }

         if (tsk_increasing_result.f1_score > best_f1_tsk_increasing)
         {
            best_f1_tsk_increasing = tsk_increasing_result.f1_score;
            best_stop_tsk_increasing = percentage;
            best_width_tsk_increasing = width;
         }

         if (tsk_steady_result.f1_score > best_f1_tsk_steady)
         {
            best_f1_tsk_steady = tsk_steady_result.f1_score;
            best_stop_tsk_steady = percentage;
            best_width_tsk_steady = width;
         }
      }
   }

   std::cout << "Best ANNBFIS increasing: stop=" << best_stop_annbfis_increasing
             << ", width=" << best_width_annbfis_increasing
             << ", f1=" << best_f1_annbfis_increasing << std::endl;
   std::cout << "Best ANNBFIS steady: stop=" << best_stop_annbfis_steady
             << ", width=" << best_width_annbfis_steady
             << ", f1=" << best_f1_annbfis_steady << std::endl;
   std::cout << "Best TSK increasing: stop=" << best_stop_tsk_increasing
             << ", width=" << best_width_tsk_increasing
             << ", f1=" << best_f1_tsk_increasing << std::endl;
   std::cout << "Best TSK steady: stop=" << best_stop_tsk_steady
             << ", width=" << best_width_tsk_steady
             << ", f1=" << best_f1_tsk_steady << std::endl;
}
