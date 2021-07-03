/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "../neuro-fuzzy/ma.h" 
#include "../neuro-fuzzy/abstract-ma.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/consequence-MA.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
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
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../service/debug.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
 
ksi::partition ksi::ma::doPartition(const ksi::dataset& X)
{
    try 
    {
        if (_pPartitioner)
            return _pPartitioner->doPartition(X);
        else 
            throw ksi::exception ("no clustering method provided");
    }
    CATCH;
} 
 
void ksi::ma::set_name ()
{
   _name_of_neuro_fuzzy_system = std::string("MA");
   _description_of_neuro_fuzzy_system = std::string("Mamdami-Assilan neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm");
}
 

ksi::neuro_fuzzy_system * ksi::ma::clone() const
{
   try 
   {
      return new ksi::ma (*this);
   }
   CATCH;
}


ksi::ma::ma()
{
//    debug(__LINE__); 
    
   set_name(); 
}

ksi::ma::~ma()
{
    
}


ksi::ma::ma(const ksi::ma & right) : neuro_fuzzy_system(right), abstract_ma(right)
{
 
}

ksi::ma::ma(ksi::ma && right) : neuro_fuzzy_system(right), abstract_ma(right)
{
  
}

ksi::ma & ksi::ma::operator=(const ksi::ma & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right); 
   ksi::abstract_ma::operator=(right);
      
   return *this;
}

ksi::ma & ksi::ma::operator= (ksi::ma && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right); 
   ksi::abstract_ma::operator=(right);

   return *this;

}
 
ksi::discriminative_model * ksi::ma::clone_discriminant() const
{
    return new ksi::ma (*this);
}
 
ksi::generative_model * ksi::ma::clone_generator() const
{
    return new ksi::ma (*this);
}




ksi::ma::ma(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm
             ) : neuro_fuzzy_system ( ksi::fcm (nRules, nClusteringIterations)),
                 abstract_ma(nRules, nClusteringIterations,
                                      nTuningIterations, dbLearningCoefficient,
                                      bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations))
{
    
//     debug(this->_pPartitioner->getAbbreviation());
    set_name();
}


ksi::ma::ma(int nRules, 
            int nClusteringIterations, 
            int nTuningIterations, 
            double dbLearningCoefficient, 
            bool bNormalisation, 
            const ksi::t_norm & tnorm, 
            double positive_class, 
            double negative_class, 
            ksi::roc_threshold threshold_type)
  : neuro_fuzzy_system ( ksi::fcm (nRules, nClusteringIterations)),
    abstract_ma (nRules, nClusteringIterations,
                             nTuningIterations, dbLearningCoefficient,
                             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
                             positive_class, negative_class, threshold_type)
{
    _positive_class = positive_class;
    _negative_class = negative_class;
    _threshold_type = threshold_type;
    
    set_name();
}
