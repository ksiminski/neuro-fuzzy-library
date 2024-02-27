
#include "../neuro-fuzzy/abstract-annbfis.h"
#include "../neuro-fuzzy/weighted_annbfis.h"
#include "../neuro-fuzzy/logicalrule.h"
#include "../neuro-fuzzy/consequence-CL.h"
#include "../tnorms/t-norm-product.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../partitions/fcm-conditional.h"



ksi::weighted_annbfis::weighted_annbfis ()
{
    set_name();
}

ksi::weighted_annbfis::~weighted_annbfis ()
{
   // delete what is to delete

}

ksi::weighted_annbfis::weighted_annbfis (const ksi::weighted_annbfis & wzor) : ksi::abstract_annbfis(wzor)
{
   // copy what is to copy

}

ksi::weighted_annbfis & ksi::weighted_annbfis::operator= (const ksi::weighted_annbfis & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::abstract_annbfis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::weighted_annbfis::weighted_annbfis (ksi::weighted_annbfis && wzor) : ksi::abstract_annbfis(wzor)
{
   // swap what is to swap

}

ksi::weighted_annbfis & ksi::weighted_annbfis::operator= (ksi::weighted_annbfis && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::abstract_annbfis::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::weighted_annbfis::weighted_annbfis(const int nRules, const int nClusteringIterations, const int nTuningIterations, const double dbLearningCoefficient, const bool bNormalisation, const ksi::t_norm& tnorm, const ksi::implication& imp) : ksi::abstract_annbfis(nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, bNormalisation, tnorm, imp, ksi::fcm_conditional(nRules, nClusteringIterations))
{
    set_name();
}

 
ksi::weighted_annbfis::weighted_annbfis(const ksi::implication& imp) : abstract_annbfis(imp, ksi::fcm_conditional())
{
    set_name();
}

 
void ksi::weighted_annbfis::createFuzzyRulebase
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
      
      
      // wyluskanie wag
      auto wWeights = trainX.extract_weights();
      
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
               _pRulebase->cummulate_differentials(wTrainX[x], wY[x], wWeights[x]);
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
               lser.read_data_item(linia, wY[x], wWeights[x]);
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
      }         
         // test: wyznaczam blad systemu
//          std::vector<double> wYelaborated (nX);
//          for (std::size_t x = 0; x < nX; x++)
//             wYelaborated[x] = answer( *(trainX.getDatum(x)));
//          
         //ksi::error_RMSE rmse;
         //double blad = rmse.getError(wY, wYelaborated);
         //debug(blad);
         
         

      // system nastrojony :-)
   }
   CATCH;
}


void ksi::weighted_annbfis::set_name()
{
    _name_of_neuro_fuzzy_system = std::string ("weighted-ANNBFIS");
    _description_of_neuro_fuzzy_system = std::string("weighted ANNBFIS, neuro-fuzzy system with logical interpretation of fuzzy rules, with weighted data items");
}

ksi::neuro_fuzzy_system * ksi::weighted_annbfis::clone() const
{
    return new weighted_annbfis(*this);
}

ksi::discriminative_model * ksi::weighted_annbfis::clone_discriminant() const
{
    return new weighted_annbfis(*this);
}

ksi::generative_model * ksi::weighted_annbfis::clone_generator() const
{
    return new weighted_annbfis(*this);
}

