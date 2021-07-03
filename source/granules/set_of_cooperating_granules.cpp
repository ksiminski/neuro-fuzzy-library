
#include "set_of_granules.h"
#include "set_of_cooperating_granules.h"

ksi::set_of_cooperating_granules::set_of_cooperating_granules ()
{
}

ksi::set_of_cooperating_granules::set_of_cooperating_granules (const ksi::set_of_cooperating_granules & wzor) : ksi::set_of_granules (wzor)
{
}

ksi::set_of_cooperating_granules::set_of_cooperating_granules (ksi::set_of_cooperating_granules && wzor) : ksi::set_of_granules (wzor)
{
}

ksi::set_of_cooperating_granules & ksi::set_of_cooperating_granules::operator= (const ksi::set_of_cooperating_granules & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::set_of_granules::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::set_of_cooperating_granules & ksi::set_of_cooperating_granules::operator= (ksi::set_of_cooperating_granules && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::set_of_granules::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::set_of_cooperating_granules::~set_of_cooperating_granules ()
{

   // delete what is to delete

}

 


