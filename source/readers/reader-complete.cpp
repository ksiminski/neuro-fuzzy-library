/** @file */ 


#include <string>
#include <fstream>
#include <sstream>

#include "../readers/reader.h"
#include "../readers/reader-complete.h"
#include "../common/datum.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../auxiliary/utility-string.h"
#include "../service/debug.h"

std::shared_ptr<ksi::reader> ksi::reader_complete::clone() const
{
    return std::shared_ptr<ksi::reader>(new ksi::reader_complete(*this));
}


ksi::dataset ksi::reader_complete::read (const std::string & filename)
{
   try 
   {
      std::size_t item_number = 0;
      std::ifstream infile (filename);
      if (not infile)
      {
         std::stringstream ss;
         ss << "impossible to open file <" << filename << ">";
         throw ss.str();
      }
      
      dataset ds;
      
      std::string linia;
      while (std::getline(infile, linia))
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
         }
      }
      infile.close();

      return ds;
   }
   CATCH;
}
