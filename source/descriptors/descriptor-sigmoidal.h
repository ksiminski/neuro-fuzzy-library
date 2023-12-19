/** @file */ 

#ifndef DESCRIPTOR_SIGMOIDAL_H
#define DESCRIPTOR_SIGMOIDAL_H

#include "descriptor.h"


namespace ksi
{
   /** The descriptor is describes a fuzzy set with a tanh membership function defined as \f$f(x; c, s) = 1 / \left(1+ \exp\left( - s (x - c) \right) \right)\f$. */ 
   class descriptor_sigmoidal : virtual public descriptor
   {
      double _cross;  ///< \f$ c\f$: cross
      double _slope;  ///< \f$ s\f$: slope
      
      double _previous_cross;
      double _previous_slope;

      const static std::array<std::string, 7> sigmoidalLocationDescription;
      const static std::array<std::string, 5> fuzzyDescription;
   public:
      descriptor_sigmoidal (double crosspoint, double slope);
      
      descriptor_sigmoidal (const descriptor_sigmoidal & wzor);
      
      /** @return \f$f(x; c, s) = 1 / \left(1+ \exp\left( - s (x - c) \right) \right)\f$ */
      virtual double getMembership (double x);
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector of differentials:                <BR> 
       *          vector[0] : d membership / d _cross     <BR>
       *          vector[1] : d membership / d _slope
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      virtual ~descriptor_sigmoidal ();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss) const ;

      /** The method prints an object linguistic description into output stream
		 * @param ss the output stream to print into
		 * @param descStat the descriptor statistics to print
		 * @date 2023-12-04
		 * @author Konrad Wnuk
		*/
      virtual std::ostream& prettyPrint(std::ostream& ss, const DescriptorStatistics& descStat) const;

      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as  _cross, _cross + _slope, _cross + 2 * _slope
       * @date 2018-02-16
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it returns not a number (NaN)
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
      /** @return The method returns a value \f$x\f$ for which sigmoidal function \f$f(x) \in [k, 1 - k] \f$. Here \f$k = 0.9 \f$, thus \f$x \in \left[c -\frac{1}{s}\ln \frac{1 - k}{k},  c +\frac{1}{s}\ln \frac{1 - k}{k}\right]\f$, where \f$f(c) = 0.5\f$ */
      virtual double getRandomValue(std::default_random_engine & engine);
    
   };
}

#endif
