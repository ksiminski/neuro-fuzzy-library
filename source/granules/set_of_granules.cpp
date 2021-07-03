
#include "set_of_granules.h"

ksi::set_of_granules::set_of_granules ()
{
}

ksi::set_of_granules::set_of_granules (const ksi::set_of_granules & wzor)
{
}

ksi::set_of_granules::set_of_granules (ksi::set_of_granules && wzor)
{
}

ksi::set_of_granules & ksi::set_of_granules::operator= (const ksi::set_of_granules & wzor)
{
   if (this == & wzor)
      return *this;

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::set_of_granules & ksi::set_of_granules::operator= (ksi::set_of_granules && wzor)
{
   if (this == & wzor)
      return *this;

   // swap what is to swap

   return *this;
}

ksi::set_of_granules::~set_of_granules ()
{

   // delete what is to delete

}



