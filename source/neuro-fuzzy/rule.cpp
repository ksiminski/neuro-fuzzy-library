/** @file */ 


#include <utility>
#include <vector> 

#include "rule.h"
#include "premise.h"
#include "../service/debug.h"


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

ksi::rule::rule(const ksi::rule & wzor) 
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
      pPremise = nullptr;
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
}

ksi::rule::rule (ksi::rule && r)
{
   pTnorma = r.pTnorma;
   r.pTnorma = nullptr;
   
   pPremise = r.pPremise;
   r.pPremise = nullptr;
   
   pConsequence = r.pConsequence;
   r.pConsequence = nullptr;
   
}

ksi::rule & ksi::rule::operator = (const ksi::rule & r)
{
   if (this == & r)
      return *this;
   
   pPremise = r.pPremise;
   
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
   if (pPremise)
      delete pPremise;
   
   pPremise = p.clone();
   
   if (pTnorma)
      pPremise->setTnorm(*pTnorma);
}

void ksi::rule::setConsequence (const ksi::consequence & con)
{
   if (pConsequence)
      delete pConsequence;
   pConsequence = con.clone();
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
   ss << "simple rule" << std::endl;
   ss << "t-norm: ";
   pTnorma->Print(ss);
   ss << std::endl;
   ss << "premise: " << std::endl;
   pPremise->Print (ss);
   ss << std::endl;
   ss << "consequence: " << std::endl;
   pConsequence->Print(ss);
   ss << std::endl;
   return ss;
}




