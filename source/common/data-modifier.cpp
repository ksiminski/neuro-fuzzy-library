/** @file */


#include <algorithm>
#include "data-modifier.h"
#include "../service/debug.h"


ksi::data_modifier::data_modifier()
{
   pNext = nullptr;
   //description = "";
}

ksi::data_modifier::data_modifier(const ksi::data_modifier & dm)
{
   if (dm.pNext)
      pNext = dm.pNext->clone();
   else
      pNext = nullptr;
   
   description = dm.description;
}

ksi::data_modifier::data_modifier(ksi::data_modifier && dm)
{
   //pNext = nullptr;
   std::swap(pNext, dm.pNext);
   std::swap(description, dm.description);
}

ksi::data_modifier & ksi::data_modifier::operator=(const ksi::data_modifier & dm)
{
   if (this == & dm)
      return *this;
   
   if (pNext)
      delete pNext;
   
   if (dm.pNext)
      pNext = dm.pNext->clone();
   else
      pNext = nullptr;
   
   description = dm.description;

   return *this;   
}


ksi::data_modifier & ksi::data_modifier::operator=(ksi::data_modifier&& dm)
{
   if (this == & dm)
      return *this;
   
   std::swap(pNext, dm.pNext);
   std::swap(description, dm.description);

   
   return *this;
}

/*
ksi::data_modifier* ksi::data_modifier::clone() const
{
   return new data_modifier (*this);
}
*/

ksi::data_modifier::~data_modifier()
{
   if (pNext)
      delete pNext;
}

/*
void ksi::data_modifier::modify(ksi::dataset& ds)
{
   // empty methods -- modifies nothing
   
   // only calles the modify method of the next modifier:
   if (pNext)
      pNext->modify(ds);
}
*/
void ksi::data_modifier::addModifier(ksi::data_modifier & dm)
{
   if (pNext == nullptr)
      pNext = dm.clone();
   else 
      pNext->addModifier(dm);
}


std::string ksi::data_modifier::print() const
{
   if (pNext)
   {
      auto further_description = pNext->print();
      if (further_description.empty())
         return description;
      else 
         return description + " + " + further_description;
   }
   else 
      return description;
} 

