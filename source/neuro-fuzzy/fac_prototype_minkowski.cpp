
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_minkowski.h"

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"

#include "../metrics/metric-minkowski.h"

ksi::fac_prototype_minkowski::fac_prototype_minkowski (const double m) : _m (m)
{
}

ksi::fac_prototype_minkowski::~fac_prototype_minkowski ()
{
   // delete what is to delete

}

ksi::fac_prototype_minkowski::fac_prototype_minkowski (const ksi::fac_prototype_minkowski & wzor) : ksi::fac_prototype(wzor)
{
   // copy what is to copy
   _m = wzor._m;
}

ksi::fac_prototype_minkowski & ksi::fac_prototype_minkowski::operator= (const ksi::fac_prototype_minkowski & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
   
   _m = wzor._m;

   return *this;
}

ksi::fac_prototype_minkowski::fac_prototype_minkowski (ksi::fac_prototype_minkowski && wzor) : ksi::fac_prototype(wzor)
{
   // swap what is to swap
   std::swap(_m, wzor._m);
}

ksi::fac_prototype_minkowski & ksi::fac_prototype_minkowski::operator= (ksi::fac_prototype_minkowski && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype::operator=(wzor);

   // swap what is to swap
   std::swap(_m, wzor._m);

   return *this;
}


// std::shared_ptr<ksi::prototype> ksi::fac_prototype_minkowski::get_prototype() const
// {
//     return std::shared_ptr<ksi::prototype> (new ksi::prototype_minkowski (_m));
// }

// std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_minkowski::clone() const
// {
//     return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_minkowski(*this));
// }

std::shared_ptr<ksi::metric> ksi::fac_prototype_minkowski::get_metric() const
{
    return std::shared_ptr<ksi::metric_minkowski> (new ksi::metric_minkowski(_m));
}
