
#include <random>
#include <chrono>
#include <algorithm>

#include "granule.h"
// #include "../neuro-fuzzy/rule.h"
#include "../service/debug.h"


std::default_random_engine ksi::granule::_engine;

ksi::granule::~granule ()
{
}

const double ksi::granule::get_cardinality() const
{
    return _cardinality;
}

double ksi::granule::get_quality() const
{
    return _quality;
}

void ksi::granule::set_quality(const double quality)
{
    _quality = std::min ( std::max ( quality, 0.0 ), 1.0);
}


void ksi::granule::reset_cardinality()
{
    _cardinality = 0.0;
}

ksi::granule::granule ()
{
    _engine.seed (std::chrono::system_clock::now().time_since_epoch().count());
    _cardinality = 1.0;
    _quality = -1.0;
    _error = 1.0;
}

ksi::granule::granule (const ksi::granule & wzor)
{
    _engine = wzor._engine;
    _cardinality = wzor._cardinality;
    _quality = wzor._quality;
    _error = wzor._error;
}

ksi::granule::granule (ksi::granule && wzor)
{
    std::swap(_engine, wzor._engine);
    std::swap(_cardinality, wzor._cardinality);
    std::swap(_quality, wzor._quality);
    std::swap(_error, wzor._error);
}

ksi::granule & ksi::granule::operator= (const ksi::granule & wzor)
{
   if (this == & wzor)
      return *this;

   _engine = wzor._engine;
   _cardinality = wzor._cardinality;
   _quality = wzor._quality;
   _error = wzor._error;

   return *this;
}

ksi::granule & ksi::granule::operator= (ksi::granule && wzor)
{
   if (this == & wzor)
      return *this;

   std::swap(_engine, wzor._engine);
   std::swap(_cardinality, wzor._cardinality);
   std::swap(_quality, wzor._quality);
   std::swap(_error, wzor._error);

   return *this;
}

void ksi::granule::set_cardinality(const double cardinality)
{
    _cardinality =  std::max ( cardinality, 0.0 );
}

double ksi::granule::get_error() const
{
    return _error;
}

void ksi::granule::set_error(const double error)
{
    _error = error;
}
 
ksi::rule * ksi::granule::get_rule()  const
{
    return nullptr;
}
