/** @file */


#include "number.h"

#include <algorithm>
#include <iostream>

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

ksi::number::number()
{
   value = upper_value = 0.0;
   _isInterval = false;
   _exists = false;
}


ksi::number::number(double lower, double upper)
{
   value = lower;
   upper_value = upper;
   _isInterval = true;
   _exists = true;
}

ksi::number::number(const ksi::number& wzor)
{
   value = wzor.value;
   upper_value = wzor.upper_value;
   _isInterval = wzor._isInterval;
   _exists = wzor._exists;
}

ksi::number::number(ksi::number&& wzor)
{
   std::swap(value, wzor.value);
   std::swap(upper_value, wzor.upper_value);
   std::swap(_isInterval, wzor._isInterval);
   std::swap(_exists, wzor._exists);
}

ksi::number::number(double d)
{
   value = upper_value = d;
   _isInterval = false;
   _exists = true;
}

ksi::number& ksi::number::operator=(const ksi::number& wzor)
{
   if (this == &wzor)
      return *this;
   
   value = wzor.value;
   upper_value = wzor.upper_value;
   _isInterval = wzor._isInterval;
   _exists = wzor._exists;
   
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
   
   return *this;
}

void ksi::number::setValue(double lower, double upper)
{
   value = lower;
   upper_value = upper;
   _isInterval = true;
   _exists = true;
}

void ksi::number::setValue(double d)
{
   value = upper_value = d;
   _isInterval = false;
   _exists = true;
}

void ksi::number::setValue(bool exists)
{
   _exists = exists;
}

ksi::number ksi::number::operator+(const ksi::number& right)
{
   if (not _exists and not right._exists)
      return ksi::number(false);
   else if (_exists and not right._exists)
      return *this;
   else if (not _exists and right._exists)
      return right;   
   else if (this->_exists and right._exists)
   {
      ksi::number result (0.0);
  
      result.value = value + right.value;
      result.upper_value = upper_value + right.upper_value;
      result._exists = true; 
      result._isInterval = _isInterval or right._isInterval;
      return result;
   }
}

ksi::number& ksi::number::operator+=(const ksi::number& right)
{
   if (not _exists and not right._exists)
      return *this;
   else if (_exists and not right._exists)
      return *this;
   else if (not _exists and right._exists)
      return *this = right;   
   else if (this->_exists and right._exists)
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
            ss << "(" << d.value << ", " << d.upper_value << ")";
         else
            ss << d.value;
      }
      return ss;
   }
}
