/** @file */ 

#ifndef DESCRIPTOR_INTERVAL_GAUSSIAN_H
#define DESCRIPTOR_INTERVAL_GAUSSIAN_H

#include <iostream>
#include <string>
#include "descriptor-gaussian.h"


namespace ksi
{
   class descriptor_interval_gaussian : virtual public descriptor_gaussian
   {
   protected:
      /** fuzzyfication of the upper gaussian fuzzy set, \f$ \overline{\sigma} \f$  */
      double _stddevUpper;
      double _previous_stddevUpper;
      
   public:
      /** @param mean mean :-)
          @param stddevLower lower standard deviation 
          @param stddevUpper upper standard deviation
        */
      descriptor_interval_gaussian (double mean, double stddevLower, double stddevUpper);
      descriptor_interval_gaussian (const descriptor_interval_gaussian & wzor);
      
      virtual ~descriptor_interval_gaussian();
 
      virtual descriptor * clone () const override;
      
      //virtual std::string toString() const;
     
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & print (std::ostream & ss) const override;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it is just a core of the Gaussian set
      */
      virtual double getCoreMean() const override;
      
      void reset_parameters() override;
      
      /** @return The method returs the name of the descriptor.
       *       @ date 2024-02-21 */                
      virtual std::string getName() const override;
      
      
   };
}

#endif
