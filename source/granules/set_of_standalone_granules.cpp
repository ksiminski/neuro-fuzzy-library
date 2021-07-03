
#include <vector>

#include "../granules/set_of_granules.h"
#include "../granules/set_of_standalone_granules.h"
#include "../service/debug.h"

ksi::set_of_standalone_granules::set_of_standalone_granules ()
{
}

ksi::set_of_standalone_granules::set_of_standalone_granules (const ksi::set_of_standalone_granules & wzor) : ksi::set_of_granules (wzor)
{
    for (auto * g : wzor.granules)
        granules.push_back(g->clone_granule());
}

ksi::set_of_standalone_granules::set_of_standalone_granules (ksi::set_of_standalone_granules && wzor) : ksi::set_of_granules (wzor)
{
    std::swap(granules, wzor.granules);
}

ksi::set_of_standalone_granules & ksi::set_of_standalone_granules::operator= (const ksi::set_of_standalone_granules & wzor)
{
   if (this == & wzor)
      return *this;

   for (auto * g : granules)
        delete g;
   
   granules.clear();

   for (auto * g : wzor.granules)
        granules.push_back(g->clone_granule());

   return *this;
}

ksi::set_of_standalone_granules & ksi::set_of_standalone_granules::operator= (ksi::set_of_standalone_granules && wzor)
{
   if (this == & wzor)
      return *this;

   std::swap(granules, wzor.granules);

   return *this;
}

ksi::set_of_standalone_granules::~set_of_standalone_granules ()
{
    for (auto * g : granules)
        delete g;
}

const std::size_t ksi::set_of_standalone_granules::size() const
{
    return granules.size();
}

void ksi::set_of_standalone_granules::addGranule(const ksi::granule & g)
{
    granules.push_back(g.clone_granule());
}

void ksi::set_of_standalone_granules::addGranule(const ksi::granule* g)
{
    granules.push_back(g->clone_granule());
}

const ksi::number ksi::set_of_standalone_granules::get_answer(const ksi::datum & d,  ksi::granule* pg)
{
    try 
    {
        return pg->get_answer(d);
    }
    CATCH;   
        
}

ksi::set_of_granules * ksi::set_of_standalone_granules::clone_set_of_granules() const
{
    return new ksi::set_of_standalone_granules (*this);
}

const ksi::granule * ksi::set_of_standalone_granules::getGranule(int index) const
{
    try 
    {
        if (index < 0 or index >= granules.size())
           return nullptr;
        return granules[index];
    }
    CATCH;
}

ksi::granule * ksi::set_of_standalone_granules::getGranuleNonConst(int index) 
{
    try 
    {
        if (index < 0 or index >= granules.size())
           return nullptr;
        return granules[index];
    }
    CATCH;
}
