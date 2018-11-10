/** @file */

#ifndef RIDDERS_GAUSSIAN_M_H
#define RIDDERS_GAUSSIAN_M_H

#include <vector>
#include <utility>

#include "../service/debug.h"
#include "ridders.h"

namespace ksi
{
   class ridders_gaussian_m : public ridders
   {
   protected:
      std::vector<std::pair<double, double>> _points;
      
      double _s;
   public:   
      /** The method implements a function whose root is searched. */
      virtual double f (double x);
   public:
      virtual ridders * clone () const;
       
      ridders_gaussian_m (const std::vector<std::pair<double, double>> & points, double s);
      ridders_gaussian_m (const ridders_gaussian_m & wzor);
      ridders_gaussian_m (ridders_gaussian_m && wzor);
      ~ridders_gaussian_m();
      
      ridders_gaussian_m & operator = (const ridders_gaussian_m & wzor);
      ridders_gaussian_m & operator = (ridders_gaussian_m && wzor);
      
      
   };
}
#endif
