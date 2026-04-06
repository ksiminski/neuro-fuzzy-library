/** @file */

#include <cmath>
#include <string>

#include "../auxiliary/roc.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../neuro-fuzzy/abstract-ma.h"
#include "../neuro-fuzzy/ma.h" 
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../partitions/fcm.h"
#include "../partitions/partition.h"
#include "../partitions/partition.h"
 
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
   _description_of_neuro_fuzzy_system = std::string("Mamdani-Assilan neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm");
}
 



ksi::ma::ma()
{
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

ksi::ma::ma(int nRules, 
            int nClusteringIterations, 
            int nTuningIterations, 
            double dbLearningCoefficient, 
            bool bNormalisation, 
            const ksi::t_norm & tnorm, 
            double positive_class, 
            double negative_class, 
            const double threshold_value)
: neuro_fuzzy_system ( ksi::fcm (nRules, nClusteringIterations)),
abstract_ma (nRules, nClusteringIterations,
             nTuningIterations, dbLearningCoefficient,
             bNormalisation, tnorm, ksi::fcm (nRules, nClusteringIterations),
             positive_class, negative_class, threshold_value)
{
   _positive_class = positive_class;
   _negative_class = negative_class;
   _threshold_type = ksi::roc_threshold::manual;
   _threshold_value = threshold_value;
   
   set_name();
}

ksi::neuro_fuzzy_system * ksi::ma::clone() const
{
   try 
   {
      return new ksi::ma (*this);
   }
   CATCH;
}
 
ksi::discriminative_model * ksi::ma::clone_discriminant() const
{
    return new ksi::ma (*this);
}

ksi::generative_model * ksi::ma::clone_generator() const
{
    return new ksi::ma (*this);
}
 
