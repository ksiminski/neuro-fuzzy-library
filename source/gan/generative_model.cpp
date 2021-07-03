
#include "generative_model.h"

ksi::generative_model::generative_model ()
{
}

ksi::generative_model::generative_model (const ksi::generative_model & wzor)
{
}

ksi::generative_model::generative_model (ksi::generative_model && wzor)
{
}

ksi::generative_model & ksi::generative_model::operator= (const ksi::generative_model & wzor)
{
   if (this == & wzor)
      return *this;

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::generative_model & ksi::generative_model::operator= (ksi::generative_model && wzor)
{
   if (this == & wzor)
      return *this;

   // swap what is to swap

   return *this;
}

ksi::generative_model::~generative_model ()
{

   // delete what is to delete

}

 

