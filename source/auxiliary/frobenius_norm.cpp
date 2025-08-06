
#include "frobenius_norm.h"

#include <vector>
#include <format>
#include "../common/dataset.h"
#include "../auxiliary/matrix.h"
#include "../service/exception.h"

double ksi::frobenius_norm::get_frobenius_norm (const std::vector<std::vector<double>> & left, const std::vector<std::vector<double>> & right) const
{
   // Implementation for calculating Frobenius norm between two 2D vectors
   try 
   {
      if (left.size() != right.size())
      {
         throw ksi::exception(std::format("Frobenius norm: The number of rows in the left ({}) and right matrices ({}) must be equal.", left.size(), right.size()));
      }
      double sum = 0.0;
      for (size_t i = 0; i < left.size(); ++i)
      {
         for (size_t j = 0; j < left[i].size(); ++j)
         {
            double diff = left[i][j] - right[i][j];
            sum += diff * diff;
         }
      }
      return std::sqrt(sum);
   }
   CATCH;
}

double ksi::frobenius_norm::get_frobenius_norm (const ksi::dataset & left, const ksi::dataset & right) const
{
   // Implementation for calculating Frobenius norm between two datasets
   try 
   {
      return get_frobenius_norm(left.getMatrix(), right.getMatrix());
   }
   CATCH;
}

double ksi::frobenius_norm::get_frobenius_norm (const ksi::Matrix<double> & left, const ksi::Matrix<double> & right) const
{
   // Implementation for calculating Frobenius norm between two matrices
   try 
   {
      return get_frobenius_norm(left.getConstValues(), right.getConstValues());
   }
   CATCH;
}

/*
ksi::frobenius_norm::frobenius_norm ()
{
}

ksi::frobenius_norm::~frobenius_norm ()
{
   // delete what is to delete

}

ksi::frobenius_norm::frobenius_norm (const ksi::frobenius_norm & other)
{
   // copy what is to copy

}

ksi::frobenius_norm & ksi::frobenius_norm::operator= (const ksi::frobenius_norm & other)
{
   if (this == & other)
      return *this;


   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::frobenius_norm::frobenius_norm (ksi::frobenius_norm && other)
{
   // swap what is to swap

}

ksi::frobenius_norm & ksi::frobenius_norm::operator= (ksi::frobenius_norm && other)
{
   if (this == & other)
      return *this;


   // swap what is to swap

   return *this;
}

*/

