/** @file */

#include "utility-math.h"


bool ksi::distance_index::operator<(const ksi::distance_index & right)
{
   return distance < right.distance;
}

bool ksi::utility_math::double_equal(const double a, const double b)
{
    const double EPSILON {0.00001};         
    return std::fabs(a - b) < EPSILON;
}

int ksi::utility_math::signum(const double x)
{
    if (x > 0)
        return +1;
    else if (x < 0)
        return -1;
    else 
        return 0;
}


