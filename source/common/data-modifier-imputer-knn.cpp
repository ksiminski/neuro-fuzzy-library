/** @file */

 

#include "data-modifier.h"
#include "data-modifier-imputer.h"
#include "data-modifier-imputer-knn.h"
#include "dataset.h"
#include "datum.h"
#include "../metrics/metric-euclidean-incomplete.h"
#include "../auxiliary/utility-math.h"
#include "number.h"
#include "../service/debug.h"




ksi::data_modifier_imputer_knn::data_modifier_imputer_knn (ksi::data_modifier_imputer_knn  && dm) 
    : ksi::data_modifier_imputer(dm) 
{
    
}

ksi::data_modifier_imputer_knn::data_modifier_imputer_knn(const ksi::data_modifier_imputer_knn & dm): data_modifier_imputer(dm)
{
   _k = dm._k;
}

ksi::data_modifier_imputer_knn::data_modifier_imputer_knn() 
{
   description = "knn imputer";
}

ksi::data_modifier_imputer_knn & ksi::data_modifier_imputer_knn::operator=(ksi::data_modifier_imputer_knn && dm)
{
   if (this == & dm)
      return *this;

   ksi::data_modifier_imputer::operator=(dm);   
   _k = dm._k;
   
   return *this;
}

ksi::data_modifier_imputer_knn & ksi::data_modifier_imputer_knn::operator= (const ksi::data_modifier_imputer_knn & dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier_imputer::operator=(dm);
   _k = dm._k;
   
   return *this;   
}

ksi::data_modifier_imputer_knn::~data_modifier_imputer_knn()
{
}

ksi::data_modifier_imputer_knn::data_modifier_imputer_knn (int k)
{
   _k = k;
}



std::vector<const ksi::datum *> ksi::data_modifier_imputer_knn::getNeighbours(
   const dataset & ds, 
   std::size_t r, 
   std::size_t c, 
   int _k)
{
   ksi::metric_euclidean_incomplete distancer;
   std::size_t size = ds.getNumberOfData();
   
   std::vector<ksi::distance_index> distances;
   
   const ksi::datum * pr = ds.getDatum(r);
   for (std::size_t i = 0; i < size; i++)
   {
      if (i != r and ds.exists(i, c)) // dla samego siebie nie bedziemy liczyc odleglosci
      {
         double dist = distancer.calculateDistance(*pr, *(ds.getDatum(i)));
         distances.push_back({dist, i});
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

std::string ksi::data_modifier_imputer_knn::print() const
{
   std::string full_description = description + std::string(" (k == ") +
               std::to_string(_k) + std::string (")");
               
   if (pNext)
   {
      auto further_description = pNext->print();
      if (further_description.empty())
         return full_description;
      else 
         return full_description + " + " + further_description;
   }
   else 
      return full_description;
} 

