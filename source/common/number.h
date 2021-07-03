/** @file */

#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>

#include "../common/extensional-fuzzy-number-gaussian.h"

namespace ksi
{
   /** class representing a number
    @date modified on 2018-04-02
    */
   class number 
   {
   protected:
      /** value of the number */
      double value;
      /** upper value of the inteval number */
      double upper_value;
      /** true, if interval number */
      bool _isInterval;
      /** true, if number exists */
      bool _exists;
      /** fuzzification: parameter for similarity fuzzy relation */
      double _sigma;
   public:
      
      
      /** Sets value and upper_value with zeroes, 
          _isInterval is set false, 
          _exists with false */
      number ();

      /** Sets value and upper_value with d, 
          _isInterval is set false, 
          _exists with true*/
      number (double d);
      
      /** Sets value with lower and upper_value with upper, 
          _isInterval is set false, 
          _exists with true*/
      number (double lower, double upper);
      
      number (const number & wzor);
      number (number && wzor);
      number & operator= (const number & wzor);
      number & operator= (number && wzor);      
      
      /** The constructor for construction of a number from a gaussian extensional fuzzy number 
       @date 2019-02-28 */
      number (const ksi::ext_fuzzy_number_gaussian & wzor);
      
      /** @return The method returns the value of the number. */
      virtual double getValue () const;
      /** @return The method returns the value of the number. */
      virtual double getUpperValue () const;
      /** The method sets a value; */
      virtual void   setValue (double d);
      /** The method sets a number to noexisting. */
      virtual void   setValue (bool exists);
      /** The method sets value with lower, upper_value with upper */
      virtual void   setValue (double lower, double upper);
      
      /** @return The method returns a gaussian extensional fuzzy number. 
       @date 2019-01-20 */
      virtual ext_fuzzy_number_gaussian getFuzzyNumber () const;
      
      /** The function sets _sigma field;
       @param sigma a sigma to set 
       @date 2019-01-20 */
      virtual void setSigma (double sigma);
      
      /** @return true if number exists, false if does not */
      virtual bool exists () const;
      
      /** @return true if an interval number
          @return false if not an interval number */
      virtual bool isInterval () const;
      
      /** virtual method for cloning a number
       @return a pointer to base class number */
      virtual number * clone () const;
      
      virtual ~number();
      
      /** addition operator
       non-existing + existing --> existing
       non-existing + non-existing --> non-existing
       interval + interval --> interval
       non-interval + interval --> interval
       */
      number operator + (const number & right);
      
      /** addition assignment operator */
      number & operator += (const number & right);
      
      /** division operator
       non-existing / double --> non-existing
       number       / double --> number 
       interval     / double --> interval
       */
      number operator / (const double d);
      
      /** output operator for a number
        @date 2018-04-03
        */
      friend std::ostream & operator<< (std::ostream & ss, const ksi::number & d);
   };
}
#endif


