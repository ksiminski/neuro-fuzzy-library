/** @file */ 

#include <cmath>
#include <array>

#include "descriptor-constant.h"
#include "../service/debug.h"

std::string ksi::descriptor_constant::getName() const
{
   return std::string {"constant"};
}


const std::array<std::string, 5> ksi::descriptor_constant::constantLocationDescription
{
    "false",
        "low",
        "medium",
        "high",
        "true"
};

ksi::descriptor_constant::~descriptor_constant()
{

}


ksi::descriptor_constant::descriptor_constant (const double value)
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

std::ostream& ksi::descriptor_constant::print(std::ostream& ss) const
{
   ss << "descriptor: constant" << std::endl;
   ss << "   value: " << _value << std::endl;
   return ss;
}

std::ostream& ksi::descriptor_constant::printLinguisticDescription(std::ostream& ss, const DescriptorStatistics& descStat) const
{
    if (_value == 1.0)
		ss << constantLocationDescription.back();
    else if (_value == 0.0)
        ss << constantLocationDescription.front();
    else
    {
        std::size_t range = constantLocationDescription.size() - 2;
        ss << constantLocationDescription[ceil(_value * range)];
    }

    return ss << " for all";
}

std::vector< double > ksi::descriptor_constant::getMAconsequenceParameters() const
{
   return { std::nan(""), std::nan(""), std::nan("") };
}

double ksi::descriptor_constant::getRandomValue(std::default_random_engine& engine)
{
    return _value;
}

 
