/** @file */

#include <cmath>
#include <iostream>
#include <vector>
#include "extensional-fuzzy-number-gaussian.h"

const double ksi::ext_fuzzy_number_gaussian::MINIMAL_SIGMA = 1e-6;

double ksi::ext_fuzzy_number_gaussian::get_value() const
{
    return _x;
}

double ksi::ext_fuzzy_number_gaussian::get_sigma() const
{
    return _sigma;
}

ksi::ext_fuzzy_number_gaussian::ext_fuzzy_number_gaussian() : _x(0.0), _sigma (MINIMAL_SIGMA)
{
}

ksi::ext_fuzzy_number_gaussian::ext_fuzzy_number_gaussian(double x) : _x(x), _sigma (MINIMAL_SIGMA)
{
}

ksi::ext_fuzzy_number_gaussian::ext_fuzzy_number_gaussian(double x, double sigma) : _x (x), _sigma (sigma) 
{
   if (_sigma < MINIMAL_SIGMA)
      _sigma = MINIMAL_SIGMA;
}

ksi::ext_fuzzy_number_gaussian::~ext_fuzzy_number_gaussian()
{
}

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::operator-() const
{
   return ksi::ext_fuzzy_number_gaussian(-_x, _sigma);
}

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::operator+(const ksi::ext_fuzzy_number_gaussian& op) const
{
   ksi::ext_fuzzy_number_gaussian result (_x + op._x, std::max (_sigma, op._sigma));
   return result;
}

ksi::ext_fuzzy_number_gaussian & ksi::ext_fuzzy_number_gaussian::operator+=(const ksi::ext_fuzzy_number_gaussian& op)
{
   _x += op._x;
   _sigma = std::max (_sigma, op._sigma);
   return *this;
}

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::operator-(const ksi::ext_fuzzy_number_gaussian & op) const
{
   return *this + (-op);
}

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::operator*(const ksi::ext_fuzzy_number_gaussian& op) const
{
   ksi::ext_fuzzy_number_gaussian result (_x * op._x, std::max (_sigma, op._sigma));
   return result;
}

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::operator/(const ksi::ext_fuzzy_number_gaussian& op) const
{
   ksi::ext_fuzzy_number_gaussian result (_x / op._x, std::max (_sigma, op._sigma));
   return result;
}

ksi::ext_fuzzy_number_gaussian & ksi::ext_fuzzy_number_gaussian::operator/= (const ksi::ext_fuzzy_number_gaussian& op) 
{
   _x /= op._x;
   _sigma = std::max (_sigma, op._sigma);
   return *this;
}

bool ksi::ext_fuzzy_number_gaussian::operator > (const double op) const
{
   return _x > op;
}

bool ksi::ext_fuzzy_number_gaussian::operator==(const double op) const
{
   return _x == op;
}

ksi::ext_fuzzy_number_gaussian::operator double() const
{
    return _x;
}


ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::pow(const ksi::ext_fuzzy_number_gaussian & base, double exponent)
{
   return ksi::ext_fuzzy_number_gaussian (std::pow(base._x, exponent), base._sigma); 
} 

ksi::ext_fuzzy_number_gaussian ksi::ext_fuzzy_number_gaussian::sqrt(const ksi::ext_fuzzy_number_gaussian& radicand)
{
   return ksi::ext_fuzzy_number_gaussian (std::sqrt(radicand._x), radicand._sigma); 
}

std::vector<std::vector<double>> ksi::ext_fuzzy_number_gaussian::matrix_of_extensional_fuzzy_number_2_double (const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & matrix)
{
    std::vector<std::vector<double>> result;
    for (const auto & row : matrix)
    {
        std::vector<double> row_of_doubles;
        for (const auto & number : row)
            row_of_doubles.push_back((double) number);
        result.push_back(row_of_doubles);
    }
    return result;
}


namespace ksi
{
   std::ostream & operator << (std::ostream & ss, const ksi::ext_fuzzy_number_gaussian & number)
   {
      ss << "(" << number._x << ", " << number._sigma << ")";
      return ss; 
   }
}

