 

/** @file */
#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <iostream>
#include "../descriptors/descriptor.h"

namespace ksi
{
   /** Class cluster implements a cluster.
    */
   class cluster 
   {
   protected: 
      /** Descriptors for attributes **/
      std::vector<descriptor *> descriptors;
   public:
      cluster ();
      cluster (const cluster & cl);
      cluster (cluster && cl);
      cluster & operator = (const cluster & cl);
      cluster & operator = (cluster && cl);
      /** The method copies a descriptor into a cluster (allocates new memory).
        @date 2018-01-02 */
      void addDescriptor (const descriptor & d);
      /** The method adds a descriptor into a cluster (without allocating new memory).
        @date 2018-01-02 */
      void addDescriptor (descriptor * p);
      virtual ~cluster();      
      
      /** @return a copy of a descriptor (allocates memory)
         @date   2018-01-01
         @author Krzysztof Siminski 
         @param  attribute number of attribute 
         @throw ksi::exception if attribute is invalid
       */
      virtual descriptor * getDescriptor(int attibute);
      
      /** Gets an address to a descriptor (without allocation of memory)
       * @date   2018-02-22
         @author Krzysztof Siminski 
         @param  attribute number of attribute 
         @return an address to the descriptor, if it exists
         @return nullptr if the attribute is invalid
       */
      const descriptor * getAddressOfDescriptor (int attribute);
      
      friend std::ostream & operator << (std::ostream & ss, const cluster & cl);
   };
   
}

#endif

