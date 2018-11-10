/** @file */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>
#include <numeric>
#include <map>

#include "neuro-fuzzy-system.h" 
#include "random-neuro-fuzzy-forest.h"
#include "../common/dataset.h"
#include "../common/number.h"
#include "../common/error-RMSE.h"
#include "../common/data-modifier-normaliser.h"
#include "../service/debug.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/confusion-matrix.h"
#include "../readers/reader-complete.h"


ksi::datum ksi::random_neuro_fuzzy_forest::remove_attibutes(
   const ksi::datum & dana, 
   const std::vector<bool> & attribute_pattern)
{
   try
   {
      ksi::datum abridged_datum;
      auto number_of_attributes_in_datum = dana.getNumberOfAttributes();
      auto attribute_pattern_size = attribute_pattern.size();
      
      for (std::size_t a = 0; 
         a < attribute_pattern_size and a < number_of_attributes_in_datum; 
         a++)
      {
         if (attribute_pattern[a]) // keep the attribute_pattern
            abridged_datum.push_back(dana.at(a)->clone());  
      }
      
      return abridged_datum;
   }
   CATCH;
}

std::pair <ksi::dataset, std::vector<bool>> ksi::random_neuro_fuzzy_forest::random_removal_of_attributes(
   const ksi::dataset & ds, 
   int number_of_attributes_to_keep, 
   std::default_random_engine & engine)
{  
   try
   {
      // najpierw trzeba wygenerowac wzorzec atrybutow:
      auto number_of_attributes = ds.getNumberOfAttributes();
      
      std::vector<std::size_t> indeksy (number_of_attributes - 1);
      std::iota (indeksy.begin(), indeksy.end(), 0);
      std::shuffle (indeksy.begin(), indeksy.end(), engine);
      
      std::vector<bool> attribute_pattern (number_of_attributes - 1, false);
      for (int a = 0; a < number_of_attributes_to_keep; a++)
         attribute_pattern[indeksy[a]] = true;
      // i dodaje zawsze atrybut ostatni, czyli decyzyjny:
      attribute_pattern.push_back(number_of_attributes - 1);
      
      // mam wzorzec atrybutow   
      ksi::dataset abridged_data;   
      auto number_of_data = ds.getNumberOfData();   
      for (std::size_t i = 0; i < number_of_data; i++)
      {
         auto abridged_datum = remove_attibutes(*(ds.getDatum(i)), attribute_pattern);
         abridged_data.addDatum(abridged_datum);
      }
      
      return { abridged_data, attribute_pattern };   
   }
   CATCH;
}



std::pair< ksi::dataset, std::unordered_multiset< size_t > > ksi::random_neuro_fuzzy_forest::data_bagging(const ksi::dataset & ds, const int number_of_data_items, std::default_random_engine& engine)
{
   try
   {
      ksi::dataset bagged_ds;
      std::unordered_multiset<size_t> indices;
      
      std::size_t nX = ds.getNumberOfData();
      
      std::uniform_int_distribution<std::size_t> distribution (0, nX - 1);
      
      for (std::size_t i = 0; i < number_of_data_items; i++)
      {
         auto index = distribution(engine);
         indices.insert(index);
         bagged_ds.addDatum(ds.getDatum(index)->clone());
      }
      
      return { bagged_ds, indices };
   }
   CATCH;
}


ksi::random_neuro_fuzzy_forest::random_neuro_fuzzy_forest()
{
   _engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

ksi::random_neuro_fuzzy_forest::~random_neuro_fuzzy_forest()
{
    
}


ksi::random_neuro_fuzzy_forest::random_neuro_fuzzy_forest(const ksi::random_neuro_fuzzy_forest & wzor)
{
    
      
   copy_fields(wzor);   
}

ksi::random_neuro_fuzzy_forest::random_neuro_fuzzy_forest(ksi::random_neuro_fuzzy_forest && wzor)
{
   std::swap(forest, wzor.forest);
   
   copy_fields(wzor);
}

ksi::random_neuro_fuzzy_forest & ksi::random_neuro_fuzzy_forest::operator=(const ksi::random_neuro_fuzzy_forest & wzor)
{
   if (this == & wzor)
      return *this;
   
   copy_fields(wzor);
   
   forest = wzor.forest;
   
   return *this;
}

ksi::random_neuro_fuzzy_forest & ksi::random_neuro_fuzzy_forest::operator=(ksi::random_neuro_fuzzy_forest && wzor)
{
   if (this == & wzor)
      return *this;
   
   std::swap(forest, wzor.forest);
      
   copy_fields(wzor); 
   
   return *this;
}


void ksi::random_neuro_fuzzy_forest::copy_fields (const ksi::random_neuro_fuzzy_forest& source)
{
   _number_of_trees = source._number_of_trees;
   _engine = source._engine;
}

void ksi::random_neuro_fuzzy_forest::set_number_of_trees(int count)
{
   _number_of_trees = count;
}
 
void ksi::random_neuro_fuzzy_forest::createRandomFuzzyForest (
   int nClusteringIterations, 
   int nTuningIterations, 
   double dbLearningCoefficient, 
   const int number_of_trees, 
   const ksi::dataset & train,
   bool bClassification,
   ksi::roc_threshold threshold_type,
   double positiveClassvalue,
   double negativeClassvalue,
   const ksi::neuro_fuzzy_system & nfs )
{
   try
   {
      const int MEAN_NUMBER_OF_RULES = 5;
      auto nData = train.getNumberOfData();
      auto nAttr = train.getNumberOfAttributes();
      
      std::size_t nDataOneTree = 2 * nData / number_of_trees;
      std::poisson_distribution<std::size_t> rozklad ((int)sqrt(nAttr));
      std::poisson_distribution<int> rule_number (MEAN_NUMBER_OF_RULES);
      
      for (int i = 0; i < number_of_trees; i++)
      {
         auto bagged = data_bagging(train, nDataOneTree, _engine);
         auto bagged_ds = bagged.first;
         auto bagged_used = bagged.second;
         auto abridged = random_removal_of_attributes(bagged_ds, std::min(rozklad(_engine) + 2, nAttr - 1 /* atrybut decyzyjny zawsze zostaje */), _engine);
         
         auto abridged_data = abridged.first;
         auto attribute_pattern = abridged.second;
         
         random_neuro_fuzzy_system rnfs (nfs, bagged_used, attribute_pattern);
         
         rnfs.train (abridged_data, nClusteringIterations, nTuningIterations, rule_number(_engine) + 2, dbLearningCoefficient);
         
         if (bClassification)
         {
            // Trzeba wyznaczyc prog dla klasyfikacji
            
            // najpierw trzeba odciac ostatni atrybut (decyzyjny):
            auto XYtrain = bagged_ds.splitDataSetVertically(abridged_data.getNumberOfAttributes() - 1);
            
            // teraz wyznaczam odpowiedzi dla wszystkich przykladow:
            auto nXtrain = XYtrain.first.getNumberOfData();
            
            std::vector<double> expected, elaborated;
            for (std::size_t i = 0; i < nXtrain; i++)
            {
               ksi::number odpowiedz = rnfs.answer(*(XYtrain.first.getDatum(i)));
               if (odpowiedz.exists())
               {
                  elaborated.push_back(odpowiedz.getValue());
                  expected.push_back(XYtrain.second.get(i, 0));
               }
            }
            
            // OK, mam wyniki, trzeba wypracowac prog odciecia:
            
            ksi::roc ROC;
            auto points = ROC.calculate_ROC_points(expected, elaborated, positiveClassvalue, negativeClassvalue); 
            
            switch (threshold_type)
            {
               case ksi::roc_threshold::mean:
                  rnfs.set_classification_threshold((positiveClassvalue + negativeClassvalue) / 2.0);
                  break;
               case ksi::roc_threshold::youden:
                  rnfs.set_classification_threshold(points.Youden_threshold);
                  break;
               case ksi::roc_threshold::minimal_distance:
                  rnfs.set_classification_threshold(points.Minimal_distance_threshold);
                  break;
            }
         }    
         forest.push_back(rnfs);
      }
   }
   CATCH;
}

ksi::number ksi::random_neuro_fuzzy_forest::answer_regression(
   const ksi::datum & d)
{
   try
   {
      std::size_t counter = 0;
      ksi::number summed_answers;
      
      for (const auto & rnfs : forest)
      {
         auto attribute_pattern = rnfs.get_attribute_indices();
         // wyznaczam krotke z usunietymi atrybutami:
         auto abridged_datum = remove_attibutes(d, attribute_pattern);
         
         ksi::number elaborated_answer = rnfs.answer(abridged_datum);
         if (elaborated_answer.exists())
         {
            counter++;
            summed_answers += elaborated_answer;
         }
      }
      
      if (counter == 0)
         return ksi::number(false);
      else
         return summed_answers / counter; 
   }
   CATCH;
}

double ksi::random_neuro_fuzzy_forest::answer_classification(
   const ksi::datum & d, 
   double positiveClassvalue, 
   double negativeClassvalue)
{
   try
   {
      std::map<double, size_t> odpowiedzi;
      
      for (const auto & rnfs : forest)
      {
         auto attribute_pattern = rnfs.get_attribute_indices();
         // wyznaczam krotke z usunietymi atrybutami:
         auto abridged_datum = remove_attibutes(d, attribute_pattern);
         
         ksi::number elaborated_answer = rnfs.answer(abridged_datum);
         if (elaborated_answer.exists())
         {
            auto threshold = rnfs.get_threshold();
            if (elaborated_answer.getValue() > threshold)
               odpowiedzi[positiveClassvalue]++;
            else
               odpowiedzi[negativeClassvalue]++;
         }
      }
      
      if (odpowiedzi[positiveClassvalue] > odpowiedzi[negativeClassvalue])
         return positiveClassvalue;
      else
         return negativeClassvalue;
   }
   CATCH;
}


void ksi::random_neuro_fuzzy_forest::experiment_regression
(const std::string & trainDataFile, 
 const std::string & testDataFile, 
 const std::string & outputFile, 
 const int nNumberOfClusteringIterations, 
 const int nNumberOfTuningIterations, 
 const int nNumberOfNeuroFuzzySystemsInForest, 
 const double dbLearningCoefficient, 
 const bool bNormalisation, 
 const ksi::neuro_fuzzy_system & nfs)
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
      
      createRandomFuzzyForest(nNumberOfClusteringIterations,
         nNumberOfTuningIterations, dbLearningCoefficient, nNumberOfNeuroFuzzySystemsInForest, zbiorTrain, 
         false, /* regression */
         ksi::roc_threshold::mean, /* any is good - it is not used at all for regression */
         0, /* any is good - it is not used at all for regression */
         0, /* any is good - it is not used at all for regression */
         nfs);
      
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
      std::size_t nXtest  = zbiorTest.getNumberOfData();
      std::size_t nXtrain = zbiorTrain.getNumberOfData();
      std::vector<double> wYtestExpected, wYtrainExpected;
      std::vector<ksi::number> wYtestElaborated, wYtrainElaborated;
      
      for (std::size_t i = 0; i < nXtest; i++)
      {
         auto wynik = answer_regression(*(XYtest.first.getDatum(i)));
      
         if (wynik.exists())
         {
            wYtestExpected.push_back(XYtest.second.get(i, 0));
            wYtestElaborated.push_back(wynik);
         }
      }
      
      for (std::size_t i = 0; i < nXtrain; i++)
      {
         auto wynik = answer_regression(*(XYtrain.first.getDatum(i)));
         
         if (wynik.exists())
         {
            wYtrainExpected.push_back(XYtrain.second.get(i, 0));
            wYtrainElaborated.push_back(wynik);
         }
      }
      
         
      ksi::error_RMSE rmse; 
      double blad_rmse_test  = rmse.getError(wYtestElaborated, wYtestExpected);
      double blad_rmse_train = rmse.getError(wYtrainElaborated, wYtrainExpected);
         
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << "random forest of neuro-fuzzy systems" << std::endl;
      model << "neuro-fuzzy system: " << nfs.get_nfs_name() << " ";
      model << "(" << nfs.get_nfs_description() << ")" << std::endl;
      model << "number of neuro-fuzzy systems in forest: " << nNumberOfNeuroFuzzySystemsInForest << std::endl;
      model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
      model << "number of tuning interations:    " << nNumberOfTuningIterations << std::endl;
      model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      
      model << std::endl;
   

      
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
   
      model << "RMSE for train data: " << blad_rmse_train << std::endl;
      model << "RMSE for test data:  " << blad_rmse_test  << std::endl;
      
   //    model << "number of rules:     " << nNumberOfRules << std::endl;
   //    
   //    
   //    model << std::endl << std::endl;      
   //    model << "fuzzy rule base" << std::endl;       
   //      
   //    printRulebase (model);
      
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


void ksi::random_neuro_fuzzy_forest::experiment_classification(
   const std::string & trainDataFile, 
   const std::string & testDataFile, 
   const std::string & outputFile, 
   const int nNumberOfClusteringIterations, 
   const int nNumberOfTuningIterations, 
   const int nNumberOfNeuroFuzzySystemsInForest, 
   const double dbLearningCoefficient, 
   const bool bNormalisation, 
   const double dbPositiveClassLabel, 
   const double dbNegativeClassLabel, 
   const ksi::roc_threshold threshold_type, 
   const ksi::neuro_fuzzy_system & nfs)
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
      
      createRandomFuzzyForest(nNumberOfClusteringIterations,
         nNumberOfTuningIterations, dbLearningCoefficient, nNumberOfNeuroFuzzySystemsInForest, zbiorTrain, 
         true, /* classification */
         threshold_type,  
         dbPositiveClassLabel,  
         dbNegativeClassLabel,  
         nfs);
      
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
      std::size_t nXtest  = zbiorTest.getNumberOfData();
      std::size_t nXtrain = zbiorTrain.getNumberOfData();
      std::vector<double> wYtestExpected, wYtrainExpected;
      std::vector<double> wYtestElaborated, wYtrainElaborated;
      
      for (std::size_t i = 0; i < nXtest; i++)
      {
         auto wynik = answer_classification(*(XYtest.first.getDatum(i)),
            dbPositiveClassLabel, dbNegativeClassLabel
         );
      
         wYtestExpected.push_back(XYtest.second.get(i, 0));
         wYtestElaborated.push_back(wynik);
      }
      
      for (std::size_t i = 0; i < nXtrain; i++)
      {
         auto wynik = answer_classification(*(XYtrain.first.getDatum(i)),
            dbPositiveClassLabel, dbNegativeClassLabel);
         
         wYtrainExpected.push_back(XYtrain.second.get(i, 0));
         wYtrainElaborated.push_back(wynik);
      }
      
      // no i wypisanie raportu:
      
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << "random forest of neuro-fuzzy systems" << std::endl;
      model << "neuro-fuzzy system: " << nfs.get_nfs_name() << " ";
      model << "(" << nfs.get_nfs_description() << ")" << std::endl;
      model << "number of neuro-fuzzy systems in forest: " << nNumberOfNeuroFuzzySystemsInForest << std::endl;
      model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
      model << "number of tuning interations:    " << nNumberOfTuningIterations << std::endl;
      model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      
      model << std::endl;
   

      
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;

      
      ///////////////// confusion matrices 
      confusion_matrix con_test;
      int TP, TN, FP, FN;
      
      model << std::endl;
      
      // Wyniki sa juz odpowiednimi klasami, wiec tutaj prog nie ma takiego 
      // znaczenia. Ustalam go dokladnie w polowie, zeby byl rowno odlegly
      // od obu. 
      double prog = (dbPositiveClassLabel + dbNegativeClassLabel) / 2.0;
      model << "confusion matrix for test data" << std::endl;
      con_test.calculate_statistics(wYtestExpected, wYtestElaborated,
                                    dbPositiveClassLabel, dbNegativeClassLabel,
                                    TP, TN, FP, FN, prog);
      model << con_test.print(TP, TN, FP, FN);
      model << std::endl;
      
      //----------------
      model << std::endl;
      model << "confusion matrix for train data" << std::endl;
      con_test.calculate_statistics(wYtrainExpected, wYtrainElaborated,
                                    dbPositiveClassLabel, dbNegativeClassLabel,
                                    TP, TN, FP, FN, prog);
      model << con_test.print(TP, TN, FP, FN);
      model << std::endl;
      
      ///////////////////////
      
      model.close();
   }
   CATCH;
}
