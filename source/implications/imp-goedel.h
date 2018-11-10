/** @file */ 

#ifndef IMP_GOEDEL_H
#define IMP_GOEDEL_H

#include <iostream>
#include "implication.h"

namespace ksi
{
   struct imp_goedel : virtual public implication
   {
      /** @return value of fuzzy implication: \f$ x \rightarrow y = 1\f$ for \f$x \leq  y\f$ and \f$ x \rightarrow y = y\f$ for \f$x > y\f$ */
      virtual double imply (double, double) const;
      /** @return G function for ANNBFIS NFS  */
      virtual double G (double F, double w) const;
      /** @return differential dG / dF for  ANNBFIS NFS */
      virtual double dG_dF (double F, double w) const;
      /** @return differential dG / dw for  ANNBFIS NFS */
      virtual double dG_dw (double F, double w) const;
      /** cloning method */
      virtual implication * clone() const; 
      
      virtual ~imp_goedel();
      
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif
