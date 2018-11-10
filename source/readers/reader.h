/** @file */ 

#ifndef READER_H
#define READER_H


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
   };
}

#endif
