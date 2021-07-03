/** @file */ 

#ifndef DESCRIPTOR_SINGLETON_H
#define DESCRIPTOR_SINGLETON_H

#include "descriptor-trapezoidal.h"


namespace ksi
{
   class descriptor_singleton : virtual public descriptor_trapezoidal
   {  
      const double EPSILON = 1e-3;
      
   public:
      descriptor_singleton (double value);
      
      descriptor_singleton (const descriptor_singleton & wzor);
      virtual double getMembership (double x);

      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return one element vector with one value -- always zero  <BR>
       *          vector[0] == 0.0 : d membership / d value
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      
      virtual ~descriptor_singleton ();

      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
     /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as _core_max - EPSILON, _core_max, _core_max + EPSILON,
       * where EPSILON is a small value (a field of the class)
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;

      /**
      @return the mean value of descriptor's core, for this descriptor it is just the core
      */
      virtual double getCoreMean() const;
      
      virtual double getRandomValue(std::default_random_engine & engine);
      
   };
}

#endif
