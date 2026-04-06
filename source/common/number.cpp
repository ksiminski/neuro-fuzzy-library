/** @file */


#include "number.h"
#include "../common/extensional-fuzzy-number-gaussian.h"

#include <algorithm>
#include <iostream>

ksi::number::number(const ksi::ext_fuzzy_number_gaussian & wzor)
{
    value = wzor.get_value();
    _sigma = wzor.get_sigma();
    
   upper_value = value;
   _isInterval = false;
   _exists = true;   
   
}

ksi::number::~number()
{
}

ksi::number* ksi::number::clone() const
{
   return new ksi::number (*this);
}


bool ksi::number::exists() const
{
   return _exists;
}

void ksi::number::make_non_existing()
{
   _exists = false;
}


double ksi::number::getUpperValue() const
{
   return upper_value;
}

double ksi::number::getValue() const
{
   return value;
}

bool ksi::number::isInterval() const
{
   return _isInterval;
}

ksi::ext_fuzzy_number_gaussian ksi::number::getFuzzyNumber() const
{
   return ext_fuzzy_number_gaussian (value, _sigma);
}

void ksi::number::setSigma(double sigma)
{
   _sigma = sigma;
}


ksi::number::number()
{
   value = upper_value = 0.0;
   _isInterval = false;
   _exists = false;
   _sigma = 0.0;
}


ksi::number::number(double lower, double upper)
{
   value = lower;
   upper_value = upper;
   _isInterval = true;
   _exists = true;   
   _sigma = 0.0;
}

ksi::number::number(const ksi::number& wzor)
{
   value = wzor.value;
   upper_value = wzor.upper_value;
   _isInterval = wzor._isInterval;
   _exists = wzor._exists;
   _sigma = wzor._sigma;
}

ksi::number::number(ksi::number&& wzor)
{
   std::swap(value, wzor.value);
   std::swap(upper_value, wzor.upper_value);
   std::swap(_isInterval, wzor._isInterval);
   std::swap(_exists, wzor._exists);
   std::swap(_sigma, wzor._sigma);
}

ksi::number::number(double d)
{
   value = upper_value = d;
   _isInterval = false;
   _exists = true;
   _sigma = 0.0;
}

ksi::number& ksi::number::operator=(const ksi::number& wzor)
{
   if (this == &wzor)
      return *this;
   
   value = wzor.value;
   upper_value = wzor.upper_value;
   _isInterval = wzor._isInterval;
   _exists = wzor._exists;
   _sigma = wzor._sigma;
   
   return *this;
}

ksi::number& ksi::number::operator=(ksi::number&& wzor)
{
   if (this == &wzor)
      return *this;
   
   std::swap(value, wzor.value);
   std::swap(upper_value, wzor.upper_value);
   std::swap(_isInterval, wzor._isInterval);
   std::swap(_exists, wzor._exists);
   std::swap(_sigma, wzor._sigma);
   
   return *this;
}

void ksi::number::setValue(double lower, double upper)
{
   value = lower;
   upper_value = upper;
   _isInterval = true;
   _exists = true;
   _sigma = 0.0;
}

void ksi::number::setValue(double d)
{
   value = upper_value = d;
   _isInterval = false;
   _exists = true;
   _sigma = 0.0;
}

void ksi::number::setValue(bool exists)
{
   _exists = exists;
}

ksi::number ksi::number::operator+(const ksi::number& right)
{
   if      (not _exists and not right._exists)
      return ksi::number(false);
   else if (    _exists and not right._exists)
      return *this;
   else if (not _exists and     right._exists)
      return right;   
   else //if (_exists and right._exists)
   {
      ksi::number result (0.0);
  
      result.value = value + right.value;
      result.upper_value = upper_value + right.upper_value;
      result._exists = true; 
      result._isInterval = _isInterval or right._isInterval;
      result._sigma = std::max(_sigma, right._sigma);
      return result;
   }
}

ksi::number& ksi::number::operator+=(const ksi::number& right)
{
   if      (not _exists and not right._exists)
      return *this;
   else if (    _exists and not right._exists)
      return *this;
   else if (not _exists and     right._exists)
      return *this = right;   
   else //if (    _exists and     right._exists)
   {
      *this = *this + right;
      return *this;
   }
}

ksi::number ksi::number::operator/(const double d)
{
   if (not _exists)
      return *this;
   else
   {
      ksi::number result (*this);
      result.value /= d;
      result.upper_value /= d;
      return result;
   }
}

namespace ksi 
{
   std::ostream & operator<< (std::ostream & ss, const ksi::number & d)
   {
      if (not d.exists())
         ss << "?";
      else
      {
         if (d.isInterval())
            ss << "[" << d.value << ", " << d.upper_value << "]";
         else
            ss << d.value;
         if (d._sigma > 0.0)
            ss << " (" << d._sigma << ")";
      }
      return ss;
   }
}
