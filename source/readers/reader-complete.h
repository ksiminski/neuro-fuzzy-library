/** @file */ 

#ifndef READER_COMPLETE_H
#define READER_COMPLETE_H

#include <string>
#include "reader.h"
#include "../common/dataset.h"

namespace ksi
{
   class reader_complete : virtual public reader 
   {
   public:
      virtual dataset read(const std::string& filename);
      
   };
}


#endif
