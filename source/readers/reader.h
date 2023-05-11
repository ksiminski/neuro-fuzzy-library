/** @file */ 

#ifndef READER_H
#define READER_H

#include <memory>
#include <string>
#include "../common/datum.h"
#include "../common/dataset.h"

namespace ksi
{
   class reader 
   { 
   public:
      virtual dataset read (const std::string & filename) = 0;
      
      virtual ~reader ();
      
      /** The prototype design pattern. */
      virtual std::shared_ptr<reader> clone() const = 0; 
   };
}

#endif
