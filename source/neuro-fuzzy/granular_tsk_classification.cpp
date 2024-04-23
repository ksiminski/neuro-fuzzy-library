
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../neuro-fuzzy/granular_tsk_classification.h"

ksi::granular_tsk_classification::granular_tsk_classification (
    const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set,
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate,
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type) 
    : 
    ksi::neuro_fuzzy_system (),
    ksi::granular_nfs_classification(number_of_data_to_read,
                                     minimal_number_of_granules_in_set,
                                     maximal_number_of_granules_in_set,
                                     number_of_data_to_generate, 
                                     dbPositiveClass, 
                                     dbNegativeClass, 
                                     threshold_type)
{
   _name_of_neuro_fuzzy_system = std::string("GR-TSK-class");
   _description_of_neuro_fuzzy_system = std::string("Granular Takagi-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for classification");
    
}

ksi::granular_tsk_classification::~granular_tsk_classification () 
{
   // delete what is to delete

}

ksi::granular_tsk_classification::granular_tsk_classification (const ksi::granular_tsk_classification & wzor) : ksi::neuro_fuzzy_system (wzor), ksi::granular_nfs_classification(wzor), ksi::tsk(wzor)
{
   // copy what is to copy

}

ksi::granular_tsk_classification & ksi::granular_tsk_classification::operator= (const ksi::granular_tsk_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::tsk::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_tsk_classification::granular_tsk_classification (ksi::granular_tsk_classification && wzor) : ksi::neuro_fuzzy_system (wzor), ksi::granular_nfs_classification(wzor), ksi::tsk(wzor)
{
   // swap what is to swap

}

ksi::granular_tsk_classification & ksi::granular_tsk_classification::operator= (ksi::granular_tsk_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::tsk::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap

   return *this;
}


ksi::neuro_fuzzy_system * ksi::granular_tsk_classification::clone() const
{
    return new ksi::granular_tsk_classification (*this);
}

double ksi::granular_tsk_classification::answer(const ksi::datum& item) const
{
    return ksi::tsk::answer(item);
}

void ksi::granular_tsk_classification::createFuzzyNonGranularRulebase(
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train,
    const ksi::dataset& validation)
{
    try 
    {
        ksi::tsk::createFuzzyRulebase(nClusteringIterations, nTuningIterations, dbLearningCoefficient, train, validation);
    }
    CATCH;
}


