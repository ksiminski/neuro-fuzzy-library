
#ifndef NUMERIC_FUNCTION_H
#define NUMERIC_FUNCTION_H

#include <vector>

namespace ksi
{
   /** The class represents a function for numeric calculations.
    @date 2019-08-01
    */ 
   class numeric_function
   {
    public:
      numeric_function ();
      numeric_function (const numeric_function & wzor);
      numeric_function (numeric_function && wzor);
      numeric_function & operator= (const numeric_function & wzor);
      numeric_function & operator= (numeric_function && wzor);
      virtual ~numeric_function ();
      
      virtual numeric_function * clone () const = 0;
      
      /** @return value of the function
          @param params a vector of parameters to elaborate values for */
      virtual std::vector<double> value (const std::vector<double> & params) = 0;
   };
}


#endif
