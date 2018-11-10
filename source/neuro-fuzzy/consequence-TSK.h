/** @file */ 
#ifndef CONSEQUENCE_TSK_H
#define CONSEQUENCE_TSK_H

#include <utility>
#include <vector>
#include <iostream>
#include "consequence.h"
#include "../service/debug.h"

namespace ksi
{
   class consequence_TSK : virtual public consequence 
   {
   protected:
      std::vector<double> _params;
   public:
      consequence_TSK();
      consequence_TSK(const consequence_TSK & wzor);
      consequence_TSK(consequence_TSK && wzor);
      virtual ~consequence_TSK();
      consequence_TSK (const std::vector<double> & params);
      
      /** The method elaborates localisation and weight of the answer.
       * @param X the data tuple to elaborate answer for. You should augment the X data item with 1 at the end or beginning (as you wish, but keep it consequently!).
       * @param firing firing strength of the rule
       * @return a pair: localisation and weight
       */
      virtual std::pair< double, double > 
      getLocalisationWeight(const std::vector<double> & X, double firing);
      
      virtual consequence * clone () const;
      
      /** The method sets linear parameters in the rule. 
       * @param coefficients a vector of coefficients to set.
       */
      virtual void setLinearParameters (std::vector<double> & coefficients);
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss);      
   };
}

#endif