
#ifndef PROTOTYPE_MINKOWSKI_REGRESSION_H
#define PROTOTYPE_MINKOWSKI_REGRESSION_H

#include <vector>

#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"

namespace ksi
{
   /** Prototype with Minkowski distance used for similarity.
    @date 2021-01-27 */ 
   class prototype_minkowski_regression : public prototype_minkowski
   {
 
       
    public:
      prototype_minkowski_regression (const double m);
      prototype_minkowski_regression (const prototype_minkowski_regression & wzor) = default;
      prototype_minkowski_regression (prototype_minkowski_regression && wzor) = default;
      prototype_minkowski_regression & operator= (const prototype_minkowski_regression & wzor) = default;
      prototype_minkowski_regression & operator= (prototype_minkowski_regression && wzor) = default;
      virtual ~prototype_minkowski_regression ();
      
      ksi::premise * clone() const override;
      
 
     
     /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
     virtual std::ostream & Print (std::ostream & ss) const override;
     
     /** The method actualises values of parameters of the fuzzy premise
       * @param eta learning coefficient
       */
   
     
     virtual std::string get_name() const override;
     virtual std::string get_description() const override;
     
    
   protected:
       /** The method elaborates differentials for the justified granularity principle.
      @date 2021-04-18
      */  
     virtual
     std::pair<std::vector<double>, std::vector<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y);
     
   };
}


#endif
