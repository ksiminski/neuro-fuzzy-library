/** @file */

#ifndef RANDOM_NEURO_FUZZY_SYSTEM_H
#define RANDOM_NEURO_FUZZY_SYSTEM_H

#include <vector>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <iostream>

#include "../common/dataset.h" 
#include "../common/number.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"

namespace ksi
{
   /** The class implements a random neuro-fuzzy system.
       It is an approach similar to random forest of decision trees.
       
       @date 2018-03-26
     */
   class random_neuro_fuzzy_system
   {
   protected:
      /** a pointer to a neuro-fuzzy system */
      ksi::neuro_fuzzy_system * _nfs;
      /** indices of data used to train a neuro-fuzzy system */
      std::unordered_multiset<std::size_t> _data_indices;
      /** indices of attributes valid in this neuro-fuzzy system */
      std::vector<bool> _attribute_indices;    
      
      /** The method copies automatic fields of an object from source.
       @param source An object to copy fields from.
       */
      void copy_fields(const random_neuro_fuzzy_system & source);
      
      /** Threshold for classification. Less values are negative class,
       greater values -- positive class. */
      double classification_threshold;
 
   public:
      random_neuro_fuzzy_system ();
      
      /** Constructor: creates a random neuro-fuzzy system.
       @param nfs a copy of this neuro-fuzzy system will be used to initialise 
                  the random neuro-fuzzy system
       @param data_indices indices of bagged data items
       @param attribute_pattern attributes used by this nfs
       @date 2018-03-27
       */
      random_neuro_fuzzy_system (const neuro_fuzzy_system & nfs,
         const std::unordered_multiset<std::size_t> & data_indices,
         const std::vector<bool> & attribute_pattern
      );
      
      virtual ~random_neuro_fuzzy_system();
      
      random_neuro_fuzzy_system (const random_neuro_fuzzy_system & );
      random_neuro_fuzzy_system (random_neuro_fuzzy_system && );
      
      random_neuro_fuzzy_system & operator = (const random_neuro_fuzzy_system &);
      random_neuro_fuzzy_system & operator = (random_neuro_fuzzy_system &&);
      
      /** The method trains a neuro-fuzzy system.
       @param abridged_data train data
       @param nClusteringIterations number of clustering iterations 
       @param nTuningIterations number of tuning iterations 
       @param nRules number of rules in the neuro-fuzzy system
       @param dbLearningCoefficient learning coefficient
       @date 2018-03-31
       */
      void train(dataset abridged_data, int nClusteringIterations, int nTuningIterations, int nRules, double dbLearningCoefficient);
      
      /** @return _attribute_indices */
      std::vector<bool> get_attribute_indices () const ;
      
      /** @return Returns a number representing an answer
        * @param d a datum to elaborate answer for
        */
      ksi::number answer (const ksi::datum & d) const ;
      
      /** @return a short name of the neuro-fuzzy system */
      std::string get_nfs_name () const;
      /** @return a description of the neuro-fuzzy system */
      std::string get_nfs_description () const;
      
      /** Sets classification threshold.
       @param threshold a threshold to set 
       @date 2018-04-05 
       */
      void set_classification_threshold(double threshold);
      
      /** @return classification threshold
       @date 2018-04-05 
       */
      double get_threshold() const;
      
   };
}

#endif 