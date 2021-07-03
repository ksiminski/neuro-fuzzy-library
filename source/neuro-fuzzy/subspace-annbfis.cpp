/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "subspace-annbfis.h"
#include "logicalrule.h"
#include "subspace-premise.h"
#include "consequence-CL.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/sfcm.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian-subspace.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"
#include "../common/error-RMSE.h"
#include "../common/error-MAE.h"
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"


void ksi::subspace_annbfis::set_name()
{
    init_name();
}

ksi::partition ksi::subspace_annbfis::doPartition(const ksi::dataset& X)
{
    //    ksi::sfcm clusterer;
//    clusterer.setNumberOfClusters(_nRules);
//    clusterer.setNumberOfIterations(_nClusteringIterations);
    
    try 
    {
        if (_pPartitioner)
            return _pPartitioner->doPartition(X);
        else 
            throw ksi::exception ("no clustering method provided");
    }
    CATCH;
}

void ksi::subspace_annbfis::init_name()
{
    _name_of_neuro_fuzzy_system = std::string ("SubANNBFIS");
   _description_of_neuro_fuzzy_system = std::string("Subspace ANNBFIS, subspace neuro-fuzzy system with logical interpreration of fuzzy rules");
}


ksi::subspace_annbfis::subspace_annbfis()
{
   init_name();
}

ksi::subspace_annbfis::subspace_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp
             ) : neuro_fuzzy_system(), 
                 abstract_annbfis(nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::sfcm (nRules, nClusteringIterations)),
                 annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::sfcm (nRules, nClusteringIterations))
{
    init_name(); 
}
 
 
ksi::subspace_annbfis::subspace_annbfis(int nRules, 
              int nClusteringIterations, 
              int nTuningIterations, 
              double dbLearningCoefficient,
              bool bNormalisation,
              const t_norm & tnorm,
              const implication & imp,
              double positive_class, 
              double negative_class, 
              ksi::roc_threshold threshold_type
             ) : neuro_fuzzy_system(), 
                 abstract_annbfis (nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::sfcm (nRules, nClusteringIterations), positive_class, negative_class, threshold_type),   
                 annbfis(nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, positive_class, negative_class, threshold_type)
{
   init_name();  
}

ksi::subspace_annbfis::subspace_annbfis (const ksi::implication & imp) : neuro_fuzzy_system(), ksi::abstract_annbfis(), ksi::annbfis()
{
   init_name();
   _pImplication = imp.clone();
}


ksi::subspace_annbfis::~subspace_annbfis()
{
}

ksi::subspace_annbfis & ksi::subspace_annbfis::operator=(const ksi::subspace_annbfis & a)
{
   if (this == & a)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(a);
   
   ksi::abstract_annbfis::operator=(a);
   ksi::annbfis::operator=(a);
   
   return *this;
}

ksi::subspace_annbfis & ksi::subspace_annbfis::operator=(ksi::subspace_annbfis && a)
{
   if (this == & a)
      return *this;

   ksi::neuro_fuzzy_system::operator=(a);
   ksi::abstract_annbfis::operator=(a);
   ksi::annbfis::operator=(a);

   return *this;
}

ksi::subspace_annbfis::subspace_annbfis(const ksi::subspace_annbfis & a): neuro_fuzzy_system(a), abstract_annbfis(a), annbfis(a)
{
    init_name(); 
}

ksi::subspace_annbfis::subspace_annbfis(ksi::subspace_annbfis && a): neuro_fuzzy_system(a), abstract_annbfis(a), annbfis(a)
{
    init_name(); 
}

 
void ksi::subspace_annbfis::createFuzzyRulebase
(
   int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, const ksi::dataset& train)
{
    try 
    {
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
        
        if (not _pImplication)
            throw std::string("no implication");
        
        //    ksi::sfcm clusterer;
        //    clusterer.setNumberOfClusters(_nRules);
        //    clusterer.setNumberOfIterations(_nClusteringIterations);

        std::size_t nX = train.getNumberOfData();
        std::size_t nAttr = train.getNumberOfAttributes();
        std::size_t nAttr_1 = nAttr - 1;

        auto XY = train.splitDataSetVertically (nAttr - 1);
        auto trainX = XY.first;
        auto trainY = XY.second;

        auto podzial = doPartition(trainX); 
        auto nRules = podzial.getNumberOfClusters();
            
        // pobranie danych w postaci macierzy:
        auto wTrainX = trainX.getMatrix();
        auto wTrainY = trainY.getMatrix();
//         debug(wTrainY);

        std::vector<double> wY(nX);
        for (std::size_t x = 0; x < nX; x++)
            wY[x] = wTrainY[x][0];

        for (int c = 0; c < nRules; c++)
        {
            ksi::subspace_premise przeslanka;
            auto klaster = podzial.getCluster(c);
            
            auto maxi_weight = 0.0;
            for (std::size_t a = 0; a < nAttr_1; a++)
            {
                // trzeba sprawdzić, czy w przesłance nie są zerowe wartości rozmycia: 
                 
                przeslanka.addDescriptor(klaster->getDescriptor(a));
                // for augmentation of rule's desciptors' weights;
        
                auto w = klaster->getAddressOfDescriptor(a)->getWeight();
                if (maxi_weight < w)
                    maxi_weight = w;
            }
            
            for (std::size_t a = 0; a < nAttr_1; a++)
                przeslanka.augment_attribute(a, maxi_weight);
       
            // attribute augmentation ends here :-)
            logicalrule regula (*_pTnorm, *_pImplication);
            regula.setPremise(przeslanka);
            consequence_CL konkluzja (std::vector<double>(nAttr_1 + 1, 0.0), INITIAL_W);
            regula.setConsequence(konkluzja);
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
                _pRulebase->actualise_parameters(dbLearningCoefficient);
            }
            else
            {
                // wyznaczanie wspolczynnikow konkluzji.
                least_square_error_regression lser ((nAttr_1 + 1) * nRules);

                // przygotowanie wektora D
                for (std::size_t x = 0; x < nX; x++)
                {
                    auto G_suma = std::accumulate(G_przyklad_regula[x].begin(),
                    G_przyklad_regula[x].end(), 0.0);

                    std::vector<double> linia((nAttr_1 + 1) * nRules);
                    int index = 0;
                    for (int r = 0; r < nRules; r++)
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
                for (int r = 0; r < nRules; r++)
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
 
ksi::neuro_fuzzy_system* ksi::subspace_annbfis::clone() const
{
   return new ksi::subspace_annbfis (*this);
}
