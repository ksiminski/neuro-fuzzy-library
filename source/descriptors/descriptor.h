/** @file */ 

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "../common/extensional-fuzzy-number-gaussian.h"

namespace ksi
{
   /** Class descriptor implements an interface for a descriptor (attribute).
    *  This class and cluster class compose a factory design pattern (role: product)
    */

   class descriptor 
   {
   protected:
      /** membership for the last data item */
      double last_membership;
      
   public:
      /** The method elaborates a membership value of a parameter to the descriptor. 
       *  @param x a parameter to calculate a membership for
       *  @return membership value for a parameter
       */
      virtual double getMembership (double x) = 0;      
      
      virtual double getMembershipUpper (double x);
      
      
      /** @return weight of a attribute. Default value is 1.0. */
      virtual double getWeight () const;
      
      /** The method sets the weight of the descriptor.
          Default behaviour: nothing.
        @date 2018-02-24
        */
      virtual void setWeight (double weight);
            
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector of differential (see implementation details in implementing classes.
       */
      virtual std::vector<double> getDifferentials (double x) = 0;
      
      virtual ~descriptor();
      
      /** The method sets all cummulated differentials to zero. */
      virtual void reset_differentials ();
      
      /** The method rests parameters to previous values.  */
      virtual void reset_parameters() = 0;
      
      /** The method cummulates differentials for gradient tuning of parameters.
       * Default behaviour: nothing.
       * @param x attribute's value
       * @param partial_differentials partial differentials 
       */
      virtual void cummulate_differentials (double x, double partial_differentials);
      
      virtual descriptor * clone () const = 0;
      virtual std::string toString() const;
      
     /** The method actualises values of parameters of the fuzzy descriptor
      * Default behaviour: nothing
       * @param eta learning coefficient
       */
     virtual void actualise_parameters (double eta);
     
     /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
     virtual std::ostream & Print (std::ostream & ss) const = 0;
     
     /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support */
     virtual std::vector<double> getMAconsequenceParameters () const = 0;
     
      /** @return The method returns a granule expressed with fuzzy gaussian extensional number
       @date 2019-02-28 
       */
      virtual ksi::ext_fuzzy_number_gaussian getGranule() const;
     
     /**
      @return the mean value of descriptor's core
      */
     virtual double getCoreMean() const = 0;
     
     /** The method return fuzzification of the descriptor.
      @throw ksi::exception If it is not possible to return fuzzification, it throws an exception.
      */
     virtual double getFuzzification () const;
     
     /** @return The method returns a random value covered by a descriptor. */
     virtual double getRandomValue (std::default_random_engine & engine) = 0;
     
   };
}

#endif
