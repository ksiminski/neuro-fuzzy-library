/** @file */

#include "data-modifier.h"
#include "data-modifier-marginaliser.h"
#include "dataset.h"
#include "datum.h"
#include "number.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_marginaliser::clone() const
{
    return new ksi::data_modifier_marginaliser(*this);
}


ksi::data_modifier_marginaliser::data_modifier_marginaliser (ksi::data_modifier_marginaliser  && dm): ksi::data_modifier(dm) 
{
}

ksi::data_modifier_marginaliser::data_modifier_marginaliser(const ksi::data_modifier_marginaliser & dm): data_modifier(dm)
{
}

ksi::data_modifier_marginaliser::data_modifier_marginaliser() : data_modifier()
{
   description = "marginaliser";
}

ksi::data_modifier_marginaliser & ksi::data_modifier_marginaliser::operator=(ksi::data_modifier_marginaliser && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   return *this;
}

ksi::data_modifier_marginaliser & ksi::data_modifier_marginaliser::operator= (const ksi::data_modifier_marginaliser& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
  
   return *this;   
}

ksi::data_modifier_marginaliser::~data_modifier_marginaliser()
{
}


void ksi::data_modifier_marginaliser::modify(ksi::dataset & ds)
{
   try
   {
      ///////////////////////////////////////
      // no i tu sie zaczyna zabawa :-) 
      
      ksi::dataset zmarginalizowany;
      
      std::size_t nRows = ds.getNumberOfData();
      std::size_t nCols = ds.getNumberOfAttributes();
      
      for (std::size_t r = 0; r < nRows; r++)
      {
         // sprawdzam, czy wszystkie dane istnieja
         bool krotkaPelna = true;
         for (std::size_t c = 0; c < nCols; c++)
         {
            if (not ds.exists(r, c))
            {
               krotkaPelna = false;
               break;
            }
         }
         if (krotkaPelna) // kopiuje dane:
         {
            datum d;
            for (std::size_t c = 0; c < nCols; c++)
            {
               number nc;
               nc.setValue(ds.get(r, c));
               d.push_back(nc);
            }
            d.setID(ds.getDatum(r)->getID());
            d.setIDincomplete(ds.getDatum(r)->getIDincomplete());
            zmarginalizowany.addDatum(d);
         }
      }
      // no i teraz trzeba nadpisac zbiory:
      ds = zmarginalizowany;
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
   }
   CATCH;
}



