/** @file */

#include <string>

#include "tsk.h"
#include "../partitions/fcm.h"
#include "../auxiliary/roc.h"
#include "../common/data-modifier.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
 

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
                 ksi::fcm(nRules, nClusteringIterations)),
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

ksi::tsk::tsk(const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const bool bNormalisation, 
              const ksi::t_norm & tnorm, 
              const double positive_class, 
              const double negative_class, 
              const ksi::roc_threshold threshold_type)
             :  neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations))
                ,
                abstract_tsk (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_type)
{
    set_name(); 
}

ksi::tsk::tsk(const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const bool bNormalisation, 
              const ksi::t_norm & tnorm, 
              const double positive_class, 
              const double negative_class, 
              const double threshold_value)
             :  neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations))
                ,
                abstract_tsk (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_value)
{
    set_name(); 
}


ksi::tsk::tsk(const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const bool bNormalisation, 
              const ksi::t_norm& tnorm, 
              const double positive_class, 
              const double negative_class, 
              const ksi::roc_threshold threshold_type,
              const ksi::data_modifier& modifier
              )
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


ksi::tsk::tsk(const int nRules, 
              const int nClusteringIterations, 
              const int nTuningIterations, 
              const double dbLearningCoefficient, 
              const bool bNormalisation, 
              const ksi::t_norm& tnorm, 
              const double positive_class, 
              const double negative_class, 
              const ksi::data_modifier& modifier,
              const double threshold_value
              )
            :  neuro_fuzzy_system (ksi::fcm(nRules, nClusteringIterations), modifier)
                ,
                abstract_tsk (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_value)
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

   ksi::neuro_fuzzy_system::operator=(right); 
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


 
