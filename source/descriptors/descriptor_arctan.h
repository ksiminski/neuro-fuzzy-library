/** @file */ 

#ifndef DESCRIPTOR_ARCTAN_H
#define DESCRIPTOR_ARCTAN_H

#include "descriptor.h"


namespace ksi
{
   /** The descriptor is describes a fuzzy set with a tanh membership function defined as \f$f(x; c, s) = \frac{2}{\pi}\arctan \left( s \left(x - c\right) \right)\f$. 
     * @date 2023-07-30
     * @author Krzysztof Siminski
     */
   class descriptor_arctan : virtual public descriptor
   {
      double _cross;  ///< \f$ c\f$: cross
      double _slope;  ///< \f$ s\f$: slope
      
      double _previous_cross;
      double _previous_slope;

      /** linguistic labels */
      const static std::array<std::string, 7> arctanLocationDescription;
      /** linguistic labels */
      const static std::array<std::string, 5> fuzzyDescription;
      
   public:
      descriptor_arctan (const double crosspoint, const double slope);
      
      descriptor_arctan (const descriptor_arctan & wzor);
      
      /** @return The method returns a value elaborated as \f$f(x; c, s) = \frac{2}{\pi}\arctan \left( s \left(x - c\right) \right)\f$ */
      virtual double getMembership (const double x) override;
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector of differentials:                <BR> 
       *          vector[0] : d membership / d _cross     <BR>
       *          vector[1] : d membership / d _slope
       */
      virtual std::vector<double> getDifferentials (double x) override;
      
      virtual descriptor * clone () const override;
      virtual ~descriptor_arctan ();
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & print (std::ostream & ss) const override;

      /** The method prints an object linguistic description into output stream
       * @param ss the output stream to print into
       * @param descStat the descriptor statistics to print
       * @date 2023-12-04
       * @author Konrad Wnuk
      */
     virtual std::ostream& printLinguisticDescription(std::ostream& ss, const DescriptorStatistics& descStat) const;

      /** The method returns parameters for an MA triangular consequense.
       * @return a vector of three values: minimal_support, core, and maximal_support
       * evaluated as  _cross, _cross + _slope, _cross + 2 * _slope
       * @date 2023-07-30
       */
      virtual std::vector<double> getMAconsequenceParameters () const override;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it returns not a number (NaN)
      */
      virtual double getCoreMean() const override;
      
      void reset_parameters() override;
      
      /** @warning not implemented yet */
      virtual double getRandomValue(std::default_random_engine & engine) override;
    
   };
}

#endif
