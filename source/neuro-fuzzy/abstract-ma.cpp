/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cmath>
#include <map>
#include <deque>

#include "../neuro-fuzzy/abstract-ma.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/consequence-MA.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
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
#include "../service/debug.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::abstract_ma::abstract_ma(const ksi::partitioner& Partitioner) : ksi::abstract_ma::abstract_ma()
{
   if (_pPartitioner)
      delete _pPartitioner;
   _pPartitioner = Partitioner.clone();
}

void ksi::abstract_ma::createFuzzyRulebase
(
   int nClusteringIterations, 
   int nTuningIterations, 
   double eta,
   const ksi::dataset & train,
   const ksi::dataset & validation
   )
{
   try
   {
      // std::deque<double> errors;
      
      _nClusteringIterations = nClusteringIterations;
      _nTuningIterations = nTuningIterations;
      _TrainDataset = train;
      
      if (_pTnorm)
         delete _pTnorm;
      _pTnorm = new t_norm_product ();
      
      if (_pRulebase)
         delete _pRulebase;
      _pRulebase = new rulebase();

      // remember the best rulebase:
      // std::unique_ptr<ksi::rulebase> pTheBest (_pRulebase->clone());
      // double dbTheBestRMSE = std::numeric_limits<double>::max();
      ////////

      std::size_t nAttr = train.getNumberOfAttributes();
      std::size_t nAttr_1 = nAttr - 1;
      
      auto XY = train.splitDataSetVertically (nAttr - 1);
      auto trainX = XY.first;
      auto trainY = XY.second;
      
      auto XYval = validation.splitDataSetVertically(nAttr - 1);
      auto validateX = XYval.first;
      auto validateY = XYval.second;
      
      auto mvalidateY = validateY.getMatrix();
      auto nValY = validateY.getNumberOfData();
      std::vector<double> wvalidateY (nValY);
      for (std::size_t x = 0; x < nValY; x++)
         wvalidateY[x] = mvalidateY[x][0];      
      ////////////////////////

      _original_size_of_training_dataset = trainX.getNumberOfData();
      
      auto podzial = doPartition(trainX);
      _nRules = podzial.getNumberOfClusters();
      
      auto typical_items = trainX.get_if_data_typical(_minimal_typicality);
      trainX.remove_untypical_data(typical_items);
      trainY.remove_untypical_data(typical_items);
      
      std::size_t nX = trainX.getNumberOfData();
      auto trainReduced = train;
      trainReduced.remove_untypical_data(typical_items);
      auto podzialXY = doPartition(trainReduced);
      
      ///@todo Czy na pewno dobrze tutaj jest z nX?
      nX = trainX.getNumberOfData();
      _reduced_size_of_training_dataset = nX;
      
      // pobranie danych w postaci macierzy:
      auto wTrainX = trainX.getMatrix();  
      auto wTrainY = trainY.getMatrix();

      std::vector<double> wY(nX);
      for (std::size_t x = 0; x < nX; x++)
         wY[x] = wTrainY[x][0];
      
#pragma omp parallel for 
      for (int c = 0; c < _nRules; c++)
      {
         premise przeslanka;      
         auto klaster = podzialXY.getCluster(c);
         
         for (std::size_t a = 0; a < nAttr_1; a++)
         {
            przeslanka.addDescriptor(klaster->getDescriptor(a));
         }
         
         auto needed_descriptor = klaster->getAddressOfDescriptor(nAttr - 1);
         auto scs = needed_descriptor->getMAconsequenceParameters();
         rule regula (*_pTnorm);
         regula.setPremise(przeslanka);
         consequence_MA konkluzja (scs[0], scs[1], scs[2]);
         regula.setConsequence(konkluzja);
         
#pragma omp critical
         _pRulebase->addRule(regula);
      }
      
      // mam zgrupowane dane, teraz trzeba nastroic system
      for (int i = 0; i < nTuningIterations; i++)
      {
         // strojenie gradientowe
         _pRulebase->reset_differentials();
         for (std::size_t x = 0; x < nX; x++)
         {
            // Uruchomienie strojenia gradiendowego.
            double odpowiedz = _pRulebase->answer(wTrainX[x]);
            // no i juz zwykla metoda gradientowa
            _pRulebase->cummulate_differentials(wTrainX[x], wY[x]);
         }         
         _pRulebase->actualise_parameters(eta);
      
         //////////////////////////////////
         // test: wyznaczam blad systemu
         
         // std::vector<double> wYelaborated (nValY);
         // for (std::size_t x = 0; x < nX; x++)
             // wYelaborated[x] = answer( *(validateX.getDatum(x)));
         
         ///////////////////////////
         // ksi::error_RMSE rmse;
         // double blad = rmse.getError(wvalidateY, wYelaborated);
         // errors.push_front(blad);
         
         // eta = modify_learning_coefficient(eta, errors); // modify learning coefficient
         // remember the best rulebase:
         // if (dbTheBestRMSE > blad)
         // {
         //    dbTheBestRMSE = blad;
         //    pTheBest = std::unique_ptr<ksi::rulebase>(_pRulebase->clone());
         // }
         ///////////////////////////
      }
      // system nastrojony :-)
      // update the rulebase with the best one:
      // delete _pRulebase;
      // _pRulebase = pTheBest->clone();
   }
   CATCH;
}

double ksi::abstract_ma::answer(const ksi::datum& item) const
{
   try 
   {
      auto attrs = item.getVector();
      return _pRulebase->answer(attrs);
   }
   CATCH;
}

ksi::number ksi::abstract_ma::elaborate_answer (const ksi::datum & item) const 
{ 
   try 
   {
      return number (answer(item));
   }
   CATCH;
}
  
ksi::abstract_ma::abstract_ma()
{
   _pPartitioner = nullptr;
}

double ksi::abstract_ma::discriminate(const ksi::datum& d)
{
    return answer(d);
}

void ksi::abstract_ma::train_discriminative_model(const ksi::dataset & ds)
{
    createFuzzyRulebase( _nClusteringIterations,
        _nTuningIterations, _dbLearningCoefficient, ds, ds
    );  // validation == train
}

void ksi::abstract_ma::train_generative_model(const ksi::dataset& ds)
{
    createFuzzyRulebase( _nClusteringIterations,
        _nTuningIterations, _dbLearningCoefficient, ds, ds
    );  // validation == train
}

ksi::abstract_ma::abstract_ma(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm, 
              const partitioner & Partitioner, 
              const double dbMinimalTypicality
             )  
{
    _nRules = nRules;
    _nClusteringIterations = nClusteringIterations;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
       _pTnorm = tnorm.clone();
    if (not _pPartitioner)
       _pPartitioner = Partitioner.clone();
    _minimal_typicality = dbMinimalTypicality;
}

ksi::abstract_ma::abstract_ma(int nRules, 
                                double dbFrobeniusEpsilon, 
                                int nTuningIterations, 
                                double dbLearningCoefficient, 
                                bool bNormalisation, 
                                const ksi::t_norm& tnorm,
                                const ksi::partitioner & Partitioner,
                                const double dbMinimalTypicality)
{
    _nRules = nRules;
    _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
       _pTnorm = tnorm.clone();
    if (not _pPartitioner)
       _pPartitioner = Partitioner.clone();
    _minimal_typicality = dbMinimalTypicality;
}

ksi::abstract_ma::abstract_ma(int nRules, 
                                double dbFrobeniusEpsilon, 
                                int nTuningIterations, 
                                double dbLearningCoefficient, 
                                bool bNormalisation, 
                                const ksi::t_norm & tnorm,
                                const ksi::partitioner & Partitioner, 
                                double positive_class, 
                                double negative_class, 
                                ksi::roc_threshold threshold_type, 
                                const double dbMinimalTypicality)
{
    _nRules = nRules;
    _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
       _pTnorm = tnorm.clone();
    if (not _pPartitioner)
       _pPartitioner = Partitioner.clone();
    _positive_class = positive_class;
    _negative_class = negative_class;
    _threshold_type = threshold_type;
    _minimal_typicality = dbMinimalTypicality;
}


ksi::abstract_ma::abstract_ma(int nRules, 
                              double dbFrobeniusEpsilon, 
                              int nTuningIterations, 
                              double dbLearningCoefficient, 
                              bool bNormalisation, 
                              const ksi::t_norm & tnorm,
                              const ksi::partitioner & Partitioner, 
                              double positive_class, 
                              double negative_class, 
                              const double threshold_value, 
                              const double dbMinimalTypicality)
{
   _nRules = nRules;
   _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
   _nTuningIterations = nTuningIterations;
   _dbLearningCoefficient = dbLearningCoefficient;
   _bNormalisation = bNormalisation;
   if (not _pTnorm)
      _pTnorm = tnorm.clone();
   if (not _pPartitioner)
      _pPartitioner = Partitioner.clone();
   _positive_class = positive_class;
   _negative_class = negative_class;
   _threshold_type = ksi::roc_threshold::manual;
   _threshold_value = threshold_value;
   _minimal_typicality = dbMinimalTypicality;
}


ksi::abstract_ma::abstract_ma(int nRules, 
                              int nClusteringIterations, 
                              int nTuningIterations, 
                              double dbLearningCoefficient, 
                              bool bNormalisation, 
                              const ksi::t_norm & tnorm, 
                              const partitioner & Partitioner, 
                              double positive_class, 
                              double negative_class, 
                              ksi::roc_threshold threshold_type, 
                              const double dbMinimalTypicality)
{
   _nRules = nRules;
   _nClusteringIterations = nClusteringIterations;
   _nTuningIterations = nTuningIterations;
   _dbLearningCoefficient = dbLearningCoefficient;
   _bNormalisation = bNormalisation;
   if (not _pTnorm)
      _pTnorm = tnorm.clone();
   if (not _pPartitioner)
      _pPartitioner = Partitioner.clone();
   _positive_class = positive_class;
   _negative_class = negative_class;
   _threshold_type = threshold_type;
   _minimal_typicality = dbMinimalTypicality;
}

ksi::abstract_ma::abstract_ma(int nRules, 
            int nClusteringIterations, 
            int nTuningIterations, 
            double dbLearningCoefficient, 
            bool bNormalisation, 
            const ksi::t_norm & tnorm, 
            const partitioner & Partitioner, 
            double positive_class, 
            double negative_class, 
            const double threshold_value, 
            const double dbMinimalTypicality)
{
    _nRules = nRules;
    _nClusteringIterations = nClusteringIterations;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
       _pTnorm = tnorm.clone();
    if (not _pPartitioner)
       _pPartitioner = Partitioner.clone();
    _positive_class = positive_class;
    _negative_class = negative_class;
    _threshold_type = ksi::roc_threshold::manual;
    _threshold_value = threshold_value;
    _minimal_typicality = dbMinimalTypicality;
}

ksi::abstract_ma::~abstract_ma()
{
//     if (_pPartitioner)
//         delete _pPartitioner;
//     _pPartitioner = nullptr;    
}


ksi::abstract_ma::abstract_ma(const ksi::abstract_ma & right) : neuro_fuzzy_system(right)
{
}

ksi::abstract_ma::abstract_ma(ksi::abstract_ma && right) : neuro_fuzzy_system(right)
{
}

ksi::abstract_ma & ksi::abstract_ma::operator=(const ksi::abstract_ma & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right); 
      
   return *this;
}

ksi::abstract_ma & ksi::abstract_ma::operator= (ksi::abstract_ma && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right); 
   
//    std::swap(_pPartitioner, right._pPartitioner);

   return *this;

}

ksi::partition ksi::abstract_ma::doPartition(const ksi::dataset& X)
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

