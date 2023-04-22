 

/** @file */
#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <iostream>
#include "../granules/granule.h"
#include "../descriptors/descriptor.h"
#include "../common/extensional-fuzzy-number-gaussian.h"


namespace ksi
{
   /** Class cluster implements a cluster.
    */
   class cluster : public granule
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
      
      /** @return number of clusters in partition
       *  @date 2022-03-12
       *  @author Dawid Suchy
       */
      const std::size_t getNumberOfDescriptors() const;
      
      std::size_t get_number_of_desciptors() const;
      
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
      
      
      /** @return The method returns a granule expressed with fuzzy gaussian extensional number
       @date 2019-02-28 
       */
      std::vector<ksi::ext_fuzzy_number_gaussian> getGranule() const;
      
      
      friend std::ostream & operator << (std::ostream & ss, const cluster & cl);
      
      
        // methods for granules
        virtual granule * clone_granule() const;
        
        /** The method elaborates quality of the granule. */
        virtual void elaborate_quality ();
        
        /** @return The method returns a data_item represented by the data granule. */
        virtual datum get_data_item ();
        
        /** @return The method returns a decision for a datum.
            @param  d the datum to elaborated answer for .
            @todo Jaka powinna być odpowiedź dla klastra?
            */
        virtual const number get_answer (const datum & d);

   };
   
}

#endif

