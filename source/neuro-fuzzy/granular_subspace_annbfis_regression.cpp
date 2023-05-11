
#include "granular_nfs_regression.h"
#include "granular_subspace_annbfis_regression.h"
#include "../neuro-fuzzy/subspace-annbfis.h"

ksi::granular_subspace_annbfis_regression::granular_subspace_annbfis_regression (const int number_of_data_to_read,                                                       
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate) : ksi::granular_nfs_regression(number_of_data_to_read, minimal_number_of_granules_in_set, maximal_number_of_granules_in_set, number_of_data_to_generate)
{
    _name_of_neuro_fuzzy_system = std::string ("GrSubspaceANNBFIS-reg");
   _description_of_neuro_fuzzy_system = std::string("Granular subspace ANNBFIS for regression, granular neuro-fuzzy system with logical interpretation of fuzzy rules for regression");
}

ksi::granular_subspace_annbfis_regression::~granular_subspace_annbfis_regression ()
{
   // delete what is to delete

}

ksi::granular_subspace_annbfis_regression::granular_subspace_annbfis_regression (const ksi::granular_subspace_annbfis_regression & wzor) : ksi::granular_nfs_regression (wzor), ksi::subspace_annbfis (wzor)
{
   // copy what is to copy

}

ksi::granular_subspace_annbfis_regression & ksi::granular_subspace_annbfis_regression::operator= (const ksi::granular_subspace_annbfis_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::subspace_annbfis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_subspace_annbfis_regression::granular_subspace_annbfis_regression (ksi::granular_subspace_annbfis_regression && wzor) : ksi::granular_nfs_regression (wzor), ksi::subspace_annbfis (wzor)
{
   // swap what is to swap

}

ksi::granular_subspace_annbfis_regression & ksi::granular_subspace_annbfis_regression::operator= (ksi::granular_subspace_annbfis_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::subspace_annbfis::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::neuro_fuzzy_system * ksi::granular_subspace_annbfis_regression::clone() const
{
    return new ksi::granular_subspace_annbfis_regression (*this);
}



double ksi::granular_subspace_annbfis_regression::answer(const ksi::datum& item) const
{
    return ksi::subspace_annbfis::answer(item);
}

void ksi::granular_subspace_annbfis_regression::createFuzzyNonGranularRulebase(
//     const int nRules, 
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train)
{
    try 
    {
        ksi::subspace_annbfis::createFuzzyRulebase( nClusteringIterations, nTuningIterations, dbLearningCoefficient, train);
    }
    CATCH;
}

 
 
