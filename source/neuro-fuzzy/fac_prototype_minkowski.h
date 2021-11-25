
#ifndef FAC_PROTOTYPE_MINKOWSKI_H
#define FAC_PROTOTYPE_MINKOWSKI_H


#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/fac_prototype.h"

namespace ksi
{
   class fac_prototype_minkowski : public fac_prototype
   {
   protected:
       double _m; ///< exponent for Minkowski metric
    public:
      fac_prototype_minkowski (const double m);
      fac_prototype_minkowski (const fac_prototype_minkowski & wzor);
      fac_prototype_minkowski (fac_prototype_minkowski && wzor);
      fac_prototype_minkowski & operator= (const fac_prototype_minkowski & wzor);
      fac_prototype_minkowski & operator= (fac_prototype_minkowski && wzor);
      virtual ~fac_prototype_minkowski ();
      
    public:
      virtual std::shared_ptr<metric> get_metric() const override;
//       virtual std::shared_ptr<fac_prototype> clone () const override;
   
       
    }; 
}


#endif
