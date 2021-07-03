/** @file */ 

#include <cmath>

#include "descriptor-constant.h"
#include "../service/debug.h"

ksi::descriptor_constant::~descriptor_constant()
{

}


ksi::descriptor_constant::descriptor_constant (double value)
{
   _previous_value = _value = value;
}

ksi::descriptor_constant::descriptor_constant (const descriptor_constant & wzor)
{
   _value = wzor._value;
   _previous_value = wzor._previous_value;
}

void ksi::descriptor_constant::reset_parameters()
{
   _value = _previous_value;
}

double ksi::descriptor_constant::getCoreMean() const
{
   return std::nan("");
}
      

double ksi::descriptor_constant::getMembership (double x)
{
   return _value;
}

ksi::descriptor * ksi::descriptor_constant::clone() const
{
   return new descriptor_constant(*this);
}

std::vector<double> ksi::descriptor_constant::getDifferentials(double x)
{
   try 
   {
      throw std::string ("not implemented yet");
   }
   CATCH;
   return  std::vector<double> {};
}

std::ostream& ksi::descriptor_constant::Print(std::ostream& ss) const
{
   ss << "(contant: " << _value << ")";
   return ss;
}

std::vector< double > ksi::descriptor_constant::getMAconsequenceParameters() const
{
   return { std::nan(""), std::nan(""), std::nan("") };
}

double ksi::descriptor_constant::getRandomValue(std::default_random_engine& engine)
{
    return _value;
}
