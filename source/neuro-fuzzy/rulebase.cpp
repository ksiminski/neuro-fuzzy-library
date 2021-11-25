/** @file */ 

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "rulebase.h"
#include "rule.h"
#include "../service/debug.h"

bool ksi::rulebase::validate() const
{
    for (const auto & r : rules)
        if (not r->validate())
            return false;
    
    return true;
}

ksi::rulebase * ksi::rulebase::clone() const
{
   return new ksi::rulebase (*this);
}

void ksi::rulebase::addRule(const ksi::rule & r)
{
    try 
    {
        rules.push_back(r.clone());
    }
    CATCH;
}

double ksi::rulebase::answer(const std::vector<double> & X)
{
   try
   {
      double sumLocalisationWeight = 0;
      double sumWeight             = 0;
      
      // zapamietuje wartosci odpowiedzi -- przyda sie w strojeniu
      last_rules_localisations_weights.clear();
   
//       for (auto & r : rules)
//       {
//          auto ans = r->getAnswerLocalisationWeight(X);
//          if (not std::isfinite(ans.first) or not std::isfinite(ans.second))
//             ans = {0, 0}; 
//          
//          last_rules_localisations_weights.push_back(ans);
//          sumLocalisationWeight += (ans.first * ans.second);
//          sumWeight += ans.second;
//       }

      ///////////////////////////
      last_rules_localisations_weights.resize(rules.size());
      #pragma omp parallel for reduction (+: sumLocalisationWeight, sumWeight)
      for (std::size_t i = 0; i < rules.size(); i++)
      {
         auto ans = rules[i]->getAnswerLocalisationWeight(X);
         if (not std::isfinite(ans.first) or not std::isfinite(ans.second))
            ans = {0, 0}; 
         
         last_rules_localisations_weights[i] = ans;
         sumLocalisationWeight += (ans.first * ans.second);
         sumWeight += ans.second;
      }
      //////////////////////////
      
      if (sumWeight != 0.0)
         return last_answer = sumLocalisationWeight / sumWeight;
      else 
         return last_answer = 0;
   }
   CATCH;
}

void ksi::rulebase::cummulate_differentials(const std::vector< double >& X, 
                                            double Yexpected)
{
   const double EPSILON = 1e-8;
   
   double odpowiedz = answer(X);
   double roznica = odpowiedz - Yexpected; // roznica odpowiedzi oczekiwanej od wypracowanej dla calego systemu
    
   double suma_wag = 0.0;
   for (auto & lw : last_rules_localisations_weights)
      suma_wag += lw.second;
   
   #pragma omp parallel for
   for (std::size_t i = 0; i < rules.size(); i++)
   {
      double rozniczka = 0;
      double rozniczkaMA = 0;
      if (std::fabs(suma_wag) > EPSILON)
      {
         rozniczka = roznica * (last_rules_localisations_weights[i].first - odpowiedz) / suma_wag;
         rozniczkaMA = last_rules_localisations_weights[i].second / suma_wag;
      }
      rules[i]->cummulate_differentials(X, rozniczka, rozniczkaMA);
   }
}

ksi::rulebase::~rulebase()
{
   for (auto & p : rules)
      delete p;
}

void ksi::rulebase::clear()
{
   for (auto & p : rules)
      delete p;
   rules.clear();
}

ksi::rulebase::rulebase()
{
}

ksi::rulebase::rulebase(const rulebase & rb)
{
   for (auto & r : rb.rules)
      rules.push_back(r->clone());
   
   last_answer = rb.last_answer;
   last_rules_localisations_weights = rb.last_rules_localisations_weights;
}

ksi::rulebase::rulebase(rulebase && rb)
{
   std::swap (rules, rb.rules);
   last_answer = rb.last_answer;
   last_rules_localisations_weights = rb.last_rules_localisations_weights;
}


ksi::rulebase & ksi::rulebase::operator= (const rulebase & rb)
{
   if (this == &rb)
      return *this;
   
   for (auto & p : rules)
      delete p;
   rules.clear();
   
   for (auto & r : rb.rules)
      rules.push_back(r->clone());
   
   last_answer = rb.last_answer;
   last_rules_localisations_weights = rb.last_rules_localisations_weights;
   
   return *this;
}

ksi::rulebase & ksi::rulebase::operator= (rulebase && rb)
{
   if (this == & rb)
      return *this;
   
   std::swap(rules, rb.rules);
   last_answer = rb.last_answer;
   last_rules_localisations_weights = rb.last_rules_localisations_weights;
   
   return *this;
}

void ksi::rulebase::reset_differentials()
{
   for (auto & r : rules)
      r->reset_differentials();
}

void ksi::rulebase::actualise_parameters(double eta)
{
   for (auto & r : rules)
      r->actualise_parameters(eta);
}

std::vector< std::pair< double, double > > ksi::rulebase::get_last_rules_localisations_weights()
{
   return last_rules_localisations_weights;
}

ksi::rule & ksi::rulebase::operator[] (std::size_t index)
{
   try
   {
      if (rules.size() == 0)
      {
          throw std::string ("empty rule base (no rules present)");
      }
      if (index < 0 or index >= rules.size())
      {
         std::stringstream ss;
         ss << "Invalid index value: " << index << " Range of valid values: [0, " << rules.size() - 1 << "]." << std::endl;
         throw ss.str();
      }
      else
         return *rules[index];
   }
   CATCH;
}

std::size_t ksi::rulebase::getNumberOfRules() const
{
   return rules.size();
}

void ksi::rulebase::print(std::ostream & ss)
{
   std::size_t size = getNumberOfRules();
   for (std::size_t i = 0; i < size; i++)
   {
      ss << "RULE " << (i + 1) << std::endl << std::endl;
      rules[i]->Print(ss);
      ss << std::endl;
   }
}

const std::size_t ksi::rulebase::size() const
{
    return rules.size();
}

const ksi::granule * ksi::rulebase::getGranule(int index) const
{
    if (index < 0 or index >= rules.size())
        return nullptr;
    
    return rules[index];
}

ksi::granule * ksi::rulebase::getGranuleNonConst(int index)
{
    if (index < 0 or index >= rules.size())
        return nullptr;
    
    return rules[index];
}

 
const ksi::number ksi::rulebase::get_answer(const ksi::datum & d, ksi::granule* pg)
{
    return this->answer(d.getVector());
}

void ksi::rulebase::addGranule(const ksi::granule & g)
{
    try 
    {
//         auto p = g.get_rule();
//         if (p) // p points to a rule
//             rules.push_back(p->clone());
//         delete p;

        auto p = g.get_rule();
        if (p) // p points to a rule
            rules.push_back(p);
//         delete p;
        
    }
    CATCH;
}

void ksi::rulebase::addGranule(const ksi::granule* g)
{
    try 
    {
        if (g)
        {
//             auto p = g->get_rule();
//             if (p) // p points to a rule
//                 rules.push_back(p->clone());
//             delete p;

            auto p = g->get_rule();
            if (p) // p points to a rule
                rules.push_back(p);
        }
    }
    CATCH;
}

ksi::set_of_granules * ksi::rulebase::clone_set_of_granules() const
{
    return new ksi::rulebase(*this);
}


