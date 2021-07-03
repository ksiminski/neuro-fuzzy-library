/** @file */

#ifndef FUBI_ANNBFIS_H
#define FUBI_ANNBFIS_H


#include <vector>
#include <iostream>

#include "../common/dataset.h" 
#include "../neuro-fuzzy/rulebase.h"
#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../partitions/partition.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"

 

namespace ksi
{
   /** Subspace neuro-fuzzy system with logical interpreations of fuzzy rules and fuzzy biclustering premise indentification */
   /** fubi annbfis
    * 
    * 
    */
   class fubi_annbfis : virtual public subspace_annbfis 
   {
       
   private: 
       void init_name ();
      public:
      fubi_annbfis();
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @date  2020-08-14
       */
      fubi_annbfis(int nRules, int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, bool bNormalisation, const t_norm& tnorm, const implication& imp);

      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @param dbPositiveClass label of a positive class
       * @param dbNegativeClass label of a negative class
       * @param threshold_type classification threshold type 
       * @date  2020-08-14
       */
      fubi_annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, double positive_class, double negative_class, ksi::roc_threshold threshold_type);

      
      /** A constructor with implication.
       @param imp implication
       @date 2020-08-14
       */
      fubi_annbfis(const ksi::implication & imp);
      
      fubi_annbfis(const fubi_annbfis & a);
      fubi_annbfis(fubi_annbfis && a);
      fubi_annbfis & operator = (const fubi_annbfis & a);
      fubi_annbfis & operator = (fubi_annbfis && a);
         
      virtual ~fubi_annbfis();
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      

   protected: 
      
      
       void set_name ();
       virtual partition doPartition (const dataset & X);
   public:     
   
      
   };
}




#endif 
