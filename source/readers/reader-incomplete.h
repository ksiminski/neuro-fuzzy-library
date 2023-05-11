/** @file */ 

#ifndef READER_INCOMPLETE_H
#define READER_INCOMPLETE_H

#include <memory>
#include <string>
#include "../readers/reader.h"
#include "../common/dataset.h"

namespace ksi
{
   class reader_incomplete : virtual public reader 
   {
      const char MISSING_VALUE_SYMBOL = '?';
   public:
      reader_incomplete ();
      /** @param missing_value_symbol symbol of a missing value, default: '?' */
      reader_incomplete (const char missing_value_symbol);
      virtual dataset read(const std::string& filename);
      
      /** The prototype design pattern. */
      virtual std::shared_ptr<reader> clone() const; 
      
      
   };
}


#endif
