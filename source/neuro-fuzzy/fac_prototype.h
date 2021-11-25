
#ifndef FAC_PROTOTYPE_H
#define FAC_PROTOTYPE_H

#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../metrics/metric.h"


namespace ksi
{
   class fac_prototype
   {
    public:
      fac_prototype ();
      fac_prototype (const fac_prototype & wzor);
      fac_prototype (fac_prototype && wzor);
      fac_prototype & operator= (const fac_prototype & wzor);
      fac_prototype & operator= (fac_prototype && wzor);
      virtual ~fac_prototype ();
      
   public:
      virtual std::shared_ptr<prototype> get_prototype() const = 0; 
      virtual std::shared_ptr<metric> get_metric() const = 0;
      virtual std::shared_ptr<fac_prototype> clone () const = 0; 
      
   };
}


#endif
