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
#include "../partitions/fcm-T-metrics.h"
#include "../partitions/fcom.h"
#include "../partitions/fcm-conditional.h"
#include "../partitions/fcm-possibilistic.h"
#include "../partitions/sfcm.h" 
#include "../partitions/fubi.h"
#include "../partitions/gk.h"
#include "../partitions/dbscan.h"
#include "../partitions/granular-dbscan.h"
#include "../metrics/metric-minkowski.h"
#include "../metrics/metric-euclidean.h"
#include "../metrics/metric_mahalanobis.h"
#include "../metrics/metric-chebyshev.h"
#include "../metrics/metric-cosine.h"
#include "../metrics/metric-manhattan.h"
#include "../metrics/metric.h"
#include "../dissimilarities/dis-log.h"
#include "../dissimilarities/dis-log-linear.h"
#include "../dissimilarities/dis-huber.h"
#include "../dissimilarities/dis-sigmoidal.h"
#include "../dissimilarities/dis-sigmoidal-linear.h"
#include "../owas/sowa.h"
#include "../owas/plowa.h"
#include "../owas/uowa.h"
#include "../service/debug.h"
#include "../tnorms/t-norm-product.h"
#include "../snorms/s-norm-sum.h"

#include "../experiments/exp-002.h"


void ksi::exp_002::execute()
{
   try
   { 
      /// outliers (dane nietypowe, dane odstająca)
      /// + metryka Minkowskiego  (parametryzowana, p = 2 (euklidesowa), p = 1; 1.5
      /*{  // FCM
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         
         //std::string data (dataDir + "/" + "02-out-10.txt");
         //std::string data (dataDir + "/" + "02-out-20.txt");
         //std::string data (dataDir + "/" + "02-out-50.txt");
         //std::string data (dataDir + "/" + "02-out-100.txt");
         //std::string data (dataDir + "/" + "100.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM" << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }*/
      {  // FCM + euclidean
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");

         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::metric_euclidean m;
         ksi::fcm_T_metrics<double> algorithm(m); 
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM + metric " << m.getAbbreviation() << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      {  // FCM + cosine
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::metric_cosine m;
         ksi::fcm_T_metrics<double> algorithm(m); 
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM + metric " << m.getAbbreviation() << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      {  // FCM + chebyshev
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::metric_chebyshev m;
         ksi::fcm_T_metrics<double> algorithm(m); 
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM + metric " << m.getAbbreviation() << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      {  // FCM + Minkowski
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::metric_minkowski m(5);
         ksi::fcm_T_metrics<double> algorithm(m); 
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM + metric " << m.getAbbreviation() << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      {  // FCM + Manhattan
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::metric_manhattan m;
         ksi::fcm_T_metrics<double> algorithm(m); 
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "FCM + metric " << m.getAbbreviation() << std::endl;
         std::cout << "===" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      {  // FCM + Mahalanobis
         std::string dataDir ("../data/exp-002/outliers");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 4;
         //std::string data (dataDir + "/" + "02-out-300.txt");
         //std::string data (dataDir + "/" + "02-out-400.txt");
         //std::string data (dataDir + "/" + "02-out-500.txt");
         std::string data (dataDir + "/" + "02-out-1000.txt");
         //std::string data (dataDir + "/" + "02-out-1500.txt");
         //std::string data (dataDir + "/" + "02-out-2000.txt");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::gk algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "Mahalanobis" << std::endl;
         std::cout << "================" << std::endl;
         std::cout << "data file: " << data << std::endl; 
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

     return ; 


      {  // possibilistic FCM
         std::string dataDir ("../data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "possibilistic.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm_possibilistic algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "possibilistic FCM" << std::endl;
         std::cout << "=================" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {  // conditional FCM
         std::string dataDir ("../data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "pedrycz.data");
         
         ksi::weighted_reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fcm_conditional algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "conditional FCM" << std::endl;
         std::cout << "===============" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {  // Gustafson-Kessel
         std::string dataDir ("../data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         // std::string data (dataDir + "/" + "possibilistic.data");
         // std::string data (dataDir + "/" + "two-crossed.data");
         // std::string data (dataDir + "/" + "two-parallel.data");
         // std::string data (dataDir + "/" + "two-crossed-oblique.data");
         std::string data (dataDir + "/" + "two-parallel-oblique.data");
         
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::gk algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "Gustafson-Kessel" << std::endl;
         std::cout << "================" << std::endl;
         std::cout << "data file: " << data << std::endl; 
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      
      {  // subspace FCM
         std::string dataDir ("../data/exp-002");
         const double EPSILON = 1e-8;
         const int NUMBER_OF_CLUSTERS = 2;
         std::string data (dataDir + "/" + "sub-135-245.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::sfcm algorithm;
         algorithm.setEpsilonForFrobeniusNorm(EPSILON);
         algorithm.setNumberOfClusters(NUMBER_OF_CLUSTERS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "subspace FCM" << std::endl;
         std::cout << "============" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }
      
      {  // fuzzy biclustering (FuBi)
         std::string dataDir ("../data/exp-002");
         const int NUMBER_OF_ITERATIONS { 100 };
         const int NUMBER_OF_CLUSTERS   {   2 };
         std::string data (dataDir + "/" + "sub-135-245.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
         
         ksi::fubi algorithm (NUMBER_OF_CLUSTERS, NUMBER_OF_ITERATIONS);

         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "fuzzy biclustering (FuBi)" << std::endl;
         std::cout << "=========================" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
      }

      {  // FCOM
         const double PC = 0.5;
         const double PA = 0.2;
         const double PL = 0.2;
         const double alpha = 1.0;
         const double beta  = 1.0;
         
         std::string dataDir ("../data/exp-002");
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
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << Partition << std::endl;
         std::cout << std::endl;
         
         std::cout << "data items with typicalities" << std::endl;
         std::cout << DataSet << std::endl;
      }      

      {  // DBSCAN
         const double epsilon = 5;    // 1.5
         const double minPts = 10;
         ksi::metric_euclidean metric;
         
         std::string dataDir ("../data/exp-002");
         std::string data (dataDir + "/" + "dbscan.data");
         ksi::reader_complete input;
         auto DataSet = input.read(data);
//          auto number_of_items = DataSet.getNumberOfData();
         
         ksi::dbscan algorithm(epsilon, minPts, metric);
         auto Partition = algorithm.doPartition(DataSet);
         
         std::cout << "DBSCAN" << std::endl;
         std::cout << "======" << std::endl;
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << "data item\t|\tmembership to clusters" << std::endl;
         std::cout << std::endl;
         
         std::cout << Partition.print_dataitems_with_memberships_to_clusters(DataSet) << std::endl;
//          std::cout << std::endl;
//          std::cout << "++++++++++++++++++++++++++" << std::endl;
//          std::cout << Partition.print_crisp_membership_for_data(DataSet) << std::endl;
         
      } 

      {  // GrDBSCAN
         std::string dataDir ("../data/exp-002");
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
         std::cout << "data file: " << data << std::endl;
         std::cout << std::endl;
         std::cout << "data item\t|\tmembership to clusters" << std::endl;
         std::cout << std::endl;
         std::cout << Partition.print_dataitems_with_memberships_to_clusters(DataSet) << std::endl;
         std::cout << std::endl;
      }
   }
   CATCH;

   return;
}
