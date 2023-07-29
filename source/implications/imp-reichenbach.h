/** @file */ 

#ifndef IMP_REICHENBACH_H
#define IMP_REICHENBACH_H

#include <iostream>
#include "implication.h"

namespace ksi
{
   struct imp_reichenbach : virtual public implication
   {
      /** @return value of fuzzy implication: \f$x \rightarrow y = 1 - x + xy\f$*/
      virtual double imply (double, double) const override;
      /** @return G function for ANNBFIS NFS  */
      virtual double G (double F, double w) const override;
      /** @return differential dG / dF for  ANNBFIS NFS */
      virtual double dG_dF (double F, double w) const override;
      /** @return differential dG / dw for  ANNBFIS NFS */
      virtual double dG_dw (double F, double w) const override;
      /** cloning method */
      virtual implication * clone() const override; 
      
      virtual ~imp_reichenbach();
      
      virtual std::ostream & Print (std::ostream & ss) const override;
      
      virtual std::string to_string() const override;
   };
}

#endif
