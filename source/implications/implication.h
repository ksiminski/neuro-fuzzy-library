/** @file */ 
#ifndef IMPLICATION_H
#define IMPLICATION_H

#include <iostream>
#include <string>

namespace ksi
{
   struct implication
   {
      /** @return value of fuzzy implication: p -> q */
      virtual double imply (double p, double q) const = 0;
      /** @return G function for ANNBFIS NFS  */
      virtual double G (double F, double w) const = 0;
      /** @return differential dG / dF for  ANNBFIS NFS */
      virtual double dG_dF (double F, double w) const = 0;
      /** @return differential dG / dw for  ANNBFIS NFS */
      virtual double dG_dw (double F, double w) const = 0;
      
      /** cloning method */
      virtual implication * clone() const = 0; 
      
      virtual ~implication();
      
      virtual std::ostream & Print (std::ostream & ss) const = 0;
      
      /** @return The method returns the name of the implication.
          @date 2023-07-28 */
      virtual std::string to_string() const = 0;
      
   };
}

#endif
