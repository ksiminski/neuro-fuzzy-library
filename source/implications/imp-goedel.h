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
      virtual double imply (double, double) const override;
      /** @return G function for ANNBFIS NFS  */
      virtual double G (double F, double w) const override;
      /** @return differential dG / dF for  ANNBFIS NFS */
      virtual double dG_dF (double F, double w) const override;
      /** @return differential dG / dw for  ANNBFIS NFS */
      virtual double dG_dw (double F, double w) const override;
      /** cloning method */
      virtual implication * clone() const override; 
      
      virtual ~imp_goedel();
      
      virtual std::ostream & Print (std::ostream & ss) const override;
      
      virtual std::string to_string() const override;
   };
}

#endif
