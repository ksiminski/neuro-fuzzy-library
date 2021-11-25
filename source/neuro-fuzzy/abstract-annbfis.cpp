/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cmath>
#include <map>

#include "../neuro-fuzzy/annbfis.h"
#include "../neuro-fuzzy/abstract-annbfis.h"
#include "../neuro-fuzzy/logicalrule.h"
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
#include "../neuro-fuzzy/premise.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../neuro-fuzzy/abstract_fcom.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/clock.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"
#include "../common/error-RMSE.h"
#include "../common/error-MAE.h"
#include "../common/number.h"
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::abstract_annbfis::abstract_annbfis(const ksi::implication& imp, 
                                        const ksi::partitioner& Partitioner) :
                                        ksi::abstract_annbfis::abstract_annbfis ()
{
    if (_pImplication)
        delete _pImplication;
    _pImplication = imp.clone();
    
    if (_pPartitioner)
        delete _pPartitioner;
    _pPartitioner = Partitioner.clone();
}


 
void ksi::abstract_annbfis::createFuzzyRulebase
(
   int nClusteringIterations, 
   int nTuningIterations, 
   double eta,
   const ksi::dataset& train )
{
   try 
   {
      if (not _pImplication)
         throw ksi::exception ("No fuzzy implication in neuro-fuzzy system: null pointer!");
//       if (not _pPartitioner)
//           throw ksi::exception("no partition object provided");
 
      const double INITIAL_W = 2.0;
      
      _nClusteringIterations = nClusteringIterations;
      _nTuningIterations = nTuningIterations;
      _TrainDataset = train;
      
      if (_pTnorm)
         delete _pTnorm;
      _pTnorm = new t_norm_product ();
      
      if (_pRulebase)
         delete _pRulebase;
      _pRulebase = new rulebase();
      
      std::size_t nAttr = train.getNumberOfAttributes();
      std::size_t nAttr_1 = nAttr - 1;
         
      auto XY = train.splitDataSetVertically (nAttr - 1);
      auto trainX = XY.first;
      auto trainY = XY.second;
      
//       fcm clusterer;
//       clusterer.setNumberOfClusters(_nRules);
//       clusterer.setNumberOfIterations(_nClusteringIterations);
      
      auto podzial = doPartition(trainX);
      _nRules = podzial.getNumberOfClusters();
      _original_size_of_training_dataset = trainX.getNumberOfData();

      auto typical_items = trainX.get_if_data_typical(_minimal_typicality);
      trainX.remove_untypical_data(typical_items);
      trainY.remove_untypical_data(typical_items);
       _reduced_size_of_training_dataset = trainX.getNumberOfData();
      
      std::size_t nX = trainX.getNumberOfData();
      
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
         auto klaster = podzial.getCluster(c);
         
         for (std::size_t a = 0; a < nAttr_1; a++)
            przeslanka.addDescriptor(klaster->getDescriptor(a));
         
         logicalrule regula (*_pTnorm, *_pImplication);
         regula.setPremise(przeslanka);
         consequence_CL konkluzja (std::vector<double>(nAttr_1 + 1, 1.0), INITIAL_W);
         regula.setConsequence(konkluzja);

         #pragma omp critical
         _pRulebase->addRule(regula);
      }
      
      // dla wyznaczenia wartosci konkuzji:
      std::vector<std::vector<double>> G_przyklad_regula; 
      
      // mam zgrupowane dane, teraz trzeba nastroic system
      for (int i = 0; i < nTuningIterations; i++)
      {
         if (i % 2 == 0)
         { 
            G_przyklad_regula.clear(); // dla konkluzji
            
            // strojenie gradientowe
            _pRulebase->reset_differentials();
            for (std::size_t x = 0; x < nX; x++)
            {
               // Uruchomienie strojenia gradiendowego.
               double odpowiedz = _pRulebase->answer(wTrainX[x]);
               // dla wyznaczania konkluzji:
               auto localisation_weight = _pRulebase->get_last_rules_localisations_weights();
               std::vector<double> Gs;
               for (auto & p : localisation_weight)
                  Gs.push_back(p.second);
               
               G_przyklad_regula.push_back(Gs);
               // no i juz zwykla metoda gradientowa
               _pRulebase->cummulate_differentials(wTrainX[x], wY[x]);
            }         
            _pRulebase->actualise_parameters(eta);
         }
         
         else
         {
            // wyznaczanie wspolczynnikow konkluzji.
            least_square_error_regression lser ((nAttr_1 + 1) * _nRules);
            
            // przygotowanie wektora D 
            for (std::size_t x = 0; x < nX; x++)
            {
               auto G_suma = std::accumulate(G_przyklad_regula[x].begin(),
                  G_przyklad_regula[x].end(), 0.0);
               
               std::vector<double> linia((nAttr_1 + 1) * _nRules);
               int index = 0;
               for (int r = 0; r < _nRules; r++)
               {
                  auto S = G_przyklad_regula[x][r] / G_suma;
                  for (std::size_t a = 0; a < nAttr_1; a++)
                     linia[index++] = S * wTrainX[x][a];
                  linia[index++] = S;
               }
               lser.read_data_item(linia, wY[x]);
            }
            auto p = lser.get_regression_coefficients();

            // teraz zapis do regul:
            for (int r = 0; r < _nRules; r++)
            {
               std::vector<double> coeff (nAttr_1 + 1);
            
               for (std::size_t a = 0; a < nAttr_1 + 1; a++)
                  coeff[a] = p[r * (nAttr_1 + 1) + a];
               consequence_CL konkluzja (coeff, INITIAL_W);
               (*_pRulebase)[r].setConsequence(konkluzja);
            }
         }
         
         // test: wyznaczam blad systemu
         std::vector<double> wYelaborated (nX);
         for (std::size_t x = 0; x < nX; x++)
            wYelaborated[x] = answer( *(trainX.getDatum(x)));
         
         //ksi::error_RMSE rmse;
         //double blad = rmse.getError(wY, wYelaborated);
         //debug(blad);
         
         
      }
      // system nastrojony :-)
   }
   CATCH;
}

double ksi::abstract_annbfis::answer(const ksi::datum& item) const
{
   try
   {
      auto attrs = item.getVector();
      return _pRulebase->answer(attrs);
   }
   CATCH;
}

ksi::number ksi::abstract_annbfis::elaborate_answer(const ksi::datum& d) const
{
   try
   {
      return ksi::number (answer (d));
   }
   CATCH;
}

ksi::abstract_annbfis::abstract_annbfis() : neuro_fuzzy_system()
{
   _pImplication = nullptr;
   _pTnorm = nullptr;
}

ksi::abstract_annbfis::~abstract_annbfis()
{
   delete _pImplication;
   _pImplication = nullptr;
}


ksi::abstract_annbfis::abstract_annbfis(const ksi::abstract_annbfis & right) : neuro_fuzzy_system(right) 
{
   if (right._pImplication)
      _pImplication = right._pImplication->clone();
   else
      _pImplication = nullptr;
}

ksi::abstract_annbfis::abstract_annbfis(ksi::abstract_annbfis && right) : neuro_fuzzy_system(right) 
{
   std::swap (_pImplication, right._pImplication);
}

ksi::abstract_annbfis& ksi::abstract_annbfis::operator=(const ksi::abstract_annbfis & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right);
   
   delete _pImplication;
   if (right._pImplication)
      _pImplication = right._pImplication->clone();
   else
      _pImplication = nullptr;
   
   return *this;
}

ksi::abstract_annbfis& ksi::abstract_annbfis::operator= (ksi::abstract_annbfis && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right);
   
   std::swap (_pImplication, right._pImplication);

   return *this;
}
 
 

double ksi::abstract_annbfis::discriminate(const ksi::datum& d)
{
    return answer(d);
}

/// @todo zaimplementowac
void ksi::abstract_annbfis::train_discriminative_model(const ksi::dataset& ds)
{
    throw std::string ("not implemented");
}

ksi::abstract_annbfis::abstract_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              const partitioner & par, 
              const double dbMinimalTypicality
             ) : neuro_fuzzy_system ()
{
    _nRules = nRules;
    _nClusteringIterations = nClusteringIterations;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
        _pTnorm = tnorm.clone();
    if (not _pPartitioner)
        _pPartitioner = par.clone();
    if (not _pImplication)
        _pImplication = imp.clone();

}

ksi::abstract_annbfis::abstract_annbfis(int nRules, 
              double dbFrobeniusEpsilon, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              const partitioner & par, 
              const double dbMinimalTypicality
             ) : neuro_fuzzy_system(nRules, dbFrobeniusEpsilon, nTuningIterations, dbMinimalTypicality) 
{
    _nRules = nRules;
    _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
   if (not _pTnorm)
        _pTnorm = tnorm.clone();
    if (not _pPartitioner)
        _pPartitioner = par.clone();
    if (not _pImplication)
        _pImplication = imp.clone();
}

ksi::abstract_annbfis::abstract_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              const partitioner & par,
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type, 
              const double dbMinimalTypicality
             ) : neuro_fuzzy_system() 
{
    _nRules = nRules;
    _nClusteringIterations = nClusteringIterations;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
        _pTnorm = tnorm.clone();
    if (not _pPartitioner)
        _pPartitioner = par.clone();
    if (not _pImplication)
        _pImplication = imp.clone();
    _positive_class = positive_class;
    _negative_class = negative_class;
    _threshold_type = threshold_type;
    _minimal_typicality = dbMinimalTypicality;
}

ksi::abstract_annbfis::abstract_annbfis(int nRules, 
              double dbFrobeniusEpsilon, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              const partitioner & par,
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type, 
              const double dbMinimalTypicality
             ) : neuro_fuzzy_system() 
{
    _nRules = nRules;
    _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
    _nTuningIterations = nTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    if (not _pTnorm)
        _pTnorm = tnorm.clone();
    if (not _pPartitioner)
        _pPartitioner = par.clone();
    if (not _pImplication)
        _pImplication = imp.clone();
    _positive_class = positive_class;
    _negative_class = negative_class;
    _threshold_type = threshold_type;
    _minimal_typicality = dbMinimalTypicality;
}
