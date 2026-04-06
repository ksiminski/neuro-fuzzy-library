
#ifndef PROTOTYPE_MINKOWSKI_H
#define PROTOTYPE_MINKOWSKI_H

#include <vector>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

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
       
       std::vector<double> _d_centre; ///< differentials of centres
       std::vector<double> _d_weights; ///< differentials of weights
       
    public:
      prototype_minkowski (const double m);
      prototype_minkowski (const cluster & cl, const double m);
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
     virtual void cummulate_differentials(std::vector< double > X, double partial_differential) override;
                                  
     void reset_differentials() override;
     
     /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
     virtual std::ostream & print (std::ostream & ss) const override;
     
     /** The method actualises values of parameters of the fuzzy premise
       * @param eta learning coefficient
       */
     virtual void actualise_parameters (double eta) override;
     
     
     virtual void justified_granularity_principle (const std::vector<std::vector<double>> & X, const std::vector<double> & Y) override; 
                                                   
   protected:
     /** The method elaborates differentials for the justified granularity principle.
      @date 2021-04-18
      */  
     virtual
     std::pair<std::vector<double>, std::vector<double>> differentials_justified_granularity_principle (
         const std::vector<std::vector<double>>& X, 
         const std::vector<double> & Y) = 0;
     
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
     std::pair<std::vector<double>, std::vector<double>> decision_attribute_average_differentials (
     	const std::vector<double> & Y,
     	const ksi::Matrix<double> & dsim_da, 
    	const ksi::Matrix<double> & dsim_za,
    	const double kardynalnosc);
     
     
     /** The method elaborates differentials of cardinality and variance 
      @return differentials with regard to attributes (centres),
              differentials with regard to weights of attributes.
      @param Y decision attributes
      @param similarities similarities of data examples to the prototype
      @param dyaverage_da differentials of average of decision attribute with regard to attributes (centres)
      @param dyaverage_dz differentials of average of decision attribute with regard to weights of attributes
      @param dsim_da differentials of similarities with regard to attributes (centres)
      @param dsim_za differentials of similarities with regard to weights of attributes
      @param average_y average of decision attribute
      @param cardinality cardinality of the prototype
      @date 2021-04-27
      */
     std::pair<std::vector<double>, std::vector<double>> cardinality_variance_differentials (
         const std::vector<double> & Y, 
         const std::vector<double> & similarities,
         const std::vector<double> & dyaverage_da,
         const std::vector<double> & dyaverage_dz,
         const ksi::Matrix<double> & dsim_da, 
         const ksi::Matrix<double> & dsim_dz, 
         const double & average_y, 
         const double & cardinality);

     /** @return The method returns the value of the criterion function for the principle of justified granularity. */
     virtual double criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const = 0;

   };
}


#endif
