
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/nfs_prototype.h"
#include "../neuro-fuzzy/consequence-TSK.h"

#include "../partitions/fcm_generic.h"

#include "../auxiliary/least-error-squares-regression.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::nfs_prototype::nfs_prototype ()
{
}

ksi::nfs_prototype::~nfs_prototype ()
{
   // delete what is to delete

}

ksi::nfs_prototype::nfs_prototype (const ksi::nfs_prototype & wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // copy what is to copy
    _pFactory = wzor._pFactory->clone(); 
    
}

ksi::nfs_prototype & ksi::nfs_prototype::operator= (const ksi::nfs_prototype & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
    _pFactory = wzor._pFactory->clone();

   return *this;
}

ksi::nfs_prototype::nfs_prototype (ksi::nfs_prototype && wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // swap what is to swap
   std::swap(_pFactory, wzor._pFactory); 
 
}

ksi::nfs_prototype & ksi::nfs_prototype::operator= (ksi::nfs_prototype && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap
   std::swap(_pFactory, wzor._pFactory);
 
   return *this;
}

std::string ksi::nfs_prototype::extra_report() const
{
    return _pFactory->get_metric()->get_info(); 
}


ksi::nfs_prototype::nfs_prototype(const int number_of_rules, 
                                   const int number_of_clustering_iterations, 
                                   const int number_of_tuning_iterations, 
                                   const double learning_coefficient, 
                                   const bool normalisation, 
                                   const ksi::fac_prototype & prot)
{
    this->_nRules = number_of_rules;
    this->_nClusteringIterations = number_of_clustering_iterations;
    this->_nTuningIterations = number_of_tuning_iterations;
    this->_dbLearningCoefficient = learning_coefficient;
    this->_bNormalisation = normalisation;
    this->_pFactory = prot.clone();
    
    auto p = _pFactory->get_metric();
    
    this->_pPartitioner = new ksi::fcm_generic(number_of_rules, number_of_clustering_iterations, *p);
}

ksi::nfs_prototype::nfs_prototype(const int number_of_rules, 
                                   const int number_of_clustering_iterations, 
                                   const int number_of_tuning_iterations, 
                                   const double learning_coefficient, 
                                   const bool normalisation, 
                                   const ksi::fac_prototype & prot,
                                   const double positive_class,
                                   const double negative_class,
                                   const ksi::roc_threshold threshold)
{
    this->_nRules = number_of_rules;
    this->_nClusteringIterations = number_of_clustering_iterations;
    this->_nTuningIterations = number_of_tuning_iterations;
    this->_dbLearningCoefficient = learning_coefficient;
    this->_bNormalisation = normalisation;
    this->_positive_class = positive_class;
    this->_negative_class = negative_class;
    this->_threshold_type = threshold;
    
    this->_pFactory = prot.clone();
    
    auto p = _pFactory->get_metric();
    
    this->_pPartitioner = new ksi::fcm_generic(number_of_rules, number_of_clustering_iterations, *p);
}



// void ksi::prototype_nfs::copy_fields(const ksi::prototype_nfs& wzor)
// {
//     
// }

 

ksi::partition ksi::nfs_prototype::doPartition(const ksi::dataset& X)
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

 

double ksi::nfs_prototype::discriminate(const ksi::datum& d)
{
    return answer(d);
}

void ksi::nfs_prototype::train_discriminative_model(const ksi::dataset& ds)
{
    createFuzzyRulebase(-1, -1, -1, ds);
}

void ksi::nfs_prototype::train_generative_model(const ksi::dataset& ds)
{
    createFuzzyRulebase(-1, -1, -1, ds);
}

double ksi::nfs_prototype::answer(const ksi::datum& item) const
{
   auto attrs = item.getVector();
   return _pRulebase->answer(attrs);
}
 
ksi::number ksi::nfs_prototype::elaborate_answer(const ksi::datum& d) const
{
    return number (answer(d));
}
 
 
