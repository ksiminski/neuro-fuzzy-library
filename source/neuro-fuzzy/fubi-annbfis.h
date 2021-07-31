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
   
   * CITATION REQUEST
    *  The algorithm has been described in detail in papers:

    Krzysztof Siminski, FuBiNFS – fuzzy biclustering neuro-fuzzy system, [in] Fuzzy Sets and Systems, 2021. doi: 10.1016/j.fss.2021.07.009

    If you use this neuro-fuzzy system, please cite the paper:
    <pre>
    @article{id:Siminski2021FuBiNFS,
	abstract = "In data sets some attributes may have higher or lower importance. One of the tools used for data analysis of such datasets are subspace neuro-fuzzy systems. They elaborate fuzzy rules to describe data sets. In subspace neuro-fuzzy systems fuzzy rules exists in subspaces defined with subsets of attributes. In the paper we propose a novel fuzzy biclustering algorithm that groups both objects and attributes in fuzzy clusters. In that way we create a subspace fuzzy rule base for a subspace fuzzy system. The paper is accompanied with numerical examples that show this approach can lead to better generalisation (and thus lower data prediction errors) with preserved interpretation of fuzzy models.",
	author = "Krzysztof Siminski",
	doi = "10.1016/j.fss.2021.07.009",
	issn = "0165-0114",
	journal = "Fuzzy Sets and Systems",
	keywords = "Neuro-fuzzy system; Biclustering; Subspace clustering; Subspace neuro-fuzzy system; Attribute weights",
	title = "{FuBiNFS} – fuzzy biclustering neuro-fuzzy system",
	url = "https://www.sciencedirect.com/science/article/pii/S0165011421002499",
	year = "2021"
}
    </pre>
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
