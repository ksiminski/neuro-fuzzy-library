/** @file */ 

#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <iostream>
#include "cluster.h"

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
      
   public:
      ~partition();
      partition ();
      partition (const partition &);
      partition (partition &&);
      partition & operator= (const partition &);
      partition & operator= (partition &&);
      
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
      
      
      
      /** Output operator for partition class.
       @date 2018-01-02
       */
      friend std::ostream & operator << (std::ostream& ss, const ksi::partition& part);
      
   };   
}

#endif

