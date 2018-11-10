/** @file */ 


#include <string>
#include <fstream>
#include <sstream>

#include "reader-incomplete.h"
#include "../common/datum.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../service/debug.h"
#include "../auxiliary/utility-string.h"


ksi::reader_incomplete::reader_incomplete(const char missing_value_symbol) : MISSING_VALUE_SYMBOL(missing_value_symbol)
{
}

ksi::reader_incomplete::reader_incomplete()
{

}


ksi::dataset ksi::reader_incomplete::read (const std::string & filename)
{
   try 
   {
      std::size_t item_number = 0;
      const char SEPARATOR = ' ';
      std::string MISSING;
      MISSING.append({ MISSING_VALUE_SYMBOL });
   
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
            
            //// podzielic linie spacjami
            auto slowa = utility_string::splitString(linia, SEPARATOR);
            // sprawdzic, czy napisy sa liczbami, czy znakami brakow   
               
            datum d;   
            double value;
            for (auto slowo : slowa)
            {
               number nc;
               slowo = ksi::utility_string::trimString(slowo);
               if (slowo == MISSING) // missing value
                  nc.setValue(false);
               else
                  nc.setValue(std::stof(slowo));
               
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
