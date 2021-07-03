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
#include "../auxiliary/roc.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/utility-math.h"

#include "../experiments/exp-005.h"




ksi::exp_005::exp_005()
{
}

 
void ksi::exp_005::classification()
{
//          // classification 
//       
    std::cout << "classification" << std::endl;
    ksi::imp_reichenbach implication;
    ksi::t_norm_product Tnorm;
    
    
    std::vector<ksi::roc_threshold> thresholds { ksi::roc_threshold::mean /*,
                                                 ksi::roc_threshold::minimal_distance, 
                                                 ksi::roc_threshold::youden  */
                                               };
    
    const std::string EXPERIMENT ("exp-005");
    const std::string TYPE ("classification");
    const std::string DATA_DIRECTORY ("data/" + EXPERIMENT);
    const std::string RESULTS_DIRECTORY ("results/" + EXPERIMENT + "/" + TYPE);
    
    
    std::vector<std::string> datasets { "hab" };
 

for (auto p : datasets)
{
    std::string dataset {DATA_DIRECTORY + "/" + p};

    std::string results_dir {RESULTS_DIRECTORY + "/" + p};
    std::string TRAIN   (dataset + ".train");
    std::string TEST    (dataset + ".test");
    std::string RESULTS (results_dir + ".results");
    
    const int NUMBER_OF_RULES = 5;
    const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
    const int NUMBER_OF_TUNING_ITERATIONS = 100;
    const double ETA = 0.1;
    const bool NORMALISATION = false;
    const double POSITIVE = 2.0;
    const double NEGATIVE = 1.0;
    
    for (auto th : thresholds)
    {

 //       std::unique_ptr<ksi::neuro_fuzzy_system> MA (new ksi::ma (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE, NEGATIVE, th));

        std::unique_ptr<ksi::neuro_fuzzy_system> TSK (new ksi::tsk(NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, POSITIVE, NEGATIVE, th));

        std::unique_ptr<ksi::neuro_fuzzy_system> ANNBFIS (new ksi::annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE, NEGATIVE, th));

        std::unique_ptr<ksi::neuro_fuzzy_system> SUBSPACE_ANNBFIS(new ksi::subspace_annbfis(NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE, NEGATIVE, th));
        
        std::unique_ptr<ksi::neuro_fuzzy_system> FUBI_ANNBFIS (new ksi::fubi_annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication, POSITIVE, NEGATIVE, th));
        
        std::vector<std::unique_ptr<ksi::neuro_fuzzy_system>> systems;

     //   systems.push_back(std::move(MA));
     //   systems.push_back(std::move(TSK));
     //   systems.push_back(std::move(ANNBFIS));
     //   systems.push_back(std::move(SUBSPACE_ANNBFIS));
     //   systems.push_back(std::move(FUBI_ANNBFIS));
        
        std::string threshold_name;
        switch(th)
        {
          case ksi::roc_threshold::mean             : threshold_name = "mean"; break;
          case ksi::roc_threshold::minimal_distance : threshold_name = "minimal_distance"; break;
          case ksi::roc_threshold::youden           : threshold_name = "youden"; break;
          default : threshold_name = "something-wrong-has-happened"; break;
        }
        
        for (auto & p : systems)
        {
            debug(threshold_name);
            debug(p->get_nfs_name());
            p->experiment_classification(TRAIN, TEST, 
                                        RESULTS + "-" + p->get_nfs_name() + "-" + threshold_name);    
            
            
        }
    }
    }
}

void ksi::exp_005::regression()
{
    // regression 
    
    debug("regression");
    ksi::imp_reichenbach implication;
    ksi::t_norm_product Tnorm;
    
    const std::string EXPERIMENT ("exp-005");
    const std::string TYPE ("regression");
    const std::string DATA_DIRECTORY ("data/" + TYPE);
    const std::string RESULTS_DIRECTORY ("results/" + EXPERIMENT + "/" + TYPE);

    
    std::vector<std::pair<std::string,std::string>> datasets {
              {"leukocytes", "leukocytes"},
    };


 

    std::map<bool, // normalisation
                std::map<std::string, // dataset
                        std::map<std::string, // nfs 
                                std::map<int, // rules 
                                        std::map<double, // eta
                                                    std::pair<std::vector<double>, // train
                                                            std::vector<double>> // test
                                                    >>>>> wyniki;
                    

    const int NUMBER_OF_CLUSTERING_ITERATIONS = 100;
    const int NUMBER_OF_TUNING_ITERATIONS = 100;
        
   // std::string short_log_file_name {"./podsumowanie.short"}; 
   // std::string log_file_name {"./regression-error.log"}; 
        
        
    for (auto p : datasets)
    {
     //   std::ofstream short_log_file (short_log_file_name + "-" + p.first);
     //   std::ofstream log_file (log_file_name + "-" + p.first);

        
        debug(p.first);
        for (int iter = 0; iter < 13; iter++)
//         int iter = 0;
        {
            debug(iter);
            std::string dataset {DATA_DIRECTORY + "/" + p.first + "/" + p.second};

            std::string TRAIN   (dataset + ".data");
            std::string TEST    (dataset + ".test");
        
            for (const int NUMBER_OF_RULES : { 3, 4, 5, 6, 7, 8, 9 })
//             for (const int NUMBER_OF_RULES : { 6 })
            {
                debug(NUMBER_OF_RULES);
//                 for (const double ETA : { 0.1 })
                for (const double ETA : { 0.1, 0.01, 0.001, 0.0001, 0.00001 })
                {
                    debug(ETA);
    //                 const double ETA = 0.1;
        //             const bool NORMALISATION = false;
                    for (bool NORMALISATION : { true })
    //                 for (bool NORMALISATION : { true, false })    
                    {
                        debug(NORMALISATION);
                    
                        std::unique_ptr<ksi::neuro_fuzzy_system> MA (new ksi::ma (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm));
                        std::unique_ptr<ksi::neuro_fuzzy_system> TSK (new ksi::tsk(NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm));
                        std::unique_ptr<ksi::neuro_fuzzy_system> ANNBFIS (new ksi::annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication));
                        std::unique_ptr<ksi::neuro_fuzzy_system> SUBSPACE_ANNBFIS(new ksi::subspace_annbfis(NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication));
                        std::unique_ptr<ksi::neuro_fuzzy_system> FUBI_ANNBFIS (new ksi::fubi_annbfis (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, Tnorm, implication));
                        
                        std::vector<std::unique_ptr<ksi::neuro_fuzzy_system>> systems;

                        systems.push_back(std::move(MA));
                        systems.push_back(std::move(TSK));
                        systems.push_back(std::move(FUBI_ANNBFIS));
                        systems.push_back(std::move(SUBSPACE_ANNBFIS));
                        systems.push_back(std::move(ANNBFIS));
                    
                        std::string results_dir {RESULTS_DIRECTORY + "/norm-" + (NORMALISATION ? "on" : "off" ) + "/" + p.second /* + "/" + p.second*/};
                        std::string RESULTS (results_dir/* + ".results"*/);
                
                        
                        for (auto & sys : systems)
                        {
                            
                                auto nfs = sys->get_nfs_name();
                                debug(nfs);
                                std::stringstream ss;
                                ss << RESULTS << "/"     << nfs
                                            << "/r-"   << NUMBER_OF_RULES 
                                            << "/eta-" << ETA
                                            << "/" <<  p.second << "-iter-" << iter;
                                auto plik_wyjsciowy = ss.str();
                                
                            try 
                            {
                                auto wynik = sys->experiment_regression(TRAIN, TEST, plik_wyjsciowy);
    //                                     ksi::result wynik { 1.5 * ETA, 2 * ETA, 1.5 * ETA, 2 * ETA};
                                
                                wyniki[NORMALISATION][p.first][nfs][NUMBER_OF_RULES][ETA].first.push_back(wynik.rmse_train);
                                wyniki[NORMALISATION][p.first][nfs][NUMBER_OF_RULES][ETA].second.push_back(wynik.rmse_test);
                            }
                            catch (const ksi::exception & wyjatek)
                            {
/*                                log_file << "======================" << std::endl;
                                log_file << ksi::getDateTimeNow()    << std::endl;
                                log_file << "dataset:   " << p.first << std::endl;
                                log_file << "nfs:       " << nfs     << std::endl;
                                log_file << "rules:     " << NUMBER_OF_RULES << std::endl;
                                log_file << "eta:       " << ETA     << std::endl;
                                log_file << "norm:      " << std::boolalpha << NORMALISATION << std::endl;
                                log_file << wyjatek.what() << std::endl;
*/                            }
                        }
                    }
                }
            }
        
            // wypisanie wynikow po kazdym zbiorze danych
            
        } 
/*        
        std::ofstream s {"./podsumowanie-" + p.first};
    //         std::ostream & s = std::cout;
        for (auto iNorm : wyniki )
        {
            for (auto iDataset : iNorm.second)
            {
                for (auto iNfs : iDataset.second)
                {
                    s << "=====================================" << std::endl;
                    s << iDataset.first << std::endl;
                    s << iNfs.first     << std::endl;
    //                     s << std::endl;
                    s << "normalisation: " << std::boolalpha << iNorm.first << std::endl;
                    s << std::endl;
                    
                    // najpierw wypisuje wartosci eta
                    s << "eta ->";
                    for (auto iter = iNfs.second.begin()->second.begin(); iter != iNfs.second.begin()->second.end(); iter++)
                        s << "\t" << iter->first;
                    s << std::endl;
                    s << "rules" << std::endl;
                    
                    for (auto iRules : iNfs.second)
                    {
                        s << iRules.first << "\t";
                        for (auto iEta : iRules.second)
                        {
                            //s << iEta.second.first << "\t";
                            double srednia = ksi::utility_math::getAverage(iEta.second.first.begin(), iEta.second.first.end());
                            double odchylenie = ksi::utility_math::getStandardDeviation(iEta.second.first.begin(), iEta.second.first.end());
                            s << "(" << srednia << " +/- " << odchylenie << ")\t";
                            
                        }
                        s << "(rmse-train)";
                        s << std::endl << "\t";
                        for (auto iEta : iRules.second)
                        {
    //                                     s << iEta.second.second << "\t";
                            double srednia = ksi::utility_math::getAverage(iEta.second.second.begin(), iEta.second.second.end());
                            double odchylenie = ksi::utility_math::getStandardDeviation(iEta.second.second.begin(), iEta.second.second.end());
                            s << "(" << srednia << " +/- " << odchylenie << ")\t";
                            
                        }
                        s << "(rmse-test)";
                        s << std::endl << std::endl;
                    }
                }
            }
        }
        
        for (auto iNorm : wyniki )
        {
            for (auto iDataset : iNorm.second)
            {
                short_log_file << "=====================================" << std::endl;
                short_log_file << iDataset.first << std::endl;
                short_log_file << "normalisation: " << std::boolalpha << iNorm.first << std::endl;
                short_log_file << std::endl;
                    
                for (auto iNfs : iDataset.second)
                {
                    double mini = std::numeric_limits<double>::max();

                    for (auto iRules : iNfs.second)
                    {
                        for (auto iEta : iRules.second)
                        {
                            auto wartosci = iEta.second.second;
                            debug(wartosci);
                            
                            auto srednia = ksi::utility_math::getAverage(wartosci.begin(), wartosci.end());
                            
                            if (srednia < mini)
                                mini = srednia;
                        }    
                    }
                    
                    short_log_file << iNfs.first     << " : " << mini <<  std::endl;
                }
            }
        }
        
*/
    }

}

 
 

void ksi::exp_005::execute()
{
   try
   {
      classification();
     // regression();
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
