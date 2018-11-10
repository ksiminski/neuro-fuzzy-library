/** @file */

#ifndef RIDDERS_TEST_H
#define RIDDERS_TEST_H

#include <vector>
#include "../service/debug.h"
#include "ridders.h"

namespace ksi
{
   class ridders_test : public ridders
   {
       /** The method implements a function whose root is searched. */
       virtual double f (double x);
       
       virtual ridders * clone () const;
   };
}
#endif
