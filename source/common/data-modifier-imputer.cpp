/** @file */


/** @file */

#include "data-modifier.h"
#include "data-modifier-imputer.h"
#include "dataset.h"
#include "datum.h"
#include "number.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_imputer::clone() const
{
   return new ksi::data_modifier_imputer(*this);
}

ksi::data_modifier_imputer::data_modifier_imputer(double value)
{
   _value = value;
}

ksi::data_modifier_imputer::data_modifier_imputer (ksi::data_modifier_imputer && dm): ksi::data_modifier(dm) 
{
   _value = dm._value;
}

ksi::data_modifier_imputer::data_modifier_imputer(const ksi::data_modifier_imputer & dm): data_modifier(dm)
{
   _value = dm._value;
}

ksi::data_modifier_imputer::data_modifier_imputer() : data_modifier()
{
   _value = 0.0;
   description = "imputer with constant value"; 
}

ksi::data_modifier_imputer & ksi::data_modifier_imputer::operator=(ksi::data_modifier_imputer && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   _value = dm._value;
   
   return *this;
}

ksi::data_modifier_imputer & ksi::data_modifier_imputer::operator= (const ksi::data_modifier_imputer& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   _value = dm._value;
   return *this;   
}

ksi::data_modifier_imputer::~data_modifier_imputer()
{
}


void ksi::data_modifier_imputer::modify(ksi::dataset & ds)
{
   try
   {
      ///////////////////////////////////////
      // no i tu sie zaczyna zabawa :-) 
      
      ksi::dataset zbior_z_uzupelnionymi;
      
      std::size_t nRows = ds.getNumberOfData();
      std::size_t nCols = ds.getNumberOfAttributes();
      
      auto id_max = ds.getMaximalNumericalLabel();
      std::size_t licznik = 1;
      
      for (std::size_t r = 0; r < nRows; r++)
      {
         datum d;         
         auto id_krotki_oryginalnej = ds.getDatum(r)->getID();         
         
         int number_of_missing_values = 0;
         for (std::size_t c = 0; c < nCols; c++)
         {
            number nc;
            if (ds.exists(r, c))
               nc.setValue(ds.get(r, c));
            else
            {
               nc.setValue(_value);
               number_of_missing_values++;
            }
            // ustawiam wage krotki uzupelnianej:
            if (number_of_missing_values == 0)
               d.setWeight(1.0);
            else
               d.setWeight(1.0 * (nCols - number_of_missing_values) / nCols);
            d.push_back(nc);
         }
         
         // jeszcze ustawienie numeru krotki:
         if (number_of_missing_values > 0)
         {
            d.setID(id_max + licznik);
            d.setIDincomplete(id_krotki_oryginalnej);
            licznik++;
         }
         else
         {
            d.setID(id_krotki_oryginalnej);
            d.setIDincomplete(0);
         }
         // koniec ustawiania numeru krotek
         
         zbior_z_uzupelnionymi.addDatum(d);
         
      }
      // no i teraz trzeba nadpisac zbiory:
      ds = zbior_z_uzupelnionymi;
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
   }
   CATCH;
}



