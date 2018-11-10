/** @file */

#ifndef RANDOM_NEURO_FUZZY_FOREST_H
#define RANDOM_NEURO_FUZZY_FOREST_H

#include <list>
#include <utility>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <random>

#include "../common/dataset.h" 
#include "../common/number.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/random-neuro-fuzzy-system.h"

namespace ksi
{
   /** The class implements a random forest (set) of neuro-fuzzy system.
       It is an approach similar to random forest of decision trees.
       
       @date 2018-03-26
       @todo wyznaczanie błędu out-of-bag (OOB) error -- jak i po co? Czy będzie naprawdę potrzebny?
        **/
   class random_neuro_fuzzy_forest
   {
   protected:
      /** forest -- a set of neuro-fuzzy systems */
      std::list<ksi::random_neuro_fuzzy_system> forest;
      
      /** number of neuro-fuzzy systems in a forest */
      int _number_of_trees;

      /** random engine */
      std::default_random_engine _engine;
             
      /** distribution for bagging of attributes */
      std::uniform_int_distribution<std::size_t> _distribution;
      
      
      
      /** The method copies automatic fields of an object from source.
       @param source An object to copy fields from.
       */
      void copy_fields(const random_neuro_fuzzy_forest & source);
      
      
      /** The method bags an original dataset: draws at random (with 
          repetitions) N data item. 
        @param ds original data set to draw from
        @param number_of_data_items number N of data items to draw 
        @param engine random engine
        @return a pair: bagged data set and a container with indices of 
                data item from original data set
          */
      std::pair<ksi::dataset, std::unordered_multiset<size_t>> data_bagging (const ksi::dataset & ds, const int number_of_data_items, std::default_random_engine & engine);
      
      /** The method removes at random some number of attribes.
       * Decision attribute (the last attribute) is always kept and never removed.
       @param ds a dataset to remove data items from
       @param number_of_attributes number of attributes to keep
       @param engine random engine
       @return a pair: a dataset with removed attributes, a container of bool values representing existing attributes 
       */
      std::pair<ksi::dataset, std::vector<bool>> random_removal_of_attributes (const ksi::dataset & ds, int number_of_attributes, std::default_random_engine & engine);
      
      /** The method removes attributes from a datum according to the attribute pattern.
       @param dana a datum to remove attributes from
       @param attribute_pattern a vector representing attributes to keep in resulting data, true -- attribute exists, false -- attribute removed
       @return a data item with removed attributes
       */
      ksi::datum remove_attibutes (const ksi::datum & dana, const std::vector<bool> & attribute_pattern);
      
     
      
      
   public:
      random_neuro_fuzzy_forest ();
      virtual ~random_neuro_fuzzy_forest();
      
      random_neuro_fuzzy_forest (const random_neuro_fuzzy_forest & );
      random_neuro_fuzzy_forest (random_neuro_fuzzy_forest && );
      
      random_neuro_fuzzy_forest & operator = (const random_neuro_fuzzy_forest &);
      random_neuro_fuzzy_forest & operator = (random_neuro_fuzzy_forest &&);
 
      
      /** The method sets a number of trees.
       @param count number of trees to set 
       @date 2018-03-27
       */
      void set_number_of_trees (int count);
      
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param number_of_trees number of neuro-fuzzy systems in a forest
       * @param train train dataset 
       * @param bClassification true if classification, false if regression
       * @param threshold_type threshold type for classification, not used in regression
       * @param positiveClassvalue positive class label (for classification, not used in regression)
       * @param negativeClassvalue negative class label (for classification, not used in regression)
       * @param nfs a reference to a neuro-fuzzy system -- this system is copied to create a forest, but the copies are not identical
       * @date  2018-03-27
       * @author Krzysztof Siminski  
       */
      void createRandomFuzzyForest (int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient,
         const int number_of_trees, const dataset & train,
         bool bClassification,
         ksi::roc_threshold threshold_type,
         double positiveClassvalue,
         double negativeClassvalue,
         const neuro_fuzzy_system & nfs ); 

      
      /** The method elaborates an answer in a regression task.
       @param d datum to elaborate answer for
       @return a number
       @date  2018-03-31
       @author Krzysztof Siminski  
       */
      ksi::number answer_regression (const ksi::datum & d);
      
      /** The method elaborates an answer in a classification task.
       @param d datum to elaborate answer for
       @param positiveClassvalue positive class label
       @param negativeClassvalue negative class label
       @return positive of negative class label
       @date  2018-04-05
       @author Krzysztof Siminski  
       */
      double answer_classification (const ksi::datum & d, 
                                    double positiveClassvalue, 
                                    double negativeClassvalue
      );
      
      
      
      /** The method executes an experiment for regression with 
        * forest of random neuro-fuzzy systems.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberOfTuningIterations     number of tuning iterations
        * @param nNumberOfNeuroFuzzySystemsInForest number of NFS in forest
        * @param dbLearingCoefficient  learning coefficient for gradient method 
        * @param bNormalisation true, if normalisation of data, false -- otherwise
        * @param nfs neuro-fuzzy system
        * @date  2018-04-03
        * @author Krzysztof Siminski
        */
      void experiment_regression (const std::string & trainDataFile, 
                                  const std::string & testDataFile, 
                                  const std::string & outputFile, 
                                  const int nNumberOfClusteringIterations, 
                                  const int nNumberOfTuningIterations,
                                  const int nNumberOfNeuroFuzzySystemsInForest,
                                  const double dbLearningCoefficient, 
                                  const bool bNormalisation,
                                  const ksi::neuro_fuzzy_system & nfs 
                                 );

      /** The method executes an experiment for classification with 
        * forest of random neuro-fuzzy systems.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberOfTuningIterations     number of tuning iterations
        * @param nNumberOfNeuroFuzzySystemsInForest number of NFS in forest
        * @param dbLearingCoefficient  learning coefficient for gradient method 
        * @param bNormalisation true, if normalisation of data, false -- otherwise
        * @param dbPossitiveClassLabel label of positive class
        * @param dbNegativeClassLabel label of negative class
        * @param threshold_type threshold type
        * @param nfs neuro-fuzzy system
        * @date  2018-04-04
        * @author Krzysztof Siminski
        */
      void experiment_classification (
         const std::string & trainDataFile, 
         const std::string & testDataFile, 
         const std::string & outputFile, 
         const int nNumberOfClusteringIterations, 
         const int nNumberOfTuningIterations, 
         const int nNumberOfNeuroFuzzySystemsInForest, 
         const double dbLearningCoefficient, 
         const bool bNormalisation, 
         const double dbPositiveClassLabel, 
         const double dbNegativeClassLabel, 
         const ksi::roc_threshold threshold_type, 
         const ksi::neuro_fuzzy_system& nfs 
         );
   };
}
 

#endif 