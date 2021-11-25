
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/nfs_prototype.h"
#include "../neuro-fuzzy/tsk_prototype.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/consequence-TSK.h"

#include "../partitions/fcm.h"

#include "../auxiliary/least-error-squares-regression.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::tsk_prototype::tsk_prototype ()
{
}

ksi::tsk_prototype::~tsk_prototype ()
{
   // delete what is to delete

}

ksi::tsk_prototype::tsk_prototype (const ksi::tsk_prototype & wzor) : ksi::nfs_prototype(wzor)
{
   // copy what is to copy 
   
}

ksi::tsk_prototype & ksi::tsk_prototype::operator= (const ksi::tsk_prototype & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate 

   return *this;
}

ksi::tsk_prototype::tsk_prototype (ksi::tsk_prototype && wzor) : ksi::nfs_prototype(wzor)
{
   // swap what is to swap 

}

ksi::tsk_prototype & ksi::tsk_prototype::operator= (ksi::tsk_prototype && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap 

   return *this;
}

ksi::tsk_prototype::tsk_prototype(const int number_of_rules, 
                                   const int number_of_clustering_iterations, 
                                   const int number_of_tuning_iterations, 
                                   const double learning_coefficient, 
                                   const bool normalisation, 
                                   const ksi::fac_prototype & prot)
: ksi::nfs_prototype(number_of_rules, number_of_clustering_iterations, number_of_tuning_iterations, learning_coefficient, normalisation, prot)
{
}

ksi::tsk_prototype::tsk_prototype(const int number_of_rules, 
                                  const int number_of_clustering_iterations, 
                                  const int number_of_tuning_iterations, 
                                  const double learning_coefficient, 
                                  const bool normalisation, 
                                  const ksi::fac_prototype& prot, 
                                  const double positive_class, 
                                  const double negative_class, 
                                  const ksi::roc_threshold threshold_type)
: ksi::nfs_prototype(number_of_rules, number_of_clustering_iterations, number_of_tuning_iterations, learning_coefficient, normalisation, prot, positive_class, negative_class, threshold_type)
{
}


 
void ksi::tsk_prototype::createFuzzyRulebase(int nClusteringIterations, 
                                             int nTuningIterations, 
                                             double dbLearningCoefficient, 
                                             const ksi::dataset& train)
{
   try
   {
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
      ksi::partition podzial;
      
      try 
      {
          podzial = doPartition(trainX);
      } CATCH; 
      
      std::size_t nX = trainX.getNumberOfData();
      // pobranie danych w postaci macierzy:
      auto wTrainX = trainX.getMatrix();  
      auto wTrainY = trainY.getMatrix();      
 
      std::vector<double> wY(nX);
      for (std::size_t x = 0; x < nX; x++)
         wY[x] = wTrainY[x][0];
      
      try 
      {
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

            rule regula;
            regula.setPremise(*pPrzeslanka);
            consequence_TSK konkluzja (std::vector<double>(nAttr_1 + 1, 0.0));
            regula.setConsequence(konkluzja);
            
#pragma omp critical
            _pRulebase->addRule(regula);
        }
      } CATCH;
      
      try 
      {
        // dla wyznaczenia wartosci konkuzji:
        std::vector<std::vector<double>> F_przyklad_regula; 
        
        // mam zgrupowane dane, teraz trzeba nastroic system
        for (int i = 0; i < _nTuningIterations; i++)
        {
            if (i % 2 == 0)
            { 
                F_przyklad_regula.clear(); // dla konkluzji
                
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
                    
                    F_przyklad_regula.push_back(Gs);
                    // no i juz zwykla metoda gradientowa
                    _pRulebase->cummulate_differentials(wTrainX[x], wY[x]);
                }         
                _pRulebase->actualise_parameters(_dbLearningCoefficient);
            }
            else
            {
                // wyznaczanie wspolczynnikow konkluzji.
                least_square_error_regression lser ((nAttr_1 + 1) * _nRules);
                
                // przygotowanie wektora D 
                for (std::size_t x = 0; x < nX; x++)
                {
                auto F_suma = std::accumulate(F_przyklad_regula[x].begin(),
                    F_przyklad_regula[x].end(), 0.0);
                
                std::vector<double> linia((nAttr_1 + 1) * _nRules);
                int index = 0;
                for (int r = 0; r < _nRules; r++)
                {
                    auto S = F_przyklad_regula[x][r] / F_suma;
                    for (std::size_t a = 0; a < nAttr_1; a++)
                        linia[index++] = S * wTrainX[x][a];
                    linia[index++] = S;
                }
                lser.read_data_item(linia, wY[x]);
                }
                auto p = lser.get_regression_coefficients();

                // teraz zapis do regul:
                #pragma omp parallel for 
                for (int r = 0; r < _nRules; r++)
                {
                    std::vector<double> coeff (nAttr_1 + 1);
                    
                    for (std::size_t a = 0; a < nAttr_1 + 1; a++)
                        coeff[a] = p[r * (nAttr_1 + 1) + a];
                    consequence_TSK konkluzja (coeff);
                    (*_pRulebase)[r].setConsequence(konkluzja);
                }
            }
            
            // test: wyznaczam blad systemu
            std::vector<double> wYelaborated (nX);
            #pragma omp parallel for 
            for (std::size_t x = 0; x < nX; x++)
                wYelaborated[x] = answer( *(trainX.getDatum(x)));
            
            
        }
      } CATCH;
      // system nastrojony :-)
   }
   CATCH;
}

 

ksi::neuro_fuzzy_system * ksi::tsk_prototype::clone() const
{
    return new ksi::tsk_prototype(*this);
}

ksi::discriminative_model * ksi::tsk_prototype::clone_discriminant() const
{
    return new ksi::tsk_prototype(*this);
}

ksi::generative_model * ksi::tsk_prototype::clone_generator() const
{
    return new ksi::tsk_prototype(*this);
}

 
 
std::string ksi::tsk_prototype::get_nfs_description() const
{
    std::shared_ptr<ksi::prototype> p (_pFactory->get_prototype());
    return std::string("Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm and fuzzy c-means (FCM) clustering algorithm with ") + p->get_description();
}

std::string ksi::tsk_prototype::get_nfs_name() const
{
    std::shared_ptr<ksi::prototype> p (_pFactory->get_prototype());
    return std::string("PTSK+") + p->get_name();
 
}
