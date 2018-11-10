/** @file */ 

#ifndef LOGICALRULE_H
#define LOGICALRULE_H

#include <utility>
#include <vector>

#include "premise.h"
#include "consequence.h"
#include "../tnorms/t-norm.h"
#include "../implications/implication.h"
#include "rule.h"

namespace ksi
{
   class logicalrule : virtual public rule 
   {
   protected:
      implication * pImplication;
      
   public:
      virtual ~logicalrule();
      logicalrule (const logicalrule &);
      logicalrule (logicalrule &&);
      logicalrule (const t_norm & t, const implication & imp);
      
      logicalrule & operator = (const logicalrule &);
      logicalrule & operator = (logicalrule &&);
      
      /** The method returns localisation and weight of an answer for an X data item
       * @param X data item to elaborate answer for
       * @return a pair: first is localisation, second is weight
       */
     virtual std::pair<double, double> getAnswerLocalisationWeight (const std::vector<double> & X); 
     
     /** The method cummulates differentials for an X data item in a rule. 
       * Default behaviour: nothing :-)
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules 
       @param secundary_partial_differential some differentials (when needed, 
              otherwise not used)
       */
      virtual void cummulate_differentials (const std::vector<double> & X, 
                                            double partial_differential,
                                            double secundary_partial_differentials
                                           );
      
      virtual rule * clone() const;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
   };
}

#endif