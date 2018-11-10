/** @file */

#include "utility-math.h"


bool ksi::distance_index::operator<(const ksi::distance_index & right)
{
   return distance < right.distance;
}

