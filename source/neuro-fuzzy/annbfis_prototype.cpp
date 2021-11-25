
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/nfs_prototype.h"
#include "../neuro-fuzzy/annbfis_prototype.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../neuro-fuzzy/logicalrule.h"
#include "../implications/implication.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/fcm.h"

#include "../auxiliary/least-error-squares-regression.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::annbfis_prototype::annbfis_prototype ()
{
    _pTnorm = new ksi::t_norm_product();
}

ksi::annbfis_prototype::~annbfis_prototype ()
{
   // delete what is to delete

}

ksi::annbfis_prototype::annbfis_prototype (const ksi::annbfis_prototype & wzor) : ksi::nfs_prototype(wzor)
{
   // copy what is to copy
    _pImplication = std::shared_ptr<ksi::implication> (wzor._pImplication->clone());
    
}

ksi::annbfis_prototype & ksi::annbfis_prototype::operator= (const ksi::annbfis_prototype & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
   _pImplication = std::shared_ptr<ksi::implication> (wzor._pImplication->clone()); 

   return *this;
}

ksi::annbfis_prototype::annbfis_prototype (ksi::annbfis_prototype && wzor) : ksi::nfs_prototype(wzor)
{
   // swap what is to swap
   std::swap(_pImplication, wzor._pImplication); 
}

ksi::annbfis_prototype & ksi::annbfis_prototype::operator= (ksi::annbfis_prototype && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap
   std::swap(_pImplication, wzor._pImplication);

   return *this;
}

ksi::annbfis_prototype::annbfis_prototype(const int number_of_rules, 
                                   const int number_of_clustering_iterations, 
                                   const int number_of_tuning_iterations, 
                                   const double learning_coefficient, 
                                   const bool normalisation, 
                                   const implication & imp,
                                   const ksi::fac_prototype & prot)
: 
ksi::nfs_prototype(number_of_rules, number_of_clustering_iterations, number_of_tuning_iterations, learning_coefficient, normalisation, prot)
{
    _pTnorm = new ksi::t_norm_product();
    _pImplication = std::shared_ptr<ksi::implication> (imp.clone());
}


ksi::annbfis_prototype::annbfis_prototype(const int number_of_rules, 
                                          const int number_of_clustering_iterations, 
                                          const int number_of_tuning_iterations, 
                                          const double learning_coefficient, 
                                          const bool normalisation, 
                                          const ksi::implication& imp, 
                                          const ksi::fac_prototype& prot, 
                                          const double positive_class, 
                                          const double negative_class, 
                                          const ksi::roc_threshold threshold_type)
:
ksi::nfs_prototype(number_of_rules, number_of_clustering_iterations, number_of_tuning_iterations, learning_coefficient, normalisation, prot, positive_class, negative_class, threshold_type)
{
    _pTnorm = new ksi::t_norm_product();
    _pImplication = std::shared_ptr<ksi::implication> (imp.clone());
}


 
void ksi::annbfis_prototype::createFuzzyRulebase(int nClusteringIterations, 
                                             int nTuningIterations, 
                                             double dbLearningCoefficient, 
                                             const ksi::dataset& train)
{
   try
   {
       if (not _pImplication)
         throw ksi::exception ("No fuzzy implication in neuro-fuzzy system: null pointer!");
       
       const double INITIAL_W = 2.0;
       
      _TrainDataset = train;
      
      if (_pRulebase)
         delete _pRulebase;
      _pRulebase = new rulebase();
      
      std::size_t nAttr = _TrainDataset.getNumberOfAttributes();
      std::size_t nAttr_1 = nAttr - 1;
         
      auto XY = train.splitDataSetVertically (nAttr - 1);
      auto trainX = XY.first;
      auto trainY = XY.second;
      
      _original_size_of_training_dataset = trainX.getNumberOfData();
      
      auto podzial = doPartition(trainX);
      
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
         std::shared_ptr<ksi::prototype> pPrzeslanka (_pFactory->get_prototype());
         
         auto klaster = podzial.getCluster(c);
     
         for (std::size_t a = 0; a < nAttr_1; a++)
         {
             const ksi::descriptor & des = *klaster->getAddressOfDescriptor(a);
             pPrzeslanka->addDescriptor(des);
         }
 
         pPrzeslanka->justified_granularity_principle(wTrainX, wY);
         
         logicalrule regula (*_pTnorm, *_pImplication);
         regula.setPremise(*pPrzeslanka);
         consequence_CL konkluzja (std::vector<double>(nAttr_1 + 1, 1.0), INITIAL_W);
         regula.setConsequence(konkluzja);
#pragma omp critical
         _pRulebase->addRule(regula);
      }
      
      // dla wyznaczenia wartosci konkuzji:
      std::vector<std::vector<double>> G_przyklad_regula; 
      
      // mam zgrupowane dane, teraz trzeba nastroic system
      for (int i = 0; i < _nTuningIterations; i++)
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
//                debug(odpowiedz);
               // dla wyznaczania konkluzji:
               auto localisation_weight = _pRulebase->get_last_rules_localisations_weights();
               std::vector<double> Gs;
               for (auto & p : localisation_weight)
                  Gs.push_back(p.second);
               
               G_przyklad_regula.push_back(Gs);
               // no i juz zwykla metoda gradientowa
               _pRulebase->cummulate_differentials(wTrainX[x], wY[x]);
            }         
            _pRulebase->actualise_parameters(_dbLearningCoefficient);
//             debug(G_przyklad_regula);
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
//                debug(G_suma);
               
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
            
//             debug(p);

            // teraz zapis do regul:
            #pragma omp parallel for 
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
         #pragma omp parallel for 
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
 

ksi::neuro_fuzzy_system * ksi::annbfis_prototype::clone() const
{
    return new ksi::annbfis_prototype(*this);
}

ksi::discriminative_model * ksi::annbfis_prototype::clone_discriminant() const
{
    return new ksi::annbfis_prototype(*this);
}

ksi::generative_model * ksi::annbfis_prototype::clone_generator() const
{
    return new ksi::annbfis_prototype(*this);
}

 
 
std::string ksi::annbfis_prototype::get_nfs_description() const
{
    std::shared_ptr<ksi::prototype> p (_pFactory->get_prototype());
    return std::string("Neuro-fuzzy system with logical interpretation of fuzzy rules with gaussian fuzzy sets in premises and product t-norm and fuzzy c-means (FCM) clustering algorithm with ") + p->get_description();
}

std::string ksi::annbfis_prototype::get_nfs_name() const
{
    std::shared_ptr<ksi::prototype> p (_pFactory->get_prototype());
    return std::string("PANNBFIS+") + p->get_name();
 
}
