/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cmath>

#include "annbfis.h"
#include "logicalrule.h"
#include "premise.h"
#include "consequence-CL.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
#include "../neuro-fuzzy/premise.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/clock.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"
#include "../common/error-RMSE.h"
#include "../common/error-MAE.h"
#include "../common/number.h"
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"


void ksi::annbfis::set_name()
{
    _name_of_neuro_fuzzy_system = std::string ("ANNBFIS");
    _description_of_neuro_fuzzy_system = std::string("ANNBFIS, neuro-fuzzy system with logical interpretation of fuzzy rules");
}


ksi::partition ksi::annbfis::doPartition(const ksi::dataset& X)
{
    //ksi::fcm clusterer;
    
    //clusterer.setNumberOfClusters(_nRules);
    //clusterer.setNumberOfIterations(_nClusteringIterations);
    //return clusterer.doPartition(X);
    try 
    {
        if (_pPartitioner)
            return _pPartitioner->doPartition(X);
        else 
            throw ksi::exception ("no clustering method provided");
    }
    CATCH;
}

ksi::annbfis::annbfis(const ksi::implication & imp) : ksi::neuro_fuzzy_system(), 
ksi::abstract_annbfis(imp, ksi::fcm()) 
{
    set_name();
}

ksi::neuro_fuzzy_system* ksi::annbfis::clone() const
{
    return new ksi::annbfis (*this);
}


ksi::annbfis::annbfis() : neuro_fuzzy_system(), abstract_annbfis()
{
   _pImplication = nullptr;
   _pTnorm = nullptr;
   
   set_name();
   
}

ksi::annbfis::~annbfis()
{
   
}


ksi::annbfis::annbfis(const ksi::annbfis & right) : neuro_fuzzy_system(right), abstract_annbfis(right)
{
    set_name();
}

ksi::annbfis::annbfis(ksi::annbfis&& right) : neuro_fuzzy_system(right), abstract_annbfis(right)
{
    set_name();
}

ksi::annbfis& ksi::annbfis::operator=(const ksi::annbfis & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_annbfis::operator=(right);
   
   delete _pImplication;
   if (right._pImplication)
      _pImplication = right._pImplication->clone();
   else
      _pImplication = nullptr;
         
   return *this;
}

ksi::annbfis& ksi::annbfis::operator= (ksi::annbfis && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_annbfis::operator=(right);
   
   std::swap (_pImplication, right._pImplication);

   return *this;
}
 
ksi::discriminative_model * ksi::annbfis::clone_discriminant() const
{
    return new ksi::annbfis (*this);
}

ksi::generative_model * ksi::annbfis::clone_generator() const
{
    return new ksi::annbfis (*this);
}

 
 

ksi::annbfis::annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp
             ) : neuro_fuzzy_system(),  abstract_annbfis (nRules, nClusteringIterations,
                 nTuningIterations, dbLearningCoefficient, bNormalisation,
                 tnorm, imp, ksi::fcm(nRules, nClusteringIterations) )
{
    set_name();
}


ksi::annbfis::annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp, 
              const ksi::data_modifier& modifier
             ) : neuro_fuzzy_system(modifier),  
                 abstract_annbfis (nRules, 
                                   nClusteringIterations,
                                   nTuningIterations, 
                                   dbLearningCoefficient, 
                                   bNormalisation,
                                   tnorm, 
                                   imp, 
                                   ksi::fcm(nRules, nClusteringIterations) )
{
    set_name();
}

ksi::annbfis::annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              const partitioner & par
             ) : neuro_fuzzy_system(),  abstract_annbfis (nRules, nClusteringIterations,
                 nTuningIterations, dbLearningCoefficient, bNormalisation,
                 tnorm, imp, par )
{
    set_name();
}

ksi::annbfis::annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              double positive_class, 
              double negative_class, 
              const ksi::roc_threshold threshold_type
             ) : neuro_fuzzy_system(),  abstract_annbfis (nRules, nClusteringIterations,
                 nTuningIterations, dbLearningCoefficient, bNormalisation,
                 tnorm, imp, ksi::fcm(nRules, nClusteringIterations), positive_class, negative_class, threshold_type )
{
    set_name();
}

ksi::annbfis::annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              double positive_class, 
              double negative_class, 
              const ksi::roc_threshold threshold_type,
              const ksi::data_modifier & modifier
             ) : neuro_fuzzy_system(modifier),  abstract_annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::fcm(nRules, nClusteringIterations), positive_class, negative_class, threshold_type )
{
    set_name();
}

