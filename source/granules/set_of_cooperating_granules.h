
#ifndef SET_OF_COOPERATING_GRANULES_H
#define SET_OF_COOPERATING_GRANULES_H

#include "set_of_granules.h"

namespace ksi
{
   class set_of_cooperating_granules : public set_of_granules
   {
    public:
      set_of_cooperating_granules ();
      set_of_cooperating_granules (const set_of_cooperating_granules & wzor);
      set_of_cooperating_granules (set_of_cooperating_granules && wzor);
      set_of_cooperating_granules & operator= (const set_of_cooperating_granules & wzor);
      set_of_cooperating_granules & operator= (set_of_cooperating_granules && wzor);
      virtual ~set_of_cooperating_granules ();
      
//       virtual void addGranule(const ksi::granule & g) override;
//       virtual void addGranule(const ksi::granule * g) override; 
      
   };
}

  
#endif
