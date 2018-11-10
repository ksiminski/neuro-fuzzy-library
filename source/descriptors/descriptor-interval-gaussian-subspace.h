/** @file */ 

#ifndef DESCRIPTOR_INTERVAL_GAUSSIAN_SUBSPACE_H
#define DESCRIPTOR_INTERVAL_GAUSSIAN_SUBSPACE_H

#include <iostream>
#include <string>
#include "descriptor-interval-gaussian.h"
#include "descriptor-gaussian-subspace.h"


namespace ksi
{
   class descriptor_interval_gaussian_subspace : virtual public descriptor_interval_gaussian, virtual public descriptor_gaussian_subspace
   {
      
   public:
      /** @param mean mean :-)
          @param stddevLower lower standard deviation 
          @param stddevUpper upper standard deviation
          @param weight attribute weight
          */
      descriptor_interval_gaussian_subspace (double mean, double stddevLower, double stddevUpper, double weight);
      
      descriptor_interval_gaussian_subspace (const descriptor_interval_gaussian_subspace & wzor);
      
      virtual ~descriptor_interval_gaussian_subspace();
      
      virtual descriptor * clone () const;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it is just a core of the Gaussian set
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
   };
}

#endif
