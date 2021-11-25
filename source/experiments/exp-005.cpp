/** @file */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
    
 
#include "../service/debug.h"
#include "../implications/imp-reichenbach.h"
#include "../tnorms/t-norm-product.h"
 
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../neuro-fuzzy/fubi-annbfis.h"
#include "../neuro-fuzzy/tsk_prototype.h"
#include "../neuro-fuzzy/annbfis_prototype.h"
#include "../neuro-fuzzy/fac_prototype_minkowski_regression.h"

#include "../auxiliary/roc.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/utility-math.h"

#include "../experiments/exp-005.h"

 


ksi::exp_005::exp_005()
{
}

 
void ksi::exp_005::classification()
{
    std::cout << "classification" << std::endl;
    ksi::imp_reichenbach implication;
    ksi::t_norm_product Tnorm;
    
    
    std::vector<ksi::roc_threshold> thresholds { ksi::roc_threshold::mean,
                                                 ksi::roc_threshold::minimal_distance, 
                                                 ksi::roc_threshold::youden
                                               };
    
    const std::string EXPERIMENT           ("exp-005");
    const std::string TYPE                 ("classification");
    const std::string DATA_DIRECTORY       ("data/" + EXPERIMENT + "/" + TYPE);
    const std::string RESULTS_DIRECTORY    ("results/" + EXPERIMENT + "/" + TYPE);
    
    const int NUMBER_OF_RULES = 5;
    const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
    const int NUMBER_OF_TUNING_ITERATIONS = 100;
    
    const bool NORMALISATION = false;
        
    const double ETA = 0.1;
    const double POSITIVE_CLASS_LABEL = 1.0;
    const double NEGATIVE_CLASS_LABEL = 0.0;
    
    
    // dataset
    std::string dataset_name { "haberman" };
    
    
    std::cout << "data set: " << dataset_name << std::endl;
    std::string dataset {DATA_DIRECTORY + "/" + dataset_name};

    std::string results_dir {RESULTS_DIRECTORY + "/" + dataset_name};
    std::string TRAIN   (dataset + "/" + dataset_name + ".train");
    std::string TEST    (dataset + "/" + dataset_name + ".test");
    std::string RESULTS (results_dir + "/results-" + dataset_name);

    // MA 
    {
        for (auto th : thresholds)  // for all thresholds
        {

            ksi::ma system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th);
            
            std::string threshold_name;
            switch(th)
            {
                case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
                case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
                case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
                default                                   : threshold_name = "something-wrong-has-happened"; break;
            }
            
            
            std::string result_file { RESULTS + "-" + system.get_nfs_name() + "-" + threshold_name }; 
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
        }
    }

    // TSK
    {
        for (auto th : thresholds)  // for all thresholds
        {

            ksi::tsk system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th);
            
            std::string threshold_name;
            switch(th)
            {
                case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
                case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
                case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
                default                                   : threshold_name = "something-wrong-has-happened"; break;
            }
            
            
            std::string result_file { RESULTS + "-" + system.get_nfs_name() + "-" + threshold_name }; 
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
        }
    }

    // ANNBFIS
    {
        for (auto th : thresholds)  // for all thresholds
        {

            ksi::annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th);
            
            std::string threshold_name;
            switch(th)
            {
                case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
                case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
                case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
                default                                   : threshold_name = "something-wrong-has-happened"; break;
            }
            
            
            std::string result_file { RESULTS + "-" + system.get_nfs_name() + "-" + threshold_name }; 
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
        }
    }

    // SUBSPACE_ANNBFIS    
    {
        for (auto th : thresholds)  // for all thresholds
        {

            ksi::subspace_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th);
            
            std::string threshold_name;
            switch(th)
            {
                case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
                case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
                case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
                default                                   : threshold_name = "something-wrong-has-happened"; break;
            }
            
            
            std::string result_file { RESULTS + "-" + system.get_nfs_name() + "-" + threshold_name }; 
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
        }
    }

    // FUBI_ANNBFIS
    {
        for (auto th : thresholds)  // for all thresholds
        {

            ksi::fubi_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE_CLASS_LABEL, NEGATIVE_CLASS_LABEL, th);
            
            
            std::string threshold_name;
            switch(th)
            {
                case ksi::roc_threshold::mean             : threshold_name = "mean";                         break;
                case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance";             break;
                case ksi::roc_threshold::youden           : threshold_name = "youden";                       break;
                default                                   : threshold_name = "something-wrong-has-happened"; break;
            }
            
            
            std::string result_file { RESULTS + "-" + system.get_nfs_name() + "-" + threshold_name }; 
            std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
            std::cout << "\tthreshold: " << threshold_name    << std::endl;
            system.experiment_classification(TRAIN, TEST, result_file);    
            std::cout << "\tResults saved to file " << result_file << std::endl;
            std::cout << std::endl;
        }
    }
    
}

void ksi::exp_005::regression()
{
    std::cout << std::endl;
    std::cout <<  "regression" << std::endl;
    
    ksi::imp_reichenbach implication;
    ksi::t_norm_product Tnorm;
    
    const std::string EXPERIMENT           ("exp-005");
    const std::string TYPE                 ("regression");
    const std::string DATA_DIRECTORY       ("data/" + EXPERIMENT + "/" + TYPE);
    const std::string RESULTS_DIRECTORY    ("results/" + EXPERIMENT + "/" + TYPE);

    const int NUMBER_OF_RULES = 5;
    const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
    const int NUMBER_OF_TUNING_ITERATIONS = 100;
    
    const bool NORMALISATION = false;
        
    const double ETA = 0.1;
    
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
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }

    // TSK
    {
        ksi::tsk system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }
    
    // ANNBFIS
    {
        ksi::annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }

    // SUBSPACE_ANNBFIS
    {
        ksi::subspace_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }

    // FUBI_ANNBFIS
    {
        ksi::fubi_annbfis system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }

    // PROTO_TSK
    {
        const double minkowski_coefficient { 2.0 };
        ksi::fac_prototype_minkowski_regression factory (minkowski_coefficient);
        ksi::tsk_prototype system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, factory);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }

    // PROTO_ANNBFIS
    {
        const double minkowski_coefficient { 2.0 };
        ksi::fac_prototype_minkowski_regression factory (minkowski_coefficient);
        ksi::annbfis_prototype system (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, ksi::imp_reichenbach(), factory);
        std::cout << "\tmethod:    " << system.get_nfs_name() << std::endl;
        std::string result_file { RESULTS + "-" + system.get_nfs_name() }; 
        system.experiment_regression(TRAIN, TEST, result_file);
        std::cout << "\tResults saved to file " << result_file << std::endl;
        std::cout << std::endl;
    }
}
 

void ksi::exp_005::execute()
{
   try
   {
      classification();
      regression();
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
