/** @file */

#ifndef RIDDERS_GAUSSIAN_S_H
#define RIDDERS_GAUSSIAN_S_H

#include <vector>
#include <utility>

#include "../service/debug.h"
#include "ridders.h"

namespace ksi
{
   class ridders_gaussian_s : public ridders
   {
   protected:
      std::vector<std::pair<double, double>> _points;
      
      double _m;
   public:   
      /** The method implements a function whose root is searched. */
      virtual double f (double x);
   public:
      virtual ridders * clone () const;
       
      ridders_gaussian_s (const std::vector<std::pair<double, double>> & points, double m);
      ridders_gaussian_s (const ridders_gaussian_s & wzor);
      ridders_gaussian_s (ridders_gaussian_s && wzor);
      ~ridders_gaussian_s();
      
      ridders_gaussian_s & operator = (const ridders_gaussian_s & wzor);
      ridders_gaussian_s & operator = (ridders_gaussian_s && wzor);
      
      
   };
}
#endif
