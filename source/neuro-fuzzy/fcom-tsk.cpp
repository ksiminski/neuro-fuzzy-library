/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "../neuro-fuzzy/fcom-tsk.h"
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
 
 
ksi::partition ksi::fcom_tsk::doPartition(const ksi::dataset& X)
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

void ksi::fcom_tsk::set_name()
{
   _name_of_neuro_fuzzy_system = std::string("FCOM-TSK");
   _description_of_neuro_fuzzy_system = std::string("Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm and fuzzy c-ordered means (FCOM) clustering algorithm");
}
 

  
ksi::fcom_tsk::fcom_tsk() 
{
    set_name();
}

 
ksi::fcom_tsk::fcom_tsk(int nRules, 
                        double dbFrobeniusEpsilon, 
                        int nTuningIterations, 
                        double dbLearningCoefficient, 
                        bool bNormalisation, 
                        const ksi::t_norm& tnorm, 
                        const ksi::dissimilarity & Dissimilarity, 
                        const ksi::owa & Owa, 
                        const double dbMinimalTypicality)
                        : abstract_tsk(nRules, dbFrobeniusEpsilon,
                                         nTuningIterations, dbLearningCoefficient,
                                         bNormalisation, tnorm, ksi::fcom(nRules, dbFrobeniusEpsilon, Dissimilarity, Owa),
                                         dbMinimalTypicality
                                      ) 
{
     set_name();
     _pDissimilarity = Dissimilarity.clone();
     _pOwa = Owa.clone();
}


ksi::fcom_tsk::fcom_tsk(int nRules, 
                        double dbFrobeniusEpsilon, 
                        int nTuningIterations, 
                        double dbLearningCoefficient, 
                        bool bNormalisation, 
                        const ksi::t_norm& tnorm,  
                        const ksi::dissimilarity & Dissimilarity, 
                        const ksi::owa & Owa, 
                        double positive_class, 
                        double negative_class, 
                        const ksi::roc_threshold threshold_type, 
                        const double dbMinimalTypicality)
                        : abstract_tsk(nRules, dbFrobeniusEpsilon,
                                       nTuningIterations, dbLearningCoefficient,
                                       bNormalisation, tnorm, ksi::fcom(nRules, dbFrobeniusEpsilon, Dissimilarity, Owa), 
                                       positive_class, negative_class, threshold_type,
                                       dbMinimalTypicality
                                      ) 
{
     set_name();
     _pDissimilarity = Dissimilarity.clone();
     _pOwa = Owa.clone(); 
}


ksi::fcom_tsk::~fcom_tsk()
{
     
}

ksi::fcom_tsk::fcom_tsk(const ksi::fcom_tsk & right) : neuro_fuzzy_system(right), abstract_tsk(right), abstract_fcom(right)
{    
}

ksi::fcom_tsk::fcom_tsk(ksi::fcom_tsk&& right) : neuro_fuzzy_system(right), abstract_tsk(right), abstract_fcom(right)
{
}

ksi::fcom_tsk & ksi::fcom_tsk::operator=(const ksi::fcom_tsk & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_tsk::operator=(right);
   ksi::abstract_fcom::operator=(right);
      
   return *this;
}

ksi::fcom_tsk & ksi::fcom_tsk::operator= (ksi::fcom_tsk && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right);
   ksi::abstract_tsk::operator=(right);
   ksi::abstract_fcom::operator=(right);

   return *this;

}


ksi::neuro_fuzzy_system* ksi::fcom_tsk::clone() const
{
   return new ksi::fcom_tsk (*this);
}



ksi::discriminative_model * ksi::fcom_tsk::clone_discriminant() const
{
    return new ksi::fcom_tsk (*this);
}


ksi::generative_model * ksi::fcom_tsk::clone_generator() const
{
    return new ksi::fcom_tsk (*this);
}


std::string ksi::fcom_tsk::extra_report()
{
    std::stringstream ss;
    ss << ksi::abstract_fcom::extra_report();
    ss << "minimal typicality: " << _minimal_typicality << std::endl;
    ss << "number of items in original train data set: " << _original_size_of_training_dataset << std::endl;
    ss << "number of items in reduced train data set: " << _reduced_size_of_training_dataset;
    return ss.str();
    
}  
