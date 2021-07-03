/** @file */

 

#include "data-modifier.h"
#include "data-modifier-imputer-knn.h"
#include "data-modifier-imputer-knn-average.h"
#include "dataset.h"
#include "datum.h"
#include "../metrics/metric-euclidean-incomplete.h"
#include "../auxiliary/utility-math.h"
#include "number.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_imputer_knn_average::clone() const
{
    return new ksi::data_modifier_imputer_knn_average(*this);
}

ksi::data_modifier_imputer_knn_average::data_modifier_imputer_knn_average (ksi::data_modifier_imputer_knn_average  && dm) 
    : ksi::data_modifier_imputer_knn(dm) 
{
    
}

ksi::data_modifier_imputer_knn_average::data_modifier_imputer_knn_average(const ksi::data_modifier_imputer_knn_average & dm): data_modifier_imputer_knn(dm)
{
    
}

ksi::data_modifier_imputer_knn_average::data_modifier_imputer_knn_average() 
{
   description = "knn average imputer";
    
}

ksi::data_modifier_imputer_knn_average & ksi::data_modifier_imputer_knn_average::operator=(ksi::data_modifier_imputer_knn_average && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
 
   return *this;
}

ksi::data_modifier_imputer_knn_average & ksi::data_modifier_imputer_knn_average::operator= (const ksi::data_modifier_imputer_knn_average & dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
 
   return *this;   
}

ksi::data_modifier_imputer_knn_average::~data_modifier_imputer_knn_average()
{
   _k = 0;
}

ksi::data_modifier_imputer_knn_average::data_modifier_imputer_knn_average (int k) : data_modifier_imputer_knn_average()
{
   _k = k;
}

void ksi::data_modifier_imputer_knn_average::modify(ksi::dataset & ds)
{
   try
   {
      if (_k < 1)
         throw std::string ("number of neighbours not set");
      
      ///////////////////////////////////////
      // no i tu sie zaczyna zabawa :-) 
      
      std::size_t nRows = ds.getNumberOfData();
      std::size_t nCols = ds.getNumberOfAttributes();
      
      std::vector<double> sums (nCols, 0.0);
      std::vector<std::size_t> count (nCols, 0.0);
      
      auto id_max = ds.getMaximalNumericalLabel();
      std::size_t licznik = 1;
      
      ksi::dataset imputed;
      for (std::size_t r = 0; r < nRows; r++)
      {
         auto id_krotki_oryginalnej = ds.getDatum(r)->getID(); 
         
         bool bComplete = true;
         for (std::size_t c = 0; c < nCols; c++)
         {
            if (not ds.exists(r, c))
            {
               bComplete = false;
               c += nCols;
            }
         }
         
         if (bComplete)
         {
            datum d;
            for (std::size_t c = 0; c < nCols; c++)
            {
               number nc;
               nc.setValue(ds.get(r, c));
               d.push_back(nc);
            }
            // jeszcze ustawienie numeru krotki:
            d.setID(id_krotki_oryginalnej);
            d.setIDincomplete(0);
            // koniec ustawiania numeru krotek
            imputed.addDatum(d);
         }
         else // incomplete data item 
         {
            datum d;
            int number_of_missing_attr = 0;
            for (std::size_t c = 0; c < nCols; c++)
            {
               number nc;
               if (not ds.exists(r, c))
               {
                  // nie ma wartosci dla atrybutu c
                  // trzeba znalezc odleglosci do wszystkich sasiadow
                  std::vector<const ksi::datum *> neighbours = getNeighbours (ds, r, c, _k);
                  double attrSum = 0.0;
                  for (auto & p : neighbours)
                     attrSum += p->at(c)->getValue();
                  double valueToInput = attrSum / _k;
                  
                  nc.setValue(valueToInput);
                  number_of_missing_attr++;
               }
               else
                  nc.setValue(ds.get(r, c));
               
               d.push_back(nc);
               d.setWeight(1.0 - 1.0 * number_of_missing_attr / nCols);
               
            }
            // jeszcze ustawienie numeru krotki:
            if (number_of_missing_attr > 0)
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
         
      }
      
      // no i teraz trzeba nadpisac zbiory:
      ds = imputed;
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
   }
   CATCH;
}

 
