/** @file */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric> // std::iota
 

#include "../dissimilarities/dissimilarity.h"
#include "../dissimilarities/dis-huber.h"
#include "../dissimilarities/dis-linear.h"
#include "../dissimilarities/dis-log.h"
#include "../dissimilarities/dis-square.h"
#include "../dissimilarities/dis-log-linear.h"
#include "../dissimilarities/dis-sigmoidal.h"
#include "../dissimilarities/dis-sigmoidal-linear.h"
#include "../descriptors/descriptor.h"
#include "../owas/owa.h" 
#include "../owas/plowa.h"
#include "../owas/sowa.h"
#include "../owas/uowa.h"
#include "../partitions/rfcm.h"
#include "../partitions/rfcom.h"
#include "../partitions/rsfcm.h"
#include "../readers/reader-complete.h"
#include "../readers/reader-incomplete.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-imputer-median.h"
#include "../common/data-modifier-imputer-average.h" 
#include "../common/data-modifier-imputer-knn-median.h"
#include "../common/data-modifier-imputer-knn-average.h"
#include "../common/data-modifier-imputer-values-from-knn.h"
#include "../common/data-modifier-marginaliser.h"
#include "../common/data-modifier-imputer-median.h"
#include "../auxiliary/matrix.h"

#include "../auxiliary/utility-string.h"

#include "../experiments/exp-006.h"

#include <fstream>
#include <map>

void ksi::exp_006::execute()
{
   try
   {  
      /// @todo Jak dobrać parametry dla Hubera, sigmoidal itd?
      /// @todo zbiory z różną liczbę danych nietypowych
 
      // First I try to find the best dissimilarity function.
      //exp_6_dissimilarity_function();
      
      // the best imputer:
      //exp_6_influence_of_imputer_on_cluster_centres();
      
     // exp_6_jeden_jedyny_eksperyment();
      exp_6_all();
      
    }
   catch (...)
   {
       
         
      throw;
   }
   
   return;
}

std::pair<std::vector<std::vector<double>>, double>
ksi::exp_006::bestFrobenius ( 
    const std::vector<std::vector<double>> & original, 
    const std::vector<std::vector<double>> & elaborated)
{
   try 
   {
      if (original.size() != elaborated.size())
         throw std::string ("The numbers of clusters do not match!");
      
      auto nClusters = original.size();
      std::vector<std::size_t> order (nClusters);
      std::iota (order.begin(), order.end(), 0);
      
      Matrix<double> mPerfectLocalisations (original);
      
      Matrix<double> bestElaboratedLocalisation (elaborated);
      double bestFrobenius = std::numeric_limits<double>::max();
      
      do 
      {
         std::vector<std::vector<double>> permutation_of_clusters;
         for (std::size_t i = 0; i < elaborated.size(); i++)
            permutation_of_clusters.push_back(elaborated[order[i]]);
      
         Matrix<double> mElaboratedLocalisations(permutation_of_clusters);
         
         double frob = (mElaboratedLocalisations - mPerfectLocalisations).Frobenius_norm();
         
         if (frob < bestFrobenius)
         {
            bestFrobenius = frob;
            bestElaboratedLocalisation = mElaboratedLocalisations;
         }
         
      } while (std::next_permutation(order.begin(), order.end()));
      
      return { bestElaboratedLocalisation.to2DimVector(), bestFrobenius };
   }
   CATCH;
}

void ksi::exp_006::exp_6_jeden_jedyny_eksperyment()
{
    try
   {
      {
         const int REPETITIONS = 13;
         const int INDEX_MIN = 0;
         const int INDEX_Q1  = (REPETITIONS - 1) / 4;
         const int INDEX_MED = (REPETITIONS - 1) / 2;
         const int INDEX_Q3  = 2 * (REPETITIONS - 1) / 4;
         const int INDEX_MAX = REPETITIONS - 1;
         
         const int K_a  =  3;
         const int K_b  =  5;
         const int K_c  = 10;
         
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 6.0;
         const double beta  = 1.0;
         const double delta = 1.0;
         
         const bool useMarginalisedDatasetForClusterCentres = false;
         
         const std::vector<std::vector<double>> perfectLocalisations 
               { {5 , 5}, {5, 1}, {1, 5}};
               
         const int NUMBER_OF_ATTRIBUTES = 2;
         const int PRECISION = 10;
         
         const std::string from (" ");
         const std::string to   ("_");
 
         std::string dataDir ("dane");
         std::string resultsDir ("results");
         
         std::string directory ("exp-006-jeden-out");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         
//          std::vector<std::string> outliers { "10"};
        std::vector<std::string> outliers { "00", "01", "02", "05", "10", "20", "30", "40", "50"  };

//         std::vector<std::string> missing  { "0.00"};
        std::vector<std::string> missing  { "0.00", "0.01", "0.02", "0.05", "0.10", "0.20", "0.50"  };

         std::vector<ksi::dissimilarity *> dissimilarities = 
         {  
//             new ksi::dis_square(),
//             new ksi::dis_linear(),
//             new ksi::dis_huber(delta),
//             new ksi::dis_log(), 
            new ksi::dis_log_linear() //,
//             new ksi::dis_sigmoidal(alpha, beta),
//             new ksi::dis_sigmoidal_linear(alpha, beta)
         };

         std::vector<ksi::data_modifier *> imputers =
         {
            new ksi::data_modifier_marginaliser(),
            new ksi::data_modifier_imputer_average(),
            new ksi::data_modifier_imputer_median(), 
            new ksi::data_modifier_imputer_knn_average(K_a),
            new ksi::data_modifier_imputer_knn_median(K_a),
            new ksi::data_modifier_imputer_values_from_knn(K_a),
            new ksi::data_modifier_imputer_knn_average(K_b),
            new ksi::data_modifier_imputer_knn_median(K_b),
            new ksi::data_modifier_imputer_values_from_knn(K_b),
            new ksi::data_modifier_imputer_knn_average(K_c),
            new ksi::data_modifier_imputer_knn_median(K_c),
            new ksi::data_modifier_imputer_values_from_knn(K_c)
         };
         
         
         ksi::data_modifier_marginaliser marg; 

                                 
         std::string allresults (resultsDir + "/" + directory + "/all-results");
         std::ofstream file_allresults (allresults);
         file_allresults << "#  dissimilarity owa imputer outliers missing repetition Frobenius" << std::endl << std::endl;
         
         std::map<std::string,   // dissimilarity
          std::map<std::string,   // owa
           std::map<std::string,   // imputer
            std::map<std::string,   // outliers
             std::map<std::string,   // missing 
              std::vector<double>  // the best Frobenius in repetitions
              >>>>> ElaboratedResults;
         
         for (auto out : outliers)
         {
            for (auto mis : missing)
            {
               // exp-006-a-o00-m0.00
               std::string file ("exp-006-jeden-o" + out + "-m" + mis);
               std::string data (dataDir + "/" + directory + "/" + file);
               std::string results (resultsDir + "/" + directory + "/" + file);
               
               ksi::reader_incomplete input;
               auto DataSet = input.read(data);
               auto number_of_items = DataSet.getNumberOfData();
               
               
               std::vector<ksi::owa *> owas = 
               {
                  new ksi::uowa(),
                  new ksi::sowa(number_of_items, PC, PA),
                  new ksi::plowa(number_of_items, PC, PL)
               };  
                
               for (auto d : dissimilarities)
               {
                  auto str_dissim = ksi::utility_string::replaceString(d->print(), from, to);
                  
                  for (auto o : owas)
                  {
                     auto str_owa = ksi::utility_string::replaceString(o->print(), from, to);
                     
                     for (auto i : imputers)
                     {
                        auto str_imp = ksi::utility_string::replaceString(i->print(), from, to);
                        
                        for (int r = 0; r < REPETITIONS; r++)
                        {
                        
                           std::string method = std::string("-") + str_dissim + 
                                                std::string("-") + str_owa +
                                                std::string("-") + str_imp + 
                                                std::string("-o-") + out + 
                                                std::string("-m-") + mis +
                                                std::string("-") + std::to_string(r)
                                                ;
                           method = ksi::utility_string::replaceString(method, from, to);                     
                           debug(method);
                                                      
                           ksi::rfcom algorithm (*i, marg, *d, *o, useMarginalisedDatasetForClusterCentres);
                  
                           algorithm.setEpsilonForFrobeniusNorm(EPSILON);
                           algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

                           auto Partition = algorithm.doPartition(DataSet);
                           
                           std::vector<std::vector<double>> elaboratedLocalisations;
                           for (int c = 0; c < NUMBER_OF_CLUSTERS; c++)
                           {
                              std::vector<double> clusterLocalisation;
                              auto cluster = Partition.getCluster(c);
                              for (int a = 0; a < NUMBER_OF_ATTRIBUTES; a++)
                              {
                                 auto d = cluster->getAddressOfDescriptor(a);
                                 // here descriptor has three parameters: 
                                 // core, lower fuzzyfication, upper fuzzyfication
                                 auto core = d->getCoreMean();
                                 clusterLocalisation.push_back(core);                           
                              }
                              elaboratedLocalisations.push_back(clusterLocalisation);
                           }
                           
                           auto BestLocalisationBestFrobenius =
                           bestFrobenius(perfectLocalisations, elaboratedLocalisations);
                           
                           ElaboratedResults[d->print()][o->print()][i->print()][out][mis].push_back(BestLocalisationBestFrobenius.second);
                           
                           // OK. Now I have to elaborate a Frobenius norm 
                           // for each permutation of clusters -- I do not 
                           // know the sequence they are elaborated.
                           
                           /// ................. 
                           std::ofstream file (results + method);
                           file << "EXPERIMENT" << std::endl;
                           file << std::endl;
                           
                           file << "dissimilarity: " << str_dissim << std::endl;
                           file << "owa:           " << str_owa    << std::endl;
                           file << "imputer:       " << str_imp    << std::endl;
                           file << "outliers:      " << out        << std::endl;
                           file << "missing ratio: " << mis        << std::endl;
                           file << std::endl;
                           
                           
                           file << "partition" << std::endl;
                           file << "=========" << std::endl;
                           file << std::endl;
                           file << Partition << std::endl;
                           file << std::endl;
                           
                           file << "best localisation" << std::endl;
                           file << "=================" << std::endl;
                           file << "Frobenius norm:  " << BestLocalisationBestFrobenius.second << std::endl;
                           file << std::endl;
                           file << std::endl;
                           file << BestLocalisationBestFrobenius.first << std::endl;
                           
                           file << std::endl;
                           file << "typicalities" << std::endl;
                           file << "============" << std::endl;
                           file << std::endl;
                           file << DataSet << std::endl;
                           
                           file.close();
                           
                           file_allresults << str_dissim << " "
                                           << str_owa    << " "
                                           << str_imp    << " "
                                           << out        << " "
                                           << mis        << " "
                                           << r          << " "
                                           << std::fixed 
                                           << std::setprecision(PRECISION) 
                                           << BestLocalisationBestFrobenius.second 
                                           << std::endl
                                           << std::flush;
                                           
                           
                           
                        }
                     }
                  }
               }
               
               
               
               for (auto iDis =  ElaboratedResults.begin();
                        iDis != ElaboratedResults.end();
                        iDis++)
               {
                  std::cout << iDis->first << std::endl;
                  
                  for (auto iOwa =  iDis->second.begin();
                           iOwa != iDis->second.end();
                           iOwa++)
                  {
                     std::cout << "   " << iOwa->first << std::endl;
                     
                     for (auto iImp  = iOwa->second.begin();
                               iImp != iOwa->second.end();
                               iImp++)
                     {
                        std::cout << "     " << iImp->first << std::endl;
                        
                        for (auto iOut  = iImp->second.begin();
                                  iOut != iImp->second.end();
                                  iOut++)
                        {
                           std::cout << "        outliers:" << iOut->first << std::endl;
                           
                           for (auto iMis  = iOut->second.begin();
                                     iMis != iOut->second.end();
                                     iMis++)
                           {
                              std::cout << "           missing:" << iMis->first << std::endl;

                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MAX, iMis->second.end());
                              std::cout << "              " << "max: " << iMis->second[INDEX_MAX] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_Q3, iMis->second.end());
                              std::cout << "              " << "Q3:  " << iMis->second[INDEX_Q3] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MED, iMis->second.end());
                              std::cout << "              " << "med: " << iMis->second[INDEX_MED] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_Q1, iMis->second.end());
                              std::cout << "              " << "Q1:  " << iMis->second[INDEX_Q1] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MIN, iMis->second.end());
                              std::cout << "              " << "min: " << iMis->second[INDEX_MIN] << std::endl;
                           }
                        }
                     }
                  }
               }
               
               // memory clean-up :-)         

               for (auto p : owas)
               {
                  delete p;
                  p = nullptr;
               }
               owas.clear();

         
            }
         }
         
         file_allresults.close();
  
         // memory clean-up :-)         
         
         for (auto p : dissimilarities)
         {
            delete p;
            p = nullptr;
         }
         dissimilarities.clear();
         
         
         for (auto p : imputers)
         {
            delete p;
            p = nullptr;
         }
         imputers.clear();

  
      }
   }
   CATCH;
}


void ksi::exp_006::exp_6_dissimilarity_function()
{
   try
   {
      {
         const int REPETITIONS = 13;
         const int INDEX_MIN = 0;
         const int INDEX_Q1  = (REPETITIONS - 1) / 4;
         const int INDEX_MED = (REPETITIONS - 1) / 2;
         const int INDEX_Q3  = 2 * (REPETITIONS - 1) / 4;
         const int INDEX_MAX = REPETITIONS - 1;
         
         const int K_a  =  3;
         const int K_b  =  5;
         const int K_c  = 10;
         
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 6.0;
         const double beta  = 1.0;
         const double delta = 1.0;
         
         const bool useMarginalisedDatasetForClusterCentres = false;
         
         const std::vector<std::vector<double>> perfectLocalisations 
               { {5 , 5}, {5, 1}, {1, 5}};
               
         const int NUMBER_OF_ATTRIBUTES = 2;
         const int PRECISION = 10;
         
         const std::string from (" ");
         const std::string to   ("_");
 
         std::string dataDir ("dane");
         std::string resultsDir ("results");
         
         std::string directory ("exp-006-a-out");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         
         std::vector<std::string> outliers { "00", "01", "02", "05",
                                                   "10", "20", "50"  };
         std::vector<std::string> missing  { "0.00", "0.01", "0.02", "0.05",
                                                     "0.10", "0.20", "0.50"  };

         std::vector<ksi::dissimilarity *> dissimilarities = 
         {  
            new ksi::dis_square(),
            new ksi::dis_linear(),
            new ksi::dis_huber(delta),
            new ksi::dis_log(), 
            new ksi::dis_log_linear(),
            new ksi::dis_sigmoidal(alpha, beta),
            new ksi::dis_sigmoidal_linear(alpha, beta)
         };

         std::vector<ksi::data_modifier *> imputers =
         {
            new ksi::data_modifier_marginaliser(),
            new ksi::data_modifier_imputer_average(),
            new ksi::data_modifier_imputer_median(), 
            new ksi::data_modifier_imputer_knn_average(K_a),
            new ksi::data_modifier_imputer_knn_median(K_a),
            new ksi::data_modifier_imputer_values_from_knn(K_a),
            new ksi::data_modifier_imputer_knn_average(K_b),
            new ksi::data_modifier_imputer_knn_median(K_b),
            new ksi::data_modifier_imputer_values_from_knn(K_b),
            new ksi::data_modifier_imputer_knn_average(K_c),
            new ksi::data_modifier_imputer_knn_median(K_c),
            new ksi::data_modifier_imputer_values_from_knn(K_c)
         };
         
         
         ksi::data_modifier_marginaliser marg; 

                                 
         std::string allresults (resultsDir + "/" + directory + "/all-results");
         std::ofstream file_allresults (allresults);
         file_allresults << "#  dissimilarity owa imputer outliers missing Frobenius" << std::endl << std::endl;
         
         std::map<std::string,   // dissimilarity
          std::map<std::string,   // owa
           std::map<std::string,   // imputer
            std::map<std::string,   // outliers
             std::map<std::string,   // missing 
              std::vector<double>  // the best Frobenius in repetitions
              >>>>> ElaboratedResults;
         
         for (auto out : outliers)
         {
            for (auto mis : missing)
            {
               // exp-006-a-o00-m0.00
               std::string file ("exp-006-a-o" + out + "-m" + mis);
               std::string data (dataDir + "/" + directory + "/" + file);
               std::string results (resultsDir + "/" + directory + "/" + file);
               
               ksi::reader_incomplete input;
               auto DataSet = input.read(data);
               auto number_of_items = DataSet.getNumberOfData();
               
               
               std::vector<ksi::owa *> owas = 
               {
                  new ksi::uowa(),
                  new ksi::sowa(number_of_items, PC, PA),
                  new ksi::plowa(number_of_items, PC, PL)
               };  
                
               for (auto d : dissimilarities)
               {
                  auto str_dissim = ksi::utility_string::replaceString(d->print(), from, to);
                  
                  for (auto o : owas)
                  {
                     auto str_owa = ksi::utility_string::replaceString(o->print(), from, to);
                     
                     for (auto i : imputers)
                     {
                        auto str_imp = ksi::utility_string::replaceString(i->print(), from, to);
                        
                        for (int r = 0; r < REPETITIONS; r++)
                        {
                        
                           std::string method = std::string("-") + str_dissim + 
                                                std::string("-") + str_owa +
                                                std::string("-") + str_imp + 
                                                std::string("-o-") + out + 
                                                std::string("-m-") + mis +
                                                std::string("-") + std::to_string(r)
                                                ;
                           method = ksi::utility_string::replaceString(method, from, to);                     
                           debug(method);
                                                      
                           ksi::rfcom algorithm (*i, marg, *d, *o, useMarginalisedDatasetForClusterCentres);
                  
                           algorithm.setEpsilonForFrobeniusNorm(EPSILON);
                           algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

                           auto Partition = algorithm.doPartition(DataSet);
                           
                           std::vector<std::vector<double>> elaboratedLocalisations;
                           for (int c = 0; c < NUMBER_OF_CLUSTERS; c++)
                           {
                              std::vector<double> clusterLocalisation;
                              auto cluster = Partition.getCluster(c);
                              for (int a = 0; a < NUMBER_OF_ATTRIBUTES; a++)
                              {
                                 auto d = cluster->getAddressOfDescriptor(a);
                                 // here descriptor has three parameters: 
                                 // core, lower fuzzyfication, upper fuzzyfication
                                 auto core = d->getCoreMean();
                                 clusterLocalisation.push_back(core);                           
                              }
                              elaboratedLocalisations.push_back(clusterLocalisation);
                           }
                           
                           auto BestLocalisationBestFrobenius =
                           bestFrobenius(perfectLocalisations, elaboratedLocalisations);
                           
                           ElaboratedResults[d->print()][o->print()][i->print()][out][mis].push_back(BestLocalisationBestFrobenius.second);
                           
                           // OK. Now I have to elaborate a Frobenius norm 
                           // for each permutation of cluster -- I do not 
                           // know the sequence they are elaborated.
                           
                           /// ................. 
                           std::ofstream file (results + method);
                           file << "partition" << std::endl;
                           file << "=========" << std::endl;
                           file << std::endl;
                           file << Partition << std::endl;
                           file << std::endl;
                           
                           file << "best localisation" << std::endl;
                           file << "=================" << std::endl;
                           file << "Frobenius norm:  " << BestLocalisationBestFrobenius.second << std::endl;
                           file << std::endl;
                           file << std::endl;
                           file << BestLocalisationBestFrobenius.first << std::endl;
                           
                           file << std::endl;
                           file << "typicalities" << std::endl;
                           file << "============" << std::endl;
                           file << std::endl;
                           file << DataSet << std::endl;
                           
                           file.close();
                           
                           file_allresults << str_dissim << "  "
                                           << str_owa    << "  "
                                           << str_imp    << "  "
                                           << out        << "  "
                                           << mis        << "  "
                                           << std::fixed 
                                           << std::setprecision(PRECISION) 
                                           << BestLocalisationBestFrobenius.second 
                                           << std::endl
                                           << std::flush;
                                           
                           
                           
                        }
                     }
                  }
               }
               
               
               
               for (auto iDis =  ElaboratedResults.begin();
                        iDis != ElaboratedResults.end();
                        iDis++)
               {
                  std::cout << iDis->first << std::endl;
                  
                  for (auto iOwa =  iDis->second.begin();
                           iOwa != iDis->second.end();
                           iOwa++)
                  {
                     std::cout << "   " << iOwa->first << std::endl;
                     
                     for (auto iImp  = iOwa->second.begin();
                               iImp != iOwa->second.end();
                               iImp++)
                     {
                        std::cout << "     " << iImp->first << std::endl;
                        
                        for (auto iOut  = iImp->second.begin();
                                  iOut != iImp->second.end();
                                  iOut++)
                        {
                           std::cout << "        outliers:" << iOut->first << std::endl;
                           
                           for (auto iMis  = iOut->second.begin();
                                     iMis != iOut->second.end();
                                     iMis++)
                           {
                              std::cout << "           missing:" << iMis->first << std::endl;

                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MAX, iMis->second.end());
                              std::cout << "              " << "max: " << iMis->second[INDEX_MAX] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_Q3, iMis->second.end());
                              std::cout << "              " << "Q3:  " << iMis->second[INDEX_Q3] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MED, iMis->second.end());
                              std::cout << "              " << "med: " << iMis->second[INDEX_MED] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_Q1, iMis->second.end());
                              std::cout << "              " << "Q1:  " << iMis->second[INDEX_Q1] << std::endl;
                              std::nth_element (iMis->second.begin(), iMis->second.begin() + INDEX_MIN, iMis->second.end());
                              std::cout << "              " << "min: " << iMis->second[INDEX_MIN] << std::endl;
                           }
                        }
                     }
                  }
               }
               
               // memory clean-up :-)         

               for (auto p : owas)
               {
                  delete p;
                  p = nullptr;
               }
               owas.clear();

         
            }
         }
         
         file_allresults.close();
  
         // memory clean-up :-)         
         
         for (auto p : dissimilarities)
         {
            delete p;
            p = nullptr;
         }
         dissimilarities.clear();
         
         
         for (auto p : imputers)
         {
            delete p;
            p = nullptr;
         }
         imputers.clear();

  
      }
   }
   CATCH;
}

void ksi::exp_006::exp_6_all()
{
   try
   {
      {
         const int REPETITIONS = 13;
//          const int INDEX_MIN = 0;
//          const int INDEX_Q1  = (REPETITIONS - 1) / 4;
//          const int INDEX_MED = (REPETITIONS - 1) / 2;
//          const int INDEX_Q3  = 2 * (REPETITIONS - 1) / 4;
//          const int INDEX_MAX = REPETITIONS - 1;
         
         const int K_a  =  3;
         const int K_b  =  5;
         const int K_c  = 10;
         
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 1.0;
         const double beta  = 1.0;
         const double huber = 0.3;
         const bool useMarginalisedDatasetForClusterCentres = false; // imputed data set used         
         const std::vector<std::vector<double>> perfectLocalisations 
               { {5 , 5}, {5, 1}, {1, 5}};
               
         const int NUMBER_OF_ATTRIBUTES = 2;
         const int PRECISION = 10;
         
         const std::string from (" ");
         const std::string to   ("_");
 
         std::string dataDir ("dane");
         std::string resultsDir ("results");
         
         std::string directory ("exp-006-b-out");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         
         std::vector<std::string> outliers { "00", "01", "02", "05", "10", "20", "30", "40", "50"  };
//          std::vector<std::string> outliers { /*"00", "01", "02", "05", */"10"/*, "20", "30", "40", "50" */ };
         

         std::vector<std::string> missing  { "0.00", "0.01", "0.02", "0.05", "0.10", "0.20", "0.50"  };
//         std::vector<std::string> missing  { "0.00" };
         
         std::vector<ksi::dissimilarity *> dissimilarities = 
         {  
             new ksi::dis_log_linear()//,
//             new ksi::dis_linear(),
//             new ksi::dis_huber(huber),
//             new ksi::dis_log(), 
//             new ksi::dis_sigmoidal(alpha, beta),
//             new ksi::dis_sigmoidal_linear(alpha, beta)
         };

         std::vector<ksi::data_modifier *> imputers =
         {
//             new ksi::data_modifier_imputer_average(),
//             new ksi::data_modifier_imputer_median(), 
//             new ksi::data_modifier_imputer_knn_average(K_a),
//             new ksi::data_modifier_imputer_knn_median(K_a),
//             new ksi::data_modifier_imputer_values_from_knn(K_a),
//             new ksi::data_modifier_imputer_knn_average(K_b),
//             new ksi::data_modifier_imputer_knn_median(K_b),
//             new ksi::data_modifier_imputer_values_from_knn(K_b),
//             new ksi::data_modifier_imputer_knn_average(K_c),
//             new ksi::data_modifier_imputer_knn_median(K_c),
            new ksi::data_modifier_imputer_values_from_knn(K_c)
         };
         
         
         ksi::data_modifier_marginaliser marg; 

                                 
         std::string allresults (resultsDir + "/" + directory + "/all-results");
         std::ofstream file_allresults (allresults);
         file_allresults << "#  dissimilarity owa imputer outliers missing Frobenius" << std::endl << std::endl;
         
         std::map<std::string,   // dissimilarity
          std::map<std::string,   // owa
           std::map<std::string,   // imputer
            std::map<std::string,   // outliers
             std::map<std::string,   // missing 
              std::vector<double>  // the best Frobenius in repetitions
              >>>>> ElaboratedResults;
         
         for (auto out : outliers)
         {
            for (auto mis : missing)
            {
               std::string file ("exp-006-a-o" + out + "-m" + mis);
               std::string data (dataDir + "/" + directory + "/" + file);
               std::string results (resultsDir + "/" + directory + "/" + file);
               
               ksi::reader_incomplete input;
               auto DataSet = input.read(data);
               auto number_of_items = DataSet.getNumberOfData();
               
               
               std::vector<ksi::owa *> owas = 
               {
//                   new ksi::uowa(),
                  new ksi::sowa(number_of_items, PC, PA) //,
//                   new ksi::plowa(number_of_items, PC, PL)
               };  
                
               for (auto d : dissimilarities)
               {
                  auto str_dissim = ksi::utility_string::replaceString(d->print(), from, to);
                  
                  for (auto o : owas)
                  {
                     auto str_owa = ksi::utility_string::replaceString(o->print(), from, to);
                     
                     for (auto i : imputers)
                     {
                        auto str_imp = ksi::utility_string::replaceString(i->print(), from, to);
                        
                        for (int r = 0; r < REPETITIONS; r++)
                        {
                        
                           std::string method = std::string("-") + str_dissim + 
                                                std::string("-") + str_owa +
                                                std::string("-") + str_imp + 
                                                std::string("-o-") + out + 
                                                std::string("-m-") + mis +
                                                std::string("-") + std::to_string(r)
                                                ;
                           method = ksi::utility_string::replaceString(method, from, to);                     
                           debug(method);
                                                      
                           ksi::rfcom algorithm (*i, marg, *d, *o, useMarginalisedDatasetForClusterCentres);
                  
                           algorithm.setEpsilonForFrobeniusNorm(EPSILON);
                           algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

                           auto Partition = algorithm.doPartition(DataSet);
                           
                           std::vector<std::vector<double>> elaboratedLocalisations;
                           for (int c = 0; c < NUMBER_OF_CLUSTERS; c++)
                           {
                              std::vector<double> clusterLocalisation;
                              auto cluster = Partition.getCluster(c);
                              for (int a = 0; a < NUMBER_OF_ATTRIBUTES; a++)
                              {
                                 auto d = cluster->getAddressOfDescriptor(a);
                                 // here descriptor has three parameters: 
                                 // core, lower fuzzyfication, upper fuzzyfication
                                 auto core = d->getCoreMean();
                                 clusterLocalisation.push_back(core);                           
                              }
                              elaboratedLocalisations.push_back(clusterLocalisation);
                           }
                           
                           auto BestLocalisationBestFrobenius =
                           bestFrobenius(perfectLocalisations, elaboratedLocalisations);
                           
                           ElaboratedResults[d->print()][o->print()][i->print()][out][mis].push_back(BestLocalisationBestFrobenius.second);
                           
                           // OK. Now I have to elaborate a Frobenius norm 
                           // for each permutation of cluster -- I do not 
                           // know the sequence they are elaborated.
                           
                           /// ................. 
                           std::ofstream file (results + method);
                           file << "EXPERIMENT" << std::endl;
                           file << std::endl;
                           
                           file << "dissimilarity: " << str_dissim << std::endl;
                           file << "owa:           " << str_owa    << std::endl;
                           file << "imputer:       " << str_imp    << std::endl;
                           file << "outliers:      " << out        << std::endl;
                           file << "missing ratio: " << mis        << std::endl;
                           file << "repetition:    " << r          << std::endl;
                           file << std::endl;
                           
                           
                           file << "partition" << std::endl;
                           file << "=========" << std::endl;
                           file << std::endl;
                           file << Partition << std::endl;
                           file << std::endl;
                           
                           file << "best localisation" << std::endl;
                           file << "=================" << std::endl;
                           file << "Frobenius norm:  " << BestLocalisationBestFrobenius.second << std::endl;
                           file << std::endl;
                           file << std::endl;
                           file << BestLocalisationBestFrobenius.first << std::endl;
                           
                           file << std::endl;
                           file << "typicalities" << std::endl;
                           file << "============" << std::endl;
                           file << std::endl;
                           file << DataSet << std::endl;
                           
                           file.close();
                           
                        }
                        file_allresults << str_dissim << "  "
                                           << str_owa    << "  "
                                           << str_imp    << "  "
                                           << out        << "  "
                                           << mis        << "  "
                                           ;
                                           
                        std::vector<double> & rWyniki = ElaboratedResults[d->print()][o->print()][i->print()][out][mis];
                        std::sort (rWyniki.begin(), rWyniki.end());
                        for (auto value :  rWyniki)
                           file_allresults << std::fixed 
                                           << std::setprecision(PRECISION) 
                                           << value
                                           <<  "  ";
                               
                        file_allresults << std::endl << std::flush;
                     }
                  }
               }
               
               // memory clean-up :-)         
               for (auto p : owas)
               {
                  delete p;
                  p = nullptr;
               }
               owas.clear();

         
            }
         }
         
         file_allresults.close();
  
         // memory clean-up :-)         
         
         for (auto p : dissimilarities)
         {
            delete p;
            p = nullptr;
         }
         dissimilarities.clear();
         
         
         for (auto p : imputers)
         {
            delete p;
            p = nullptr;
         }
         imputers.clear();

  
      }
   }
   CATCH;
}
