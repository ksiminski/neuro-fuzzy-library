/** @file */ 

#ifndef READER_COMPLETE_BY_PARTS_H
#define READER_COMPLETE_BY_PARTS_H

#include <string>
#include <fstream>
#include <memory>
#include "reader.h"
#include "reader-complete.h"
#include "../common/dataset.h"

namespace ksi
{
   /** The class implements a reader of complete data. It does not read the whole data, but by parts. 
    @date 2019-03-16
    */ 
   class reader_complete_by_parts : virtual public reader_complete 
   {
   protected:
       /** name of data file  */
       std::string _filename;
       std::ifstream file_handler;
       std::size_t item_number = 0;
   public:
       /** Parametrised constructor
        @param file_name name of file with data 
        @date 2019-03-16
       */
       reader_complete_by_parts (const std::string & file_name);
       
       reader_complete_by_parts (const reader_complete_by_parts & wzor);
       
       
       /** The method read a part of data
        @param size size (number of data tuples) of data to read
        @return The method returns a dataset of read-in data 
        @date 2019-03-16
       */
       dataset read_part (std::size_t size);
       
       virtual ~reader_complete_by_parts();
       
       /** The prototype design pattern. */
      std::shared_ptr< ksi::reader > clone() const; 
      
   };
}


#endif
