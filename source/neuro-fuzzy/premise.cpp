/** @file */ 

#include <chrono>
#include <random>
#include <sstream>

#include "../neuro-fuzzy/premise.h"
#include "../descriptors/descriptor.h"
#include "../tnorms/t-norm.h"
#include "../service/debug.h"
#include "../common/datum.h"

ksi::premise::premise()
{
   pTnorma = nullptr;
}


ksi::premise::~premise()
{
   for (auto & p : descriptors)
      delete p;
   
   delete pTnorma;
}

ksi::premise* ksi::premise::clone() const
{
   return new ksi::premise (*this);
}


void ksi::premise::addDescriptor (descriptor * p)
{
    descriptors.push_back(p);
}

ksi::t_norm * ksi::premise::getTnorm()
{
   return pTnorma;
}

void ksi::premise::addDescriptor (descriptor & d)
{
   descriptors.push_back(d.clone());
}

ksi::premise::premise (const t_norm & t)
{
   pTnorma = t.clone();
}

void ksi::premise::setTnorm (const ksi::t_norm & t)
{
   pTnorma = t.clone();
}

ksi::premise & ksi::premise::operator = (const ksi::premise & prawa) 
{
   if (this != & prawa)
   {
      for (auto & p : descriptors)
         delete p;
      descriptors.clear();
      
      for (auto & p : prawa.descriptors)
         descriptors.push_back(p->clone());
      
      if (prawa.pTnorma)
         pTnorma = prawa.pTnorma->clone();
      else
         pTnorma = nullptr;
   }
   return *this;
}

double ksi::premise::getFiringStrength(const std::vector<double> & X)
{
   try
   {
      if (not pTnorma)
         throw std::string ("no T-norm");
      if (X.size() != descriptors.size())
      {
         std::stringstream ss;
         ss << "Data vector size (" << X.size() << ") and number of descriptors (" << descriptors.size() << ") do not match!";
         throw ss.str();
      }
      double result = 1;
      std::size_t nAttr = X.size();
      for (std::size_t a = 0; a < nAttr; a++)
      {
         result = pTnorma->tnorm (result, descriptors[a]->getMembership(X[a]));
      }
      last_firingStrength = result;
     
      return result;
   }
   CATCH;
}

ksi::premise::premise(const premise & wzor) 
{
   if (wzor.pTnorma)
      pTnorma = wzor.pTnorma->clone();
   else
      pTnorma = nullptr;
   
   for (auto * p : wzor.descriptors)
   {
      addDescriptor(p->clone());
   }
}


void ksi::premise::cummulate_differentials(std::vector< double > X, double factor)
{
   for (std::size_t i = 0; i < descriptors.size(); i++)
      descriptors[i]->cummulate_differentials(X[i], factor * last_firingStrength);
}

double ksi::premise::getLastFiringStrength()
{
   return last_firingStrength;
}

void ksi::premise::reset_differentials()
{
   for (auto & d : descriptors)
      d->reset_differentials();
}

void ksi::premise::actualise_parameters(double eta)
{
   for (auto & d : descriptors)
      d->actualise_parameters(eta);
}

std::ostream & ksi::premise::Print(std::ostream & ss) const
{
   ss << "premise" << std::endl;
   ss << "desciptors" << std::endl;
   std::size_t i = 1;
   for (auto * p : descriptors)
   {
      ss << i++ << ": " << std::endl; 
      p->Print(ss);
      ss << std::endl;
   }  
   return ss;
}

namespace ksi 
{
    std::ostream & operator << (std::ostream & ss, const premise & p)
    {
        p.Print (ss);
        return ss;
    }
}

ksi::datum ksi::premise::getRandomValue(std::default_random_engine & engine)
{
//    debug(descriptors.size());
    ksi::datum dat;
    for (auto & d : descriptors)
        dat.push_back(ksi::number(d->getRandomValue(engine)));
    return dat;
}

void ksi::premise::justified_granularity_principle(const std::vector<std::vector<double> >& X, const std::vector<double>& Y)
{
    return;
}
