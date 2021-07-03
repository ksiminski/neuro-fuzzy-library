/** @file */ 

#ifndef PARTITIONER_GRID_H
#define PARTITIONER_GRID_H

#include "partition.h"
#include "partitioner.h"
#include "../common/dataset.h"


namespace ksi
{
   /** Class partitioner implements an interface for input domain partition algorithms.
    *  This class and cluster (subclass of partition class) class compose a factory design pattern (role: producer).
    */
   class partitioner_grid : virtual public partitioner
   {
      int _number_of_intervals;
   protected:
            
   public:
      partitioner_grid ();
      /** @param number_of_intervals of grid for one attribute */
      partitioner_grid (int number_of_intervals);
      virtual ~partitioner_grid ();
      
      /** The method for grid partition of the dataset ds.
       @param ds dataset to partition 
      */
      virtual partition doPartition(const ksi::dataset& ds);
      virtual partitioner * clone () const;
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };
}

#endif

