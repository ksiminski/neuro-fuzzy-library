/** @file */ 

#ifndef PREMISE_H
#define PREMISE_H

#include <vector>
#include <random>
#include "../descriptors/descriptor.h"
#include "../tnorms/t-norm.h"
#include "../common/datum.h"

namespace ksi
{
  class premise 
  {
  protected:
     std::vector<descriptor *> descriptors;
     t_norm * pTnorma = nullptr; 
     
     /** firing strength for the last data item */
     double last_firingStrength;
     
  public:
     premise ();
     premise (const premise &);
     premise (const t_norm & tnorm);
     virtual ~premise ();
     
     
     void setTnorm (const t_norm & tnorm);
     t_norm * getTnorm ();
     premise & operator= (const premise & prawa);
     
     /** The methods add an descriptor WITHOUT allocation of memory. */
     void addDescriptor (descriptor * p);
     /** The methods add an descriptor WITH allocation of memory (copies
      *  the descriptor). */
     void addDescriptor (descriptor & d);
     
     
     /** @return firing strength of a rule. It is a T-norm of 
      *          activations of all descriptors.
      * \f[ F = T \left( u_{1}, u_{2}, \ldots, u_{n}  \right),  \f]
      * where \f$F\f$ is activation of rule, \f$u_i\f$ is activation of the \f$i\f$-th descriptor of the rule, and \f$T\f$ is a T-norm.
      */
     virtual double getFiringStrength(const std::vector<double> & X);
     
     virtual premise * clone () const ;
     
     double getLastFiringStrength();
     
     /** The method cummulates differentials for an X data item in a rule. 
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @date 2018-01-20
       */
     virtual void cummulate_differentials(std::vector<double> X, 
                                  double partial_differential);
     
     /** The method sets all cummulated differentials to zero. */
     virtual void reset_differentials ();
 
     /** The method actualises values of parameters of the fuzzy premise
       * @param eta learning coefficient
       */
     virtual void actualise_parameters (double eta);
     
     /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
     virtual std::ostream & Print (std::ostream & ss) const;
     
     friend std::ostream & operator << (std::ostream & ss, const premise & p);
     
     /** @return The method returns a random datum covered by a premise. */
     virtual datum  getRandomValue (std::default_random_engine & engine); 
     
     
     /** The method transforms a premise into a granule with justified granularity principle.
      @date 2021-04-18
      */
     virtual void justified_granularity_principle (const std::vector<std::vector<double>> & X, const std::vector<double> & Y);
     
  };
}
#endif

