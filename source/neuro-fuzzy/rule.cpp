/** @file */ 


#include <utility>
#include <vector> 
#include <chrono>

#include "rule.h"
#include "premise.h"
#include "../service/debug.h"
#include "../granules/granule.h"


ksi::rule::rule()
{
    pPremise     = nullptr;
    pConsequence = nullptr;
    pTnorma      = nullptr;
      
    last_localisation = 0;
    last_weight       = 0;
}


bool ksi::rule::validate() const
{
    return (pPremise and pConsequence);
}



std::pair<double, double> 
ksi::rule::getAnswerLocalisationWeight(const std::vector<double> & X)
{
   try
   {
      // trzeba wyznaczyc wartosc przeslanki:
      double firingStrength = pPremise->getFiringStrength(X);
      // i konkluzji:
      auto ans = pConsequence->getLocalisationWeight(X, firingStrength);
      last_localisation = ans.first;
      last_weight = ans.second;
      return ans;
   }
   CATCH;
}

 

void ksi::rule::cummulate_differentials(const std::vector< double >& X, 
                                        double partial_differential,
                                        double secundary_partial_differentials
                                       )
{
   // trzeba jeszcze pobrac
   double last_F = pPremise->getLastFiringStrength();
   
   pPremise->cummulate_differentials(X, partial_differential);
   pConsequence->cummulate_differentials(X, partial_differential, secundary_partial_differentials, last_F);
   
}

void ksi::rule::reset_differentials()
{
   if (pPremise)
      pPremise->reset_differentials();
   if (pConsequence)
      pConsequence->reset_differentials();
}


ksi::rule::rule (const ksi::t_norm & t)
{ 
   pTnorma = t.clone();
   pConsequence = nullptr;
   pPremise = nullptr;
}

ksi::rule::rule(const ksi::rule & wzor) : granule (wzor)
{
   if (not wzor.pTnorma)
   {
      //exception nexc (__FILE__, __func__, __LINE__, "wzor.pTnorma == nullptr");
      //throw nexc;
      pTnorma = nullptr;
   }
   else
      pTnorma = wzor.pTnorma->clone();
     
   if (not wzor.pPremise)
   {
      //exception nexc (__FILE__, __func__, __LINE__, "wzor.pPremise == nullptr");
      //throw nexc;
      pPremise = nullptr;
   }
   else
      pPremise = wzor.pPremise->clone();
   
   if (wzor.pConsequence != nullptr)
      pConsequence = wzor.pConsequence->clone();  
   else
   {
      pConsequence = nullptr;
      //exception nexc (__FILE__, __func__, __LINE__, "wzor.pConsequence == nullptr");
      //throw nexc;
   }
   
   last_localisation = wzor.last_localisation;
   last_weight = wzor.last_weight;
}

ksi::rule::rule (ksi::rule && r) : granule (r)
{
    std::swap (pTnorma, r.pTnorma);
    std::swap (pPremise, r.pPremise);
    std::swap (pConsequence, r.pConsequence);
    std::swap (r.last_localisation, last_localisation);
    std::swap (r.last_weight, last_weight);
}

ksi::rule & ksi::rule::operator = (const ksi::rule & r)
{
   if (this == & r)
      return *this;
   
   granule::operator= (r);
   
   if (r.pTnorma)
      pTnorma = r.pTnorma->clone();
   else
      pTnorma = nullptr;
   
   if (r.pPremise)
      pPremise = r.pPremise->clone();
   else
      pPremise = nullptr;
   
   if (r.pConsequence)
      pConsequence = r.pConsequence->clone();  
   else
      pConsequence = nullptr;
   
   last_localisation = r.last_localisation;
   last_weight = r.last_weight;
   
   return *this;
}

ksi::rule & ksi::rule::operator=(ksi::rule && r)
{
   if (this == & r)
      return *this;
   
   granule::operator=(r);
      
   std::swap (r.pTnorma, pTnorma);
   std::swap (r.pPremise, pPremise);
   std::swap (r.pConsequence, pConsequence);  
   std::swap (r.last_localisation, last_localisation);
   std::swap (r.last_weight, last_weight);
   
   return *this; 
}


ksi::rule::~rule()
{
   delete pTnorma;
   pTnorma = nullptr;
   
   delete pPremise;
   pPremise = nullptr;
   
   delete pConsequence;
   pConsequence = nullptr;
}

void ksi::rule::setPremise(const ksi::premise & p)
{
    try 
    {
        if (pPremise)
        {
            delete pPremise;
            pPremise = nullptr;
        }
        pPremise = p.clone();
        
        if (pTnorma)
            pPremise->setTnorm(*pTnorma);
    }
    CATCH;
}

void ksi::rule::setConsequence (const ksi::consequence & con)
{
    try 
    {
        if (pConsequence)
            delete pConsequence;
        pConsequence = con.clone();
    }
    CATCH;
}


ksi::rule * ksi::rule::clone() const
{
   return new rule(*this);
}


void ksi::rule::actualise_parameters(double eta)
{
   if (pPremise)
      pPremise->actualise_parameters(eta);
   if (pConsequence)
      pConsequence->actualise_parameters(eta);
}

std::ostream & ksi::rule::Print(std::ostream & ss) const
{
   ss << "rule" << std::endl;
   if (pTnorma)
   {
        ss << "t-norm: ";
        pTnorma->Print(ss);
        ss << std::endl;
   }
   ss << "premise: " << std::endl;
   pPremise->Print (ss);
   ss << std::endl;
   ss << "consequence: " << std::endl;
   pConsequence->Print(ss);
   ss << std::endl;
   ss << "quality: " <<  this->get_quality() << std::endl;
   return ss;
}
 
ksi::granule * ksi::rule::clone_granule() const
{
    return new  ksi::rule (*this);
}

const ksi::number ksi::rule::get_answer(const ksi::datum& d)
{
    auto LocalisationWeight = getAnswerLocalisationWeight(d.getVector());
    return number(LocalisationWeight.first);
}

ksi::datum ksi::rule::get_data_item()
{
    try 
    {
        ksi::datum x = pPremise->getRandomValue(_engine);
        ksi::number odpowiedz = get_answer(x);
        x.setDecision(odpowiedz);
        return x;
    }
    CATCH;
}

void ksi::rule::elaborate_quality()
{
    try 
    {
        throw std::string ("not implemented yet");
    }
    CATCH;
}


ksi::rule * ksi::rule::get_rule() const
{
    return clone();
}
