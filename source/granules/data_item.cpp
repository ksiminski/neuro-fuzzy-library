
#include "../service/debug.h"
#include "granule.h"
#include "data_item.h"

ksi::data_item::data_item ()
{
    pDatum = nullptr;
}

ksi::data_item::data_item (const ksi::data_item & wzor) : granule (wzor)
{
    if (wzor.pDatum)
        pDatum = wzor.pDatum->clone();
    _decision = wzor._decision;
}

ksi::data_item::data_item (ksi::data_item && wzor) : granule (wzor)
{
    std::swap (pDatum, wzor.pDatum);
    std::swap (_decision, wzor._decision);
}

ksi::data_item::~data_item ()
{
    delete pDatum;
    pDatum = nullptr; 
}

ksi::data_item & ksi::data_item::operator= (const ksi::data_item & wzor)
{
   if (this == & wzor)
      return *this;

   granule::operator=(wzor);

   delete pDatum;
   pDatum = nullptr; 

   if (wzor.pDatum)
       pDatum = wzor.pDatum->clone();
   _decision = wzor._decision;

   return *this;
}

ksi::data_item & ksi::data_item::operator= (ksi::data_item && wzor)
{
   if (this == & wzor)
      return *this;

   granule::operator=(wzor);

   std::swap (pDatum, wzor.pDatum);
   std::swap (_decision, wzor._decision);

   return *this;
}

ksi::granule * ksi::data_item::clone_granule() const
{
    return new ksi::data_item (*this);
}

ksi::data_item::data_item(const ksi::datum & d)
{
    pDatum = d.clone(); 
}
 
ksi::datum ksi::data_item::get_data_item()
{
    try 
    {
        if (pDatum) 
           return *pDatum;
        else 
            throw std::string ("pDatum == nullptr");
    }
    CATCH;
}

const ksi::number ksi::data_item::get_answer(const ksi::datum& d)
{
    return _decision;
}

void ksi::data_item::elaborate_quality()
{
    _quality = 1.0;
}
 
ksi::data_item::data_item(const ksi::datum& d, const ksi::number& decision)
{
    pDatum = d.clone();
    _decision = decision;
}


