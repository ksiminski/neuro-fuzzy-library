/** @file */ 

#ifndef CONSEQUENCE_H
#define CONSEQUENCE_H

#include <utility>
#include <vector>
#include <iostream>

namespace ksi
{
   class consequence 
   {
   protected:
      /** localisation and weight for the last data item */
      std::pair<double, double> last_localisationWeight;
      
   public:
      
      
      virtual ~consequence();
      /** @return pair: localisation and weight  
       */
      virtual std::pair<double, double> 
      getLocalisationWeight(const std::vector<double> & X, double firing) = 0;
      
      /** A method returns width of the support of a triangle fuzzy set, if such 
       *  a triangle exists in a consequence. Otherwise returns 0.
       * @return width of the support of a triangle fuzzy set, if such 
       *  triangle exists in a consequence, otherwise returns 0.
       */
      virtual double getW() const;
      
      virtual consequence * clone () const = 0;
      
      /** The method sets all cummulated differentials to zero. */
      virtual void reset_differentials ();

      
      /** The method cummulates differentials for an X data item in the consequence.
       *  Default behaviour: nothing 
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @param secundary_partial_differential some differentials (when needed, 
              otherwise not used)
       @param firing firing strength of the premise of the rule              
       @date 2018-01-20
       */
      virtual void cummulate_differentials(std::vector< double > X, 
                                           double partial_differential,
                                           double secundary_partial_differential,
                                           double firing
                                          );
      
      /** The method actualises values of parameters of the fuzzy consequence.
       * Default behaviour: nothing
       * @param eta learning coefficient
       */
      virtual void actualise_parameters(double eta);
      
      /** The method sets linear parameters in the rule. 
       * Default behaviour: nothing
       * @param coefficients a vector of coefficients to set.
       */
      virtual void setLinearParameters (std::vector<double> & coefficients);
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) = 0;  
      
   };
}

#endif