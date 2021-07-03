/** @file */

 

#include "../common/data-modifier.h"
#include "../common/data-modifier-imputer-knn.h"
#include "../common/data-modifier-imputer-values-from-knn.h"
#include "../common/dataset.h"
#include "../common/datum.h"
#include "../common/number.h"
#include "../metrics/metric.h"
#include "../metrics/metric-euclidean-incomplete.h"
#include "../auxiliary/utility-math.h"
#include "../service/debug.h"


ksi::data_modifier* ksi::data_modifier_imputer_values_from_knn::clone() const
{
   return new ksi::data_modifier_imputer_values_from_knn (*this);
}

ksi::data_modifier_imputer_values_from_knn::data_modifier_imputer_values_from_knn (ksi::data_modifier_imputer_values_from_knn  && dm) 
    : ksi::data_modifier_imputer_knn(dm) 
{ 
}

ksi::data_modifier_imputer_values_from_knn::data_modifier_imputer_values_from_knn(const ksi::data_modifier_imputer_values_from_knn & dm): data_modifier_imputer_knn(dm)
{
}

ksi::data_modifier_imputer_values_from_knn::data_modifier_imputer_values_from_knn() 
{
   description = "imputer with values from knn";
}

ksi::data_modifier_imputer_values_from_knn & ksi::data_modifier_imputer_values_from_knn::operator=(ksi::data_modifier_imputer_values_from_knn && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
   
   return *this;
}

ksi::data_modifier_imputer_values_from_knn & ksi::data_modifier_imputer_values_from_knn::operator= (const ksi::data_modifier_imputer_values_from_knn & dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer_knn::operator=(dm);
    
   return *this;   
}

ksi::data_modifier_imputer_values_from_knn::~data_modifier_imputer_values_from_knn()
{ 
}

ksi::data_modifier_imputer_values_from_knn::data_modifier_imputer_values_from_knn (int k) : data_modifier_imputer_values_from_knn()
{
   _k = k;
}

void ksi::data_modifier_imputer_values_from_knn::modify(ksi::dataset & ds)
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
         std::vector<std::size_t> indices_of_missing_attr;
         for (std::size_t c = 0; c < nCols; c++)
         {
            if (not ds.exists(r, c))
            {
               if (not ds.exists(r, c))
                  indices_of_missing_attr.push_back(c);
            }
         }
         
         if (indices_of_missing_attr.size() == 0) // complete data item
         {
            datum d;
            for (std::size_t c = 0; c < nCols; c++)
            {
               number nc;
               nc.setValue(ds.get(r, c));
               d.push_back(nc);
               d.setID(id_krotki_oryginalnej);
               d.setIDincomplete(0);
            }
            imputed.addDatum(d);
         }
         else // incomplete data item 
         {
            std::vector<const ksi::datum *> neighbours = getNeighbours (ds, r, indices_of_missing_attr, _k);
            
            auto id = ds.getDatum(r)->getID();
            for (int k = 0; k < _k; k++)
            {
               datum d;         
               int missing_index = 0;
               for (int a = 0; a < nCols; a++)
               {
                  number nc;
                  if (a == indices_of_missing_attr[missing_index])
                  { 
                     nc.setValue(neighbours[k]->at(a)->getValue());
                     missing_index++;
                  }
                  else
                  {
                     nc.setValue(ds.get(r, a));
                  }
                  d.push_back(nc);
               }
               
               d.setID(id_max + licznik);
               d.setIDincomplete(id_krotki_oryginalnej);
               licznik++;
               imputed.addDatum(d);    
            }
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

std::vector< const ksi::datum* >  ksi::data_modifier_imputer_values_from_knn::getNeighbours(
   const ksi::dataset & ds, 
   std::size_t r, 
   const std::vector<std::size_t> & indices_of_missing_attr, 
   int _k)
{
   ksi::metric_euclidean_incomplete distancer;
   std::size_t size = ds.getNumberOfData();
   std::size_t number_of_missing_attributes = indices_of_missing_attr.size();
   std::vector<ksi::distance_index> distances;
   
   const ksi::datum * pr = ds.getDatum(r);
   for (std::size_t i = 0; i < size; i++)
   {
      if (i != r) // dla samego siebie nie bedziemy liczyc odleglosci
      {
         // trzeba sprawdzic, czy dla tej danej instnieja wszystkie potrzebne 
         // atrybuty
         bool bAllExist = true;
         for (std::size_t m = 0; bAllExist and m < number_of_missing_attributes; m++)
         {
            if (not ds.exists(i, indices_of_missing_attr[m]))
               bAllExist = false;
         }
         if (bAllExist)
         {
            double dist = distancer.calculateDistance(*pr, *(ds.getDatum(i)));
            distances.push_back({dist, i});
         }
      }
   }
   
   // OK, we have all distances, know we have to find _k neighbours:
   std::vector<const ksi::datum *> neighbours;
   for (int i = 0; i < _k ; i++)
   {
      auto dist_index = utility_math::k_th_element<distance_index>(
         distances.begin(), distances.end(), i);
      neighbours.push_back(ds.getDatum(dist_index.index));
   }
   return neighbours;  
}
 
