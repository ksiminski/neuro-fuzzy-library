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
   };
}

#endif

