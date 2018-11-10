/** @file */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "neuro-fuzzy-system.h"
#include "rulebase.h" 
#include "../service/debug.h"


// void ksi::neuro_fuzzy_system::createFuzzyRulebase(int nRules, 
//                                                   int nClusteringIterations, 
//                                                   int nTuningIterations, 
//                                                   double dbLearningCoefficient,
//                                                   const ksi::dataset& train)
// {
//    // empty method
// }



ksi::neuro_fuzzy_system::neuro_fuzzy_system (int nRules, 
                                             int nClusteringIterations, 
                                             int nTuningIterations, 
                                             const ksi::dataset & TrainDataset,
                                             const ksi::t_norm  * pTnorm 
                                            )
{
   _nRules = nRules;
   _nClusteringIterations = nClusteringIterations;
   _nTuningIterations = nTuningIterations;
   _TrainDataset = TrainDataset;
   _pTnorm = pTnorm ? pTnorm->clone() : nullptr;
   _pRulebase = nullptr;
}


// ksi::neuro_fuzzy_system * ksi::neuro_fuzzy_system::clone() const
// {
//    return new ksi::neuro_fuzzy_system (*this);
// }

// ksi::number ksi::neuro_fuzzy_system::elaborate_answer(const ksi::datum& d) const
// {
//    return ksi::number(false);
// }

std::string ksi::neuro_fuzzy_system::get_nfs_description() const
{
   return _description_of_neuro_fuzzy_system; 
}
 
std::string ksi::neuro_fuzzy_system::get_nfs_name() const
{
   return _name_of_neuro_fuzzy_system;
}
 

void ksi::neuro_fuzzy_system::printRulebase(std::ostream & ss)
{
   _pRulebase->print(ss);
}

ksi::neuro_fuzzy_system::~neuro_fuzzy_system()
{
   delete _pTnorm;
   _pTnorm = nullptr;
   
   delete _pRulebase;
   _pRulebase = nullptr;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system()
{
   _pTnorm = nullptr;
   _pRulebase = nullptr;
   _name_of_neuro_fuzzy_system = std::string("");
   _description_of_neuro_fuzzy_system = std::string ("");
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const ksi::neuro_fuzzy_system & wzor)
{
   if (wzor._pTnorm)
      _pTnorm = wzor._pTnorm->clone();
   else
      _pTnorm = nullptr;
   
   _pRulebase = (wzor._pRulebase) ? wzor._pRulebase->clone() : nullptr;
   
   copy_fields(wzor);
      
}

ksi::neuro_fuzzy_system & ksi::neuro_fuzzy_system::operator=(const ksi::neuro_fuzzy_system & wzor)
{
   if (this == & wzor)
      return *this;
   
   delete _pTnorm;
   _pTnorm = (wzor._pTnorm) ? wzor._pTnorm->clone() : nullptr;
   
   delete _pRulebase;
   _pRulebase = (wzor._pRulebase) ? wzor._pRulebase->clone() : nullptr;
   
   copy_fields(wzor);
   
   return *this;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(ksi::neuro_fuzzy_system&& wzor)
{
   std::swap (_pTnorm, wzor._pTnorm);
   std::swap (_pRulebase, wzor._pRulebase);
   
   copy_fields(wzor);
}

ksi::neuro_fuzzy_system & ksi::neuro_fuzzy_system::operator=(ksi::neuro_fuzzy_system && wzor)
{
   if (this == & wzor)
      return *this;
   
   std::swap (_pTnorm, wzor._pTnorm);
   std::swap (_pRulebase, wzor._pRulebase); 
   
   copy_fields(wzor);
   
   return *this;
}


void ksi::neuro_fuzzy_system::copy_fields(const ksi::neuro_fuzzy_system & wzor)
{
   _nRules = wzor._nRules;
   _nClusteringIterations = wzor._nClusteringIterations;
   _nTuningIterations = wzor._nTuningIterations;
   _TrainDataset = wzor._TrainDataset;
   _TestDataset = wzor._TestDataset;
   _name_of_neuro_fuzzy_system = wzor._name_of_neuro_fuzzy_system;
   _description_of_neuro_fuzzy_system = wzor._description_of_neuro_fuzzy_system;
}

