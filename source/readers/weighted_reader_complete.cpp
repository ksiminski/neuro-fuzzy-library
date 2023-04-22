
#include <algorithm>    // std::reverse
#include <vector>       // std::vector
#include <fstream>
#include <sstream>


#include "../readers/reader.h"
#include "../readers/reader-complete.h"
#include "../readers/weighted_reader_complete.h"
#include "../common/datum.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../auxiliary/utility-string.h"
#include "../service/debug.h"

ksi::weighted_reader_complete::weighted_reader_complete ()
{
}

ksi::weighted_reader_complete::~weighted_reader_complete ()
{
   // delete what is to delete

}

ksi::weighted_reader_complete::weighted_reader_complete (const ksi::weighted_reader_complete & wzor) : ksi::multilabel_reader_complete(wzor)
{
   // copy what is to copy

}

ksi::weighted_reader_complete & ksi::weighted_reader_complete::operator= (const ksi::weighted_reader_complete & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::multilabel_reader_complete::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::weighted_reader_complete::weighted_reader_complete (ksi::weighted_reader_complete && wzor) : ksi::multilabel_reader_complete(wzor)
{
   // swap what is to swap

}

ksi::weighted_reader_complete & ksi::weighted_reader_complete::operator= (ksi::weighted_reader_complete && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::multilabel_reader_complete::operator=(wzor);

   // swap what is to swap

   return *this;
}



std::shared_ptr<ksi::reader> ksi::weighted_reader_complete::clone() const
{
     return std::shared_ptr<ksi::reader>(new ksi::weighted_reader_complete(*this));
}


ksi::datum ksi::weighted_reader_complete::extract_values(const std::string& atrybuty, const std::string& szWeight)
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
	// odczytaj wage danej

	{
		std::stringstream ss;
		ss << szWeight;
		double weight = 1;

		ss >> weight;
		d.setWeight(weight);  
	}
	return d;
}

 
 
