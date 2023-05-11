
#include "granular_nfs_regression.h"
#include "granular_ma_regression.h"
#include "../neuro-fuzzy/ma.h"

ksi::granular_ma_regression::granular_ma_regression (const int number_of_data_to_read,                                                       
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate) : ksi::granular_nfs_regression(number_of_data_to_read, minimal_number_of_granules_in_set, maximal_number_of_granules_in_set, number_of_data_to_generate)
{
    _name_of_neuro_fuzzy_system = std::string("GR-MA-reg");
   _description_of_neuro_fuzzy_system = std::string("Granular Mamdami-Assilan neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for regression");
    
}

ksi::granular_ma_regression::~granular_ma_regression ()
{
   // delete what is to delete

}

ksi::granular_ma_regression::granular_ma_regression (const ksi::granular_ma_regression & wzor) : ksi::granular_nfs_regression (wzor), ksi::ma (wzor)
{
   // copy what is to copy

}

ksi::granular_ma_regression & ksi::granular_ma_regression::operator= (const ksi::granular_ma_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::ma::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_ma_regression::granular_ma_regression (ksi::granular_ma_regression && wzor) : ksi::granular_nfs_regression (wzor), ksi::ma (wzor)
{
   // swap what is to swap

}

ksi::granular_ma_regression & ksi::granular_ma_regression::operator= (ksi::granular_ma_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::ma::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::neuro_fuzzy_system * ksi::granular_ma_regression::clone() const
{
    return new ksi::granular_ma_regression (*this);
}



double ksi::granular_ma_regression::answer(const ksi::datum& item) const
{
    return ksi::ma::answer(item);
}

void ksi::granular_ma_regression::createFuzzyNonGranularRulebase(
//     const int nRules, 
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train)
{
    try 
    {
        ksi::ma::createFuzzyRulebase(nClusteringIterations, nTuningIterations, dbLearningCoefficient, train);
    }
    CATCH;
}

 
 
