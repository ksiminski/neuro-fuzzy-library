
#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/prototype_mahalanobis_classification.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis_classification.h"

ksi::fac_prototype_mahalanobis_classification::fac_prototype_mahalanobis_classification (const ksi::Matrix<double> & A) : ksi::fac_prototype_mahalanobis (A)
{
}

ksi::fac_prototype_mahalanobis_classification::~fac_prototype_mahalanobis_classification ()
{
   // delete what is to delete

}
/*
ksi::fac_prototype_mahalanobis_classification::fac_prototype_mahalanobis_classification (const ksi::fac_prototype_mahalanobis_classification & wzor) : ksi::fac_prototype_mahalanobis(wzor)
{
   // copy what is to copy

}

ksi::fac_prototype_mahalanobis_classification & ksi::fac_prototype_mahalanobis_classification::operator= (const ksi::fac_prototype_mahalanobis_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_mahalanobis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::fac_prototype_mahalanobis_classification::fac_prototype_mahalanobis_classification (ksi::fac_prototype_mahalanobis_classification && wzor) : ksi::fac_prototype_mahalanobis(wzor)
{
   // swap what is to swap

}

ksi::fac_prototype_mahalanobis_classification & ksi::fac_prototype_mahalanobis_classification::operator= (ksi::fac_prototype_mahalanobis_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fac_prototype_mahalanobis::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::fac_prototype_mahalanobis * ksi::fac_prototype_mahalanobis_classification::clone () const
{
   // prototype design pattern
   return new ksi::fac_prototype_mahalanobis_classification(*this);
}


*/

std::shared_ptr<ksi::prototype> ksi::fac_prototype_mahalanobis_classification::get_prototype() const
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_mahalanobis_classification (_A));
}

std::shared_ptr<ksi::prototype> ksi::fac_prototype_mahalanobis_classification::get_prototype_for_cluster(const ksi::cluster & cl) 
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_mahalanobis_classification (cl, _A));
}



std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_mahalanobis_classification::clone() const
{
    return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_mahalanobis_classification(*this));
}
