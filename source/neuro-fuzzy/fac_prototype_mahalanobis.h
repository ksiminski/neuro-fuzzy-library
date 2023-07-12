
#ifndef FAC_PROTOTYPE_MAHALANOBIS_H
#define FAC_PROTOTYPE_MAHALANOBIS_H


#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/fac_prototype.h"
#include "../auxiliary/matrix.h"

namespace ksi
{
   class fac_prototype_mahalanobis : public fac_prototype
   {
   protected:
       Matrix<double> _A; ///< covariance matrix for the Mahalanobis metric
    public:
      fac_prototype_mahalanobis (const Matrix<double> & A);
      fac_prototype_mahalanobis (const fac_prototype_mahalanobis & wzor) = default; 
      fac_prototype_mahalanobis (fac_prototype_mahalanobis && wzor) = default;
      fac_prototype_mahalanobis & operator= (const fac_prototype_mahalanobis & wzor) = default;
      fac_prototype_mahalanobis & operator= (fac_prototype_mahalanobis && wzor) = default;
      virtual ~fac_prototype_mahalanobis ();
      
    public:
      virtual std::shared_ptr<metric> get_metric() const override;
//       virtual std::shared_ptr<fac_prototype> clone () const override;
   
       
    }; 
}


#endif
