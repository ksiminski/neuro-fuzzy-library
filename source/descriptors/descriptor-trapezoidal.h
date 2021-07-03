/** @file */ 

#ifndef DESCRIPTOR_TRAPEZOIDAL_H
#define DESCRIPTOR_TRAPEZOIDAL_H

#include "descriptor.h"


namespace ksi
{
   class descriptor_trapezoidal : virtual public descriptor
   {
   protected:
      double _support_min;
      double _support_max;
      double _core_min;
      double _core_max;
      
      double _previous_support_min;
      double _previous_support_max;
      double _previous_core_min;
      double _previous_core_max;
      
   public:
      descriptor_trapezoidal (double support_min, double core_min, double core_max, double support_max);
      
      descriptor_trapezoidal(const descriptor_trapezoidal & wzor);
      
      virtual double getMembership (double x);
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return four element vector with values <BR>
       *          vector[0] : d membership / d _support_min <BR>
       *          vector[1] : d membership / d _core_min    <BR>
       *          vector[2] : d membership / d _core_max    <BR>
       *          vector[3] : d membership / d _support_max
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      
      virtual ~descriptor_trapezoidal();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
      /** The method returns parameters for an MA triangular consequenses.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as: _support_min, (_core_min + _core_max) / 2.0 , _support_max 
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
     
      /**
      @return the mean value of descriptor's core (the mean of minimal and maximal core values)
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
      virtual double getRandomValue(std::default_random_engine & engine);
      
   };
}

#endif
