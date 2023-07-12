
#ifndef FAC_PROTOTYPE_MAHALANOBIS_REGRESSION_H
#define FAC_PROTOTYPE_MAHALANOBIS_REGRESSION_H

#include <memory>

#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"

namespace ksi
{
   class fac_prototype_mahalanobis_regression : public fac_prototype_mahalanobis
   {
    public:
      fac_prototype_mahalanobis_regression (const Matrix<double> & A);
      fac_prototype_mahalanobis_regression (const fac_prototype_mahalanobis_regression & wzor) = default;
      fac_prototype_mahalanobis_regression (fac_prototype_mahalanobis_regression && wzor) = default;
      fac_prototype_mahalanobis_regression & operator= (const fac_prototype_mahalanobis_regression & wzor) = default;
      fac_prototype_mahalanobis_regression & operator= (fac_prototype_mahalanobis_regression && wzor) = default;
      virtual ~fac_prototype_mahalanobis_regression ();
      // virtual fac_prototype_mahalanobis * clone () const;  // prototype design pattern
      
      public:
      virtual std::shared_ptr<prototype> get_prototype() const override; 
      virtual std::shared_ptr<prototype> get_prototype_for_cluster(const cluster & cl) override;
//       virtual std::shared_ptr<metric> get_metric() const override;
      virtual std::shared_ptr<fac_prototype> clone () const override;
   };
 
}


#endif
