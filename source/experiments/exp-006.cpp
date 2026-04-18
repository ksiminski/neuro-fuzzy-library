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
#include <filesystem>
#include <iomanip>

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

using cascade = std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>;

const std::map<std::string, int> datasets_rules = 
   {
      {"haberman", 5},
   };

namespace
{
   const std::filesystem::path DATA_DIRECTORY {"../data/exp-005/classification"};

   ksi::dataset load_dataset(const std::string& dataset_name)
   {
      ksi::reader_complete reader;
      const std::filesystem::path dataset_directory = DATA_DIRECTORY / dataset_name;
      const std::filesystem::path train_file = dataset_directory / (dataset_name + ".train");
      const std::filesystem::path test_file = dataset_directory / (dataset_name + ".test");

      auto merged_dataset = reader.read(train_file.string());
      merged_dataset += reader.read(test_file.string());
      return merged_dataset;
   }
}



double f1_score(const ksi::result& result)
{
   return 2.0 * result.TestPositive2Positive / (2.0 * result.TestPositive2Positive + result.TestPositive2Negative + result.TestNegative2Positive);
}

double accuracy(const ksi::result& result)
{
   const double correct = static_cast<double>(result.TestPositive2Positive + result.TestNegative2Negative);
   const double total = static_cast<double>(result.TestPositive2Positive + result.TestPositive2Negative + result.TestNegative2Positive + result.TestNegative2Negative);
   return correct / total;
}

void save_to_file(const std::string& file_path, const std::vector<double>& f1_scores, const std::vector<double>& avg_num_samples, const std::vector<double>& accuracies)
{
   using namespace std::string_literals;
   assert(f1_scores.size() == avg_num_samples.size());
   assert(f1_scores.size() == accuracies.size());
   std::ofstream file(file_path);
   if (!file) throw std::runtime_error("Cannot open file: "s + file_path);
   for(auto i = 0; i < f1_scores.size(); ++i)
   {
      file << i << " " << f1_scores.at(i) << " " << avg_num_samples.at(i) << " " << accuracies.at(i) << std::endl;
   }
}
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
   cascade to_return(5);
   for(int i = 0; i < 5; ++i)   {
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
   cascade to_return(5);
   for (int i = 0; i < 5; ++i)
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
   cascade to_return(5);
   for(int i = 0; i < 5; ++i)
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
   cascade to_return(5);
   for (int i = 0; i < 5; ++i)
   {
      to_return.at(i) = std::make_shared<ksi::tsk> (NUMBER_OF_RULES + 2*i, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, threshold);
   }
   return to_return;
}

void save_depth_to_file(const std::string& file_path, const std::vector<std::tuple<std::vector<double>, std::size_t, std::size_t>>& answers, const ksi::dataset& original_dataset)
{
   using namespace std::string_literals;
   std::ofstream file(file_path);
   if (!file) throw std::runtime_error("Cannot open file: "s + file_path);
   const auto label_column = original_dataset.getNumberOfAttributes() - 1;
   if (answers.size() != original_dataset.getNumberOfData())
   {
      throw std::runtime_error("Size of answers does not match number of data items in original dataset for file: "s + file_path);
   }
   for(std::size_t i = 0; i < answers.size(); ++i)
   {
      const auto& answer = answers.at(i);
      for(const auto& val : std::get<0>(answer))
      {
         file << val << ",";
      }
      const auto cascade_level = std::get<1>(answer);
      const auto predicted_class = std::get<2>(answer);
      const auto expected_class = original_dataset.get(i, label_column);
      const auto is_correct = std::fabs(predicted_class - expected_class) < 1e-9;
      file << cascade_level << "," << predicted_class << "," << is_correct << std::endl;
   }
}
struct experiment_result{
   double f1_score;
   double accuracy;
   double avg_num_of_samples;
};

std::string format_width(const double width)
{
   std::ostringstream os;
   os << std::fixed << std::setprecision(2) << width;
   return os.str();
}

double mean(const std::vector<double>& values)
{
   if (values.empty())
      return 0.0;
   return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

double select_best_non_commitment_width_with_inner_cv(
   const std::string& dataset_name,
   const std::string& model_name,
   const int outer_fold,
   const ksi::dataset& outer_train_pool,
   const std::function<cascade()>& cascade_factory,
   const std::vector<double>& non_commitment_candidates,
   const double stop_criterion_percentage)
{
   const std::string INNER_RESULTS_DIRECTORY {"../results_inner_cv/"};
   const std::string inner_dir = INNER_RESULTS_DIRECTORY + "/" + dataset_name + "/" + model_name + "/outer-fold-" + std::to_string(outer_fold);
   std::filesystem::create_directories(inner_dir);

   const std::string summary_file = inner_dir + "/inner-summary.txt";
   std::ofstream summary(summary_file);
   if (!summary)
      throw std::runtime_error("Cannot open file: " + summary_file);

   ksi::reader_complete cr;
   ksi::train_validation_test_model inner_tvt(cr, 1);
   inner_tvt.split(outer_train_pool, 3);

   double best_width = non_commitment_candidates.front();
   double best_mean_f1 = -1.0;

   for (const auto width : non_commitment_candidates)
   {
      std::vector<double> inner_f1_scores;
      std::vector<double> inner_accuracies;
      int inner_fold = 0;

      for (const auto& [inner_train, inner_validate, inner_test] : inner_tvt)
      {
         auto merged_inner_train = inner_train;
         merged_inner_train += inner_validate;

         const std::string fold_dir = inner_dir + "/inner-fold-" + std::to_string(inner_fold);
         std::filesystem::create_directories(fold_dir);
         const std::string result_file = fold_dir + "/inner-width-" + format_width(width) + ".txt";

         auto system = std::make_shared<ksi::three_way_decision_nfs>(
            cascade_factory(),
            merged_inner_train,
            inner_test,
            result_file,
            width,
            stop_criterion_percentage);

         const auto result = system->experiment_classification_core();
         inner_f1_scores.push_back(f1_score(result));
         inner_accuracies.push_back(accuracy(result));
         ++inner_fold;
      }

      const double current_mean_f1 = mean(inner_f1_scores);
      const double current_mean_accuracy = mean(inner_accuracies);
      summary << "width=" << width
              << " mean_f1=" << current_mean_f1
              << " mean_accuracy=" << current_mean_accuracy
              << std::endl;

      if (current_mean_f1 > best_mean_f1)
      {
         best_mean_f1 = current_mean_f1;
         best_width = width;
      }
   }

   summary << "selected_width=" << best_width << " selected_mean_f1=" << best_mean_f1 << std::endl;
   return best_width;
}

experiment_result run_outer_cv_with_inner_width_selection(
   const std::string& dataset_name,
   const std::function<cascade()>& cascade_factory,
   const std::string& model_name,
   const double stop_criterion_percentage,
   const std::vector<double>& non_commitment_candidates)
{
   const std::string RESULT_EXTENSION {".txt"};
   const std::string RESULTS_DIRECTORY ("../results/");

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string RESULTS (results_dir + "/" + model_name + "-stop-" + std::to_string(stop_criterion_percentage));

   ksi::reader_complete cr;
   ksi::train_validation_test_model tvt(cr, 1);

   const int chunks {9};
   tvt.split(load_dataset(dataset_name), chunks);

   std::filesystem::create_directories(RESULTS);

   std::vector<double> f1_scores(chunks), avg_num_of_samples(chunks), accuracies(chunks), selected_widths(chunks);
   int counter = 0;

   for (const auto& [train, validate, test] : tvt)
   {
      auto outer_train_pool = train;
      outer_train_pool += validate;
      const auto selected_width = select_best_non_commitment_width_with_inner_cv(
         dataset_name,
         model_name,
         counter,
         outer_train_pool,
         cascade_factory,
         non_commitment_candidates,
         stop_criterion_percentage);

      selected_widths.at(counter) = selected_width;

      std::string cascade_name;
      cascade_name += std::string{"-"} + std::to_string(counter);
      std::string result_file {
         RESULTS + "/" + std::to_string(counter) + "/results-" + dataset_name + cascade_name + "-selected-width-" + format_width(selected_width) + RESULT_EXTENSION
      };

      auto system = std::make_shared<ksi::three_way_decision_nfs>(
         cascade_factory(),
         outer_train_pool,
         test,
         result_file,
         selected_width,
         stop_criterion_percentage);

      const auto result = system->experiment_classification_core();
      const auto second_result = system->get_answers_for_test_classification_depth();
      save_depth_to_file(RESULTS + "/" + std::to_string(counter) + "/depth-test-" + dataset_name + cascade_name + RESULT_EXTENSION, second_result, test);

      f1_scores.at(counter) = f1_score(result);
      avg_num_of_samples.at(counter) = system->get_number_of_rules();
      accuracies.at(counter) = accuracy(result);
      ++counter;
   }

   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples, accuracies);

   std::ofstream selected_widths_file(RESULTS + "-selected-widths" + RESULT_EXTENSION);
   if (!selected_widths_file)
      throw std::runtime_error("Cannot open file: " + RESULTS + "-selected-widths" + RESULT_EXTENSION);

   for (int fold = 0; fold < chunks; ++fold)
   {
      selected_widths_file << fold << " " << selected_widths.at(fold) << std::endl;
   }

   experiment_result to_return;
   to_return.f1_score = mean(f1_scores);
   to_return.accuracy = mean(accuracies);
   to_return.avg_num_of_samples = mean(avg_num_of_samples);
   return to_return;
}

experiment_result run_cross_validation_for_dataset(const std::string& dataset_name, std::function<cascade()> cascade_factory, std::function<std::shared_ptr<ksi::three_way_decision_nfs> (const std::function<cascade()>, const ksi::dataset&, const ksi::dataset&, const ksi::dataset&, const std::string&)> func, std::string name)
{
   std::string RESULT_EXTENSION {".txt"};
   const std::string RESULTS_DIRECTORY    ("../results/");

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string RESULTS (results_dir +"/" + name );

   ksi::reader_complete cr;
   ksi::train_validation_test_model tvt(cr, 4);

   const int chunks { 9 };
   tvt.split(load_dataset(dataset_name), chunks);

   int counter { 0 };
   std::vector<double> f1_scores(chunks), avg_num_of_samples(chunks), accuracies(chunks);
   for (const auto & [train, validate, test] : tvt)
   {
      std::string cascade_name;
      cascade_name += std::string{"-"} + std::to_string(counter);


      std::string result_file { RESULTS + "/" + std::to_string(counter) +"/results-" + dataset_name + cascade_name + RESULT_EXTENSION }; 
      
      auto system = func(cascade_factory, train, test, validate, result_file);
      auto result = system->experiment_classification_core();
      auto second_result = system->get_answers_for_test_classification_depth();
      save_depth_to_file(RESULTS + "/" + std::to_string(counter) +"/depth-test-" + dataset_name + cascade_name + RESULT_EXTENSION, second_result, test);
      f1_scores.at(counter) = f1_score(result);
      avg_num_of_samples.at(counter) = system->get_number_of_rules();
      accuracies.at(counter) = accuracy(result);

      counter++;
   }
   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples, accuracies);
   std::cout << "Main results saved to file " << RESULTS + RESULT_EXTENSION << std::endl;

   experiment_result to_return;
   to_return.f1_score = std::accumulate(f1_scores.begin(), f1_scores.end(), 0.0)/f1_scores.size();
   to_return.accuracy = std::accumulate(accuracies.begin(), accuracies.end(), 0.0)/accuracies.size();
   to_return.avg_num_of_samples = std::accumulate(avg_num_of_samples.begin(), avg_num_of_samples.end(), 0.0)/avg_num_of_samples.size();
   return to_return;
}

experiment_result run_cross_validation_for_single_system_dataset(
   const std::string& dataset_name,
   const std::function<std::shared_ptr<ksi::neuro_fuzzy_system>()>& system_factory,
   std::string name)
{
   std::string RESULT_EXTENSION {".txt"};
   const std::string RESULTS_DIRECTORY    ("../results/");

   std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
   std::string RESULTS (results_dir + "/" + name );

   ksi::reader_complete cr;
   ksi::train_validation_test_model tvt(cr, 4);

   const int chunks {9};
   tvt.split(load_dataset(dataset_name), chunks);

   std::filesystem::create_directories(results_dir);

   int counter {0};
   std::vector<double> f1_scores(chunks), avg_num_of_samples(chunks), accuracies(chunks);
   for (const auto& [train, validate, test] : tvt)
   {
      auto merged_train = train;
      merged_train += validate;

      std::string fold_dir {RESULTS + "/" + std::to_string(counter)};
      std::filesystem::create_directories(fold_dir);

      std::string result_file {fold_dir + "/results-" + dataset_name + "-fold-" + std::to_string(counter) + RESULT_EXTENSION};

      auto system = system_factory();
      auto result = system->experiment_classification(merged_train, test, result_file);
      f1_scores.at(counter) = f1_score(result);
      avg_num_of_samples.at(counter) = system->get_number_of_rules();
      accuracies.at(counter) = accuracy(result);

      std::vector<std::tuple<std::vector<double>, std::size_t, std::size_t>> single_system_depth_answers;
      const auto test_answers = system->get_answers_for_test_classification();
      single_system_depth_answers.reserve(test_answers.size());
      for (const auto& [expected_class, elaborated_numeric, elaborated_class] : test_answers)
      {
         (void)expected_class;
         const std::size_t predicted_class = elaborated_class >= 0.5 ? 1u : 0u;
         single_system_depth_answers.emplace_back(std::vector<double>{elaborated_numeric}, 1u, predicted_class);
      }
      save_depth_to_file(
         fold_dir + "/depth-test-" + dataset_name + "-fold-" + std::to_string(counter) + RESULT_EXTENSION,
         single_system_depth_answers,
         test);
      ++counter;
   }

   save_to_file(RESULTS + RESULT_EXTENSION, f1_scores, avg_num_of_samples, accuracies);
   std::cout << "Main results saved to file " << RESULTS + RESULT_EXTENSION << std::endl;

   experiment_result to_return;
   to_return.f1_score = std::accumulate(f1_scores.begin(), f1_scores.end(), 0.0)/f1_scores.size();
   to_return.accuracy = std::accumulate(accuracies.begin(), accuracies.end(), 0.0)/accuracies.size();
   to_return.avg_num_of_samples = std::accumulate(avg_num_of_samples.begin(), avg_num_of_samples.end(), 0.0)/avg_num_of_samples.size();
   return to_return;
}

void ksi::exp_006::execute_nested_cv_for_width_selection()
{
   struct stop_criteria_per_architecture
   {
      double annbfis_increasing;
      double annbfis_steady;
      double tsk_increasing;
      double tsk_steady;
   };

   const stop_criteria_per_architecture stop_criteria
   {
      0.25,
      0.25,
      0.25,
      0.25
   };

   const std::vector<double> non_commitment_candidates {0.05, 0.10, 0.15, 0.20, 0.25, 0.30};

   for (const auto& [dataset_name, number_of_rules] : datasets_rules)
   {
      std::cout << "nested cv dataset: " << dataset_name << std::endl;

      experiment_result annbfis_increasing {};
      experiment_result annbfis_steady {};
      experiment_result tsk_increasing {};
      experiment_result tsk_steady {};

      std::thread annbfis_increasing_thread([&]() {
         annbfis_increasing = run_outer_cv_with_inner_width_selection(
            dataset_name,
            [=](){ return create_anbfis_increasing_no_rules(number_of_rules); },
            "ANNBFIS-INCREASING-WIDENING-INNERCV",
            stop_criteria.annbfis_increasing,
            non_commitment_candidates);
      });

      std::thread annbfis_steady_thread([&]() {
         annbfis_steady = run_outer_cv_with_inner_width_selection(
            dataset_name,
            [=](){ return create_anbfis_constant_number_of_rules(number_of_rules); },
            "ANNBFIS-STEADY-WIDENING-INNERCV",
            stop_criteria.annbfis_steady,
            non_commitment_candidates);
      });

      std::thread tsk_increasing_thread([&]() {
         tsk_increasing = run_outer_cv_with_inner_width_selection(
            dataset_name,
            [=](){ return create_tsk_increasing_no_rules(number_of_rules); },
            "TSK-INCREASING-WIDENING-INNERCV",
            stop_criteria.tsk_increasing,
            non_commitment_candidates);
      });

      std::thread tsk_steady_thread([&]() {
         tsk_steady = run_outer_cv_with_inner_width_selection(
            dataset_name,
            [=](){ return create_tsk_constant_number_of_rules(number_of_rules); },
            "TSK-STEADY-WIDENING-INNERCV",
            stop_criteria.tsk_steady,
            non_commitment_candidates);
      });

      annbfis_increasing_thread.join();
      annbfis_steady_thread.join();
      tsk_increasing_thread.join();
      tsk_steady_thread.join();

      std::cout << "nested summary for " << dataset_name << std::endl;
      std::cout << "annbfis increasing f1: " << annbfis_increasing.f1_score << ", accuracy: " << annbfis_increasing.accuracy << std::endl;
      std::cout << "annbfis steady f1: " << annbfis_steady.f1_score << ", accuracy: " << annbfis_steady.accuracy << std::endl;
      std::cout << "tsk increasing f1: " << tsk_increasing.f1_score << ", accuracy: " << tsk_increasing.accuracy << std::endl;
      std::cout << "tsk steady f1: " << tsk_steady.f1_score << ", accuracy: " << tsk_steady.accuracy << std::endl;
   }
}

void ksi::exp_006::execute_single_system_cv()
{
   const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
   const int NUMBER_OF_TUNING_ITERATIONS = 100;
   const bool NORMALISATION = false;
   const double ETA = 0.001;
   const double POSITIVE_CLASS_LABEL = 1.0;
   const double NEGATIVE_CLASS_LABEL = 0.0;
   const ksi::roc_threshold threshold = ksi::roc_threshold::youden;

   for (const auto& [dataset_name, number_of_rules] : datasets_rules)
   {
      std::cout << "single-system dataset: " << dataset_name << std::endl;

      auto annbfis_factory = [=]()
      {
         return std::make_shared<ksi::annbfis>(
            number_of_rules,
            NUMBER_OF_CLUSTERING_ITERATIONS,
            NUMBER_OF_TUNING_ITERATIONS,
            ETA,
            NORMALISATION,
            ksi::t_norm_product{},
            ksi::imp_reichenbach{},
            POSITIVE_CLASS_LABEL,
            NEGATIVE_CLASS_LABEL,
            threshold);
      };

      auto tsk_factory = [=]()
      {
         return std::make_shared<ksi::tsk>(
            number_of_rules,
            NUMBER_OF_CLUSTERING_ITERATIONS,
            NUMBER_OF_TUNING_ITERATIONS,
            ETA,
            NORMALISATION,
            ksi::t_norm_product{},
            POSITIVE_CLASS_LABEL,
            NEGATIVE_CLASS_LABEL,
            threshold);
      };

      const auto annbfis_result = run_cross_validation_for_single_system_dataset(
         dataset_name,
         annbfis_factory,
         "ANNBFIS-SINGLE-CV");

      const auto tsk_result = run_cross_validation_for_single_system_dataset(
         dataset_name,
         tsk_factory,
         "TSK-SINGLE-CV");

      std::cout << "single-system summary for " << dataset_name << std::endl;
      std::cout << "annbfis f1: " << annbfis_result.f1_score << ", accuracy: " << annbfis_result.accuracy << ", avg rules: " << annbfis_result.avg_num_of_samples << std::endl;
      std::cout << "tsk f1: " << tsk_result.f1_score << ", accuracy: " << tsk_result.accuracy << ", avg rules: " << tsk_result.avg_num_of_samples << std::endl;
   }
}

void ksi::exp_006::execute()
{
   struct stop_criteria_per_architecture
   {
      double annbfis_increasing;
      double annbfis_steady;
      double tsk_increasing;
      double tsk_steady;
   };

   const stop_criteria_per_architecture meta_stop {0.25, 0.25, 0.25, 0.25};

   const stop_criteria_per_architecture widening_stop {0.25, 0.25, 0.25, 0.25};

   const std::vector<double> non_commitment_widths {0.1, 0.15, 0.2, 0.25, 0.3};

   for (const auto & [dataset_name, number_of_rules] : datasets_rules)
   {
      std::cout << "dataset: " << dataset_name << std::endl;

      experiment_result meta_annbfis_increasing_result {};
      experiment_result meta_annbfis_steady_result {};
      experiment_result meta_tsk_increasing_result {};
      experiment_result meta_tsk_steady_result {};

      experiment_result widening_annbfis_increasing_result {};
      experiment_result widening_annbfis_steady_result {};
      experiment_result widening_tsk_increasing_result {};
      experiment_result widening_tsk_steady_result {};

      std::thread meta_annbfis_increasing_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto primary = c();
            auto meta = primary;
            meta.pop_back();
            return std::make_shared<ksi::three_way_decision_nfs_meta>(primary, meta, train, validate, test, result_file, meta_stop.annbfis_increasing);
         };

         meta_annbfis_increasing_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_anbfis_increasing_no_rules(number_of_rules); },
            system_factory,
            "ANNBFIS-INCREASING-META-stop-" + std::to_string(meta_stop.annbfis_increasing)
         );
      });

      std::thread meta_annbfis_steady_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto primary = c();
            auto meta = primary;
            meta.pop_back();
            return std::make_shared<ksi::three_way_decision_nfs_meta>(primary, meta, train, validate, test, result_file, meta_stop.annbfis_steady);
         };

         meta_annbfis_steady_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_anbfis_constant_number_of_rules(number_of_rules); },
            system_factory,
            "ANNBFIS-STEADY-META-stop-" + std::to_string(meta_stop.annbfis_steady)
         );
      });

      std::thread meta_tsk_increasing_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto primary = c();
            auto meta = primary;
            meta.pop_back();
            return std::make_shared<ksi::three_way_decision_nfs_meta>(primary, meta, train, validate, test, result_file, meta_stop.tsk_increasing);
         };

         meta_tsk_increasing_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_tsk_increasing_no_rules(number_of_rules); },
            system_factory,
            "TSK-INCREASING-META-stop-" + std::to_string(meta_stop.tsk_increasing)
         );
      });

      std::thread meta_tsk_steady_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto primary = c();
            auto meta = primary;
            meta.pop_back();
            return std::make_shared<ksi::three_way_decision_nfs_meta>(primary, meta, train, validate, test, result_file, meta_stop.tsk_steady);
         };

         meta_tsk_steady_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_tsk_constant_number_of_rules(number_of_rules); },
            system_factory,
            "TSK-STEADY-META-stop-" + std::to_string(meta_stop.tsk_steady)
         );
      });

      std::thread widening_annbfis_increasing_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto merged_train = train;
            merged_train += validate;
            return std::make_shared<ksi::three_way_decision_nfs>(c(), merged_train, test, result_file, non_commitment_widths, widening_stop.annbfis_increasing);
         };

         widening_annbfis_increasing_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_anbfis_increasing_no_rules(number_of_rules); },
            system_factory,
            "ANNBFIS-INCREASING-WIDENING-stop-" + std::to_string(widening_stop.annbfis_increasing)
         );
      });

      std::thread widening_annbfis_steady_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto merged_train = train;
            merged_train += validate;
            return std::make_shared<ksi::three_way_decision_nfs>(c(), merged_train, test, result_file, non_commitment_widths, widening_stop.annbfis_steady);
         };

         widening_annbfis_steady_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_anbfis_constant_number_of_rules(number_of_rules); },
            system_factory,
            "ANNBFIS-STEADY-WIDENING-stop-" + std::to_string(widening_stop.annbfis_steady)
         );
      });

      std::thread widening_tsk_increasing_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto merged_train = train;
            merged_train += validate;
            return std::make_shared<ksi::three_way_decision_nfs>(c(), merged_train, test, result_file, non_commitment_widths, widening_stop.tsk_increasing);
         };

         widening_tsk_increasing_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_tsk_increasing_no_rules(number_of_rules); },
            system_factory,
            "TSK-INCREASING-WIDENING-stop-" + std::to_string(widening_stop.tsk_increasing)
         );
      });

      std::thread widening_tsk_steady_thread([&]() {
         auto system_factory = [&](const std::function<cascade()> c, const ksi::dataset& train, const ksi::dataset& test, const ksi::dataset& validate, const std::string& result_file)
         {
            auto merged_train = train;
            merged_train += validate;
            return std::make_shared<ksi::three_way_decision_nfs>(c(), merged_train, test, result_file, non_commitment_widths, widening_stop.tsk_steady);
         };

         widening_tsk_steady_result = run_cross_validation_for_dataset(
            dataset_name,
            [=](){ return create_tsk_constant_number_of_rules(number_of_rules); },
            system_factory,
            "TSK-STEADY-WIDENING-stop-" + std::to_string(widening_stop.tsk_steady)
         );
      });

      meta_annbfis_increasing_thread.join();
      meta_annbfis_steady_thread.join();
      meta_tsk_increasing_thread.join();
      meta_tsk_steady_thread.join();
      widening_annbfis_increasing_thread.join();
      widening_annbfis_steady_thread.join();
      widening_tsk_increasing_thread.join();
      widening_tsk_steady_thread.join();

      std::cout << "summary for " << dataset_name << std::endl;
      std::cout << "meta annbfis increasing f1: " << meta_annbfis_increasing_result.f1_score << std::endl;
      std::cout << "meta annbfis steady f1: " << meta_annbfis_steady_result.f1_score << std::endl;
      std::cout << "meta tsk increasing f1: " << meta_tsk_increasing_result.f1_score << std::endl;
      std::cout << "meta tsk steady f1: " << meta_tsk_steady_result.f1_score << std::endl;
      std::cout << "widening annbfis increasing f1: " << widening_annbfis_increasing_result.f1_score << std::endl;
      std::cout << "widening annbfis steady f1: " << widening_annbfis_steady_result.f1_score << std::endl;
      std::cout << "widening tsk increasing f1: " << widening_tsk_increasing_result.f1_score << std::endl;
      std::cout << "widening tsk steady f1: " << widening_tsk_steady_result.f1_score << std::endl;
   }
   execute_single_system_cv();
   execute_nested_cv_for_width_selection();
}
