
#ifndef PROTOTYPE_MAHALANOBIS_REGRESSION_H
#define PROTOTYPE_MAHALANOBIS_REGRESSION_H

#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/premise.h"
#include "../partitions/cluster.h"

namespace ksi
{
   /** Prototype with Mahalanobis distance (used for similarity) for regression.
    @date 2023-07-06 */ 
   class prototype_mahalanobis_regression : public prototype_mahalanobis
   {
    public:
      prototype_mahalanobis_regression (const Matrix<double> m);
      prototype_mahalanobis_regression (const cluster & cl);
      prototype_mahalanobis_regression (const prototype_mahalanobis_regression & wzor) = default;
      prototype_mahalanobis_regression (prototype_mahalanobis_regression && wzor) = default;
      prototype_mahalanobis_regression & operator= (const prototype_mahalanobis_regression & wzor) = default;
      prototype_mahalanobis_regression & operator= (prototype_mahalanobis_regression && wzor) = default;
      virtual ~prototype_mahalanobis_regression ();
      virtual premise * clone () const override;


     virtual double criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const override;
      
   public:
      /** The method elaborates differentials for the justified granularity principle.
       @ date 2023-07-07  
       */  
      virtual
      std::pair<std::vector<double>,  ksi::Matrix<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) override;
     
     virtual std::string get_name() const override;
     virtual std::string get_description() const override;
   };
}


#endif
