/** @file */


 

#include <vector>
#include "data-modifier.h"
#include "data-modifier-normaliser.h"
#include "../service/debug.h"

ksi::data_modifier* ksi::data_modifier_normaliser::clone() const
{
    return new ksi::data_modifier_normaliser(*this);
}


ksi::data_modifier_normaliser::data_modifier_normaliser (ksi::data_modifier_normaliser  && dm): ksi::data_modifier(dm) 
{
}

ksi::data_modifier_normaliser::data_modifier_normaliser(const ksi::data_modifier_normaliser & dm): data_modifier(dm)
{
}

ksi::data_modifier_normaliser::data_modifier_normaliser() : data_modifier()
{
   description = "normaliser";
}

ksi::data_modifier_normaliser& ksi::data_modifier_normaliser::operator=(ksi::data_modifier_normaliser&& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   return *this;
}

ksi::data_modifier_normaliser& ksi::data_modifier_normaliser::operator=(const ksi::data_modifier_normaliser& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   return *this;   
}

ksi::data_modifier_normaliser::~data_modifier_normaliser()
{
}

void ksi::data_modifier_normaliser::modify(ksi::dataset & ds)
{
   try
   {
      // no i tu sie zaczyna zabawa :-) 
      size_t nAttributes = ds.getNumberOfAttributes();
      size_t nDataItems = ds.getNumberOfData();
      std::vector<double> mins (nAttributes, 0);
      std::vector<double> maxs (nAttributes, 0);
      
      if (nDataItems < 2)
         return; // finito :-)
         
      for (size_t k = 0; k < nAttributes; k++)
         mins[k] = maxs[k] = ds.get(0, k);

      for (size_t w = 1; w < nDataItems; w++)
      {
         for (size_t k = 0; k < nAttributes; k++)
         {
            double value = ds.get(w, k);
            if (mins[k] > value)
               mins[k] = value;
            if (maxs[k] < value)
               maxs[k] = value;
         }
      }
      // no i teraz normalizacja:
      for (size_t k = 0; k < nAttributes; k++)
      {
         if (mins[k] == maxs[k])   
         {
            for (size_t w = 0; w < nDataItems; w++)
               ds.set (w, k, 0.5);
         }
         else
         {
            double roznica = maxs[k] - mins[k];
            double minimum = mins[k];
            for (size_t w = 0; w < nDataItems; w++)
            {
               double value = ds.get (w, k);
               ds.set (w, k, (value - minimum) / roznica);
            }
         }
      }
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
   }
   CATCH;
   
}




