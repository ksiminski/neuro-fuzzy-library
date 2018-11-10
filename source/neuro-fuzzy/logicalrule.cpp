/** @file */ 


#include <utility>
#include <vector> 
#include <string>

#include "rule.h"
#include "logicalrule.h"
#include "premise.h"
#include "../service/debug.h"


std::pair<double, double> 
ksi::logicalrule::getAnswerLocalisationWeight(const std::vector<double> & X)
{
   try
   {
      if (not pImplication)
         throw std::string ("not implication set (empty pointer)");
      
      // trzeba wyznaczyc wartosc przeslanki:
      double firingStrength = pPremise->getFiringStrength(X);
      // i konkluzji:
      auto res_consequence = pConsequence->getLocalisationWeight(X, firingStrength);
      
      // no i teraz korzystam z implikacji:
      double localisation = res_consequence.first;
      double w = res_consequence.second;
      double g = pImplication->G(firingStrength, w);
      
      last_localisation = localisation;
      last_weight = g;
      
      return { localisation, g };
   }
   CATCH;
}

ksi::logicalrule::logicalrule (const ksi::t_norm & tnorm, 
                               const ksi::implication & imp) : ksi::rule (tnorm)
{
   pImplication = imp.clone();
}
 
ksi::logicalrule::logicalrule(const ksi::logicalrule & wzor) : rule (wzor)
{
   if (wzor.pImplication)
      pImplication = wzor.pImplication->clone();
   else
      pImplication = nullptr;
}

ksi::logicalrule::~logicalrule()
{
   delete pImplication;
   pImplication = nullptr;
}

ksi::rule * ksi::logicalrule::clone() const
{
   return new logicalrule(*this);
}

ksi::logicalrule& ksi::logicalrule::operator=(ksi::logicalrule && wzor )
{
   if (this == & wzor)
      return *this;
   
   ksi::rule::operator=(wzor);
   
   return *this;
}

ksi::logicalrule& ksi::logicalrule::operator=(const ksi::logicalrule & wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::rule::operator=(wzor);
   
   return *this;
}


void ksi::logicalrule::cummulate_differentials(const std::vector< double >& X, 
                                               double partial_differential,
                                               double secundary_partial_differentials
                                              )
{
   // trzeba jeszcze pobrac
   double last_F = pPremise->getLastFiringStrength();
   double cons_w = pConsequence->getW();
   
   double dG_dF = pImplication->dG_dF(last_F, cons_w);
   pPremise->cummulate_differentials(X, partial_differential * dG_dF);
   double dG_dw = pImplication->dG_dw(last_F, cons_w);
   pConsequence->cummulate_differentials(X, partial_differential * dG_dw, 0.0, last_F);
} 

std::ostream & ksi::logicalrule::Print (std::ostream & ss) const
{
   ss << "logical rule" << std::endl;
   ss << "implication: ";
   pImplication->Print(ss);
   ss << std::endl;
   ss << "premise: " << std::endl;
   pPremise->Print(ss);
   ss << std::endl;
   ss << "consequence: " << std::endl;
   pConsequence->Print(ss);
   ss << std::endl;
   return ss;
}


