/** @file */  

#include <algorithm>
#include <string>
#include <sstream>
#include "cluster.h"
#include "../descriptors/descriptor.h"
#include "../granules/granule.h"
#include "../service/debug.h"


std::size_t ksi::cluster::get_number_of_desciptors() const
{
    return descriptors.size();
}


ksi::cluster::~cluster()
{
   for (auto & p : descriptors)
      delete p;
   descriptors.clear();     
}

ksi::cluster::cluster()
{
}

ksi::cluster::cluster(const ksi::cluster & cl) : granule (cl)
{
   for (auto & p : cl.descriptors)
      descriptors.push_back(p->clone());
}

ksi::cluster::cluster(ksi::cluster && cl) : granule (cl)
{
   std::swap (descriptors, cl.descriptors);
}

ksi::cluster& ksi::cluster::operator=(const ksi::cluster& cl)
{
   if (this == & cl)
      return *this;
   
   granule::operator= (cl);
      
   for (auto & p : descriptors)
      delete p;
   descriptors.clear();    

   for (auto & p : cl.descriptors)
      descriptors.push_back(p->clone());
   
   return *this;
}

ksi::cluster& ksi::cluster::operator=(ksi::cluster&& cl)
{
   if (this == & cl)
      return *this;
   
   granule::operator= (cl);
   
   std::swap (descriptors, cl.descriptors);
   
   return *this;
}

const std::size_t ksi::cluster::getNumberOfDescriptors() const
{
   return descriptors.size();
}

ksi::descriptor* ksi::cluster::getDescriptor(int attribute)
{
   try
   {
      if (descriptors.empty())   
      {
         std::stringstream ss;
         ss << "No descriptors in cluster!" << std::endl;
         throw ss.str();
      }
      if (attribute < 0 or attribute >= descriptors.size())
      {
         std::stringstream ss;
         ss << "Illegal attribute number (" << attribute << ")" << std::endl;
         ss << "Legal values: 0 .. " << descriptors.size() - 1 << std::endl;
         throw ss.str();
      }
      
      if (descriptors[attribute])
          return descriptors[attribute]->clone();
      else
          return nullptr;
      
   }
   CATCH;
}

const ksi::descriptor* ksi::cluster::getAddressOfDescriptor(int attribute)
{
   if (descriptors.empty())
      return nullptr;
   if (attribute < 0 or attribute >= descriptors.size())
      return nullptr;
   
   return descriptors[attribute];
}


void ksi::cluster::addDescriptor(ksi::descriptor * p)
{
   descriptors.push_back(p);
}

void ksi::cluster::addDescriptor(const ksi::descriptor & d)
{
   descriptors.push_back(d.clone());
}

namespace ksi 
{
   std::ostream& operator<<(std::ostream& ss, const ksi::cluster& cl)
   {
      int attr = 1;
      for (auto & d : cl.descriptors)
      {
         ss << "descriptor " << attr++ << ": " << std::endl;
         ss << d->toString() << std::endl;
      }
      return ss;
   }
}

std::vector<ksi::ext_fuzzy_number_gaussian> ksi::cluster::getGranule() const
{
    try 
    {
        std::vector<ksi::ext_fuzzy_number_gaussian> granule;
        
        for (auto const d : descriptors)
            granule.push_back(d->getGranule());
        
        return granule;
    }
    CATCH;
}

ksi::granule * ksi::cluster::clone_granule() const
{
    return new ksi::cluster (*this);
}

const ksi::number ksi::cluster::get_answer(const ksi::datum& d)
{
    try 
    {
        throw std::string ("not implemented yet");
    }
    CATCH;
    return number();
}

ksi::datum ksi::cluster::get_data_item()
{
    ksi::datum d; 
    for (auto * p : descriptors)
        d.push_back(p->getRandomValue(_engine));
    
    return d;
}

void ksi::cluster::elaborate_quality()
{
    try 
    {
        throw std::string ("not implemented yet");
    }
    CATCH;
}

