/** @file */ 
#ifndef T_NORM_PARAMETRIZED_H
#define T_NORM_PARAMETRIZED_H

#include <iostream>

#include "../tnorms/t-norm.h"

namespace ksi
{
   struct t_norm_parametrized : public t_norm 
   {
   protected:
      double _parameter;
   public:
      t_norm_parametrized (double parameter);
      t_norm_parametrized (const t_norm_parametrized & wzor);
      
      virtual ~t_norm_parametrized();
   };
}

#endif
