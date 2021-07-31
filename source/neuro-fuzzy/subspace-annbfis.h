/** @file */

#ifndef SUBSPACE_ANNBFIS_H
#define SUBSPACE_ANNBFIS_H


#include <vector>
#include <iostream>

#include "../common/dataset.h" 
#include "rulebase.h"
#include "annbfis.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm.h"
#include "../auxiliary/roc.h"
 

namespace ksi
{
   /** Subspace neuro-fuzzy system with logical interpreations of fuzzy rules */
   /** subspace annbfis
    * CITATION REQUEST
    *  The algorithm has been described in detail in papers:

    Krzysztof Siminski, Neuro-fuzzy system with weighted attributes, [in] Soft Computing, 2014, volume 18, number 2, pp. 285-297. doi: 10.1007/s00500-013-1057-z

    If you use this neuro-fuzzy system, please cite the paper:
    <pre>
    ARTICLE{id:Siminski2014Neuro,
      author = {Krzysztof Siminski},
      title = {Neuro-fuzzy system with weighted attributes},
      journal = {Soft Computing},
      volume = {18}, 
      number = {2}, 
      pages = {285--297}, 
      year = {2014},
      doi = {10.1007/s00500-013-1057-z},
      abstract = {The paper presents the neuro-fuzzy system with weighted attributes.
                  Its crucial part is the fuzzy rule base composed of fuzzy rules
                  (implications). In each rule the attributes have their own weights.
                  In our system the weights of the attributes are numbers from the
                  interval $[0, 1]$ and they are not global: each fuzzy rule has its
                  own attributes' weights, thus it exists in its own weighted
                  subspace. The theoretical description is accompanied by  results
                  of experiments on real life data sets. They show that 
                  the neuro-fuzzy system  with weighted attributes can elaborate 
                  more precise results than the system that does not apply  weights
                  to attributes. Assigning weights to attributes can also discover 
                  knowledge about importance of attributes and their relations.},
    }
    </pre>
    * 
    * 
    */
   class subspace_annbfis : virtual public annbfis 
   {
       
   private: 
       void init_name ();
      public:
      subspace_annbfis();
      
      /** constructor
       * @param nRules number of rules
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param tnorm a t-norm
       * @param imp implication
       * @date  2019-07-16
       */
      subspace_annbfis(int nRules, int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, bool bNormalisation, const t_norm& tnorm, const implication& imp);

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
       * @date  2019-12-22
       */
      subspace_annbfis (int nRules, int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient, bool bNormalisation, const t_norm & tnorm, const implication & imp, double positive_class, double negative_class, ksi::roc_threshold threshold_type);

      
      /** A constructor with implication.
       @param imp implication
       @date 2018-03-29
       */
      subspace_annbfis(const ksi::implication & imp);
      
      subspace_annbfis(const subspace_annbfis & a);
      subspace_annbfis(subspace_annbfis && a);
      subspace_annbfis & operator = (const subspace_annbfis & a);
      subspace_annbfis & operator = (subspace_annbfis && a);
         
      virtual ~subspace_annbfis();
      
      /** @return a pointer to a copy of the NFS */
      virtual neuro_fuzzy_system * clone () const ;
      

   protected: 
      /** The method creates a fuzzy rulebase from the dataset.
       * @param nClusteringIterations number of clustering iterations
       * @param nTuningIterations number of tuning iterations
       * @param dbLearningCoefficient learning coefficient for gradient method
       * @param train train dataset 
       * @param impl fuzzy implication
       * @date  2018-02-24
       * @author Krzysztof Siminski 
       */
      virtual void createFuzzyRulebase (
         int nClusteringIterations, int nTuningIterations,
         double dbLearningCoefficient,
         const dataset & train); 
      
       void set_name ();
       virtual partition doPartition (const dataset & X);
   public:     
   
      
   };
}




#endif 
