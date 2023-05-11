
#ifndef GRANULAR_NFS_H
#define GRANULAR_NFS_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../common/dataset.h"
#include "../common/result.h"
#include "../granules/granule.h"
// #include "../granules/granule_set.h"
#include "../granules/set_of_granules.h"


namespace ksi
{
    /** The class represents a granular neuro-fuzzy system. 
     @date 2019-04-28
     */
    class granular_nfs : virtual public neuro_fuzzy_system
    {
    public:
//         granular_nfs ();
        granular_nfs (const granular_nfs & wzor);
        granular_nfs (granular_nfs && wzor);
        granular_nfs & operator= (const granular_nfs & wzor);
        granular_nfs & operator= (granular_nfs && wzor);
        virtual ~granular_nfs ();
        
        granular_nfs (const int number_of_data_to_read,
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate);
        
    protected:
        /** number of data items to read in one part of data */
        int NUMBER_OF_DATA_TO_READ = 100;
        /** minimal number of granules in a set of granules */
        int MINIMAL_NUMBER_OF_GRANULES_IN_SET;
        /** maximal number of granules in a set of granules */
        int MAXIMAL_NUMBER_OF_GRANULES_IN_SET;
        /** number of data to generate from granules */
        unsigned int NUMBER_OF_DATA_TO_GENERATE = 5000;
        
     protected:    
        virtual void createFuzzyRulebase (
            int nClusteringIterations, 
            int nTuningIterations,
            double dbLearningCoefficient,
            const ksi::set_of_granules & train) = 0; 
 
            
         /** The method reads data by parts and creates a fuzzy rule base hierarchically with rules treated as granules. 
          * @param trainDataFile name of file with train data
          * @param nNumberOfRules                number of rules 
          * @param nNumberOfClusteringIterations number of clustering iterations
          * @param nNumberofTuningIterations     number of tuning iterations
          * @param dbLearingCoefficient  learning coefficient for gradient method 
          * @param bNormalisation true, if normalisation of data, false -- otherwise
          * @date  2019-05-06
          * @author Krzysztof Siminski
          */
        virtual void createFuzzyRulebaseHierarchical (
            const std::string & trainDataFile, 
            const int nNumberOfRules, 
            const int nNumberOfClusteringIterations, 
            const int nNumberofTuningIterations, 
            const double dbLearningCoefficient, 
            const bool bNormalisation
        );    
        
        /** The method generates a dataset from a set of granules.
         @param granules a set of granules
         @param NUMBER_OF_DATA number of data to generate 
         @return a dataset with generated data
         @date 2019-04-29
         
         @todo To jest najsłabsze miejsce tego pomysłu. Locus minoris resistentiae.
         */
        ksi::dataset generate_dataset_from_granules (const ksi::set_of_granules & granules, const int NUMBER_OF_DATA);
        
 

        /** The method reads data by parts and creates a fuzzy rule base hierarchically with rules treated as granules. The method works for classificatio. 
          * @param trainDataFile name of file with train data
          * @param nNumberOfRules                number of rules 
          * @param nNumberOfClusteringIterations number of clustering iterations
          * @param nNumberofTuningIterations     number of tuning iterations
          * @param dbLearingCoefficient  learning coefficient for gradient method 
          * @param bNormalisation true, if normalisation of data, false -- otherwise
          * @param dbPositiveClass value of positive class
          * @param dbNegativeClass value of negative class
          * @param threshold_type method for elaboration of threshold value for separation of positive and negative classes
          * @date  2019-11-18
          * @author Krzysztof Siminski
          */
//         virtual void createFuzzyRulebaseHierarchicalForClassification (
//             const std::string & trainDataFile, 
//             const int nNumberOfRules, 
//             const int nNumberOfClusteringIterations, 
//             const int nNumberofTuningIterations, 
//             const double dbLearningCoefficient, 
//             const bool bNormalisation,
//             const double dbPositiveClass, 
//             const double dbNegativeClass, 
//             ksi::roc_threshold threshold_type
//         );  

        
        /** The method reads data by parts and creates a fuzzy rule base with rules treated as granules.
          * @param trainDataFile name of file with train data
          * @param nNumberOfRules                number of rules 
          * @param nNumberOfClusteringIterations number of clustering iterations
          * @param nNumberofTuningIterations     number of tuning iterations
          * @param dbLearingCoefficient  learning coefficient for gradient method 
          * @param bNormalisation true, if normalisation of data, false -- otherwise
          * @date  2019-05-15
          * @author Krzysztof Siminski
          */
        virtual void createFuzzyRulebaseByParts (
            const std::string & trainDataFile, 
            const int nNumberOfRules, 
            const int nNumberOfClusteringIterations, 
            const int nNumberofTuningIterations, 
            const double dbLearningCoefficient, 
            const bool bNormalisation
        );  


        
        virtual void createFuzzyNonGranularRulebase(
            const int nClusteringIterations, 
            const int nTuningIterations, 
            const double dbLearningCoefficient, 
            const dataset & train) = 0;    
            
        /** The method reduces the set of granules. It leaves numberOfGranules rules in the set, the others are removed. */    
//         const ksi::granule_set reduce_granules_set (
//             const ksi::granule_set & set_to_reduce,    
//             const int numberOfGranules);
        
        /** The method elaborates quality of rules in the set of granules.
         * Each rule has to have two field set: _error and _cardinality.
         * The method elabotes quality of the rule ad
         * \f$ q_i = \frac{c_i}{\sum_{n=1}^{N} c_n} \left( 1.0 - \frac{e_i}{\sum_{n=1}^{N} e_n} \right)\f$, where \f$q_i\f$ stands for quality of rule, \f$c_i\f$ -- _cardinality of the rule, \f$e_i\f$ -- error of the rule.
         * @param set The method set quality of each rule in the set.
         */
        void elaborate_quality_of_rules (ksi::set_of_granules & set);
        
    public:
        virtual ksi::result experiment_regression(
            const std::string & trainDataFile, 
            const std::string & testDataFile, 
            const std::string & outputFile, 
            const int nNumberOfRules, 
            const int nNumberOfClusteringIterations, 
            const int nNumberofTuningIterations, 
            const double dbLearningCoefficient, 
            const bool bNormalisation
        ) = 0;

        virtual ksi::result experiment_classification(
            const std::string & trainDataFile, 
            const std::string & testDataFile, 
            const std::string & outputFile, 
            const int nNumberOfRules, 
            const int nNumberOfClusteringIterations, 
            const int nNumberofTuningIterations, 
            const double dbLearningCoefficient, 
            const bool bNormalisation,
            const double dbPositiveClass, 
            const double dbNegativeClass, 
            ksi::roc_threshold threshold_type) = 0;                        

           /** 
       @return rulebase's answer of a data item
       @param item data item to elaborate answer for
       */
      virtual double answer (const datum & item) const = 0;
    };
}

#endif
