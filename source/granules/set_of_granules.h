
#ifndef SET_OF_GRANULES_H
#define SET_OF_GRANULES_H

#include "../granules/granule.h"

namespace ksi
{
   class set_of_granules
   {
    public:

      set_of_granules ();
      set_of_granules (const set_of_granules & wzor);
      set_of_granules (set_of_granules && wzor);
      set_of_granules & operator= (const set_of_granules & wzor);
      set_of_granules & operator= (set_of_granules && wzor);
      
      virtual set_of_granules * clone_set_of_granules () const = 0;

      virtual ~set_of_granules ();
      
      
      /** The method adds a granule to a collection of granules. The added granule is copied.
      @param g a granule to add 
      */
      virtual void addGranule (const granule & g) = 0;

      /** The method adds a granule to a collection of granules. The added granule is copied.
      @param g a pointer to a granule to add 
      */
      virtual void addGranule (const granule * g) = 0;

        
      /** The methods return a pointer to a granule. The method does not copy a granule.
      @param index index of a granule to get address of
      @return an address to a granule, if the parameter index is invalid, nullptr is returned */
      virtual const granule * getGranule (int index) const = 0;
      
      /** @return a nonconst pointer to a granule; if the parameter index is invalid, nullptr is returned; the method does not copy a granule
       *  
       *  @param index index of a granule to get address of
       */ 
      virtual granule * getGranuleNonConst (int index) = 0;
        
      /** @return the number of granules in a set */
      virtual const std::size_t size() const = 0;
      
      /** @return The method returns a values elaborated for the granule 
       * @param d datum to elaborate answer for
       * @param pg a pointer to a granule to answer
       */
      virtual const number get_answer (const datum & d, granule * pg) = 0;
   };
}


#endif
