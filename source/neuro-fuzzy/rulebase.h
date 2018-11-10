/** @file */ 

#ifndef RULEBASE_H
#define RULEBASE_H

#include <vector>
#include <utility>
#include "premise.h"
#include "consequence.h"
#include "rule.h"


namespace ksi
{
   class rulebase 
   {
   protected:    
      /** rules of the rulebase */
      std::vector<rule *> rules;
       
      /** answer of a rulebase for the last data item */
      double last_answer;
      
      /** answers of all rules for the last data items */
      std::vector<std::pair<double, double>> last_rules_localisations_weights;
      
   public:
      rulebase();
      rulebase(const rulebase & );
      rulebase(rulebase &&);
      rulebase & operator= (const rulebase &);
      rulebase & operator= (rulebase &&);
      void addRule (const rule &);
      
      /** The method elaborates an answer for an X data item.
       * @param X data item to elaborate answer for 
       * @return an answer 
       */
      double answer (const std::vector<double> & X);
      
      /** The method cummulates the differentials for an X data item.
       * @param X data item to cummulate differentials for
       * @param Y expected value
       * @date 2018-01-20
       * @author Krzysztof Siminski
       */
      void cummulate_differentials (const std::vector< double >& X, double Yexpected);
      
      /** The method sets all cummulated differentials to zero. */
      void reset_differentials ();
      
      /** The method actualises values of parameters of the fuzzy model
       * @param eta learning coefficient
       */
      void actualise_parameters (double eta);
      
      virtual ~rulebase();
      
      /** The method removes all rules from the rulebase. */
      void clear();
      
      /** Operator return a reference to a rule with given index.
       * @param index index of a rule
       * @exception ksi::exception if index illegal
       * */
      rule & operator[] (std::size_t index);
      
      /** @return localisations and weights of all rules for the last data item */
      std::vector<std::pair<double, double>> get_last_rules_localisations_weights();
      
      /** @return number of rules in the rulebase */
      std::size_t getNumberOfRules() const;
      
      /** @return a pointer to a cloned rulebase */
      virtual rulebase * clone () const;
      
      /** The method prints the rulebase to the output stream ss.
       * @param ss the output stream to print into
       */
      void print(std::ostream & ss);
      
      
       
   };
}
#endif

