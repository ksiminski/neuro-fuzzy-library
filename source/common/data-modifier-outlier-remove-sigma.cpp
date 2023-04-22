/** @file */

#include <vector>
#include <algorithm>
#include <cmath>

#include "data-modifier.h"
#include "data-modifier-outlier-remove-sigma.h"
#include "../service/debug.h"

ksi::data_modifier* ksi::data_modifier_outlier_remove_sigma::clone() const
{
    return new ksi::data_modifier_outlier_remove_sigma(*this);
}


ksi::data_modifier_outlier_remove_sigma::data_modifier_outlier_remove_sigma (ksi::data_modifier_outlier_remove_sigma  && dm): ksi::data_modifier(dm), _n(dm._n)
{
}

ksi::data_modifier_outlier_remove_sigma::data_modifier_outlier_remove_sigma(const ksi::data_modifier_outlier_remove_sigma & dm): data_modifier(dm), _n(dm._n)
{
}

ksi::data_modifier_outlier_remove_sigma::data_modifier_outlier_remove_sigma(const double n) : data_modifier(), _n(n)
{
   description = "outlier remove with sigma approach";
}

ksi::data_modifier_outlier_remove_sigma & ksi::data_modifier_outlier_remove_sigma::operator=(ksi::data_modifier_outlier_remove_sigma && dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   _n = dm._n;
     
   return *this;
}

ksi::data_modifier_outlier_remove_sigma & ksi::data_modifier_outlier_remove_sigma::operator=(const ksi::data_modifier_outlier_remove_sigma& dm)
{
   if (this == & dm)
      return *this;
   
   ksi::data_modifier::operator=(dm);
   
   _n = dm._n;
   
   return *this;   
}

ksi::data_modifier_outlier_remove_sigma::~data_modifier_outlier_remove_sigma()
{
}

void ksi::data_modifier_outlier_remove_sigma::modify(ksi::dataset & ds)
{
   try
   {
       // dwie iteracje:
       // 1. policzyc odchylenie standardowe (sigma)
       
       
      // no i tu sie zaczyna zabawa :-) 
      size_t nAttributes = ds.getNumberOfAttributes();
      size_t nDataItems = ds.getNumberOfData();
      std::vector<double> sums   (nAttributes, 0);
      std::vector<double> sqsums (nAttributes, 0);
      
         
      for (size_t k = 0; k < nAttributes; k++)
         sums[k] = sqsums[k] = 0.0;

      for (size_t w = 0; w < nDataItems; w++)
      {
         for (size_t k = 0; k < nAttributes; k++)
         {
            double value = ds.get(w, k);

            sums[k] += value;
            sqsums[k] += (value * value);
         }
      }
      
      // no i teraz wyznaczam srednia i odchylenie
      
      std::vector<double> averages (nAttributes, 0);
      std::vector<double> stddevs  (nAttributes, 0);
      
      for (size_t k = 0; k < nAttributes; k++)
      {
         averages[k] = sums[k] / nDataItems;
         stddevs[k]  = std::sqrt (sqsums[k] / nDataItems - pow(averages[k], 2));
      }
      
      
      // 2. usunac odstajace wartosci
       
      ksi::dataset nowy_zbior_danych;
      
      for (size_t w = 0; w < nDataItems; w++)
      {
          bool doUsuniecia = false;
          for (size_t k = 0; k < nAttributes and not doUsuniecia; k++)
          {
              double value = ds.get(w, k);
              if (std::abs(value - averages[k]) > _n * stddevs[k])
                  doUsuniecia = true;
          }
          
          if (not doUsuniecia) // kopiujemy dana
              nowy_zbior_danych.addDatum(* ds.getDatum(w));
      }
      
      // i tyle
      ds = nowy_zbior_danych;
            
      
      // and call pNext modifier
      if (pNext)
         pNext->modify(ds);
      
   }
   CATCH;   
}





