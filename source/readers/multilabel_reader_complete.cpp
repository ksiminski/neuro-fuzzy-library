
#include <algorithm>    // std::reverse
#include <vector>       // std::vector
#include <fstream>
#include <sstream>


#include "../readers/reader.h"
#include "../readers/reader-complete.h"
#include "../readers/multilabel_reader_complete.h"
#include "../common/datum.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../auxiliary/utility-string.h"
#include "../service/debug.h"

ksi::multilabel_reader_complete::multilabel_reader_complete ()
{
}

ksi::multilabel_reader_complete::~multilabel_reader_complete ()
{
   // delete what is to delete

}

ksi::multilabel_reader_complete::multilabel_reader_complete (const ksi::multilabel_reader_complete & wzor) : ksi::reader_complete(wzor)
{
   // copy what is to copy

}

ksi::multilabel_reader_complete & ksi::multilabel_reader_complete::operator= (const ksi::multilabel_reader_complete & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::reader_complete::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::multilabel_reader_complete::multilabel_reader_complete (ksi::multilabel_reader_complete && wzor) : ksi::reader_complete(wzor)
{
   // swap what is to swap

}

ksi::multilabel_reader_complete & ksi::multilabel_reader_complete::operator= (ksi::multilabel_reader_complete && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::reader_complete::operator=(wzor);

   // swap what is to swap

   return *this;
}



std::shared_ptr<ksi::reader> ksi::multilabel_reader_complete::clone() const
{
     return std::shared_ptr<ksi::reader>(new ksi::multilabel_reader_complete(*this));
}


ksi::dataset ksi::multilabel_reader_complete::read(const std::string& filename)
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
      
      // Labels are separated from attributes with a bar '|'. 
      
      std::string linia;
      while (std::getline(infile, linia))
      {
          linia = ksi::utility_string::trimString(linia);
          if (linia.length() > 0)
          {
              for (auto & c : linia)
                 if (c == ',' or c == '\t')
                     c = ' ';
                 
            // find the separator
            auto pos = linia.find_first_of(SEPARATOR);
            std::string atrybuty;
            std::string etykiety;
            if (pos != std::string::npos) // separator found
            {
                atrybuty = linia.substr(0, pos);
                etykiety = linia.substr(pos + 1);
            }
            else 
            {
                atrybuty = linia; 
            }           
            
            
            
            datum d = extract_values(atrybuty, etykiety);   
//             double value;
//             
//             
//             // odczytaj atrybuty
//             {
//                 std::stringstream ss;
//                 ss << atrybuty;
//                 while (ss >> value)
//                 {
//                     number nc (value);
//                     d.push_back(nc);
//                 }
//                 
//             }
//             // odczytaj etykiety
//             std::vector<std::string> labels;
//             {
//                 std::stringstream ss;
//                 ss << etykiety;
//                 std::string value;
//                 
//                 while (ss >> value)
//                 {
//                     labels.push_back(value);
//                 }
//                 
//             }
            
            
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

ksi::datum ksi::multilabel_reader_complete::extract_values(const std::string& atrybuty, const std::string& etykiety)
{
	datum d;  
	double value;

	// odczytaj atrybuty
	{
		std::stringstream ss;
		ss << atrybuty;
		while (ss >> value)
		{
			number nc (value);
			d.push_back(nc);
		}

	}
	// odczytaj etykiety
	std::vector<std::string> labels;
	{
		std::stringstream ss;
		ss << etykiety;
		std::string value;

		while (ss >> value)
		{
			labels.push_back(value);
		}

	}
	d.setLabels(labels);

	return d;
}


/*
ksi::dataset ksi::multilabel_reader_complete::read(const std::string& filename)
{
   try 
   {
       const char PREFIX { '#' };
      std::size_t item_number = 0;
      std::ifstream infile (filename);
      if (not infile)
      {
         std::stringstream ss;
         ss << "impossible to open file <" << filename << ">";
         throw ss.str();
      }
      
      dataset ds;
      
      // First line hold a number of labels just after #, eg:
      // # 4
      // stands for 4 labels in each data item

      char c;
      int nLabels;
      std::string linia;
      infile >> c >> nLabels;
      if (c != PREFIX)
          throw std::string("Provide the number of labels in the first line proceeded by \'" + std::to_string(PREFIX) + "\'!");
      
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
            
            std::vector<std::string> words;
            std::string word;
            while (ss >> word)
            {
                words.push_back(word);
//                number nc (value);
//                d.push_back(nc);
            }
            
            std::vector<std::string> labels;
            for (int i = 0; i < nLabels; i++)
            {
                auto word = words.back();
                words.pop_back();
                labels.push_back(word);
            }
            std::reverse(labels.begin(), labels.end());
            // mam odczytane etykiety
            
            // teraz jeszcze trzeba odczytac wartoci
            
            datum d;   
            double value;
            for (auto w : words)
            {
                try 
                {
                    double value = std::stof(w);
                    number nc(value);
                    d.push_back(nc);
                }
                CATCH; 
            }
            
            d.setID(item_number++);
            d.setIDincomplete(-1);
            d.setLabels(labels);
            ds.addDatum(d);
         }
      }
      infile.close();

      return ds;
   }
   CATCH;
}
*/
