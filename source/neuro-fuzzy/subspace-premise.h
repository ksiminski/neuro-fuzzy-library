/** @file */ 

#ifndef SUBSPACE_PREMISE_H
#define SUBSPACE_PREMISE_H

#include <vector>

#include "../neuro-fuzzy/premise.h"
#include "../descriptors/descriptor.h"
#include "../tnorms/t-norm.h"

namespace ksi
{
  class subspace_premise : virtual public premise
  {
     /** default weight exponent */
     double _weight_expo = 2.0;
  public:
     subspace_premise ();
     /** construct a subspace premise with weight exponent */
     subspace_premise(double weight_exponent);
     subspace_premise (const subspace_premise &);
     subspace_premise (const t_norm & tnorm);
     subspace_premise & operator= (const subspace_premise & prawa);
     subspace_premise & operator= (subspace_premise && prawa);
     
     virtual ~subspace_premise ();
     
     virtual premise * clone () const ;
     
     
     /** @return firing strength of a rule. It is a T-norm of 
      *          activations of all descriptors with attributes weights.
      * \f[ F = T \left( u_{1}, u_{2}, \ldots, u_{n}; 
      *                  z_{1}, z_{2}, \ldots, z_{n}; \right)\f] 
      * \f[ F = T \left( 1 - z_{1} \left(1 - u_{1} \right), 
      *                  1 - z_{2} \left(1 - u_{2} \right), 
      *                  \ldots,
      *                  1 - z_{n} \left(1 - u_{n} \right)
      *                  \right)
      * \f]
      * where \f$F\f$ is activation of rule, \f$u_i\f$ is activation of the \f$i\f$-th descriptor of the rule, \f$z_i\f$ is the weight of the \f$i\f$-th descriptor of the rule, and \f$T\f$ is a T-norm.
      */
     virtual double getFiringStrength(const std::vector<double> & X);
     
     /** The method cummulates differentials for an X data item in a rule. 
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @date 2018-01-20
       */
     virtual void cummulate_differentials(std::vector< double > X, 
                                          double partial_differential);
     
     
     /** The method augments a-th attribute weights. */
     void augment_attribute (int a, double maxi_weight);
      
  };
}
#endif