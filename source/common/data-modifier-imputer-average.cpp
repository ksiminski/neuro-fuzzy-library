/** @file */


/** @file */

#include "data-modifier.h"
#include "data-modifier-imputer.h"
#include "data-modifier-imputer-average.h"
#include "dataset.h"
#include "datum.h"
#include "number.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_imputer_average::clone() const
{
   return new ksi::data_modifier_imputer_average(*this);
}
 

ksi::data_modifier_imputer_average::data_modifier_imputer_average (ksi::data_modifier_imputer_average  && dm) 
    : ksi::data_modifier_imputer(dm) 
{
   
}

ksi::data_modifier_imputer_average::data_modifier_imputer_average(const ksi::data_modifier_imputer_average & dm): data_modifier_imputer(dm)
{
}

ksi::data_modifier_imputer_average::data_modifier_imputer_average() : data_modifier_imputer()
{
   description = "average imputer";
}

ksi::data_modifier_imputer_average & ksi::data_modifier_imputer_average::operator=(ksi::data_modifier_imputer_average && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer::operator=(dm);
    
   return *this;
}

ksi::data_modifier_imputer_average & ksi::data_modifier_imputer_average::operator= (const ksi::data_modifier_imputer_average& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer::operator=(dm);
   
   return *this;   
}

ksi::data_modifier_imputer_average::~data_modifier_imputer_average()
{
}


void ksi::data_modifier_imputer_average::modify(ksi::dataset & ds)
{
   try
   {
      ///////////////////////////////////////
      // no i tu sie zaczyna zabawa :-) 
      
      std::size_t nRows = ds.getNumberOfData();
      std::size_t nCols = ds.getNumberOfAttributes();
      
      std::vector<double> sums (nCols, 0.0);
      std::vector<std::size_t> count (nCols, 0.0);
      
      for (std::size_t r = 0; r < nRows; r++)
      {
         for (std::size_t c = 0; c < nCols; c++)
         {
            if (ds.exists(r, c))
            {
               sums[c] += ds.get(r, c);
               count[c]++;
            }
         }
      }
      
      /////////////
      std::vector<double> averages (nCols);
      for (std::size_t a = 0; a < nCols; a++)
      {
         if (count[a] == 0)
            averages[a] = 0.0;
         else
            averages[a] = sums[a] / count[a];
      }
      //////////////
      auto id_max = ds.getMaximalNumericalLabel();
      std::size_t licznik = 1;
      // imputation:
      ksi::dataset imputed;
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
               nc.setValue(averages[c]);
               number_of_missing_values++;
            }
            d.push_back(nc);
            d.setWeight(1.0 - 1.0 * number_of_missing_values / nCols);
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
         
         imputed.addDatum(d);
      }
      
      // no i teraz trzeba nadpisac zbiory:
      ds = imputed;
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
   }
   CATCH;
}



