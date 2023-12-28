
#ifndef PROTOTYPE_MINKOWSKI_CLASSIFICATION_H
#define PROTOTYPE_MINKOWSKI_CLASSIFICATION_H

#include <vector>

#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

namespace ksi
{
   /** Prototype with Minkowski distance used for similarity.
    @date 2021-01-27 */ 
   class prototype_minkowski_classification : public prototype_minkowski
   {
   protected:
       double _positive_class_label;
       double _negative_class_label;
       
    public:
      prototype_minkowski_classification (const double m, const double positive_class_label, const double negative_class_label);
      prototype_minkowski_classification (const cluster & cl, const double m, const double positive_class_label, const double negative_class_label);
      prototype_minkowski_classification (const prototype_minkowski_classification & wzor) = default;
      prototype_minkowski_classification (prototype_minkowski_classification && wzor) = default;
      prototype_minkowski_classification & operator= (const prototype_minkowski_classification & wzor) = default;
      prototype_minkowski_classification & operator= (prototype_minkowski_classification && wzor) = default;
      virtual ~prototype_minkowski_classification ();
      
      ksi::premise * clone() const override;
      
        /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
      virtual std::ostream & print (std::ostream & ss) const override;
          
      virtual std::string get_name() const override;
      virtual std::string get_description() const override;
      
      /** @return The method returns the value of the criterion function for the principle of justified granularity.
       @todo ¿Czy na pewno? */
      virtual double criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const override;
 
                                                   
   protected:
   
     /** The method elaborates differentials for the justified granularity principle.
      @date 2021-06-21
      */  
     virtual
     std::pair<std::vector<double>, std::vector<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) override;
     
      /** The method elaborates differentials of cardinality.
      @return differentials of cardinality with regard to attributes (centres),
              differentials of cardinality with regard to weights of attributes.
      @param dsim_da differences of similarities with regard to attributes (centres)
      @param dsim_dz differences of similarities with regard to weights of attributes
      @param nItems number of items
      @date 2021-06-21
      */
     std::pair<std::vector<double>, std::vector<double>>    
     cardinality_differentials(const ksi::Matrix<double> & dsim_da,
                               const ksi::Matrix<double> & dsim_dz,
                               const std::size_t nItems
                              );    
         
   
     std::pair<std::vector<double>, std::vector<double>>  probability_differentials(
            const std::vector<double>& similarities,
            const std::vector<double>& classes, 
            const ksi::Matrix<double>& dsim_da, 
            const ksi::Matrix<double>& dsim_dz, 
            const double cardinality, 
            const std::vector<double>& dkappa_da, 
            const std::vector<double>& dkappa_dz,
            const double class_label);
     
     std::pair<std::vector<double>, std::vector<double>>
         Gini_differentials(
            const double probability_positive, 
            const double probability_negative, 
            const std::vector<double> & dPpos_da, 
            const std::vector<double> & dPpos_dz,
            const std::vector<double> & dPneg_da, 
            const std::vector<double> & dPneg_dz);
         
     std::pair<std::vector<double>, std::vector<double>> final_differentials(
            const std::vector<double> & dkappa_da, 
            const std::vector<double> & dkappa_dz, 
            const double specificity, 
            const double cardinality, 
            const std::vector<double> & dsigma_da, 
            const std::vector<double> & dsigms_dz);   
     
      /** The method elaborates cardinality of the prototype, probabilities of positive and negative classes, and similarities of data to the prototype
      @param X dataset
      @param Y decision attribute
      @param positive_class positive class label
      @param negative_class negative class label
      @return cardinality of the prototype, probability of positive class, probability of negative class, and similarities of add data to the prototype
      @date 2021-06-21
      */
     std::tuple<double, double, double, std::vector<double>> cardinality_class_probabilities_similarities (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y, 
         const double positive_class, 
         const double negative_class) const;
         
      
     
   };
}


#endif
