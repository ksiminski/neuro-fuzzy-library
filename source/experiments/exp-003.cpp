/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 

#include "../dissimilarities/dissimilarity.h"
#include "../dissimilarities/dis-huber.h"
#include "../dissimilarities/dis-log.h"
#include "../dissimilarities/dis-linear.h"
#include "../owas/sowa.h" 
#include "../partitions/rfcm.h"
#include "../partitions/rfcom.h"
#include "../partitions/rsfcm.h"
#include "../readers/reader-complete.h"
#include "../readers/reader-incomplete.h"
#include "../common/data-modifier-imputer-average.h"
#include "../common/data-modifier-marginaliser.h"
#include "../common/data-modifier-imputer-median.h"
#include "../auxiliary/matrix.h"

#include "../experiments/exp-003.h"

#include <fstream>

void ksi::exp_003::execute()
{
   try
   {
      {
         std::string dataDir ("data/exp-003");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         std::string data (dataDir + "/" + "rfcom-10-5.data");
         ksi::reader_incomplete input;
         auto DataSet = input.read(data);
         
         ksi::data_modifier_marginaliser marg;
         ksi::data_modifier_imputer_median imp;
         
         bool useMarginalisedDatasetForClusterCentres = true;
         ksi::rfcm algorithm (imp, marg, useMarginalisedDatasetForClusterCentres);
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "RFCM" << std::endl;
         std::cout << "====" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      
      {
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 1.0;
         const double beta  = 1.0;
         const bool useMarginalisedDatasetForClusterCentres = true;

         std::string dataDir ("data/exp-003");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         std::string data (dataDir + "/" + "rfcom-10-5.data");
         ksi::reader_incomplete input;
         auto DataSet = input.read(data);
         auto number_of_items = DataSet.getNumberOfData();

         
         ksi::dis_log Dissimilarity;
         // or use other dissimilarities:
//          ksi::dis_huber Dissimilarity (0.3);
//          ksi::dis_linear Dissimilarity;
//          ksi::dis_log_linear Dissimilarity;
//          ksi::dis_sigmoidal Dissimilarity (alpha, beta);
//          ksi::dis_sigmoidal_linear Dissimilarity(alpha, beta); 
         
         ksi::sowa Owa (number_of_items, PC, PA);
         // or use other owas:
//          ksi::uowa Owa;
//          ksi::plowa Owa(number_of_items, PC, PL);

         
         ksi::data_modifier_marginaliser marg;
         ksi::data_modifier_imputer_median imp;
         // or use some other imputer
         
         ksi::rfcom algorithm (imp, marg, Dissimilarity, Owa, useMarginalisedDatasetForClusterCentres);
         
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "RFCOM" << std::endl;
         std::cout << "=====" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
         
         std::cout << "data items with typicalities" << std::endl;
         std::cout << DataSet << std::endl;
      }
      
      
      {
         const bool useMarginalisedDatasetForClusterCentres = true;

         std::string dataDir ("data/exp-003");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         std::string data (dataDir + "/" + "sub-135-245-m10");
         ksi::reader_incomplete input;
         auto DataSet = input.read(data);
         auto number_of_items = DataSet.getNumberOfData();

         ksi::data_modifier_marginaliser marg;
         ksi::data_modifier_imputer_median imp;
         // or use some other imputer
         
         ksi::rsfcm algorithm (imp, marg, useMarginalisedDatasetForClusterCentres);
         
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "RSFCM" << std::endl;
         std::cout << "=====" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
         
         
      }
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
