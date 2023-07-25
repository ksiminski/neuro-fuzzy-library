
#ifndef PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H
#define PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H

#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/premise.h"

#include "../partitions/cluster.h"

namespace ksi
{
   class prototype_mahalanobis_classification : public prototype_mahalanobis
   {
   public:
      prototype_mahalanobis_classification();
      prototype_mahalanobis_classification(const Matrix<double> m, double positive_class_label, const double negative_class_label);
      prototype_mahalanobis_classification(const cluster &cl, double positive_class_label, const double negative_class_label);
      prototype_mahalanobis_classification(const prototype_mahalanobis_classification &wzor) = default;
      prototype_mahalanobis_classification(prototype_mahalanobis_classification &&wzor) = default;
      prototype_mahalanobis_classification &operator=(const prototype_mahalanobis_classification &wzor) = default;
      prototype_mahalanobis_classification &operator=(prototype_mahalanobis_classification &&wzor) = default;
      virtual ~prototype_mahalanobis_classification();
      virtual premise *clone() const override; // prototype design pattern

   public:
      /** The method elaborates differentials for the justified granularity principle.
       @ date 2023-07-07                         *  *
       */
      virtual std::pair<std::vector<double>, ksi::Matrix<double>> differentials_justified_granularity_principle(
          const std::vector<std::vector<double>> &X,
          const std::vector<double> &Y) override;

   protected:
      /** The method elaborates cardinality of the prototype, probabilities of positive and negative classes, and similarities of data to the prototype
           @param X dataset
           @param Y decision attribute
           @param positive_class positive class label
           @param negative_class negative class label
           @return cardinality of the prototype, probability of positive class, probability of negative class, and similarities of add data to the prototype
           @date 2021-06-21
           */
      std::tuple<double, double, double, std::vector<double>> cardinality_class_probabilities_similarities(
          const std::vector<std::vector<double>> &X,
          const std::vector<double> &Y,
          const double positive_class,
          const double negative_class) const;

   protected:
      double _positive_class_label;
      double _negative_class_label;
   
protected:
      /** The method elaborates differentials of cardinality.
      @return differentials of cardinality with regard to attributes (centres),
              differentials of cardinality with regard to weights of attributes.
      @param dsim_dp differences of similarities with regard to attributes (centres)
      @param dsim_daij differences of similarities with regard to values of the covariance matrix
      @param nItems number of items
      @date 2023-07-16
      *//*
     std::pair<std::vector<double>, std::vector<double>>    
     cardinality_differentials(const std::vector<std::vector<double>> & dsim_dp,
                               const std::vector<ksi::Matrix<double>> & dsim_daij,
                               const std::size_t nItems
                              );    
*/

     std::pair<std::vector<double>, ksi::Matrix<double>>  probability_differentials(
            const std::vector<double>& similarities,
            const std::vector<double>& classes, 
            const std::vector<std::vector<double>>& dsim_dp, 
            const std::vector<ksi::Matrix<double>>& dsim_da, 
            const double cardinality, 
            const std::vector<double>& dkappa_dp, 
            const ksi::Matrix<double>& dkappa_da,
            const double class_label);
     
     /** @date 2023-07-17 */
     std::pair<std::vector<double>, ksi::Matrix<double>>
         Gini_differentials(
            const double probability_positive, 
            const double probability_negative, 
            const std::vector<double> & dPpos_dp, 
            const ksi::Matrix<double> & dPpos_da,
            const std::vector<double> & dPneg_dp, 
            const ksi::Matrix<double> & dPneg_da);

     /** @date 2023-07-17 */
     std::pair<std::vector<double>, ksi::Matrix<double>> final_differentials(
            const std::vector<double> & dkappa_dp, 
            const ksi::Matrix<double> & dkappa_da, 
            const double specificity, 
            const double cardinality, 
            const std::vector<double> & dsigma_dp, 
            const ksi::Matrix<double> & dsigms_da);   
     
     /** @date 2023-07-22 */
     virtual double criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const override;
   };

}

#endif
