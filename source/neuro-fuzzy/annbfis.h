/** @file */

#ifndef ANNBFIS_H
#define ANNBFIS_H


#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "../common/number.h"
#include "rulebase.h"
#include "neuro-fuzzy-system.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"

namespace ksi 
{
   /** Annbfis neuro-fuzzy system  */
   /** annbfis 
    */
   class annbfis : virtual public neuro_fuzzy_system
   {
   protected: 
      /** fuzzy implication */
      implication * _pImplication;

 
      
   public:
      
      annbfis();      
      annbfis(const annbfis & a);
      annbfis(annbfis && a);
      
      /** A constructor with implication.
       @param imp implication
       @date 2018-03-29
       */
      annbfis (const ksi::implication & imp);
      
      annbfis & operator = (const annbfis & a);
      annbfis & operator = (annbfis && a);
      ~annbfis();
      
      
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      
     
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset 
       * @param impl fuzzy implication
       * @date  2018-02-03
       * @author Krzysztof Siminski
       * 
       */
      virtual void createFuzzyRulebase (int nRules, 
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train); 
      
      /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      double answer (const datum & item) const ;
      
      /** The method executes an experiment for regression with ANNBFIS 
        * neuro-fuzzy system with logical interpretation of fuzzy rules.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfRules                number of rules 
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberofTuningIterations     number of tuning iterations
        * @param dbLearingCoefficient  learning coefficient for gradient method 
        * @param bNormalisation true, if normalisation of data, false -- otherwise
        * @date  2018-02-04
        * @author Krzysztof Siminski
        */
      virtual void experiment_regression (const std::string & trainDataFile, 
                                  const std::string & testDataFile, 
                                  const std::string & outputFile, 
                                  const int nNumberOfRules, 
                                  const int nNumberOfClusteringIterations, 
                                  const int nNumberofTuningIterations, 
                                  const double dbLearningCoefficient, 
                                  const bool bNormalisation
                                 );
                                  
      /** The method executes an experiment for classification with ANNBFIS 
        * neuro-fuzzy system with logical interpretation of fuzzy rules.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfRules                number of rules 
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberofTuningIterations     number of tuning iterations
        * @param dbLearingCoefficient  learning coefficient for gradient method
        * @param Implication  implication for rules
        * @param bNormalisation true, if normalisation of data, false -- otherwise
        * @param dbPositiveClass label of a positive class
        * @param dbNegativeClass label of a negative class
        * @param threshold_type classification threshold type 
        * @date  2018-02-04
        * @author Krzysztof Siminski
        */
      virtual void experiment_classification (const std::string & trainDataFile,
                                  const std::string & testDataFile,
                                  const std::string & outputFile,
                                  const int nNumberOfRules,
                                  const int nNumberOfClusteringIterations,
                                  const int nNumberofTuningIterations,
                                  const double dbLearningCoefficient, 
                                  const bool bNormalisation,
                                  const double dbPositiveClass,
                                  const double dbNegativeClass,
                                  ksi::roc_threshold threshold_type
                                 );

      /** A method elaborates an answer of a datum (data item). 
       * @param d datum to elaborate answer for 
       * @return The method returns a number.
       */   
      virtual number elaborate_answer (const datum & d) const; 
      
      
   };
}




#endif 