/** @file */ 

#ifndef DESCRIPTOR_TANH_H
#define DESCRIPTOR_TANH_H

#include "descriptor.h"


namespace ksi
{
   /** The descriptor is describes a fuzzy set with a tanh membership function defined as \f$f(x; c, s) = \frac{1}{2} + \frac{1}{2} \tanh \left( s (x - c) \right)\f$. 
     * @date 2023-07-29
     * @author Krzysztof Siminski
     */
   class descriptor_tanh : virtual public descriptor
   {
      double _cross;  ///< \f$ c\f$: cross
      double _slope;  ///< \f$ s\f$: slope
      
      double _previous_cross;
      double _previous_slope;

      const static std::array<std::string, 7> tanhLocationDescription;
      const static std::array<std::string, 5> fuzzyDescription;
   public:
      descriptor_tanh (const double crosspoint, const double slope);
      
      descriptor_tanh (const descriptor_tanh & wzor);
      
      /** @return The method returns a value elaborated as \f$f(x; c, s) = \frac{1}{2} + \frac{1}{2} \tanh \left( s (x - c) \right)\f$ */
      virtual double getMembership (const double x) override;
      
      /** The method elaborates the differentials of the membership function
       *  for an attribute value x 
       *  @param x a parameter to calculate differentials for
       *  @return vector of differentials:                <BR> 
       *          vector[0] : d membership / d _cross     <BR>
       *          vector[1] : d membership / d _slope
       */
      virtual std::vector<double> getDifferentials (double x);
      
      virtual descriptor * clone () const;
      virtual ~descriptor_tanh ();
      
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
       * @date 2023-07-29
       */
      virtual std::vector<double> getMAconsequenceParameters () const;
      
      /**
      @return the mean value of descriptor's core, for this descriptor it returns not a number (NaN)
      */
      virtual double getCoreMean() const;
      
      void reset_parameters();
      
      /** @warning not implemented yet */
      virtual double getRandomValue(std::default_random_engine & engine);
    
   };
}

#endif
