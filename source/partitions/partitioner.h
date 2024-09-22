/** @file */ 

#ifndef PARTITIONER_H
#define PARTITIONER_H

#include "partition.h"
#include "../common/dataset.h"

namespace ksi
{
   /** Class partitioner implements an interface for input domain partition algorithms. 
    */
   class partitioner
   {
   protected:
      /** Number of iterations of partition algorithm. */
      int _nIterations = -1;
      
      /** Number of clusters to split the dataset into. */
      int _nClusters   = -1;
            
   public:
      virtual ~partitioner();
      
      /** Virtual method for partition of dataset.
       * @param ds dataset to partition 
       * @return returns a elaborated partition (clusters with descriptors)
       */
      virtual partition doPartition(const dataset & ds) = 0;
      /** The method clones a partitioner and return a pointer to a cloned 
       *  object. This method is implemented in derived classes.
       **/
      virtual partitioner * clone () const = 0;
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;

      /** @return The method return the number of iterations (if set). If the number if not set, it returns -1. */
      virtual int get_number_of_iterations () const ;

      /** @return The method return the number of clusters (if set). If the number if not set, it returns -1. */
      virtual int get_number_of_clusters() const;

   };
}

#endif

