
#ifndef PROTOTYPE_MAHALONOBIS_H
#define PROTOTYPE_MAHALONOBIS_H

#include <vector>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

namespace ksi
{
   /** Prototype with Mahalanobis distance used for similarity.
    @date 2023-06-26 */ 
   class prototype_mahalanobis : public prototype
   {
   protected:
       Matrix<double> _A;   ///< matrix for the Mahalanobis distance
       std::vector<double> _centre; ///< localisation of prototype centre (attributes)
       
       Matrix<double> _d_A;   ///< differencial for matrix for the Mahalanobis distance
       std::vector<double> _d_centre; ///< differentials of centres
       
    public:
      prototype_mahalanobis ();
      prototype_mahalanobis (const Matrix<double> m);
      prototype_mahalanobis (const cluster & cl);
      prototype_mahalanobis (const prototype_mahalanobis & wzor) = default;
      prototype_mahalanobis (prototype_mahalanobis && wzor) = default;
      prototype_mahalanobis & operator= (const prototype_mahalanobis & wzor) = default;
      prototype_mahalanobis & operator= (prototype_mahalanobis && wzor) = default;
      virtual ~prototype_mahalanobis ();
      
      virtual double get_similarity (const ksi::datum & d) const override;
      virtual double get_similarity (const std::vector<double> & X) const override;
      
      virtual void addDescriptor (const descriptor & d) override; 
      
      
      /** The method cummulates differentials for an X data item in a rule. 
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @date 2023-07-06
       */
     virtual void cummulate_differentials(std::vector< double > X, double partial_differential) override;
                                  
     /** @date 2023-07-02*/
     void reset_differentials() override;
     
     /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
     virtual std::ostream & Print (std::ostream & ss) const override;
     
     /** The method actualises values of parameters of the fuzzy premise
       * @param eta learning coefficient
       */
     virtual void actualise_parameters (double eta) override;
     
     virtual std::string get_name() const override;
     virtual std::string get_description() const override;
     
     virtual void justified_granularity_principle (const std::vector<std::vector<double>> & X, const std::vector<double> & Y) override; 
                                                   
   protected:
     /** The method elaborates differentials for the justified granularity principle.
      @date 2023-07-04
      @return first:  vector of differentials for prototype centres
              second: matrix of differentials for matrix in Mahalanobis metric
      */  
     virtual
     std::pair<std::vector<double>, ksi::Matrix<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) = 0;

     /** The method elaborates differentials of similarities. This method is a part of the grandient tuning algorithm.
      @return differentials of similarities with regard to attributes (centres),
              differentials of similarities with regard to elements of covariance matrix for the Mahalanobis distance 
      @param X dataset
      @date 2023-07-03
      */
     std::pair<std::vector<std::vector<double>>, std::vector<ksi::Matrix<double>>> similarity_differentials(const std::vector<std::vector<double>>& X);
     
     
     /** The method elaborates differentials of average of decision attribute
      @return differentials with regard to attributes (centres),
              differentials with regard to items of the distance matrix
      @param X dataset
      @param dsim_dp differentials of similarities with regard to attributes (centres)
      @param dsim_aij differentials of similarities with regard to items of the distance matrix
      @param cardinality cardinality of the prototype
      @date 2023-07-09
      */
      std::pair<std::vector<double>, ksi::Matrix<double>> decision_attribute_average_differentials (
            const std::vector<double> & Y,
            const std::vector<std::vector<double>> & dsim_dp,
            const std::vector<ksi::Matrix<double>> & dsim_aij,
            const double cardinality);
     
     
     /** The method elaborates differentials of cardinality and variance 
      @return differentials with regard to attributes (centres),
              differentials with regard to elements of covariance matrix.
      @param Y decision attributes
      @param similarities similarities of data examples to the prototype
      @param dyaverage_dp differentials of average of decision attribute with regard to attributes (centres)
      @param dyaverage_da differentials of average of decision attribute with regard to elements of the covariance matrix
      @param dsim_dp differentials of similarities with regard to attributes (centres)
      @param dsim_da differentials of similarities with regard to weights of attributes
      @param average_y average of decision attribute
      @param cardinality cardinality of the prototype
      @date 2021-07-11
      */
     std::pair<std::vector<double>, ksi::Matrix<double>> cardinality_variance_differentials (
         const std::vector<double> & Y, 
         const std::vector<double> & similarities,
         const std::vector<double> & dyaverage_dp,
         const ksi::Matrix<double> & dyaverage_da,
         const std::vector<std::vector<double>> & dsim_dp, 
         const std::vector<ksi::Matrix<double>> & dsim_da, 
         const double & average_y, 
         const double & cardinality);
     
     virtual double criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const = 0;
     
     /** @return  dkappa_dp, dkappa_daij */
     std::pair<std::vector<double>, ksi::Matrix<double>>  cardinality_differentials (const std::vector<std::vector<double>> & dsim_dp, const std::vector<ksi::Matrix<double>> & dsim_da);

   };
}


#endif
