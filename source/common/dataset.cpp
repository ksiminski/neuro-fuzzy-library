/** @file */


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include "dataset.h"
#include "../service/debug.h"



ksi::dataset::dataset(const ksi::dataset & ds)
{
   for (auto & p : ds.data)
      data.push_back(p->clone());
   
   _maximalNumberLabel = ds._maximalNumberLabel;
}


ksi::dataset::dataset(ksi::dataset && ds)
{
   std::swap (data, ds.data);
   std::swap ( _maximalNumberLabel, ds._maximalNumberLabel );
}

ksi::dataset::dataset()
{
}

ksi::dataset::~dataset()
{
   for (auto & p : data)
   {
      delete p;
      p = nullptr;
   }
}

ksi::dataset& ksi::dataset::operator=(const ksi::dataset& ds)
{
   if (this == & ds)
      return *this;
   
   for (auto & p : data)
      delete p;
   
   data.clear();
   
   for (auto & p : ds.data)
      data.push_back(p->clone());
   
   _maximalNumberLabel = ds._maximalNumberLabel;
   return *this;
}


ksi::dataset& ksi::dataset::operator=(ksi::dataset&& ds)
{
   if (this == & ds)
      return *this;
   
   std::swap (data, ds.data);
   std::swap ( _maximalNumberLabel, ds._maximalNumberLabel );
   
   return *this;
}

void ksi::dataset::addDatum(const ksi::datum d)
{
   data.push_back(new ksi::datum(d));
   if (_maximalNumberLabel < d.getID())
       _maximalNumberLabel = d.getID();
}

void ksi::dataset::addDatum(ksi::datum * p)
{
   data.push_back(p);
   if (_maximalNumberLabel < p->getID())
       _maximalNumberLabel = p->getID();
}

std::size_t ksi::dataset::getMaximalNumericalLabel() const
{
    return _maximalNumberLabel;
}

void ksi::dataset::setMaximalNumericalLabel(std::size_t id)
{
    _maximalNumberLabel = id;
}


std::size_t ksi::dataset::getNumberOfData() const
{
   return data.size();
}

std::size_t ksi::dataset::getNumberOfAttributes() const
{
   if (data.size() > 0)
      return data[0]->getNumberOfAttributes();
   else 
      return 0;
}

double ksi::dataset::get (std::size_t row, std::size_t col) const 
{
   try 
   {
      if (row < 0 and row >= data.size())
      {
         std::stringstream ss;
         ss << "Incorrect row index, row == " << row << "." << std::endl;
         ss << "Valid values: 0, ... , " << data.size() - 1 << std::endl;
         throw ss.str();
      }
      else
         return data[row]->at(col)->getValue();
   }
   CATCH;
}

bool ksi::dataset::exists(std::size_t row, std::size_t col) const 
{
   try 
   {
      if (row < 0 and row >= data.size())
      {
         std::stringstream ss;
         ss << "Incorrect row index, row == " << row << "." << std::endl;
         ss << "Valid values: 0, ... , " << data.size() - 1 << std::endl;
         throw ss.str();
      }
      else
         return data[row]->at(col)->exists();
   }
   CATCH;
}


void ksi::dataset::set (std::size_t row, std::size_t col, double value)
{
   try 
   {
      if (row < 0 and row >= data.size())
      {
         std::stringstream ss;
         ss << "Incorrect row index, row == " << row << "." << std::endl;
         ss << "Valid values: 0, ... , " << data.size() - 1 << std::endl;
         throw ss.str();
      }
       
      data[row]->at(col)->setValue(value);
   }
   CATCH;
}

std::vector<std::vector<double>> ksi::dataset::getMatrix() const
{
   try 
   {
      std::size_t nRow = getNumberOfData();
      std::size_t nCol = getNumberOfAttributes();
      
      std::vector<std::vector<double>> wynik (nRow);
      for (std::size_t w = 0; w < nRow; w++)
      {
         wynik[w] = std::vector<double> (nCol);
         for (std::size_t k = 0; k < nCol; k++)
         {
            wynik[w][k] = get(w, k);
         }
      }
      
      return wynik;
   }
   CATCH;
} 

ksi::datum * ksi::dataset::getDatum(std::size_t r) const
{
   try
   {
      if (r < 0 or r >= data.size())
         return nullptr;
      return data[r];
   }
   CATCH;
}

void ksi::dataset::resetIDs()
{
   try
   {
      auto maxi = getNumberOfData();
      for (long int i = 0; i < maxi; i++)
      {
         data[i]->setID(i);
         data[i]->setIDincomplete(-1);
      }
      
   }
   CATCH;
}


namespace ksi
{
   std::ostream& operator<<(std::ostream& ss, const ksi::dataset & d)
   {
      const int WIDTH = 10;
      auto rows = d.getNumberOfData();
      auto cols = d.getNumberOfAttributes();
      
      for (std::size_t w = 0; w < rows; w++)
      {
         ss << *(d.getDatum(w));
         /*
         for (std::size_t k = 0; k < cols; k++)
         {
            if (d.data[w]->at(k)->exists())
               ss << std::setw(WIDTH) << d.data[w]->at(k)->getValue();
            else
               ss << std::setw(WIDTH) << d.MISSING_VALUE_SYMBOL;
         }
         */
         ss << std::endl;
      }
      
      
      return ss;
   }
}

std::pair< ksi::dataset, ksi::dataset > ksi::dataset::splitDataSetVertically(
   std::size_t last_index) const
{
   dataset left, right;
   
   for (auto & d : data)
   {
      auto para = d->splitDatum(last_index);
      left.addDatum(para.first);
      right.addDatum(para.second);
   }
      
   return { left, right }; 
}
