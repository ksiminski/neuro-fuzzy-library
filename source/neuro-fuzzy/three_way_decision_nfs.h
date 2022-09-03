
#ifndef THREE_WAY_DECISION_NFS_H
#define THREE_WAY_DECISION_NFS_H

#include <vector>
#include <memory>

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

namespace ksi
{
	/** 
     Three way decision neuro-fuzzy classifier. 
	  The main feature of the system is the three way decision. It returns three answers: positive class, negative class, or noncommintment decision (“I do not know”, “I cannot decide” answer).

	  @author Krzysztof Siminski
	  @date   2021-09-12
	*/
   class three_way_decision_nfs : public neuro_fuzzy_system
   {
   protected:
       double _noncommintment_value = 0.2; ///< maximal deviation from the threshold in classification
   protected:
	   /** This is the crucial part of this three-way-decision system – a cascade of classifiers.  */
	   std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> _cascade;  
  
   
   public:
      three_way_decision_nfs ();
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade);
      
      /** @param cascade cascade of neuro-fuzzy systems
          @param train   name of train dataset file 
          @param test    name of test  dataset file
          @param result  name of output result file 
          @param maximal_deviation maximal deviation from a classification threshold
          @date 2021-09-14
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::string & train, 
                              const std::string & test, 
                              const std::string & result,
                              const double maximal_deviation
                             );

      /** @param cascade cascade of neuro-fuzzy systems
          @param train   train dataset
          @param test    test  dataset
          @param result  name of output result file 
          @param maximal_deviation maximal deviation from a classification threshold
          @date 2022-02-02
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const ksi::dataset & train, 
                              const ksi::dataset & test, 
                              const std::string & result,
                              const double maximal_deviation
                             );

      
      three_way_decision_nfs (const three_way_decision_nfs & wzor);
      three_way_decision_nfs (three_way_decision_nfs && wzor);
      three_way_decision_nfs & operator= (const three_way_decision_nfs & wzor);
      three_way_decision_nfs & operator= (three_way_decision_nfs && wzor);
      virtual ~three_way_decision_nfs ();

       
     public:  
       ksi::neuro_fuzzy_system * clone() const override;
       
     public:   
       // interface declaration   
       virtual discriminative_model * clone_discriminant () const override;
       virtual generative_model * clone_generator () const override;
       virtual void train_discriminative_model (const dataset & ds) override;
       virtual double discriminate (const datum & d) override;
       
     public:
       /** The method calls createFuzzyRulebase(const ksi::dataset &).
        @param nClusteringIterations  passed value ignored
        @param nTuningIterations      passed value ignored
        @param dbLearningCoefficient  passed value ignored 
        @param train                  trainset to train the system 
        @date 2021-09-14
        @author Krzysztof Siminski */  
       virtual void createFuzzyRulebase (int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, const dataset & train) override;
       
       /** The method trains a cascade of neuro-fuzzy systems. 
        @param train   train dataset
        @param test    test  dataset 
        @date 2021-09-14
        @author Krzysztof Siminski
        */
       virtual void createFuzzyRulebase(const ksi::dataset & train, const ksi::dataset & test) override;
       
       virtual number elaborate_answer (const datum & d) const override;
       
       virtual double answer (const datum & item) const override;
       
       /** The method elaborates answer for classification.
       @return a pair: elaborated numeric, class
       @date   2021-09-27
       */
      virtual std::pair<double, double> answer_classification (const datum & item) const override;
       
             /** The method prints rule base.
       * @param ss ostream to print to */
       virtual void printRulebase(std::ostream & ss) override;
       
       
      /** @return a short name of the neuro-fuzzy system */
      virtual std::string get_nfs_name () const override;
      /** @return a description of the neuro-fuzzy system */
      virtual std::string get_nfs_description () const override;
      
   protected:
       /** @return The method returns always an empty string.
           @date   2021-09-28
        */
       virtual std::string get_classification_threshold_value () const override;
      
   protected:
        /** The method elaborates a classification threshold.
        @param Expected           not used
        @param Elaborated         not used
        @param positiveClassvalue not used
        @param negativeClassvalue not used
        @param type               not used
        @return always zero
        
        */
       virtual double elaborate_threshold_value (std::vector<double> & Expected, 
                                         std::vector<double> & Elaborated, 
                                         double positiveClassvalue,
                                         double negativeClassvalue,
                                         const ksi::roc_threshold & type) override;
       
       
   protected:
       /** @todo Ta metoda jest do poprawy. Nie działa dobrze.  */
       ksi::dataset extract_poor_results(const dataset & data, 
                                         const std::vector<std::tuple<double, double, double>> &                                         results_train, 
                                         const double threshold_value, 
                                         const double maximal_deviation);
      
   protected:    
       std::string extra_report() const override;
       
       virtual std::string classification_intro() const override;

       virtual void copy_fields(const three_way_decision_nfs & _3wnfs);
       
   public:
       friend
       std::ostream & operator<< (std::ostream & ss, const ksi::three_way_decision_nfs & system);
   };
}


#endif
