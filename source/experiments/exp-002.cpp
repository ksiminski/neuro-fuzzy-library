/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 

#include "../readers/reader-complete.h" 
#include "../readers/weighted_reader_complete.h"
#include "../common/dataset.h" 
#include "../partitions/partitioner.h" 
#include "../partitions/fcm.h"
#include "../partitions/fcom.h"
#include "../partitions/fcm-conditional.h"
#include "../partitions/fcm-possibilistic.h"
#include "../partitions/sfcm.h" 
#include "../partitions/fubi.h"
#include "../partitions/dbscan.h"
#include "../partitions/granular-dbscan.h"
#include "../metrics/metric-minkowski.h"
#include "../metrics/metric-euclidean.h"
#include "../dissimilarities/dis-log.h"
#include "../dissimilarities/dis-log-linear.h"
#include "../dissimilarities/dis-huber.h"
#include "../dissimilarities/dis-sigmoidal.h"
#include "../dissimilarities/dis-sigmoidal-linear.h"
#include "../owas/sowa.h"
#include "../owas/plowa.h"
#include "../owas/uowa.h"
#include "../service/debug.h"
#include "../metrics/metric-euclidean.h"
#include "../tnorms/t-norm-product.h"
#include "../snorms/s-norm-sum.h"

#include "../experiments/exp-002.h"

#include <fstream>

void ksi::exp_002::execute()
{
   try
   {  
      {
         std::string dataDir ("data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "possibilistic");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM" << std::endl;
         std::cout << "===" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {
         std::string dataDir ("data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "possibilistic");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm_possibilistic algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "possibilistic FCM" << std::endl;
         std::cout << "=================" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {
         std::string dataDir ("data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "pedrycz");
         
         ksi::weighted_reader_complete input;
         auto DataSet = input.read(data);
         auto number_of_items = DataSet.getNumberOfData();
         
         ksi::fcm_conditional algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "conditional FCM" << std::endl;
         std::cout << "===============" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
         
      }
      
      
      {
         std::string dataDir ("data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "sub-135-245");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::sfcm algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "subspace FCM" << std::endl;
         std::cout << "============" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      
      {
         std::string dataDir ("data/exp-002");
         const int NUMBER_OF_ITERATIONS { 100 };
         const int NUMBER_OF_CLUSTERS   {   2 };
         std::string data (dataDir + "/" + "sub-135-245");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fubi algorithm (NUMBER_OF_CLUSTERS, NUMBER_OF_ITERATIONS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "fuzzy biclustering (FuBi)" << std::endl;
         std::cout << "=========================" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 1.0;
         const double beta  = 1.0;
         
         std::string dataDir ("data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 3;
         std::string data (dataDir + "/" + "fcom-10.data");
         ksi::reader_complete input;
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
         
         ksi::fcom algorithm (Dissimilarity, Owa);
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCOM" << std::endl;
         std::cout << "====" << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
         
         std::cout << "data items with typicalities" << std::endl;
         std::cout << DataSet << std::endl;
      }      

      {
         const double epsilon = 5;    // 1.5
         const double minPts = 10;
         ksi::metric_euclidean metric;
         
         std::string dataDir ("data/exp-002");
         std::string data (dataDir + "/" + "dbscan.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
//          auto number_of_items = DataSet.getNumberOfData();
         
         ksi::dbscan algorithm(epsilon, minPts, metric);
         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "DBSCAN" << std::endl;
         std::cout << "======" << std::endl;
         std::cout << "data item\t|\tmembership to clusters" << std::endl;
         std::cout << std::endl;
         
         std::cout << Partition.print_dataitems_with_memberships_to_clusters(DataSet) << std::endl;
//          std::cout << std::endl;
//          std::cout << "++++++++++++++++++++++++++" << std::endl;
//          std::cout << Partition.print_crisp_membership_for_data(DataSet) << std::endl;
         
      } 

      {
         std::string dataDir ("data/exp-002");
         const int ITERATIONS = 100;
         const int FCM_NUMBER_OF_CLUSTERS = 30;
         std::string data (dataDir + "/" + "dbscan.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm fuzzyficationAlgorihm;
         fuzzyficationAlgorihm.setNumberOfIterations(ITERATIONS);
         fuzzyficationAlgorihm.setNumberOfClusters(FCM_NUMBER_OF_CLUSTERS);

         const double EPSILON = 6;
         const double MIN_POINTS = 3;
         const double MAX_MEMB_NEW_CORE = 0.3;
         const double MIN_MEMB_NEIGHBOUR = 0.8;
         const ksi::s_norm_sum snorm;
         const ksi::t_norm_product tnorm;

         ksi::granular_dbscan granularDBSCAN(EPSILON, MIN_POINTS, MAX_MEMB_NEW_CORE, MIN_MEMB_NEIGHBOUR, fuzzyficationAlgorihm, snorm, tnorm);

         auto Partition = granularDBSCAN.doPartition(DataSet);
         
         std::cout << "GrDBSCAN" << std::endl;
         std::cout << "========" << std::endl;
         std::cout << "data item\t|\tmembership to clusters" << std::endl;
         std::cout << std::endl;
         std::cout << Partition.print_dataitems_with_memberships_to_clusters(DataSet) << std::endl;
         std::cout << std::endl;
      }
   }
   CATCH;

   return;
}
