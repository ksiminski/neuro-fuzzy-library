
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis_regression.h"

#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (m)
{
}

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::cluster & cl, const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (cl, m)
{
}

ksi::prototype_mahalanobis_regression::~prototype_mahalanobis_regression ()
{
   // delete what is to delete

}

std::pair<std::vector<double>,  ksi::Matrix<double>> ksi::prototype_mahalanobis_regression::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double>& Y)
{
   /// @todo brak implementacji
   return { {}, {} };
}


/*
ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::prototype_mahalanobis_regression & wzor) : ksi::prototype_mahalanobis(wzor)
{
   // copy what is to copy

}

ksi::prototype_mahalanobis_regression & ksi::prototype_mahalanobis_regression::operator= (const ksi::prototype_mahalanobis_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (ksi::prototype_mahalanobis_regression && wzor) : ksi::prototype_mahalanobis(wzor)
{
   // swap what is to swap

}

ksi::prototype_mahalanobis_regression & ksi::prototype_mahalanobis_regression::operator= (ksi::prototype_mahalanobis_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::prototype_mahalanobis * ksi::prototype_mahalanobis_regression::clone () const
{
   // prototype design pattern
   return new ksi::prototype_mahalanobis_regression(*this);
}
*/


