/** @file */ 

#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <iostream>
#include <string>
#include "../partitions/cluster.h"
#include "../common/extensional-fuzzy-number-gaussian.h"
#include "../common/dataset.h"

namespace ksi
{
   /** Class partition implements an interface for input domain partitions.
    *  Class cluster (subclass of partition class) and partitioner class compose a factory design pattern (role: product).
    *  Class cluster (subclass of partition class) and descriptor class compose a factory design pattern (role: producer)
    */
   class partition 
   {
   protected:
      std::vector<cluster *> clusters;
      
      /** partition matrix */
      std::vector<std::vector<double>> U;
      /** cluster centres */
      std::vector<std::vector<double>> V;
      
   public:
      ~partition();
      partition ();
      partition (const partition &);
      partition (partition &&);
      partition & operator= (const partition &);
      partition & operator= (partition &&);
      
      /** The operator merges two partitions. 
       @date 2019-02-27
       */
      partition & operator += (const partition & right);
      
      /** Method adds a cluster to the partition. The method creates a new cluster (with new operator)
         @date   2017-12-28
         @author Krzysztof Siminski 
       */
      void addCluster (const cluster & c);
      
      /** Method adds a cluster to the partition. The method simply adds the passed address (does not allocate memory for a cluster to add).
         @date   2017-12-28
         @author Krzysztof Siminski 
       */
      void addCluster (cluster * p);
      
      
      /** The method gets an pointer to a cluster.
       *  @param index index of a cluster 
       *  @return a valid pointer to the cluster or nullptr if index invalid 
       *  @date 2018-01-21
       *  @author Krzysztof Siminski
       */
      cluster * getCluster (std::size_t index);
      
      /** @return number of clusters in partition 
       *  @date 2018-12-16
       */
      std::size_t getNumberOfClusters () const ;
            
      /** @return partition matrix */
      std::vector<std::vector<double>> getPartitionMatrix () const;
      /** @return cluster centres 
       *  @date 2018-12-16
       */
      std::vector<std::vector<double>> getClusterCentres () const; 
      
 
      
      /** The method sets partition matrix.
       @param partition_matrix a matrix to set 
       @date 2018-12-16
       */
      void setPartitionMatrix (const std::vector<std::vector<double>> & partition_matrix);

      /** The method sets partition matrix.
       @param partition_matrix a matrix to set, it is set with cores of gaussian extensional numbers
       @date 2019-01-24o
       */
      void setPartitionMatrix (const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & partition_matrix);
      
      /** The method sets cluster centres.
       @param cluster_centres a matrix to set 
       @date 2018-12-16
       */
      void setClusterCentres (const std::vector<std::vector<double>> & cluster_centres);

      /** The method sets cluster centres.
       @param cluster_centres a matrix to set, it is set with cores of gaussian extensional numbers
       @date 2019-01-24
       */
      void setClusterCentres (const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & cluster_centres);

      
      /** Output operator for partition class.
       @date 2018-01-02
       */
      friend std::ostream & operator << (std::ostream& ss, const ksi::partition& part);
      
      /** The method prints to a string the membership matrix. 
       Each row represents a cluster. Each column represents 
       a data item. 
       @return string with membership matrix 
       @date 2022-04-13 
       */
      std::string print_partition_matrix ();
      
      /** The method prints to a string each data item with the cluster number, the data items has the highest membeship to.
       @return string with data items and cluster number
       @date 2022-04-13 
       */
      std::string print_crisp_membership_for_data(const ksi::dataset & ds);
      
   };   
}

#endif

