/** @file */ 

#ifndef DESCRIPTOR_TRIANGULAR_H
#define DESCRIPTOR_TRIANGULAR_H

#include <random>
#include "descriptor.h"

namespace ksi
{
   class descriptor_triangular : virtual public descriptor
   {
      double _support_min;  ///< minimal value of support 
      double _support_max;  ///< maximal value of support 
      double _core;         ///< value of core

      double _previous_support_min;  ///< previous minimal value of support 
      double _previous_support_max;  ///< previous maximal value of support 
      double _previous_core;         ///< previous value of core
      
      
   public:
      descriptor_triangular (double support_min, double core, double support_max);
      
      /** copy constructor */
      descriptor_triangular (const descriptor_triangular & wzor);
      
      virtual double getMembership (double x);
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return three element vector with values <BR>
       *          vector[0] : d membership / d _support_min <BR>
       *          vector[1] : d membership / d _core        <BR>
       *          vector[2] : d membership / d _support_max
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      
      virtual ~descriptor_triangular();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as: _support_min, _core, _support_max 
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
      
      /**
      @return the mean value of descriptor's core, for this desctribute it is just the descriptor's core
      */
      virtual double getCoreMean() const;
      
      /** The method rests parameters to previous values.  */
      virtual void reset_parameters();
      
      virtual double getRandomValue(std::default_random_engine & engine);
      
   };
}

#endif
