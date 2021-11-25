
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_minkowski_regression.h"

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/prototype_minkowski_regression.h"

#include "../metrics/metric-minkowski.h"

ksi::fac_prototype_minkowski_regression::fac_prototype_minkowski_regression (const double m) : ksi::fac_prototype_minkowski (m)
{
}

ksi::fac_prototype_minkowski_regression::~fac_prototype_minkowski_regression ()
{
   // delete what is to delete

}

ksi::fac_prototype_minkowski_regression::fac_prototype_minkowski_regression (const ksi::fac_prototype_minkowski_regression & wzor) : ksi::fac_prototype_minkowski(wzor)
{
   // copy what is to copy
   _m = wzor._m;
}

ksi::fac_prototype_minkowski_regression & ksi::fac_prototype_minkowski_regression::operator= (const ksi::fac_prototype_minkowski_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_minkowski::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
   
   _m = wzor._m;

   return *this;
}

ksi::fac_prototype_minkowski_regression::fac_prototype_minkowski_regression (ksi::fac_prototype_minkowski_regression && wzor) : ksi::fac_prototype_minkowski(wzor)
{
   // swap what is to swap
   std::swap(_m, wzor._m);
}

ksi::fac_prototype_minkowski_regression & ksi::fac_prototype_minkowski_regression::operator= (ksi::fac_prototype_minkowski_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_minkowski::operator=(wzor);

   // swap what is to swap
   std::swap(_m, wzor._m);

   return *this;
}


std::shared_ptr<ksi::prototype> ksi::fac_prototype_minkowski_regression::get_prototype() const
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_minkowski_regression (_m));
}

std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_minkowski_regression::clone() const
{
    return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_minkowski_regression(*this));
}

// std::shared_ptr<ksi::metric> ksi::fac_prototype_minkowski_regression::get_metric() const
// {
//     return std::shared_ptr<ksi::metric_minkowski> (new ksi::metric_minkowski(_m));
// }
