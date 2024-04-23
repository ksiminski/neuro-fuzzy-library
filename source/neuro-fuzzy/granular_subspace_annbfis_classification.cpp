
#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../neuro-fuzzy/subspace-annbfis.h"
#include "../neuro-fuzzy/granular_subspace_annbfis_classification.h"

ksi::granular_subspace_annbfis_classification::granular_subspace_annbfis_classification (
    const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set,
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate,
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type,
    const ksi::implication & imp) 
    : 
    ksi::neuro_fuzzy_system (),
    ksi::granular_nfs_classification(number_of_data_to_read,
                                     minimal_number_of_granules_in_set,
                                     maximal_number_of_granules_in_set,
                                     number_of_data_to_generate, 
                                     dbPositiveClass, 
                                     dbNegativeClass, 
                                     threshold_type),
    ksi::annbfis (imp) 
{
   _name_of_neuro_fuzzy_system = std::string("GR-subspace-ANNBFIS-class");
   _description_of_neuro_fuzzy_system = std::string("Granular subspace ANNBFIS neuro-fuzzy system with logical interpretation of fuzzy rulesM");
    
}

ksi::granular_subspace_annbfis_classification::~granular_subspace_annbfis_classification ()
{
   // delete what is to delete

}

ksi::granular_subspace_annbfis_classification::granular_subspace_annbfis_classification (const ksi::granular_subspace_annbfis_classification & wzor) : ksi::neuro_fuzzy_system (wzor), ksi::granular_nfs_classification(wzor), ksi::subspace_annbfis(wzor)
{
   // copy what is to copy

}

ksi::granular_subspace_annbfis_classification & ksi::granular_subspace_annbfis_classification::operator= (const ksi::granular_subspace_annbfis_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::subspace_annbfis::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_subspace_annbfis_classification::granular_subspace_annbfis_classification (ksi::granular_subspace_annbfis_classification && wzor) : ksi::neuro_fuzzy_system (wzor), ksi::granular_nfs_classification(wzor), ksi::subspace_annbfis(wzor)
{
   // swap what is to swap

}

ksi::granular_subspace_annbfis_classification & ksi::granular_subspace_annbfis_classification::operator= (ksi::granular_subspace_annbfis_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_classification::operator=(wzor);
   ksi::subspace_annbfis::operator=(wzor);
   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap

   return *this;
}



ksi::neuro_fuzzy_system * ksi::granular_subspace_annbfis_classification::clone() const
{
    return new ksi::granular_subspace_annbfis_classification (*this);
}

double ksi::granular_subspace_annbfis_classification::answer(const ksi::datum& item) const
{
    return ksi::subspace_annbfis::answer(item);
}

void ksi::granular_subspace_annbfis_classification::createFuzzyNonGranularRulebase(
//     const int nRules, 
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train, 
    const ksi::dataset & validation)
{
    try 
    {
        ksi::subspace_annbfis::createFuzzyRulebase( nClusteringIterations, nTuningIterations, dbLearningCoefficient, train, validation);
    }
    CATCH;
}

