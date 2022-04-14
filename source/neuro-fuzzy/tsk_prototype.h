
#ifndef TSK_PROTOTYPE_H
#define TSK_PROTOTYPE_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/nfs_prototype.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../common/dataset.h"
#include "../common/datum.h"
#include "../common/number.h"
#include "../partitions/partition.h"



namespace ksi
{
    
   /** The TSK prototype neuro-fuzzy system.
    This is a neuro-fuzzy systems (in the Takagi-Sugeno-Kang architecture) based on prototypes in premises.
      
    * CITATION REQUEST    
    <pre>
    @article{id:Siminski2022Prototype,
	author = "Krzysztof Siminski",
	doi = "10.1016/j.fss.2022.03.001",
	issn = "0165-0114",
	journal = "Fuzzy Sets and Systems",
	keywords = "Prototype; Granular computing; Neuro-fuzzy system; Regression",
	title = "Prototype based granular neuro-fuzzy system for regression task",
	url = "https://www.sciencedirect.com/science/article/pii/S0165011422000963",
	year = "2022"
    }
    </pre>
    
    @author Krzysztof Siminski
    */ 
   class tsk_prototype : public nfs_prototype
   {
       
    public:
      tsk_prototype ();
      tsk_prototype (const tsk_prototype & wzor);
      tsk_prototype (tsk_prototype && wzor);
      tsk_prototype & operator= (const tsk_prototype & wzor);
      tsk_prototype & operator= (tsk_prototype && wzor);
      virtual ~tsk_prototype ();

      /** constructor
       * @param number_of_rules number of rules
       * @param number_of_clustering_iterations number of clustering iterations
       * @param number_of_tuning_iterations number of tuning iterations
       * @param learning_coefficient learning coefficient for gradient method
       * @param normalisation normalisation of data 
       * @param prot prototype factory 
       */
      tsk_prototype (const int number_of_rules,
                     const int number_of_clustering_iterations,
                     const int number_of_tuning_iterations,
                     const double learning_coefficient,
                     const bool normalisation,
                     const ksi::fac_prototype & prot);

      /** constructor
       * @param number_of_rules number of rules
       * @param number_of_clustering_iterations number of clustering iterations
       * @param number_of_tuning_iterations number of tuning iterations
       * @param learning_coefficient learning coefficient for gradient method
       * @param normalisation normalisation of data 
       * @param prot prototype factory 
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @date 2021-03-22
       */
      tsk_prototype (const int number_of_rules,
                     const int number_of_clustering_iterations,
                     const int number_of_tuning_iterations,
                     const double learning_coefficient,
                     const bool normalisation,
                     const ksi::fac_prototype & prot,
                     const double positive_class, 
                     const double negative_class, 
                     const ksi::roc_threshold threshold_type);
      
      
      virtual void createFuzzyRulebase(int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, const ksi::dataset & train) override;
      
    public:
      ksi::neuro_fuzzy_system * clone() const override;
      virtual std::string get_nfs_name() const override;
      virtual std::string get_nfs_description() const override;

      // jakies metody, żeby interfejs był zaimplementowany -- zasmiecanie interfejsu  
      ksi::discriminative_model * clone_discriminant() const override;
      ksi::generative_model * clone_generator() const override;
      
   };
}


#endif
