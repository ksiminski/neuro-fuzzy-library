
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
	  The main feature of the system is the three way decision. It returns three answers: positive class, negative class, or noncommitment decision (“I do not know”, “I cannot decide” answer).

	  @author Krzysztof Siminski
	  @date   2021-09-12
	*/
   class three_way_decision_nfs : public neuro_fuzzy_system
   {
   protected:
       mutable std::size_t _number_of_rules_used      {0};
       mutable std::size_t _number_of_data_items      {0};
       mutable double _dbTrainAverageNumerOfRulesUsed {0.0};
       mutable double _dbTestAverageNumerOfRulesUsed  {0.0};

   protected:
       /** The vector stores F1score for the train dataset.
        *  The i-th cell holds the value for [0 .. i-1] NFS in the cascade. 
        *  @date 2024-04-30 */
       std::vector<double> _cascade_F1score_train;

       /** The vector stores F1score for the test dataset.
        *  The i-th cell holds the value for [0 .. i-1] NFS in the cascade. 
        *  @date 2024-04-30 */
       std::vector<double> _cascade_F1score_test;

   public:
       std::vector<std::tuple<double,double,double>> get_answers_for_train_classification() override;
       
   public:
       std::vector<std::tuple<double,double,double>> get_answers_for_test_classification() override;	
       
       
   protected:
	   /** This is the crucial part of this three-way-decision system – a cascade of classifiers.  */
	   std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> _cascade;  
   protected:
       /*** halfs of width of concommitment intervals for each NFS in the cascade */
       std::vector<double> _noncommitment_widths;  
       
   public:
      three_way_decision_nfs ();
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade);
      
      /** @param cascade cascade of neuro-fuzzy systems
          @param train   name of train dataset file 
          @param test    name of test  dataset file
          @param result  name of output result file 
          @param maximal_deviation maximal deviation from a classification threshold, 
                                   the same of all systems in a cascade
          @date 2021-09-14
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::string & train, 
                              const std::string & test, 
                              const std::string & result,
                              const double maximal_deviation
                             );
      
      /** @param cascade cascade of neuro-fuzzy systems
       @param train   name o*f train dataset file 
       @param test    name of test  dataset file
       @param result  name of output result file 
       @param maximal_deviations maximal deviations from a classification thresholds for each system separatedly
       @date 2024-04-23
       */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::string & train, 
                              const std::string & test, 
                              const std::string & result,
                              const std::vector<double> & maximal_deviations
      );
      
      
      /** @param cascade cascade of neuro-fuzzy systems
       @param maximal_deviation maximal deviation from a classification threshold,
                                the same of all systems in a cascade
       @date 2024-03-16
       */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const double maximal_deviation
      );

      /** @param cascade cascade of neuro-fuzzy systems
       *  @param maximal_deviations maximal deviations from a classification thresholds for each system separatedly
       *  @date 2024-03-17
       */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::vector<double> & maximal_deviations);
            
 
      /** @param cascade cascade of neuro-fuzzy systems
          @param train   name of train dataset file 
          @param validation name of validation file
          @param test    name of test  dataset file
          @param result  name of output result file 
          @param maximal_deviation maximal deviation from a classification threshold
          @date 2024-03-11
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::string & train, 
                              const std::string & validation,
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

      /** @param cascade cascade of neuro-fuzzy systems
          @param train   train dataset
          @param test    test  dataset
          @param result  name of output result file 
          @param maximal_deviations maximal deviations from a classification threshold for each system separatedly
          @date 2024-04-23
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const ksi::dataset & train, 
                              const ksi::dataset & test, 
                              const std::string & result,
                              const std::vector<double> & maximal_deviations
                             );

     /** @param cascade cascade of neuro-fuzzy systems
          @param train   train dataset
          @param validation validation dataset
          @param test    test  dataset
          @param result  name of output result file 
          @param maximal_deviation maximal deviation from a classification threshold
          @date 2024-03-11
          */
      three_way_decision_nfs (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const ksi::dataset & train, 
                              const ksi::dataset & validation,
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
       virtual void createFuzzyRulebase (int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, const dataset & train, const dataset & validation) override;
       
       /** The method trains a cascade of neuro-fuzzy systems. 
        @param train      train      dataset
        @param test       test       dataset 
        @param validation validation dataset
        @date 2021-09-14
        @author Krzysztof Siminski
        */
       virtual void createFuzzyRulebase(const ksi::dataset & train, const ksi::dataset & test, const ksi::dataset & validation) override;
       
       virtual number elaborate_answer (const datum & d) const override;
       
       virtual double answer (const datum & item) const override;
       
       /** The method elaborates answer for classification.
       @return a pair: elaborated numeric, class
       @date   2021-09-27 */
      virtual std::pair<double, double> answer_classification (const datum & item) const override;
      
      
      /** The method elaborates answer for classification.
       * @param item data item to elaborated answer for 
       * @param depth number of systems (in the cascade) used to elaborate the answer 
       *          Depth is indexed from 0 up to _cascade.size() - 1.
       * @return a pair: elaborated numeric, class 
       * @date   2024-04-29 */
      virtual std::pair<double, double> answer_classification (const datum & item, const std::size_t depth) const;
       
       /** The method prints rule base.
       * @param ss ostream to print to */
       virtual void printRulebase(std::ostream & ss) override;
              
      /** @return a short name of the neuro-fuzzy system */
      virtual std::string get_nfs_name () const override;
      /** @return a brief name of the neuro-fuzzy system 
       * @date 2024-04-21 */
      virtual std::string get_brief_nfs_name () const override;
      /** @return a description of the neuro-fuzzy system */
      virtual std::string get_nfs_description () const override;
      
      /** @return a description of the cascade 
       *  @date 2024-03-05 */
      virtual std::string get_cascade_names () const;
      /** @return a brief description of the cascade 
       *  @date 2024-04-21 */
      virtual std::string get_brief_cascade_names () const;
      
      /** @param cascade_depth number of neuro-fuzzy systems that will be used to elaborate answers
       *          Depth is indexed from 0 up to _cascade.size() - 1.
       *  @return expected class, elaborated_numeric answer, elaborated_class for the test dataset
       *  @date   2024-04-29 */
      virtual std::vector<std::tuple<double, double, double>> get_answers_for_train_classification(const std::size_t cascade_depth);
      
      /** @param cascade_depth number of neuro-fuzzy systems that will be used to elaborate answers
       *          Depth is indexed from 0 up to _cascade.size() - 1.
       *  @return expected class, elaborated_numeric answer, elaborated_class for the test dataset
       *  @date   2024-04-29 */
      virtual std::vector<std::tuple<double, double, double>> get_answers_for_test_classification(const std::size_t cascade_depth);
      
      /** @return The F1score for the train dataset for a part of the cascade. 
       *          Only ``depth'' systems in the cascade are used.
       *          Depth is indexed from 0 up to _cascade.size() - 1.
       *  @date 2024-04-29 */
      double get_train_F1score_for_part_of_the_cascade(const std::size_t depth);
      
      /** @return The F1score for the test dataset for a part of the cascade. 
       *          Only ``depth'' systems in the cascade are used.
       *          Depth is indexed from 0 up to _cascade.size() - 1.
       *  @date 2024-04-29 */
      double get_test_F1score_for_part_of_the_cascade(const std::size_t depth);
      
      /** The method elaborates F1scores for all depth of the cascade 
       *  (both for the train and test datasets).
       @date 2024-04-30 */
      void elaborate_cascade_f1scores();

   protected:
       /** @return The method returns always an empty string.
           @date   2021-09-28
        */
       virtual std::string get_classification_threshold_value () const override;
      
   protected:
        /** This system is composed of a cascade of NFSs. 
         *  Each of them has is own threshold.
         *  There is no general threshold. This is why zero is returned.
         *  The method is to satisfy the concordance with other NFS.
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
                                         const std::vector<std::tuple<double, double, double>> & results_train, 
                                         const double threshold_value, 
                                         const double maximal_deviation);
      
   protected:    
       std::string extra_report() const override;
       virtual std::string classification_intro() const override;
       virtual void three_copy_fields(const three_way_decision_nfs & _3wnfs);
       
       
   public:
       /** A report entry on the average number of rules for the train dataset.
        *  It is used in three way decision NFS and fuzzy three way decision NFS.
        *  @return string with the report
        *  @date 2024-03-24 */
       virtual std::string report_average_number_of_rules_for_train () const override;

   public:
     /** @return average number of rules fired for the test dateset 
      *  @date 2024-03-28 */
      virtual double get_number_of_rules () const override;
       
   public:
       /** A report entry on the average number of rules for the test dataset.
        *  It is used in three way decision NFS and fuzzy three way decision NFS.
        *  @return string with the report
        *  @date 2024-03-24 */
       virtual std::string report_average_number_of_rules_for_test () const override;
       
   protected:
     /** This method elaborates the F1score for all depth 
      *  of the cascade for train and test dataset.
      *  @date 2024-05-02 */  
       virtual void run_extra_activities_for_the_model() override;
   
   protected:
       /** The functions prints the f1scores for all depth
        *  of the cascade for train and test datasets
        *  in a string and returns it. 
        *  @date 2024-05-02 */  
       virtual std::string print_f1scores_cascade() const;
       
   public:
       friend
       std::ostream & operator<< (std::ostream & ss, const ksi::three_way_decision_nfs & system);
   };
}

#endif
