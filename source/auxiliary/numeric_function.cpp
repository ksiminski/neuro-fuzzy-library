
#include "numeric_function.h"

ksi::numeric_function::numeric_function ()
{
}

ksi::numeric_function::numeric_function (const ksi::numeric_function & wzor)
{
}

ksi::numeric_function::numeric_function (ksi::numeric_function && wzor)
{
}

ksi::numeric_function & ksi::numeric_function::operator= (const ksi::numeric_function & wzor)
{
   if (this == & wzor)
      return *this;

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::numeric_function & ksi::numeric_function::operator= (ksi::numeric_function && wzor)
{
   if (this == & wzor)
      return *this;

   // swap what is to swap

   return *this;
}

ksi::numeric_function::~numeric_function ()
{

   // delete what is to delete

}



