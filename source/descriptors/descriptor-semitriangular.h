/** @file */ 

#ifndef DESCRIPTOR_SEMITRIANGULAR_H
#define DESCRIPTOR_SEMITRIANGULAR_H

#include <random>
#include "descriptor.h"

namespace ksi
{
   class descriptor_semitriangular : virtual public descriptor 
   {
      double _support_extremum;
      double _core;
      
      double _previous_support_extremum;
      double _previous_core;
      
   public:
      
      
      /** If core is less than support_extremum, then core is the maximal value of x for which membership is 1 and support_extremum is the minimal value of x for which membership is 0.
       * If support_extremum is less than core, then support_extremum is the maximal value of x for which membership is zero and core is the minimal value of x for which membership is 1.
       */
      descriptor_semitriangular (double support_extremum, double core);
      descriptor_semitriangular (const descriptor_semitriangular & wzor);
      virtual double getMembership (double x);
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector with values <BR>
       *          vector[0] : d membership / d _support_extremum <BR>
       *          vector[1] : d membership / d _core            
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      virtual ~descriptor_semitriangular();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;

      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it is not a number value (NaN)
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
      /** @return The method returns a value  */
      virtual double getRandomValue(std::default_random_engine & engine);
      
   };
}

#endif
