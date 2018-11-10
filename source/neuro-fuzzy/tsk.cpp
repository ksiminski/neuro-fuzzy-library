/** @file */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>

#include "tsk.h"
#include "rule.h"
#include "premise.h"
#include "consequence-TSK.h"
#include "../tnorms/t-norm-product.h"
#include "../partitions/cluster.h"
#include "../partitions/fcm.h"
#include "../tnorms/t-norm-product.h"
#include "../implications/imp-reichenbach.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../auxiliary/least-error-squares-regression.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/roc.h"
#include "../service/debug.h"
#include "../common/error-RMSE.h"
#include "../common/error-MAE.h"
#include "../common/number.h" 
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../partitions/partition.h"
 
void ksi::tsk::experiment_regression(const std::string & trainDataFile, 
                                         const std::string & testDataFile, 
                                         const std::string & outputFile, 
                                         const int nNumberOfRules, 
                                         const int nNumberOfClusteringIterations, 
                                         const int nNumberofTuningIterations, 
                                         const double dbLearningCoefficient,  
                                         const bool bNormalisation
                                        )
{
   try
   {
      ksi::reader_complete czytacz;
      auto zbiorTrain = czytacz.read(trainDataFile);
      auto zbiorTest  = czytacz.read(testDataFile);
      
      if (bNormalisation)
      {
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(zbiorTrain);
         normaliser.modify(zbiorTest);   
      }
      
      createFuzzyRulebase(nNumberOfRules, nNumberOfClusteringIterations,
                        nNumberofTuningIterations, dbLearningCoefficient,
                        zbiorTrain);
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
      std::size_t nXtest  = zbiorTest.getNumberOfData();
      std::size_t nXtrain = zbiorTrain.getNumberOfData();
      std::vector<double> wYtestExpected,  wYtestElaborated,
                        wYtrainExpected, wYtrainElaborated;
      for (std::size_t i = 0; i < nXtest; i++)
      {
         wYtestExpected.push_back(XYtest.second.get(i, 0));
         wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
      }
      
      for (std::size_t i = 0; i < nXtrain; i++)
      {
         wYtrainExpected.push_back(XYtrain.second.get(i, 0));
         wYtrainElaborated.push_back(answer(*(XYtrain.first.getDatum(i))));
      }
      
         
      ksi::error_RMSE rmse; 
      double blad_rmse_test  = rmse.getError(wYtestElaborated, wYtestExpected);
      double blad_rmse_train = rmse.getError(wYtrainElaborated, wYtrainExpected);
      ksi::error_MAE mae;
      double blad_mae_test   = mae.getError(wYtestElaborated, wYtestExpected);
      double blad_mae_train  = mae.getError(wYtrainElaborated, wYtrainExpected);
      
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << _description_of_neuro_fuzzy_system << std::endl;
      
      model << "number of rules:     " << nNumberOfRules << std::endl;
      model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
      model << "number of tuning interations:    " << nNumberofTuningIterations << std::endl;
      model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
      
      model << "RMSE for train data: " << blad_rmse_train << std::endl;
      model << "RMSE for test data:  " << blad_rmse_test  << std::endl;
      
      model << "MAE  for train data: " << blad_mae_train << std::endl;
      model << "MAE  for test data:  " << blad_mae_test  << std::endl;
      
      model << std::endl << std::endl;      
      model << "fuzzy rule base" << std::endl;       
      
      printRulebase (model);
      
      model << std::endl << std::endl << std::endl;      
      model << "train data" << std::endl;
      model << "excepted\telaborated" << std::endl;
      model << "===========================" << std::endl;
      for (std::size_t i = 0; i < nXtrain; i++)
         model << wYtrainExpected[i] << '\t' << wYtrainElaborated[i] << std::endl;
      
      model << std::endl << std::endl;      
      model << "test data" << std::endl;
      model << "excepted\telaborated" << std::endl;
      model << "===========================" << std::endl;
      for (std::size_t i = 0; i < nXtest; i++)
         model << wYtestExpected[i] << '\t' << wYtestElaborated[i] << std::endl;
      
      model.close();
   }
   CATCH;
}
 

void ksi::tsk::experiment_classification (const std::string & trainDataFile,
                                  const std::string & testDataFile,
                                  const std::string & outputFile,
                                  const int nNumberOfRules,
                                  const int nNumberOfClusteringIterations,
                                  const int nNumberofTuningIterations,
                                  const double dbLearningCoefficient,
                                  const bool bNormalisation,
                                  const double dbPositiveClass,
                                  const double dbNegativeClass,
                                  ksi::roc_threshold threshold_type
                                 )
{
   ksi::reader_complete czytacz;
   auto zbiorTrain = czytacz.read(trainDataFile);
   auto zbiorTest  = czytacz.read(testDataFile);
   
   if (bNormalisation)
   {
      ksi::data_modifier_normaliser normaliser;
      normaliser.modify(zbiorTrain);
      normaliser.modify(zbiorTest);   
   }
   
   createFuzzyRulebase(nNumberOfRules, nNumberOfClusteringIterations,
                       nNumberofTuningIterations, dbLearningCoefficient,
                       zbiorTrain);
   auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
   auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
   std::size_t nXtest  = zbiorTest.getNumberOfData();
   std::size_t nXtrain = zbiorTrain.getNumberOfData();
   std::vector<double> wYtestExpected,  wYtestElaborated,
                       wYtrainExpected, wYtrainElaborated;
   for (std::size_t i = 0; i < nXtest; i++)
   {
      wYtestExpected.push_back(XYtest.second.get(i, 0));
      wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
   }
   
   for (std::size_t i = 0; i < nXtrain; i++)
   {
      wYtrainExpected.push_back(XYtrain.second.get(i, 0));
      wYtrainElaborated.push_back(answer(*(XYtrain.first.getDatum(i))));
   }
   
   //for (std::size_t i = 0; i < nXtrain; i++)
   //   std::cout << wYtrainExpected[i] << "\t" << wYtrainElaborated[i] << std::endl;
   
         
   std::ofstream model (outputFile);
   
   model << "EXPERIMENT" << std::endl;
   model << "==========" << std::endl;
   model << getDateTimeNow() << std::endl;
   model << std::endl;
   model << _description_of_neuro_fuzzy_system << std::endl;
   
   model << "number of rules:     " << nNumberOfRules << std::endl;
   model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
   model << "number of tuning interations:    " << nNumberofTuningIterations << std::endl;
   model << "learning coefficient: " << dbLearningCoefficient << std::endl;
   model << "train data file: " << trainDataFile << std::endl;
   model << "test  data file: " << testDataFile << std::endl;
   model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
   
   model << "classification threshold type: ";
   roc ROC;
   auto progi = ROC.calculate_ROC_points(wYtrainExpected, wYtrainElaborated, 
                                         dbPositiveClass, dbNegativeClass);
   
   double prog;
   switch (threshold_type)
   {
      case ksi::roc_threshold::mean:
         prog = (dbPositiveClass + dbNegativeClass) / 2.0;
         model << " mean of (+) and (-) labels";
         break;
      case ksi::roc_threshold::minimal_distance:
         prog = progi.Minimal_distance_threshold;
         model << " minimal distance";
         break;
      case ksi::roc_threshold::youden:
         prog = progi.Youden_threshold;
         model << " Youden";
   }
   model << std::endl;
   model << "threshold value: " << prog << std::endl;

   ///////////////// confusion matrices 
   confusion_matrix con_test;
   int TP, TN, FP, FN;
   
   
   model << std::endl;
   model << "confusion matrix for test data" << std::endl;
   con_test.calculate_statistics(wYtestExpected, wYtestElaborated,
                                 dbPositiveClass, dbNegativeClass,
                                 TP, TN, FP, FN, prog);
   model << con_test.print(TP, TN, FP, FN);
   model << std::endl;
   
   //----------------
   model << std::endl;
   model << "confusion matrix for train data" << std::endl;
   con_test.calculate_statistics(wYtrainExpected, wYtrainElaborated,
                                 dbPositiveClass, dbNegativeClass,
                                 TP, TN, FP, FN, prog);
   model << con_test.print(TP, TN, FP, FN);
   model << std::endl;
   
   ///////////////////////
   
   model << std::endl << std::endl;      
   model << "fuzzy rule base" << std::endl;       
     
   printRulebase (model);
   
   model << std::endl << std::endl;      
   model << "answers for the train set" << std::endl;
   model << "expected\telaborated" << std::endl;
   for (std::size_t i = 0; i < nXtest; i++)
      model << wYtrainExpected[i] << "   " << wYtrainElaborated[i] <<  "  " << (wYtrainElaborated[i] > prog ? dbPositiveClass : dbNegativeClass) <<  std::endl;
   
   model << std::endl << std::endl;      
   model << "answers for the test set" << std::endl;
   model << "expected\telaborated" << std::endl;
   for (std::size_t i = 0; i < nXtest; i++)
      model << wYtestExpected[i] << "   " << wYtestElaborated[i] << "  " << (wYtestElaborated[i] > prog ? dbPositiveClass : dbNegativeClass) << std::endl;
   
   
   model.close();
}
 
 
void ksi::tsk::createFuzzyRulebase
(
   int nRules, int nClusteringIterations, int nTuningIterations, double dbLearningCoefficient, const ksi::dataset& train)
{
   try
   {
      _nRules = nRules;
      _nClusteringIterations = nClusteringIterations;
      _nTuningIterations = nTuningIterations;
      _TrainDataset = train;
      
      if (_pTnorm)
         delete _pTnorm;
      _pTnorm = new t_norm_product ();
         
      if (_pRulebase)
         delete _pRulebase;
      _pRulebase = new rulebase();
      
      fcm clusterer;
      clusterer.setNumberOfClusters(_nRules);
      clusterer.setNumberOfIterations(_nClusteringIterations);
      
      std::size_t nX = train.getNumberOfData();
      std::size_t nAttr = train.getNumberOfAttributes();
      std::size_t nAttr_1 = nAttr - 1;
         
      auto XY = train.splitDataSetVertically (nAttr - 1);
      auto trainX = XY.first;
      auto trainY = XY.second;
      
      auto podzial = clusterer.doPartition(trainX);
      //debug(podzial);
      
      // pobranie danych w postaci macierzy:
      auto wTrainX = trainX.getMatrix();   
      auto wTrainY = trainY.getMatrix();
      
      std::vector<double> wY(nX);
      for (std::size_t x = 0; x < nX; x++)
         wY[x] = wTrainY[x][0];
      
      for (int c = 0; c < nRules; c++)
      {
         premise przeslanka;      
         auto klaster = podzial.getCluster(c);
         
         for (std::size_t a = 0; a < nAttr_1; a++)
            przeslanka.addDescriptor(klaster->getDescriptor(a));
         
         rule regula (*_pTnorm);
         regula.setPremise(przeslanka);
         consequence_TSK konkluzja (std::vector<double>(nAttr_1 + 1, 0.0));
         regula.setConsequence(konkluzja);
         _pRulebase->addRule(regula);
      }
      
      // dla wyznaczenia wartosci konkuzji:
      std::vector<std::vector<double>> F_przyklad_regula; 
      
      
      // mam zgrupowane dane, teraz trzeba nastroic system
      for (int i = 0; i < nTuningIterations; i++)
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
            _pRulebase->actualise_parameters(dbLearningCoefficient);
         }
         
         else
         {
            // wyznaczanie wspolczynnikow konkluzji.
            least_square_error_regression lser ((nAttr_1 + 1) * nRules);
            
            // przygotowanie wektora D 
            for (std::size_t x = 0; x < nX; x++)
            {
               auto F_suma = std::accumulate(F_przyklad_regula[x].begin(),
                  F_przyklad_regula[x].end(), 0.0);
               
               std::vector<double> linia((nAttr_1 + 1) * nRules);
               int index = 0;
               for (int r = 0; r < nRules; r++)
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
            for (int r = 0; r < nRules; r++)
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
         for (std::size_t x = 0; x < nX; x++)
            wYelaborated[x] = answer( *(trainX.getDatum(x)));
         
         
         //ksi::error_RMSE rmse;
         //double blad = rmse.getError(wY, wYelaborated);
         // koniec testu
         
         
      }
   // system nastrojony :-)
   }
   CATCH;
  
}

double ksi::tsk::answer(const ksi::datum& item) const
{
   auto attrs = item.getVector();
   return _pRulebase->answer(attrs);
}

ksi::number ksi::tsk::elaborate_answer(const ksi::datum& d) const
{
   return number (answer(d));
}


ksi::tsk::tsk()
{
   _name_of_neuro_fuzzy_system = std::string("TSK");
   _description_of_neuro_fuzzy_system = std::string("Tagaki-Sugeno-Kang neuro-fuzzy system with gaussian fuzzy sets in premises and product t-norm");
}

ksi::tsk::~tsk()
{
 
}


ksi::tsk::tsk(const ksi::tsk & right) : neuro_fuzzy_system(right)
{
 
}

ksi::tsk::tsk(ksi::tsk&& right) : neuro_fuzzy_system(right)
{
   
}

ksi::tsk & ksi::tsk::operator=(const ksi::tsk & right)
{
   if (this == & right)
      return *this;
   
   ksi::neuro_fuzzy_system::operator=(right);
      
   return *this;
}

ksi::tsk & ksi::tsk::operator= (ksi::tsk && right)
{
   if (this == & right)
      return *this;

   ksi::neuro_fuzzy_system::operator=(right);  

   return *this;

}


ksi::neuro_fuzzy_system* ksi::tsk::clone() const
{
   return new ksi::tsk (*this);
}




