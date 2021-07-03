/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "subspace-annbfis.h"
#include "logicalrule.h"
#include "subspace-premise.h"
#include "consequence-CL.h"
#include "../neuro-fuzzy/fubi-annbfis.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fubi.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian-subspace.h" 
#include "../service/debug.h" 
#include "../partitions/partition.h" 


void ksi::fubi_annbfis::set_name()
{
    init_name();
}

ksi::partition ksi::fubi_annbfis::doPartition(const ksi::dataset& X)
{
    //    ksi::sfcm clusterer;
//    clusterer.setNumberOfClusters(_nRules);
//    clusterer.setNumberOfIterations(_nClusteringIterations);
    try 
    {
        if (_pPartitioner)
            return _pPartitioner->doPartition(X);
        else 
            throw ksi::exception ("no clustering method provided");
    }
    CATCH;
}

void ksi::fubi_annbfis::init_name()
{
    _name_of_neuro_fuzzy_system = std::string ("FubiANNBFIS");
   _description_of_neuro_fuzzy_system = std::string("FubiANNBFIS, subspace neuro-fuzzy system with logical interpreration of fuzzy rules and fuzzy biclustering for rule identification");
}


ksi::fubi_annbfis::fubi_annbfis()
{
   init_name();
}

ksi::fubi_annbfis::fubi_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp
             ) :             
             neuro_fuzzy_system(), 
             abstract_annbfis(nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::fubi (nRules, nClusteringIterations)), 
             annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::fubi (nRules, nClusteringIterations)), 
             subspace_annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp)
{
    init_name(); 
}
 
 
ksi::fubi_annbfis::fubi_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type
             ) : 
             neuro_fuzzy_system(), 
             abstract_annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::fubi (nRules, nClusteringIterations), positive_class, negative_class, threshold_type),
             annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, positive_class, negative_class, threshold_type),
             subspace_annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, positive_class, negative_class, threshold_type)
{
   init_name();  
}

ksi::fubi_annbfis::fubi_annbfis (const ksi::implication & imp) : neuro_fuzzy_system(), ksi::abstract_annbfis(), ksi::annbfis(), ksi::subspace_annbfis()
{
   init_name();
   _pImplication = imp.clone();
}


ksi::fubi_annbfis::~fubi_annbfis()
{
}

ksi::fubi_annbfis & ksi::fubi_annbfis::operator=(const ksi::fubi_annbfis & a)
{
   if (this == & a)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(a);
   
   ksi::abstract_annbfis::operator=(a);
   ksi::annbfis::operator=(a);
   ksi::subspace_annbfis::operator=(a);
   
   return *this;
}

ksi::fubi_annbfis & ksi::fubi_annbfis::operator=(ksi::fubi_annbfis && a)
{
   if (this == & a)
      return *this;

   ksi::neuro_fuzzy_system::operator=(a);
   ksi::abstract_annbfis::operator=(a);
   ksi::annbfis::operator=(a);
   ksi::subspace_annbfis::operator=(a);

   return *this;
}

ksi::fubi_annbfis::fubi_annbfis(const ksi::fubi_annbfis & a): neuro_fuzzy_system(a), abstract_annbfis(a), annbfis(a), subspace_annbfis(a)
{
    init_name(); 
}

ksi::fubi_annbfis::fubi_annbfis(ksi::fubi_annbfis && a): neuro_fuzzy_system(a), abstract_annbfis(a), annbfis(a), subspace_annbfis(a)
{
    init_name(); 
}

 
 
 
ksi::neuro_fuzzy_system* ksi::fubi_annbfis::clone() const
{
   return new ksi::fubi_annbfis (*this);
}
