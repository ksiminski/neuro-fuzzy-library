
#ifndef PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H
#define PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H

#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/premise.h"

#include "../partitions/cluster.h"

namespace ksi
{
   class prototype_mahalanobis_classification : public prototype_mahalanobis
   {
    public:
      prototype_mahalanobis_classification (const Matrix<double> m);
      prototype_mahalanobis_classification (const cluster & cl, const Matrix<double> m);
      prototype_mahalanobis_classification (const prototype_mahalanobis_classification & wzor) = default;
      prototype_mahalanobis_classification (prototype_mahalanobis_classification && wzor) = default;
      prototype_mahalanobis_classification & operator= (const prototype_mahalanobis_classification & wzor) = default;
      prototype_mahalanobis_classification & operator= (prototype_mahalanobis_classification && wzor) = default;
      virtual ~prototype_mahalanobis_classification ();
      virtual premise * clone () const;  // prototype design pattern
      
   public:
      /** The method elaborates differentials for the justified granularity principle.
       @ date 2023-07-07                         *  *
       */  
      virtual
      std::pair<std::vector<double>,  ksi::Matrix<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) override;
   };
}


#endif
