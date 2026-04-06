/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "../neuro-fuzzy/fcom-annbfis.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/consequence-TSK.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcom.h"
#include "../partitions/partition.h"
#include "../partitions/partitioner.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/clock.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"
#include "../auxiliary/error-RMSE.h"
#include "../auxiliary/error-MAE.h"
#include "../common/number.h" 
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
 
ksi::partition ksi::fcom_annbfis::doPartition(const ksi::dataset& X)
{
    try 
    {
        if (not _pDissimilarity)
            throw ksi::exception ("no dissimilarity object provided");
        if (not _pOwa)
            throw ksi::exception ("no owa object provided");     
//         if (not _pPartitioner)
//             throw ksi::exception ("no partitioner object provided");
       
        // ustawienie liczny przykladow dla algorytmu FCOM
        _pOwa->set_number_of_data_items(X.getNumberOfData());
        
        delete _pPartitioner;
        _pPartitioner = new ksi::fcom(_nRules, _dbFrobeniusEpsilon, 
                                      *_pDissimilarity, * _pOwa);
        
        auto par = _pPartitioner->doPartition(X);
        
        return par; 
    }
    CATCH;
}

void ksi::fcom_annbfis::set_name()
{
   _name_of_neuro_fuzzy_system = std::string("FCOM-ANNBFIS");
   _description_of_neuro_fuzzy_system = std::string("Annbfis neuro-fuzzy system with logical interpretation of fuzzy rules and fuzzy c-ordered means (FCOM) clustering algorithm");
}
 

  
ksi::fcom_annbfis::fcom_annbfis() 
{
    set_name();
}

 

ksi::fcom_annbfis::fcom_annbfis(int nRules, 
                        double dbFrobeniusEpsilon, 
                        int nTuningIterations, 
                        double dbLearningCoefficient, 
                        bool bNormalisation, 
                        const ksi::t_norm& tnorm, 
                        const ksi::implication & imp,
                        const ksi::dissimilarity & Dissimilarity, 
                        const ksi::owa & Owa, 
                        const double dbMinimalTypicality)
                        : neuro_fuzzy_system (nRules, _dbFrobeniusEpsilon,
                                              nTuningIterations, dbMinimalTypicality),
                          abstract_annbfis(nRules, dbFrobeniusEpsilon,
                                         nTuningIterations, dbLearningCoefficient,
                                         bNormalisation, tnorm, imp, ksi::fcom(nRules, dbFrobeniusEpsilon, Dissimilarity, Owa),
                                         dbMinimalTypicality
                                          ) 
{
     set_name();
     _pDissimilarity = Dissimilarity.clone();
     _pOwa = Owa.clone();
}


ksi::fcom_annbfis::fcom_annbfis(int nRules, 
                        double dbFrobeniusEpsilon, 
                        int nTuningIterations, 
                        double dbLearningCoefficient, 
                        bool bNormalisation, 
                        const ksi::t_norm& tnorm,  
                        const ksi::implication & imp,
                        const ksi::dissimilarity & Dissimilarity, 
                        const ksi::owa & Owa, 
                        double positive_class, 
                        double negative_class, 
                        const ksi::roc_threshold threshold_type, 
                        const double dbMinimalTypicality)
                        : neuro_fuzzy_system (nRules, _dbFrobeniusEpsilon,
                                              nTuningIterations, dbMinimalTypicality),
                        abstract_annbfis(nRules, dbFrobeniusEpsilon,
                                       nTuningIterations, dbLearningCoefficient,
                                       bNormalisation, tnorm, imp, ksi::fcom(nRules, dbFrobeniusEpsilon, Dissimilarity, Owa), 
                                       positive_class, negative_class, threshold_type,
                                       dbMinimalTypicality
                                      )
{
     set_name();
     _pDissimilarity = Dissimilarity.clone();
     _pOwa = Owa.clone(); 
}


ksi::fcom_annbfis::fcom_annbfis(int nRules, 
                                double dbFrobeniusEpsilon, 
                                int nTuningIterations, 
                                double dbLearningCoefficient, 
                                bool bNormalisation, 
                                const ksi::t_norm& tnorm,  
                                const ksi::implication & imp,
                                const ksi::dissimilarity & Dissimilarity, 
                                const ksi::owa & Owa, 
                                double positive_class, 
                                double negative_class, 
                                const double threshold_value,
                                const double dbMinimalTypicality)
: neuro_fuzzy_system (nRules, _dbFrobeniusEpsilon,
                      nTuningIterations, dbMinimalTypicality),
                      abstract_annbfis(nRules, dbFrobeniusEpsilon,
                                       nTuningIterations, dbLearningCoefficient,
                                       bNormalisation, tnorm, imp, ksi::fcom(nRules, dbFrobeniusEpsilon, Dissimilarity, Owa), 
                                       positive_class, negative_class, threshold_value,
                                       dbMinimalTypicality
                      )
                      {
                          set_name();
                          _pDissimilarity = Dissimilarity.clone();
                          _pOwa = Owa.clone(); 
                      }
                      

ksi::fcom_annbfis::~fcom_annbfis()
{
     
}


ksi::fcom_annbfis::fcom_annbfis(const ksi::fcom_annbfis & right) : neuro_fuzzy_system(right), abstract_annbfis(right), abstract_fcom(right)
{    
}

ksi::fcom_annbfis::fcom_annbfis(ksi::fcom_annbfis&& right) : neuro_fuzzy_system(right), abstract_annbfis(right), abstract_fcom(right)
{
}

ksi::fcom_annbfis & ksi::fcom_annbfis::operator=(const ksi::fcom_annbfis & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_annbfis::operator=(right);
   ksi::abstract_fcom::operator=(right);
      
   return *this;
}

ksi::fcom_annbfis & ksi::fcom_annbfis::operator= (ksi::fcom_annbfis && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_annbfis::operator=(right);
   ksi::abstract_fcom::operator=(right);

   return *this;

}


ksi::neuro_fuzzy_system* ksi::fcom_annbfis::clone() const
{
   return new ksi::fcom_annbfis (*this);
}



ksi::discriminative_model * ksi::fcom_annbfis::clone_discriminant() const
{
    return new ksi::fcom_annbfis (*this);
}


ksi::generative_model * ksi::fcom_annbfis::clone_generator() const
{
    return new ksi::fcom_annbfis (*this);
}


std::string ksi::fcom_annbfis::extra_report() const
{
    std::stringstream ss;
    ss << ksi::abstract_fcom::extra_report();
    ss << "minimal typicality: " << _minimal_typicality << std::endl;
    ss << "number of items in original train data set: " << _original_size_of_training_dataset << std::endl;
    ss << "number of items in reduced train data set: " << _reduced_size_of_training_dataset;
    
    return ss.str();
    
} 
