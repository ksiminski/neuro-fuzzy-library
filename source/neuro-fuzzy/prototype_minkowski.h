
#ifndef PROTOTYPE_MINKOWSKI_H
#define PROTOTYPE_MINKOWSKI_H

#include <vector>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"

namespace ksi
{
   /** Prototype with Minkowski distance used for similarity.
    @date 2021-01-27 */ 
   class prototype_minkowski : public prototype
   {
   protected:
       double _m;   ///< exponent 
       std::vector<double> _centre; ///< localisation of prototype centre (attributes)
       std::vector<double> _weights; ///< weights of prototype attributes 
       
//        std::vector<double> _centre_prev; ///< previous localisation of prototype centre (attributes)
//        std::vector<double> _weights_prev; ///< previous weights of prototype attributes
       
       
       std::vector<double> _d_centre; ///< differentials of centres
       std::vector<double> _d_weights; ///< differentials of weights
       
 
       
    public:
      prototype_minkowski (const double m);
      prototype_minkowski (const prototype_minkowski & wzor) = default;
      prototype_minkowski (prototype_minkowski && wzor) = default;
      prototype_minkowski & operator= (const prototype_minkowski & wzor) = default;
      prototype_minkowski & operator= (prototype_minkowski && wzor) = default;
      virtual ~prototype_minkowski ();
      
//       ksi::premise * clone() const override;
      
      virtual double get_similarity (const ksi::datum & d) const override;
      
      virtual double get_similarity (const std::vector<double> & X) const override;
      
      virtual void addDescriptor (const descriptor & d) override;
      
      
      /** The method cummulates differentials for an X data item in a rule. 
       @param X the data item to cummulate differantials for 
       @param partial_differential some differentials from other rules
       @date 2021-01-28
       */
     virtual void cummulate_differentials(std::vector< double > X, 
                                  double partial_differential) override;
                                  
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
     
//      virtual std::string get_name() const override;
//      virtual std::string get_description() const override;
     
     virtual void justified_granularity_principle (const std::vector<std::vector<double>> & X, const std::vector<double> & Y) override; 
                                                   
   protected:
     /** The method elaborates differentials for the justified granularity principle.
      @date 2021-04-18
      */  
     virtual
     std::pair<std::vector<double>, std::vector<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) = 0;
     
     /** The method elaborates  cardinality of the prototype, average value of decision attribute in the prototype, and similarities of add data to the prototype
      @param X dataset
      @param Y decision attribute
      @return cardinality of the prototype, average value of decision attribute in the prototype, and similarities of add data to the prototype
      @date 2021-04-27
      */
     std::tuple<double, double, std::vector<double>> cardinality_similarities
(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const;


     /** The method elaborates differentials of similarities.
      @return differentials of similarities with regard to attributes (centres),
              differentials of similarities with regard to weights of attributes.
      @param X dataset
      @date 2021-04-27
      */
     std::pair<ksi::Matrix<double>, ksi::Matrix<double>> similarity_differentials(const std::vector<std::vector<double>>& X);
     
     
     /** The method elaborates differentials of average of decision attribute
      @return differentials with regard to attributes (centres),
              differentials with regard to weights of attributes.
      @param X dataset
      @param dsim_da differentials of similarities with regard to attributes (centres)
      @param dsim_za differentials of similarities with regard to weights of attributes
      @param kardynalnosc cardinality of the prototype
      @date 2021-04-27
      */
     std::pair<std::vector<double>, std::vector<double>> decision_attribute_average_differentials (const std::vector<double> & Y,                                                                                                                           const ksi::Matrix<double> & dsim_da,                                                                                                                           const ksi::Matrix<double> & dsim_za,                                                                                                                           const double kardynalnosc);
     
     
     /** The method elaborates differentials of cardinality and variance 
      @return differentials with regard to attributes (centres),
              differentials with regard to weights of attributes.
      @param Y decision attributes
      @param similarities similarities of data examples to the prototype
      @param dysrednia_da differentials of average of decision attribute with regard to attributes (centres)
      @param dysrednia_dz differentials of average of decision attribute with regard to weights of attributes
      @param dsim_da differentials of similarities with regard to attributes (centres)
      @param dsim_za differentials of similarities with regard to weights of attributes
      @param srednia_y average of decision attribute
      @param kardynalnosc cardinality of the prototype
      @date 2021-04-27
      */
     std::pair<std::vector<double>, std::vector<double>> cardinality_variance_differentials (
         const std::vector<double> & Y, 
         const std::vector<double> & similarities,
         const std::vector<double> & dysrednia_da,
         const std::vector<double> & dysrednia_dz,
         const ksi::Matrix<double> & dsim_da, 
         const ksi::Matrix<double> & dsim_dz, 
         const double & srednia_y, 
         const double & kardynalnosc);
     
     
     virtual double debug_criterion_function(const std::vector<std::vector<double>>& X,
                                     const std::vector<double> & Y) const;
     
     
   };
}


#endif
