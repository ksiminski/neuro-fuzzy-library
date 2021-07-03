/** @file */


#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "dataset.h"
#include "../service/debug.h"
#include "../common/extensional-fuzzy-number-gaussian.h"

void ksi::dataset::remove_untypical_data(const double minimal_typicality)
{
    std::vector<datum *> typical_data;
    
    auto size = data.size();
    for (std::size_t i = 0; i < size; i++)
    {
        if (not data[i]->isTypicalityOn() or data[i]->getTypicality() >= minimal_typicality)
        {
            typical_data.push_back(data[i]);
          //  debug(data[i]->getNumberOfAttributes());
            data[i] = nullptr;
        }
    }
    
    for (auto & p : data)
        if (p)
            delete p;
        
    data = typical_data;
}

void ksi::dataset::remove_untypical_data(const std::vector<bool>& typical_data)
{
    try 
    {
        if (data.size() != typical_data.size())
        {
            std::stringstream ss;
            ss << "The size of dataset (" << data.size() << ") does not match the size of passed vector (" << typical_data.size() << ")." << std::endl;
            throw ksi::exception (ss.str());
        }
        
        std::vector<datum *> typical_dataset;
        
        auto size = data.size();
        for (std::size_t i = 0; i < size; i++)
        {
            if (typical_data[i])
            {
                typical_dataset.push_back(data[i]);
                data[i] = nullptr;
            }
        }
        
        for (auto & p : data)
            if (p)
                delete p;
            
        data = typical_dataset;
    }
    CATCH;
}


std::vector<bool> ksi::dataset::get_if_data_typical(const double minimal_typicality)
{
    auto size = data.size();
    std::vector<bool> results(size, false);
    
    for (std::size_t i = 0; i < size; i++)
    {
        if (not data[i]->isTypicalityOn() or data[i]->getTypicality() >= minimal_typicality)
            results[i] = true;
    }
    
    return results;
}



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


ksi::dataset::dataset(const std::vector<std::vector<double>> & matrix_of_numbers)
{
    for (const auto row : matrix_of_numbers)
    {
        ksi::datum tuple;
        for (const auto number : row)
        {
            ksi::number liczba (number);
            tuple.push_back(number);
        }
        addDatum(tuple);    
    }
}

ksi::dataset::dataset(const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & matrix_of_numbers)
{
    for (const auto row : matrix_of_numbers)
    {
        ksi::datum tuple;
        for (const auto number : row)
        {
            ksi::number liczba (number);
            tuple.push_back(number);
        }
        addDatum(tuple);    
    }
}


ksi::dataset& ksi::dataset::operator=(ksi::dataset&& ds)
{
   if (this == & ds)
      return *this;
   
   std::swap (data, ds.data);
   std::swap ( _maximalNumberLabel, ds._maximalNumberLabel );
   
   return *this;
}

void ksi::dataset::addDatum(const ksi::datum & d)
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

ksi::ext_fuzzy_number_gaussian ksi::dataset::getFuzzyNumber(std::size_t row, std::size_t col) const
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
         return data[row]->at(col)->getFuzzyNumber();
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

std::vector<std::vector<double> > ksi::dataset::getMatrix(double) const
{
   try 
   {
      return getMatrix();
   }
   CATCH;
}


std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> ksi::dataset::getMatrixOfFuzzyNumbers() const
{
   try 
   {
      std::size_t nRow = getNumberOfData();
      std::size_t nCol = getNumberOfAttributes();
      
      std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> wynik (nRow);
      for (std::size_t w = 0; w < nRow; w++)
      {
         wynik[w] = std::vector<ksi::ext_fuzzy_number_gaussian> (nCol);
         for (std::size_t k = 0; k < nCol; k++)
         {
            wynik[w][k] = getFuzzyNumber(w, k);
         }
      }
      
      return wynik;
   }
   CATCH;
} 

std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> ksi::dataset::getMatrix(ksi::ext_fuzzy_number_gaussian) const
{
   try
   {
      return getMatrixOfFuzzyNumbers();
   }
   CATCH;
}


const ksi::datum * ksi::dataset::getDatum(std::size_t r) const
{
   try
   {
      if (r < 0 or r >= data.size())
         return nullptr;
      return data[r];
   }
   CATCH;
}

ksi::datum * ksi::dataset::getDatumNonConst(std::size_t r) const
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
   std::ostream & operator<<(std::ostream& ss, const ksi::dataset & d)
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

ksi::dataset ksi::dataset::subdataset(const std::size_t start_index, const std::size_t end_index) const
{
    ksi::dataset result;
    std::size_t maximal_index = getNumberOfData() - 1;
    std::size_t _start = start_index;
    std::size_t _end   = std::min (maximal_index, end_index);
    
    for (auto i = _start; i <= _end; i++)
       result.data.push_back(data[i]->clone());
    
    return result;
}

ksi::dataset & ksi::dataset::operator += (const ksi::dataset& ds)
{
    try 
    {
        if (getNumberOfAttributes() != ds.getNumberOfAttributes())
        {
            std::stringstream ss;
            ss << "Numbers of attributes in both data sets do not match!" << std::endl;
            ss << "left operand (*this), number of attributes: " << getNumberOfAttributes() << std::endl;
            ss << "right operand,        number of attributes: " << 
            ds.getNumberOfAttributes();
            
            throw ss.str();
        }
        
        std::size_t N = ds.getNumberOfData();
        
        for (std::size_t i = 0; i < N; i++)
            this->addDatum(*(ds.getDatum(i)));
        
        return *this;
    }
    CATCH;
}


std::pair<ksi::dataset, ksi::dataset> ksi::dataset::cufOffLastAttribute() const
{
    ksi::dataset first, second;
    auto size = getNumberOfData();
    for (std::size_t i = 0; i < size; i++)
    {
        auto res = getDatum(i)->cutOffLastAttribute();
        first.addDatum(res.first);
        second.addDatum(res.second);
    }
    return {first, second};
}

std::pair<ksi::dataset, ksi::dataset> ksi::dataset::splitDataSetHorizontally(std::size_t N) const
{
    ksi::dataset first, second;
    auto size = getNumberOfData();
    
    std::size_t i;
    for (i = 0; i < N and i < size; i++)
        first.addDatum(*(getDatum(i)));
    for ( ; i < size; i++)
        second.addDatum(*(getDatum(i)));
    
    return { first, second }; 
}
