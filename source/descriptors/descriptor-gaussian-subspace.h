/** @file */ 

#ifndef DESCRIPTOR_GAUSSIAN_SUBSPACE_H
#define DESCRIPTOR_GAUSSIAN_SUBSPACE_H
 
#include <iostream>
#include <string>
#include <utility>

#include "descriptor.h"
#include "descriptor-gaussian.h"


namespace ksi
{
   class descriptor_gaussian_subspace : virtual public descriptor_gaussian
   {
   protected:
      /** default weight exponent */
      double _weight_expo = 2.0; 
      /** attribute's weight */
      double _weight;
      double _previous_weight;
      /** cummulation of differentials */
      double sum_dE_dweight = 0.0;
   public:
      virtual ~descriptor_gaussian_subspace();
      /** @param mean mean of the gaussian sets
          @param stddev standard deviations
          @param weight attribute weight 
          */
      descriptor_gaussian_subspace (double mean, double stddev, double weight);
      /** @param mean mean of the gaussian sets
          @param stddev standard deviations
          @param weight attribute weight 
          @param weight_exponent exponent for attribute weight    
          */
      descriptor_gaussian_subspace(double mean, double stddev, double weight, double weight_exponent);
      
      /** The constructor constructs an interval gaussian descriptor and sets upperValid flag. 
       * @param mean mean of the gaussian sets
       * @param stddevLowerUpper a pair of standard deviations (lower and upper)
       * @param weight attribute weight
       * @date 2018-07-16          
       */
      
//       descriptor_gaussian_subspace(double mean, std::pair<double, double> stddevLowerUpper, double weight);
      
      /* The constructor constructs an interval gaussian descriptor and sets upperValid flag. 
       * @param mean mean of the gaussian sets
       * @param stddevLowerUpper a pair of standard deviations (lower and upper)
       * @param weight attribute weight
       * @param weight_exponent exponent for attribute weight    
       * @date 2018-07-16          
       */
//       descriptor_gaussian_subspace(double mean, std::pair<double, double> stddevLowerUpper, double weight, double weight_exponent);
      
      descriptor_gaussian_subspace(const descriptor_gaussian_subspace & wzor);
      
      virtual descriptor * clone () const;
      
//       virtual std::string toString() const; 
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
      
      /** @return weight of an attribute (_weight) represented by a descriptor. Legal values: [0, 1].
       */
      virtual double getWeight () const ;
      
      /** The method sets the weight of the descriptor. 
        @date 2018-02-24
        */
      virtual void setWeight (double weight);
      virtual void cummulate_differentials (double x, double partial_differentials);
      virtual void actualise_parameters (double eta);
      
      /**
      @return the mean value of descriptor's core, for this descriptor it is just a core of the Gaussian set
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
   };
}

#endif
