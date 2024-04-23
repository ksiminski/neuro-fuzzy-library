
#include "granular_nfs_regression.h"
#include "granular_tsk_regression.h"
#include "granular_nfs.h"
#include "../neuro-fuzzy/tsk.h"
#include "../partitions/fcm.h"
#include "../service/debug.h"
#include "../tnorms/t-norm-product.h"

ksi::granular_tsk_regression::granular_tsk_regression (const int number_of_data_to_read,                                                       
            const int minimal_number_of_granules_in_set,
            const int maximal_number_of_granules_in_set,
            const int number_of_data_to_generate) 
         : 
            ksi::neuro_fuzzy_system (ksi::fcm())
            ,
            ksi::granular_nfs_regression(number_of_data_to_read, minimal_number_of_granules_in_set, maximal_number_of_granules_in_set, number_of_data_to_generate)
            
//             ,
//             ksi::neuro_fuzzy_system (ksi::fcm())
{
   debug(_pPartitioner);
    
   _name_of_neuro_fuzzy_system = std::string("GrTSK-reg");
   _description_of_neuro_fuzzy_system = std::string("Granular Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for regression");
   
}

ksi::granular_tsk_regression::granular_tsk_regression(
    const std::string& trainDataFile, 
    const std::string& testDataFile, 
    const std::string& resultsFile, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation, 
    const int number_of_data_to_read, 
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set, 
    const int number_of_data_to_generate)
  : 
    neuro_fuzzy_system (trainDataFile, 
                        testDataFile, 
                        resultsFile, ksi::fcm (nNumberOfRules,
                                               nNumberOfClusteringIterations),
                        nNumberOfRules, 
                        nNumberOfClusteringIterations, 
                        nNumberofTuningIterations,
                        dbLearningCoefficient, 
                        bNormalisation
                       ),
    granular_nfs_regression (number_of_data_to_read,
                             minimal_number_of_granules_in_set,
                             maximal_number_of_granules_in_set,
                             number_of_data_to_generate),
    tsk (nNumberOfRules, nNumberOfClusteringIterations, nNumberofTuningIterations,
         dbLearningCoefficient, bNormalisation, ksi::t_norm_product())
{
   _name_of_neuro_fuzzy_system = std::string("GrTSK-reg");
   _description_of_neuro_fuzzy_system = std::string("Granular Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for regression");
}

ksi::granular_tsk_regression::granular_tsk_regression(
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation, 
    const int number_of_data_to_read, 
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set, 
    const int number_of_data_to_generate)
  : 
    neuro_fuzzy_system (nNumberOfRules, 
                        nNumberOfClusteringIterations, 
                        nNumberofTuningIterations,
                        dbLearningCoefficient,
                        bNormalisation,
                        ksi::t_norm_product()
                       ),
    granular_nfs_regression (number_of_data_to_read,
                             minimal_number_of_granules_in_set,
                             maximal_number_of_granules_in_set,
                             number_of_data_to_generate),
    //tsk (nNumberOfRules, nNumberOfClusteringIterations, nNumberofTuningIterations,          dbLearningCoefficient, bNormalisation, ksi::t_norm_product())
    tsk(nNumberOfRules, nNumberOfClusteringIterations)
{
//     debug(__LINE__);
   _name_of_neuro_fuzzy_system = std::string("GrTSK-reg");
   _description_of_neuro_fuzzy_system = std::string("Granular Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm for regression");
}


ksi::granular_tsk_regression::~granular_tsk_regression ()
{
   // delete what is to delete

}

ksi::granular_tsk_regression::granular_tsk_regression (const ksi::granular_tsk_regression & wzor) : ksi::granular_nfs_regression (wzor), ksi::tsk (wzor)
{
   // copy what is to copy

}

ksi::granular_tsk_regression & ksi::granular_tsk_regression::operator= (const ksi::granular_tsk_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::tsk::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_tsk_regression::granular_tsk_regression (ksi::granular_tsk_regression && wzor) : ksi::granular_nfs_regression (wzor), ksi::tsk (wzor)
{
   // swap what is to swap

}

ksi::granular_tsk_regression & ksi::granular_tsk_regression::operator= (ksi::granular_tsk_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs_regression::operator=(wzor);
   ksi::tsk::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::neuro_fuzzy_system * ksi::granular_tsk_regression::clone() const
{
    return new ksi::granular_tsk_regression (*this);
}



double ksi::granular_tsk_regression::answer(const ksi::datum& item) const
{
    return ksi::tsk::answer(item);
}

void ksi::granular_tsk_regression::createFuzzyNonGranularRulebase(
    const int nClusteringIterations, 
    const int nTuningIterations, 
    const double dbLearningCoefficient, 
    const ksi::dataset& train,
    const dataset & validation)
{
    try 
    {
        ksi::tsk::createFuzzyRulebase(nClusteringIterations, nTuningIterations, dbLearningCoefficient, train, validation);
    }
    CATCH;
}

 
 
