/** @file */ 

#ifndef RULE_H
#define RULE_H

#include <utility>
#include <vector>
#include <chrono>

#include "premise.h"
#include "consequence.h"
#include "../tnorms/t-norm.h"
#include "../granules/granule.h"

namespace ksi
{
   class rule : public granule
   {
   protected:
      premise     * pPremise     = nullptr;
      consequence * pConsequence = nullptr;
      t_norm      * pTnorma      = nullptr;
      
      /** localisation of answer for the last data item */
      double last_localisation;
      /** weight of answer for the last data item */
      double last_weight;
      
   public:
      virtual ~rule();
      rule ();
      rule (const rule &);
      rule (ksi::rule&& r);
      rule & operator = (const rule &);
      rule & operator = (rule &&);
      
      rule (const t_norm & t);
      
      /** The method returns localisation and weight of an answer for an X data item
       * @param X data item to elaborate answer for
       * @return a pair: first is localisation, second is weight
       */
      virtual std::pair<double, double> getAnswerLocalisationWeight (const std::vector<double> & X); 
      
      
      
      /** The method cummulates differentials for an X data item in a rule. 
       * Default behaviour: nothing :-)
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @param secundary_partial_differential some differentials (when needed, 
              otherwise not used)
       */
      virtual void cummulate_differentials (const std::vector<double> & X, 
                                            double partial_differential, 
                                            double secundary_partial_differential
                                           );
      
      /** The method allocates memory for a copy of P_L premise. */
      void setPremise(const premise & P_L);
      /** The method allocates memory for a copy of C_L consequence. */
      void setConsequence(const consequence & C_L);
     // void getTnorm();
      virtual rule * clone() const;
      
      /** The method sets all cummulated differentials to zero. */
      virtual void reset_differentials ();
      
      /** The method actualises values of parameters of the fuzzy rule
       * @param eta learning coefficient
       */
      virtual void actualise_parameters (double eta);
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
      virtual std::ostream & Print (std::ostream & ss) const;
            
      /** The method validates the rule. It checks if both premise and conclusion of the rule exist. 
       @return true if both premise and conclusion exist, otherwise false. */
      virtual bool validate () const;
      
      //--------------------------------------------
      // methods for granules
      
      virtual granule * clone_granule() const;
       
      /** The method elaborates quality of the granule. */
      virtual void elaborate_quality ();
       
      /** @return The method returns a data_item represented by the data granule. */
      virtual datum get_data_item ();
       
      /** @return The method returns a decision for a datum.
          @param  d the datum to elaborated answer for .*/
      virtual const number get_answer (const datum & d);
      
      virtual rule * get_rule () const;
   };
}

#endif
