
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"

#include "../metrics/metric_mahalanobis.h"

#include "../auxiliary/matrix.h"

ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis () 
{
}

ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis (const ksi::Matrix<double> & A) : _A (A)
{
}

ksi::fac_prototype_mahalanobis::~fac_prototype_mahalanobis ()
{
   // delete what is to delete

}

/*
ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis (const ksi::fac_prototype_mahalanobis & wzor) : ksi::fac_prototype(wzor)
{
   // copy what is to copy
   _m = wzor._m;
}

ksi::fac_prototype_mahalanobis & ksi::fac_prototype_mahalanobis::operator= (const ksi::fac_prototype_mahalanobis & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
   
   _m = wzor._m;

   return *this;
}

ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis (ksi::fac_prototype_mahalanobis && wzor) : ksi::fac_prototype(wzor)
{
   // swap what is to swap
   std::swap(_m, wzor._m);
}

ksi::fac_prototype_mahalanobis & ksi::fac_prototype_mahalanobis::operator= (ksi::fac_prototype_mahalanobis && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype::operator=(wzor);

   // swap what is to swap
   std::swap(_m, wzor._m);

   return *this;
}
*/

// std::shared_ptr<ksi::prototype> ksi::fac_prototype_mahalanobis::get_prototype() const
// {
//     return std::shared_ptr<ksi::prototype> (new ksi::prototype_minkowski (_m));
// }

// std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_mahalanobis::clone() const
// {
//     return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_mahalanobis(*this));
// }

std::shared_ptr<ksi::metric> ksi::fac_prototype_mahalanobis::get_metric() const
{
    return std::shared_ptr<ksi::metric_mahalanobis> (new ksi::metric_mahalanobis(_A));
}
