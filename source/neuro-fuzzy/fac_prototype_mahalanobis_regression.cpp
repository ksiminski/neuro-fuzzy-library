
#include <memory> 

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis_regression.h"

#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis_regression.h"

ksi::fac_prototype_mahalanobis_regression::fac_prototype_mahalanobis_regression () 
{
}

ksi::fac_prototype_mahalanobis_regression::fac_prototype_mahalanobis_regression (const ksi::Matrix<double> & A) : ksi::fac_prototype_mahalanobis (A)
{
}

ksi::fac_prototype_mahalanobis_regression::~fac_prototype_mahalanobis_regression ()
{
   // delete what is to delete
}
/*
ksi::fac_prototype_mahalanobis_regression::fac_prototype_mahalanobis_regression (const ksi::fac_prototype_mahalanobis_regression & wzor) : ksi::fac_prototype_mahalanobis(wzor)
{
   // copy what is to copy

}

ksi::fac_prototype_mahalanobis_regression & ksi::fac_prototype_mahalanobis_regression::operator= (const ksi::fac_prototype_mahalanobis_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_mahalanobis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::fac_prototype_mahalanobis_regression::fac_prototype_mahalanobis_regression (ksi::fac_prototype_mahalanobis_regression && wzor) : ksi::fac_prototype_mahalanobis(wzor)
{
   // swap what is to swap

}

ksi::fac_prototype_mahalanobis_regression & ksi::fac_prototype_mahalanobis_regression::operator= (ksi::fac_prototype_mahalanobis_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_mahalanobis::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/
/*
ksi::fac_prototype_mahalanobis * ksi::fac_prototype_mahalanobis_regression::clone () const
{
   // prototype design pattern
   return new ksi::fac_prototype_mahalanobis_regression(*this);
}

*/

std::shared_ptr<ksi::prototype> ksi::fac_prototype_mahalanobis_regression::get_prototype() const
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_mahalanobis_regression (_A));
}

std::shared_ptr<ksi::prototype> ksi::fac_prototype_mahalanobis_regression::get_prototype_for_cluster(const ksi::cluster & cl) 
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_mahalanobis_regression (cl));
}

std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_mahalanobis_regression::clone() const
{
    return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_mahalanobis_regression(*this));
}

