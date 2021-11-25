
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/prototype.h"

ksi::prototype::prototype ()
{
}

ksi::prototype::~prototype ()
{
   // delete what is to delete

}

ksi::prototype::prototype (const ksi::prototype & wzor) : ksi::premise(wzor)
{
   // copy what is to copy

}

ksi::prototype & ksi::prototype::operator= (const ksi::prototype & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::premise::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype::prototype (ksi::prototype && wzor) : ksi::premise(wzor)
{
   // swap what is to swap

}

ksi::prototype & ksi::prototype::operator= (ksi::prototype && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::premise::operator=(wzor);

   // swap what is to swap

   return *this;
}


double ksi::prototype::getFiringStrength(const std::vector<double>& X)
{
   return last_firingStrength = get_similarity(X);
}

std::ostream & ksi::prototype::Print(std::ostream& ss) const
{
    ss << "(default prototype)";
    return ss;
}
 
double ksi::prototype::distance_to_similarity (const double distance) const
{
    return exp(-distance);
}
