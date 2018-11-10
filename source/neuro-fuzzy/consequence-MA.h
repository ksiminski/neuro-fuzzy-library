/** @file */ 
#ifndef CONSEQUENCE_MA_H
#define CONSEQUENCE_MA_H

#include <utility>
#include <iostream>
#include "consequence.h"

namespace ksi
{
   class consequence_MA : virtual public consequence  
   {
      double _support_min, _core, _support_max;
      double _sum_support_min, _sum_core, _sum_support_max;
      
   public:
      consequence_MA (double support_min, double core, double support_max);
      consequence_MA (const consequence_MA & wzor);
      consequence_MA (consequence_MA && wzor);
      virtual ~consequence_MA();
      
      /** The method elaborates localisation and weight of the answer.
       * @param X not used in this method
       * @param firing firing strength of the rule
       * @return a pair: localisation and weight
       */

      virtual std::pair< double, double > 
      getLocalisationWeight(const std::vector<double> & X, double firing);
      
      /** A method returns width of the support of a triangle fuzzy set.
       * @return width of the support of a triangle fuzzy set
       */
      virtual double getW() const;
      
      virtual consequence * clone () const;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss);
      
      /** The method cummulates differentials for an X data item in the consequence. 
       * The method calculates differentials for parameters. For each parameter \f$a\f$ 
       * (_support_min, _core, _support_max) it calculates:
       * \f[ \frac{\partial y}{\partial a} =   \frac{\left(y_i - y\right) \frac{dw_i}{da_i} + w_i\frac{dy_i}{da_i}}{\sum_{i = 1}^I w_i}  \f]
       @param X the data item to cummulate differantials for 
       @param partial_differential \f$ \frac{\left(y_i - y\right)}{\sum_{i = 1}^I w_i}  \f$
       @param secundary_partial_differential \f$ \frac{w_i}{\sum_{i = 1}^I w_i} \f$
       @param firing firing strength of the premise of the rule
       @date 2018-02-20
       */
      virtual void cummulate_differentials(std::vector< double > X, 
                                           double partial_differential,
                                           double secundary_partial_differential,
                                           double firing
                                          );
      
      
   };
}

#endif