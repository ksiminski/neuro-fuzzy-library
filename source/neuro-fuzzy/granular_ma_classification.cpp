

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../neuro-fuzzy/granular_ma_classification.h"



ksi::granular_ma_classification::granular_ma_classification (
    const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set,
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate,
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type) 
    : 
    ksi::neuro_fuzzy_system(),
    ksi::granular_nfs_classification(number_of_data_to_read,
                                     minimal_number_of_granules_in_set,
                                     maximal_number_of_granules_in_set,
                                     number_of_data_to_generate, 
                                     dbPositiveClass, 
                                     dbNegativeClass, 
                                     threshold_type)
{
   initializeName();
}

ksi::granular_ma_classification::granular_ma_classification(
    const int number_of_rules, 
    const int number_of_clustering_iterations, 
    const int number_of_tuning_iterations, 
    double dbLearningCoefficient, 
    bool bNormalisation, 
    const ksi::t_norm& tnorm, 
    const int number_of_data_to_read, 
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set, 
    const int number_of_data_to_generate, 
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type)
  :
    ksi::granular_nfs_classification(number_of_data_to_read,
                                     minimal_number_of_granules_in_set,
                                     maximal_number_of_granules_in_set,
                                     number_of_data_to_generate, 
                                     dbPositiveClass, 
                                     dbNegativeClass, 
                                     threshold_type),
    ksi::neuro_fuzzy_system(), 
    ksi::ma(number_of_rules, 
            number_of_clustering_iterations, 
            number_of_tuning_iterations, 
            dbLearningCoefficient, 
            bNormalisation, 
            tnorm, 
            dbPositiveClass, 
            dbNegativeClass, 
            threshold_type)

{
    initializeName(); 
}

void ksi::granular_ma_classification::initializeName()
{
   _name_of_neuro_fuzzy_system = std::string("GR-MA-class");
   _description_of_neuro_fuzzy_system = std::string("Granular Mamdami-Assilan neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for classification");
}



ksi::granular_ma_classification::~granular_ma_classification ()
{
   // delete what is to delete

}

ksi::granular_ma_classification::granular_ma_classification (const ksi::granular_ma_classification & wzor) : ksi::neuro_fuzzy_system(wzor), ksi::granular_nfs_classification (wzor), ksi::ma (wzor)
{
   // copy what is to copy

}

ksi::granular_ma_classification & ksi::granular_ma_classification::operator= (const ksi::granular_ma_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::ma::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_ma_classification::granular_ma_classification (ksi::granular_ma_classification && wzor) : ksi::neuro_fuzzy_system(wzor), ksi::granular_nfs_classification (wzor), ksi::ma (wzor)
{
   // swap what is to swap

}

ksi::granular_ma_classification & ksi::granular_ma_classification::operator= (ksi::granular_ma_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::ma::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap

   return *this;
}


ksi::neuro_fuzzy_system * ksi::granular_ma_classification::clone() const
{
    return new ksi::granular_ma_classification (*this);
}

double ksi::granular_ma_classification::answer(const ksi::datum& item) const
{
    return ksi::ma::answer(item);
}

void ksi::granular_ma_classification::createFuzzyNonGranularRulebase(
//     const int nRules, 
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train,
    const ksi::dataset& validation)
{
    try 
    {
        ksi::ma::createFuzzyRulebase( nClusteringIterations, nTuningIterations, dbLearningCoefficient, train, validation);
    }
    CATCH;
}

 
 
