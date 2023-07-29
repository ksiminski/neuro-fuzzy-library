/** @file */ 

#ifndef IMP_KLEENE_DIENES_H
#define IMP_KLEENE_DIENES_H

#include <iostream>
#include "implication.h"

namespace ksi
{
   struct imp_kleene_dienes : virtual public implication
   {
      /** @return value of fuzzy implication: \f$x \rightarrow y = \max [1 - x, y] \f$*/
      virtual double imply (double, double) const override;
      /** @return G function for ANNBFIS NFS  */
      virtual double G (double F, double w) const override;
      /** @return differential dG / dF for  ANNBFIS NFS */
      virtual double dG_dF (double F, double w) const override;
      /** @return differential dG / dw for  ANNBFIS NFS */
      virtual double dG_dw (double F, double w) const override;
      /** cloning method */
      virtual implication * clone() const; 
      
      virtual ~imp_kleene_dienes();
      
      virtual std::ostream & Print (std::ostream & ss) const override;
      
      virtual std::string to_string() const override;
   };
}

#endif
