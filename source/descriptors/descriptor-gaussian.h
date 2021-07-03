/** @file */ 

#ifndef DESCRIPTOR_GAUSSIAN_H
#define DESCRIPTOR_GAUSSIAN_H

#include <iostream>
#include <string>
#include "descriptor.h" 


namespace ksi
{
   class descriptor_gaussian : virtual public descriptor
   {
   protected:
      /** core of the gaussian fuzzy set, \f$ m \f$ */
      double _mean;
      /** fuzzyfication of the gaussian fuzzy set, \f$ \sigma \f$  */
      double _stddev;
      
      double _previous_mean;
      double _previous_stddev;
      
      /** sum of dE / d mean differentials */
      double sum_dE_dmean;
      /** sum of dE / d stddev differentials */
      double sum_dE_dstddev;
      
   public:
      /** @param mean mean :-)
          @param stddev standard deviation (also for upper standard deviation) */
      descriptor_gaussian (double mean, double stddev); 
      descriptor_gaussian (const descriptor_gaussian & wzor);
      
      virtual ~descriptor_gaussian();   
      
      
      /** The method elaborates membership to the fuzzy set with formula
       *  \f[  \mu(x) = \exp \left( - \frac{(x - m)^2}{2 \sigma^2} \right)   \f]
       */
      virtual double getMembership (double x);
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector of differentials:               <BR> 
       *          vector[0] : \f$ \frac{\partial \mu(x)}{\partial m} \f$  <BR>
       *          vector[1] : \f$ \frac{\partial \mu(x)}{\partial \sigma} \f$
       */
      virtual std::vector<double> getDifferentials (double x);
      
      /** The method cummulates differentials for gradient tuning of parameters.
       * \f[ \frac{\partial E}{\partial m} = \mathrm{partial\_differentials} \cdot \frac{x - m}{\sigma^2} \f]
       * \f[ \frac{\partial E}{\partial \sigma} = \mathrm{partial\_differentials} \cdot \frac{(x - m)^2}{\sigma^3} \f]
       * 
       * @param x attribute's value
       * @param partial_differentials partial differentials 
       */
      virtual void cummulate_differentials (double x, double partial_differentials);

      virtual descriptor * clone () const;
      
      virtual std::string toString() const;
      
      /** The method sets all cummulated differentials to zero. */
      virtual void reset_differentials ();
    
      /** The method actualises values of parameters of the fuzzy descriptor.
       * If the fuzzification of the fuzzy set (_stddev, \f$\sigma\f$) is negative after
       * actualisation, it will not be changed and the old value of _stddev, \f$\sigma\f$ is kept.
       * @param eta learning coefficient
       */
      virtual void actualise_parameters (double eta);

      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const;
      
      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as _mean - _stddev, _mean, _mean + _stddev
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it is just a core of the Gaussian set
      */
      virtual double getCoreMean() const;
      
      /** The method return fuzzification of the descriptor.
      */
      virtual double getFuzzification () const;
      
      void reset_parameters();
      
      /** @return The method returns a granule expressed with fuzzy gaussian extensional number
       @date 2019-02-28 
       */
      virtual ksi::ext_fuzzy_number_gaussian getGranule() const;
      
      virtual double getRandomValue(std::default_random_engine & engine);
      
   };
}

#endif
