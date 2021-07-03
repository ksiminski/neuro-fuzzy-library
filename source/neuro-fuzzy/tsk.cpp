/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "tsk.h"
#include "rule.h"
#include "premise.h"
#include "consequence-TSK.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
#include "../partitions/partition.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian.h"
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
#include "../common/data-modifier.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

 

 
ksi::partition ksi::tsk::doPartition(const ksi::dataset& X)
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

void ksi::tsk::set_name()
{
    _name_of_neuro_fuzzy_system = std::string("TSK");
   _description_of_neuro_fuzzy_system = std::string("Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm and fuzzy c-means (FCM) clustering algorithm");
}
 
  
ksi::tsk::tsk()  
{
    set_name();
}

ksi::tsk::tsk(int nRules, int nClusteringIterations)
:
abstract_tsk(nRules, nClusteringIterations)
{
//     debug(_pPartitioner);
    
    set_name();
}


ksi::tsk::tsk(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm
             ) : 
                neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations))
                ,
                abstract_tsk(nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, 
                             ksi::fcm (nRules, nClusteringIterations)) 
{
    set_name(); 
}


ksi::tsk::tsk(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm, 
              const ksi::data_modifier& modifier
             ) : 
                neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations), modifier)
                ,
                abstract_tsk(nRules, nClusteringIterations,
                                      nTuningIterations, dbLearningCoefficient,
                                      bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations)) 
{
    set_name(); 
//     debug(_pPartitioner);
//     debug(__FUNCTION__);
}

 



ksi::tsk::tsk(const std::string& trainDataFile, 
              const std::string& testDataFile, 
              const std::string& resultsFile, 
              const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const ksi::t_norm& tnorm, 
              const bool bNormalisation)
:
   neuro_fuzzy_system (trainDataFile, testDataFile, resultsFile, 
                 ksi::fcm(nRules, 
                          nClusteringIterations)),
   abstract_tsk (nRules, nClusteringIterations, nTuningIterations,
                 dbLearningCoefficient, bNormalisation, tnorm)
{
   set_name(); 
}

ksi::tsk::tsk(const std::string& trainDataFile, 
              const std::string& testDataFile, 
              const std::string& resultsFile, 
              const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const ksi::t_norm& tnorm, 
              const bool bNormalisation,
              const ksi::data_modifier & modifier
             )
:
   neuro_fuzzy_system (trainDataFile, testDataFile, resultsFile, 
                 ksi::fcm(nRules, nClusteringIterations),
                 modifier),
   abstract_tsk (nRules, nClusteringIterations, nTuningIterations,
                 dbLearningCoefficient, bNormalisation, tnorm)
{
   set_name(); 
}




ksi::tsk::tsk(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient, 
              bool bNormalisation, 
              const ksi::t_norm & tnorm, 
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type)
             :  neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations))
                ,
                abstract_tsk (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_type)
{
    set_name(); 
//      debug(_pPartitioner);
}


ksi::tsk::tsk(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient, 
              bool bNormalisation, 
              const ksi::t_norm& tnorm, 
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type, 
              const ksi::data_modifier& modifier)
            :  neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations), modifier)
                ,
                abstract_tsk (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_type)
{
    set_name(); 
//      debug(_pPartitioner);
}



ksi::tsk::~tsk()
{
 
}


ksi::tsk::tsk(const ksi::tsk & right) : neuro_fuzzy_system(right), abstract_tsk(right)
{
 
}

ksi::tsk::tsk(ksi::tsk&& right) :  neuro_fuzzy_system(right), abstract_tsk(right)
{
   
}

ksi::tsk & ksi::tsk::operator=(const ksi::tsk & right)
{
   if (this == & right)
      return *this;
   
   ksi::abstract_tsk::operator=(right);
      
   return *this;
}

ksi::tsk & ksi::tsk::operator= (ksi::tsk && right)
{
   if (this == & right)
      return *this;

   ksi::abstract_tsk::operator=(right);  

   return *this;

}


ksi::neuro_fuzzy_system* ksi::tsk::clone() const
{
   return new ksi::tsk (*this);
}



ksi::discriminative_model * ksi::tsk::clone_discriminant() const
{
    return new ksi::tsk (*this);
}


ksi::generative_model * ksi::tsk::clone_generator() const
{
    return new ksi::tsk (*this);
}


 
