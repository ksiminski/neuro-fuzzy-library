
#ifndef SET_OF_STANDALONE_GRANULES_H
#define SET_OF_STANDALONE_GRANULES_H

#include <vector>

#include "../granules/granule.h"
#include "../granules/set_of_granules.h"

namespace ksi
{
   /** The class represents a set of standalone granules. 
    By standalone we mean completely indepent granules. They do not interact with each other. 
    @date 2019-09-19
    */ 
   class set_of_standalone_granules : public set_of_granules
   {
    protected:
        std::vector<granule *> granules;
    public:
      set_of_standalone_granules ();
      set_of_standalone_granules (const set_of_standalone_granules & wzor);
      set_of_standalone_granules (set_of_standalone_granules && wzor);
      set_of_standalone_granules & operator= (const set_of_standalone_granules & wzor);
      set_of_standalone_granules & operator= (set_of_standalone_granules && wzor);
      virtual ~set_of_standalone_granules ();
      
      /** The method elaborated answer of the set of set_of_standalone_granules granule.
       @param d the datum to elaborate answer for 
       @param pg dumb pointer, never used, you may any value you wish
       */
      virtual const ksi::number get_answer(const ksi::datum & d, ksi::granule * pg);
      
      virtual void addGranule(const ksi::granule & g) override;
      virtual void addGranule(const ksi::granule * g) override;
      
      /** @return number of granules in the set */
      virtual const std::size_t size() const override;
      
      virtual ksi::set_of_granules * clone_set_of_granules() const override;
      
      virtual const ksi::granule * getGranule(int index) const override;
      
      virtual ksi::granule * getGranuleNonConst(int index) override;
      
        
   };
}


#endif
