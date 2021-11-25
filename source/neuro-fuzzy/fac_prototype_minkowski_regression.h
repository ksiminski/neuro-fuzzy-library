
#ifndef FAC_PROTOTYPE_MINKOWSKI_REGRESSION_H
#define FAC_PROTOTYPE_MINKOWSKI_REGRESSION_H


#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../metrics/metric.h"
#include "../neuro-fuzzy/fac_prototype_minkowski.h"

namespace ksi
{
   class fac_prototype_minkowski_regression : public fac_prototype_minkowski
   {
//        double _m; ///< exponent for Minkowski metric
    public:
      fac_prototype_minkowski_regression (const double m);
      fac_prototype_minkowski_regression (const fac_prototype_minkowski_regression & wzor);
      fac_prototype_minkowski_regression (fac_prototype_minkowski_regression && wzor);
      fac_prototype_minkowski_regression & operator= (const fac_prototype_minkowski_regression & wzor);
      fac_prototype_minkowski_regression & operator= (fac_prototype_minkowski_regression && wzor);
      virtual ~fac_prototype_minkowski_regression ();
      
    public:
      virtual std::shared_ptr<prototype> get_prototype() const override; 
//       virtual std::shared_ptr<metric> get_metric() const override;
      virtual std::shared_ptr<fac_prototype> clone () const override;
   
       
    }; 
}


#endif
