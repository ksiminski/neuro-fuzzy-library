/** @file */  

#include <algorithm>
#include <string>
#include <sstream>
#include "cluster.h"
#include "../descriptors/descriptor.h"
#include "../service/debug.h"

ksi::cluster::~cluster()
{
   for (auto & p : descriptors)
      delete p;
   descriptors.clear();     
}

ksi::cluster::cluster()
{
}

ksi::cluster::cluster(const ksi::cluster & cl)
{
   for (auto & p : cl.descriptors)
      descriptors.push_back(p->clone());
}

ksi::cluster::cluster(ksi::cluster && cl)
{
   std::swap (descriptors, cl.descriptors);
}

ksi::cluster& ksi::cluster::operator=(const ksi::cluster& cl)
{
   if (this == & cl)
      return *this;
   
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
   
   std::swap (descriptors, cl.descriptors);
   
   return *this;
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
      
      return descriptors[attribute]->clone();
      
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

