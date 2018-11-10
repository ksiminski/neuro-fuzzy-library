/** @file */


/** @file */

#include "data-modifier.h"
#include "data-modifier-imputer.h"
#include "data-modifier-imputer-median.h"
#include "dataset.h"
#include "datum.h"
#include "number.h"
#include "../auxiliary/utility-string.h"
#include "../auxiliary/utility-math.h"
#include "../service/debug.h"



ksi::data_modifier* ksi::data_modifier_imputer_median::clone() const
{
    return new ksi::data_modifier_imputer_median(*this);
}
 

ksi::data_modifier_imputer_median::data_modifier_imputer_median (ksi::data_modifier_imputer_median  && dm) 
    : ksi::data_modifier_imputer(dm) 
{
    
}

ksi::data_modifier_imputer_median::data_modifier_imputer_median(const ksi::data_modifier_imputer_median & dm): data_modifier_imputer(dm)
{
   
}

ksi::data_modifier_imputer_median::data_modifier_imputer_median() : data_modifier_imputer()
{
   description = "median imputer";
}

ksi::data_modifier_imputer_median & ksi::data_modifier_imputer_median::operator=(ksi::data_modifier_imputer_median && dm)
{
   if (this == & dm)
      return *this;  
    
   ksi::data_modifier::operator=(dm);
   
   return *this;
}

ksi::data_modifier_imputer_median & ksi::data_modifier_imputer_median::operator= (const ksi::data_modifier_imputer_median & dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   return *this;   
}

ksi::data_modifier_imputer_median::~data_modifier_imputer_median()
{
}


void ksi::data_modifier_imputer_median::modify(ksi::dataset & ds)
{
   try
   {
      ///////////////////////////////////////
      // no i tu sie zaczyna zabawa :-) 
      
      std::size_t nRows = ds.getNumberOfData();
      std::size_t nCols = ds.getNumberOfAttributes();
      
      std::vector<std::vector<double>> atrybuty (nCols);
      
      for (std::size_t r = 0; r < nRows; r++)
      {
         for (std::size_t c = 0; c < nCols; c++)
         {
            if (ds.exists(r, c))
               atrybuty[c].push_back(ds.get(r, c));
         } 
      }
 
      std::vector<double> mediany (nCols);
      for (std::size_t c = 0; c < nCols; c++)
      {
         mediany[c] = ksi::utility_math::getMedian(atrybuty[c].begin(),
                                                   atrybuty[c].end());
      } 
      // imputation:
      auto id_max = ds.getMaximalNumericalLabel();
      std::size_t licznik = 1;
      ksi::dataset imputed;
      for (std::size_t r = 0; r < nRows; r++)
      {
         datum d;
         int number_of_missing_values = 0;
         auto id_krotki_oryginalnej = ds.getDatum(r)->getID();       
         for (std::size_t c = 0; c < nCols; c++)
         {
            number nc;
            if (ds.exists(r, c))
               nc.setValue(ds.get(r, c));
            else
            {
               number_of_missing_values++;
               nc.setValue(mediany[c]);
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



