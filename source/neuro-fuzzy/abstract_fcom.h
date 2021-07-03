
#ifndef ABSTRACT_FCOM_H
#define ABSTRACT_FCOM_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../owas/owa.h"
#include "../dissimilarities/dissimilarity.h"

namespace ksi
{
   class abstract_fcom : virtual public neuro_fuzzy_system
   {
   protected:
         
       ksi::dissimilarity * _pDissimilarity = nullptr; ///< dissimilarity function
       ksi::owa * _pOwa = nullptr; ///< ordered weighting average function
       
       
  
    public:
      abstract_fcom ();
      abstract_fcom (const abstract_fcom & wzor);
      abstract_fcom (abstract_fcom && wzor);
      abstract_fcom & operator= (const abstract_fcom & wzor);
      abstract_fcom & operator= (abstract_fcom && wzor);
      virtual ~abstract_fcom ();
      
      virtual std::string extra_report();
   };
}


#endif
