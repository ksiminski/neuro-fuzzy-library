
#include "fac_prototype.h"

ksi::fac_prototype::fac_prototype ()
{
}

ksi::fac_prototype::~fac_prototype ()
{
   // delete what is to delete

}

ksi::fac_prototype::fac_prototype (const ksi::fac_prototype & wzor)
{
   // copy what is to copy

}

ksi::fac_prototype & ksi::fac_prototype::operator= (const ksi::fac_prototype & wzor)
{
   if (this == & wzor)
      return *this;


   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::fac_prototype::fac_prototype (ksi::fac_prototype && wzor)
{
   // swap what is to swap

}

ksi::fac_prototype & ksi::fac_prototype::operator= (ksi::fac_prototype && wzor)
{
   if (this == & wzor)
      return *this;


   // swap what is to swap

   return *this;
}



