/** @file */ 


#include <string>
#include <fstream>
#include <sstream>


#include "../readers/reader.h"
#include "../readers/reader-complete.h"
#include "../readers/reader-complete-by-parts.h"

#include "../common/datum.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../auxiliary/utility-string.h"
#include "../service/debug.h"


std::shared_ptr<ksi::reader> ksi::reader_complete_by_parts::clone() const
{
    return std::shared_ptr<ksi::reader>(new ksi::reader_complete_by_parts(*this));
}


ksi::reader_complete_by_parts::reader_complete_by_parts(const ksi::reader_complete_by_parts& wzor)
{
    try 
    {
        throw std::string("Copying prohibited!");
    }
    CATCH;
}


ksi::reader_complete_by_parts::reader_complete_by_parts(const std::string& file_name) : _filename (file_name)
{
    try  
    {
        file_handler.open(_filename);
        if (not file_handler)
            throw std::string ("File <" + _filename + "> could not be opened!");
    }
    CATCH;
}

ksi::reader_complete_by_parts::~reader_complete_by_parts()
{
    if (file_handler.is_open())
        file_handler.close();
}


ksi::dataset ksi::reader_complete_by_parts::read_part(std::size_t size)
{
   try 
   {
       if (not file_handler.is_open())
           throw std::string ("File <" + _filename + "> could not be opened!");
       
       std::size_t items_read = 0;
       dataset ds;
       std::string linia;
       while (items_read < size and std::getline(file_handler, linia))
       {
          linia = ksi::utility_string::trimString(linia);
          if (linia.length() > 0)
          {
             for (auto & c : linia)
                if (c == ',' or c == '\t')
                   c = ' ';
            
             std::stringstream ss;
             ss << linia;
            
             datum d;   
             double value;
             while (ss >> value)
             {
                number nc (value);
                d.push_back(nc);
             }
             d.setID(item_number++);
             d.setIDincomplete(-1);
             ds.addDatum(d);
             
             items_read++;
          }
       }
       
       return ds;
   }
   CATCH;    
}


