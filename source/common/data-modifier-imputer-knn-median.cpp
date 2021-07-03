/** @file */

 

#include "data-modifier.h"
#include "data-modifier-imputer-knn.h"
#include "data-modifier-imputer-knn-median.h"
#include "dataset.h"
#include "datum.h"
#include "../metrics/metric-euclidean-incomplete.h"
#include "../auxiliary/utility-math.h"
#include "number.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_imputer_knn_median::clone() const
{
   return new ksi::data_modifier_imputer_knn_median(*this);
}

ksi::data_modifier_imputer_knn_median::data_modifier_imputer_knn_median (ksi::data_modifier_imputer_knn_median  && dm) 
    : ksi::data_modifier_imputer_knn(dm) 
{
    
}

ksi::data_modifier_imputer_knn_median::data_modifier_imputer_knn_median(const ksi::data_modifier_imputer_knn_median & dm): data_modifier_imputer_knn(dm)
{
      
}

ksi::data_modifier_imputer_knn_median::data_modifier_imputer_knn_median() 
{
   description = "knn median imputer";
}

ksi::data_modifier_imputer_knn_median & ksi::data_modifier_imputer_knn_median::operator=(ksi::data_modifier_imputer_knn_median && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
  
   return *this;
}

ksi::data_modifier_imputer_knn_median & ksi::data_modifier_imputer_knn_median::operator= (const ksi::data_modifier_imputer_knn_median & dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
  
   return *this;   
}

ksi::data_modifier_imputer_knn_median::~data_modifier_imputer_knn_median()
{ 
}

ksi::data_modifier_imputer_knn_median::data_modifier_imputer_knn_median (int k) : data_modifier_imputer_knn_median()
{
   _k = k;
}

void ksi::data_modifier_imputer_knn_median::modify(ksi::dataset & ds)
{
   try
   {
      if (_k < 0)
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
                  
                  std::vector<double> values;
                  for (auto & p : neighbours)
                     values.push_back(p->at(c)->getValue());
                   
                  auto median = ksi::utility_math::getMedian(values.begin(),
                     values.end());
                  nc.setValue(median);
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

 
