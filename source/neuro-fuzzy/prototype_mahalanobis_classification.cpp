
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis_classification.h"

#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (const Matrix<double> m) : ksi::prototype_mahalanobis (m)
{
}

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (const ksi::cluster & cl, const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (cl, m)
{
}

ksi::prototype_mahalanobis_classification::~prototype_mahalanobis_classification ()
{
   // delete what is to delete

}

std::pair<std::vector<double>,  ksi::Matrix<double>> ksi::prototype_mahalanobis_classification::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double>& Y)
{
   /// @todo brak implementacji
   return { {}, {} };
}


/*
ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (const ksi::prototype_mahalanobis_classification & wzor) : ksi::prototype_mahalanobis(wzor)
{
   // copy what is to copy

}

ksi::prototype_mahalanobis_classification & ksi::prototype_mahalanobis_classification::operator= (const ksi::prototype_mahalanobis_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (ksi::prototype_mahalanobis_classification && wzor) : ksi::prototype_mahalanobis(wzor)
{
   // swap what is to swap

}

ksi::prototype_mahalanobis_classification & ksi::prototype_mahalanobis_classification::operator= (ksi::prototype_mahalanobis_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::prototype_mahalanobis * ksi::prototype_mahalanobis_classification::clone () const
{
   // prototype design pattern
   return new ksi::prototype_mahalanobis_classification(*this);
}

*/

