/** @file */ 

#include <cmath>

#include "subspace-premise.h"
#include "../descriptors/descriptor.h"
#include "../tnorms/t-norm.h"
#include "../service/debug.h"

ksi::subspace_premise::subspace_premise(double weight_exponent)
{
   _weight_expo = weight_exponent;
}


ksi::premise* ksi::subspace_premise::clone() const
{
   return new ksi::subspace_premise::premise (*this);
}

ksi::subspace_premise::subspace_premise(const ksi::t_norm & tnorm) : ksi::premise(tnorm)
{
   
}

ksi::subspace_premise::subspace_premise(const ksi::subspace_premise & wzor) : ksi::premise (wzor)
{
   _weight_expo = wzor._weight_expo;
}

ksi::subspace_premise::subspace_premise() : ksi::premise()
{
   
}

ksi::subspace_premise::~subspace_premise()
{

}

ksi::subspace_premise & ksi::subspace_premise::operator=(const ksi::subspace_premise& prawa)
{
   if (this == & prawa)
      return *this;
   
   ksi::premise::operator=(prawa);
   _weight_expo = prawa._weight_expo;
   
   return *this;
}


ksi::subspace_premise & ksi::subspace_premise::operator=(ksi::subspace_premise && prawa)
{
   if (this == & prawa)
      return *this;
   
   ksi::premise::operator=(prawa);
   _weight_expo = prawa._weight_expo;
   
   return *this;
}

double ksi::subspace_premise::getFiringStrength(const std::vector<double> & X)
{
   if (not pTnorma)
      return -1;
   if (X.size() != descriptors.size())
      return -1; 
   
   double result = 1;
   std::size_t nAttr = X.size();
   for (std::size_t a = 0; a < nAttr; a++)
   {
      auto weighted_firing = 1.0 - std::pow(descriptors[a]->getWeight(), _weight_expo) * (1 - descriptors[a]->getMembership(X[a]));
      result = pTnorma->tnorm (result, weighted_firing);
   }
   last_firingStrength = result;
   return result;
}


void ksi::subspace_premise::augment_attribute(int a, double maxi_weight)
{
   auto weight = descriptors[a]->getWeight();
   descriptors[a]->setWeight(weight / maxi_weight);
}


void ksi::subspace_premise::cummulate_differentials(std::vector<double> X, 
                                                    double factor)
{
   for (std::size_t i = 0; i < descriptors.size(); i++)
   {
      auto z = descriptors[i]->getWeight();
      auto zf = std::pow(z, _weight_expo);
      auto mi = descriptors[i]->getMembership(X[i]);
      auto ulamek = 1.0 / ( 1.0 - zf * (1.0 - mi) );
      auto czynnik = zf * mi;
      
      descriptors[i]->cummulate_differentials(X[i], 
         factor * last_firingStrength * ulamek * czynnik);
   }
}
