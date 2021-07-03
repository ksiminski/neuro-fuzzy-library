/** @file */

#ifndef EXTENSIONAL_FUZZY_NUMBER_GAUSSIAN
#define EXTENSIONAL_FUZZY_NUMBER_GAUSSIAN

#include <iostream>
#include <vector>

namespace ksi
{

   /** Gaussian extensional fuzzy number based on fuzzy similarity relation:
   \f$ S_\sigma(x, y) = \exp \left( - \frac{(x - y)^2}{2\sigma^2} \right) \f$
   @date 2019-01-20
   */
   class ext_fuzzy_number_gaussian
   {
   protected:
      double _x;     ///< core value
      double _sigma; ///< similarity parameter 
      
      static const double MINIMAL_SIGMA; ///< minimal value of sigma (it cannot be zero)
      
   public:
      ext_fuzzy_number_gaussian();
      /** Constructor with default value of sigma (MINIMAL_SIGMA). */
      ext_fuzzy_number_gaussian(double x); 
      ext_fuzzy_number_gaussian(double x, double sigma);
      
      
      ext_fuzzy_number_gaussian   operator +  (const ext_fuzzy_number_gaussian & op) const;
      ext_fuzzy_number_gaussian & operator += (const ext_fuzzy_number_gaussian & op) ;
      ext_fuzzy_number_gaussian   operator -  (const ext_fuzzy_number_gaussian & op) const;
      ext_fuzzy_number_gaussian   operator -  () const;
      ext_fuzzy_number_gaussian   operator *  (const ext_fuzzy_number_gaussian & op) const;
      ext_fuzzy_number_gaussian   operator /  (const ext_fuzzy_number_gaussian & op) const;
      ext_fuzzy_number_gaussian & operator /= (const ext_fuzzy_number_gaussian & op) ;
      bool operator >  (const double op) const;
      bool operator == (const double op) const;
      explicit operator double () const; 
      
      /** @return returns a core value of a gaussian extensional fuzzy number (_x)
       @date 2019-01-28 */
      double get_value () const ;
      
      /** @return returns a fuzzificaton value of a gaussian extensional fuzzy number (_sigma)
       @date 2019-01-28 */
      double get_sigma () const;
      
      /** @return power of a gaussian extensional fuzzy number */
      static ext_fuzzy_number_gaussian pow  (const ext_fuzzy_number_gaussian & base, double exponent); 
      /** @return square root of a gaussian extensional fuzzy number */
      static ext_fuzzy_number_gaussian sqrt (const ext_fuzzy_number_gaussian & radicand); 
      
       /** The function tranforms a matrix of gaussian extensional numbers into a matrix of doubles */
      static std::vector<std::vector<double>> matrix_of_extensional_fuzzy_number_2_double (const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & matrix);
      
      virtual ~ext_fuzzy_number_gaussian();
      
      friend std::ostream & operator << (std::ostream & ss, const ext_fuzzy_number_gaussian & number);
      
   };

}
#endif
