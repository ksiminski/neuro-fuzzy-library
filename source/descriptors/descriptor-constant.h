/** @file */ 

#ifndef DESCRIPTOR_CONSTANT_H
#define DESCRIPTOR_CONSTANT_H

#include "descriptor.h"

namespace ksi
{
   /** The descriptor has a constant value for all arguments. */
   class descriptor_constant : virtual public descriptor
   {
      double _value;
      double _previous_value;
      
   public:
      /** @param value value of the descriptor for all arguments */
      descriptor_constant (const double value);
      descriptor_constant (const descriptor_constant & wzor);
      virtual double getMembership (double x) override;
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return three element vector with values <BR>
       *          vector[0] : d membership / d _support_min <BR>
       *          vector[1] : d membership / d _core        <BR>
       *          vector[2] : d membership / d _support_max
       */
      virtual std::vector<double> getDifferentials (double x) override;
      
      virtual descriptor * clone () const override;
      
      virtual ~descriptor_constant();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const override;
      
      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as: _support_min, _core, _support_max 
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const override;
      
      /**
      @return the mean value of descriptor's core, for this desctribute it is just the descriptor's core
      */
      virtual double getCoreMean() const override;
      
      void reset_parameters() override;
      
      virtual double getRandomValue(std::default_random_engine & engine) override;
      
      
      
   };
}

#endif
