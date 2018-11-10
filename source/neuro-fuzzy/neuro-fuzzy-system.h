/** @file */

#ifndef NEURO_FUZZY_SYSTEM_H
#define NEURO_FUZZY_SYSTEM_H

#include <vector>
#include <iostream>

#include "../common/dataset.h"
#include "rulebase.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"

namespace ksi
{
   class neuro_fuzzy_system  
   {
   protected:
      /** number of rules **/
      int _nRules;
      
      /** number of clustering iterations */
      int _nClusteringIterations;
      
      /** number of tuning iterations */
      int _nTuningIterations;
      
      /** train dataset */
      dataset _TrainDataset;
      
      /** test dataset */
      dataset _TestDataset;
      
      /** rule base of the neuro-fuzzy system. **/
      rulebase * _pRulebase = nullptr;
      
      /** t-norm */
      t_norm * _pTnorm = nullptr;
      
      /** short name of a neuro-fuzzy system */
      std::string _name_of_neuro_fuzzy_system;
      /** short description of a neuro-fuzzy system showing its main features */
      std::string _description_of_neuro_fuzzy_system;
   public:
        
      virtual ~neuro_fuzzy_system();
      
      neuro_fuzzy_system ();
      
      /** constructor
       @param nRules number of rules in a fuzzy rule base
       @param nClusteringIterations number of iterations in clustering
       @param nTuningIterations number of tuning iterations
       @param TrainDataset train dataset 
       
       @date 2018-03-28
       */
      neuro_fuzzy_system (int nRules, 
                          int nClusteringIterations,
                          int nTuningIterations,
                          const dataset & TrainDataset,
                          const t_norm * tnorma
                         );
      
      
      neuro_fuzzy_system (const neuro_fuzzy_system & wzor);
      neuro_fuzzy_system (neuro_fuzzy_system && wzor);
      
      neuro_fuzzy_system & operator = (const neuro_fuzzy_system & wzor);
      neuro_fuzzy_system & operator = (neuro_fuzzy_system && wzor);
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const = 0;
      
      /** The method prints rule base.
       * @param ss ostream to print to */
      void printRulebase(std::ostream & ss);
      
      
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset  
       * @date  2018-03-29
       * @author Krzysztof Siminski 
       */
      virtual void createFuzzyRulebase (int nRules, 
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train) = 0; 
      
      /** The method executes an experiment for regressions.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfRules                number of rules 
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberofTuningIterations     number of tuning iterations
        * @param dbLearingCoefficient  learning coefficient for gradient method 
        * @param bNormalisation true, if normalisation of data, false -- otherwise
        * @date  2018-02-14
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
                                 ) = 0;

      /** The method executes an experiment for classification.
        * @param trainDataFile name of file with train data
        * @param testDataFile  name of file with test data
        * @param outputfile    name of file to print results to
        * @param nNumberOfRules                number of rules 
        * @param nNumberOfClusteringIterations number of clustering iterations
        * @param nNumberofTuningIterations     number of tuning iterations
        * @param dbLearingCoefficient  learning coefficient for gradient method 
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
                                 ) = 0;
                                 
      /** A method elaborates an answer of a datum (data item).
       * @param d datum to elaborate answer for 
       * @return an incomplete (non-existing) number
       */   
      virtual number elaborate_answer (const datum & d) const = 0;   
      
      /** @return a short name of the neuro-fuzzy system */
      std::string get_nfs_name () const;
      /** @return a description of the neuro-fuzzy system */
      std::string get_nfs_description () const;
      
      
      
   private:
      /** The method copies non pointer fields. */
      void copy_fields (const neuro_fuzzy_system & wzor);
      
   };
}




#endif 