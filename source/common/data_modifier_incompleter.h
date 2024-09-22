
#ifndef DATA_MODIFIER_INCOMPLETER_H
#define DATA_MODIFIER_INCOMPLETER_H

#include "data-modifier.h"

namespace ksi
{
   /** The class is responsible for incompleting the data.
    @data   2024-09-22
    @author Krzysztof Siminski 
    */
   class data_modifier_incompleter : public data_modifier
   {
    public:
       
      data_modifier_incompleter ();
      
      data_modifier_incompleter (const data_modifier_incompleter & other) = default;
      data_modifier_incompleter (data_modifier_incompleter && other) = default;
      data_modifier_incompleter & operator= (const data_modifier_incompleter & other) = default;
      data_modifier_incompleter & operator= (data_modifier_incompleter && other) = default;
      
      virtual ~data_modifier_incompleter (); 
   };
}


#endif
