/** @file */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <tuple>

 

#include "neuro-fuzzy-system.h"
#include "rulebase.h" 
#include "../service/debug.h"
#include "../readers/reader-complete.h"
#include "../common/data-modifier-normaliser.h"
#include "../common/error-RMSE.h"
#include "../common/error-MAE.h"
#include "../common/number.h" 
#include "../common/result.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/clock.h"
#include "../auxiliary/roc.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/directory.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"

ksi::neuro_fuzzy_system::neuro_fuzzy_system(int nRules, 
                                            double dbFrobeniusEpsilon, 
                                            int nTuningIterations, 
                                            const double dbMinimalTypicality)
{
    _nRules = nRules;
    _dbFrobeniusEpsilon = dbFrobeniusEpsilon;
    _nTuningIterations = nTuningIterations;
    _minimal_typicality = dbMinimalTypicality;
    _pModyfikator = nullptr;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const ksi::partitioner& p)
{
//      debug(__func__);
    _pPartitioner = p.clone();
    _pModyfikator = nullptr;
//      debug(_pPartitioner);
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const ksi::partitioner& p, 
                                            const ksi::data_modifier & d)
: neuro_fuzzy_system (p)
{
    _pModyfikator = std::shared_ptr<ksi::data_modifier> (d.clone());
}



ksi::neuro_fuzzy_system::neuro_fuzzy_system(int nRules, 
                                            int nClusteringIterations, 
                                            int nTuningIterations)
{
//     debug(__LINE__);
    _nRules = nRules;
    _nClusteringIterations = nClusteringIterations;
    _nTuningIterations = nTuningIterations;
    _pModyfikator = nullptr;
}

 
void ksi::neuro_fuzzy_system::elaborate_answers_for_regression (
    const std::string & trainDataFile,
    const std::string & outputFile,
    const bool bNormalisation
    )
{
   try 
   {
      if (not _pRulebase)
          throw std::string {"no fuzzy rule base"};
       
      ksi::reader_complete czytacz;
      auto zbiorTrain = czytacz.read(trainDataFile); 
      
      if (bNormalisation)
      {
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(zbiorTrain); 
      }
      
      auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
      std::size_t nXtrain = zbiorTrain.getNumberOfData();
      std::vector<double> wYtrainExpected, wYtrainElaborated;
      
      if (not _pRulebase->validate())
          throw std::string ("rule base not valid");
   
      for (std::size_t i = 0; i < nXtrain; i++)
      {
         wYtrainExpected.push_back(XYtrain.second.get(i, 0));
         wYtrainElaborated.push_back(elaborate_answer(*(XYtrain.first.getDatum(i))).getValue());
      }
         
      ksi::error_RMSE rmse; 
      double blad_rmse_train = rmse.getError(wYtrainElaborated, wYtrainExpected);
      ksi::error_MAE mae;
      double blad_mae_train  = mae.getError(wYtrainElaborated, wYtrainExpected);
      
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << _description_of_neuro_fuzzy_system << std::endl;

      model << "answers of a fuzzy system" << std::endl;
      model << "data file: " << trainDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
      
      
      model << "RMSE: " << blad_rmse_train << std::endl;
      model << "MAE:  " << blad_mae_train << std::endl;
      
      
      model << std::endl << std::endl;      
      model << "fuzzy rule base" << std::endl;       
      
      printRulebase (model);
      
      model << std::endl << std::endl << std::endl;      
      model << "data" << std::endl;
      model << "excepted\telaborated" << std::endl;
      model << "===========================" << std::endl;
      for (std::size_t i = 0; i < nXtrain; i++)
         model << wYtrainExpected[i] << '\t' << wYtrainElaborated[i] << std::endl;
      
      
      model.close();
   }
   CATCH;
}

void ksi::neuro_fuzzy_system::set_rulebase(const ksi::rulebase & rb)
{
    if (_pRulebase)
        delete _pRulebase;
    _pRulebase = rb.clone();
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system (int nRules, 
                                             int nClusteringIterations, 
                                             int nTuningIterations, 
                                             const ksi::dataset & TrainDataset,
                                             const ksi::t_norm  * pTnorm 
                                            )
{
   _nRules = nRules;
   _nClusteringIterations = nClusteringIterations;
   _nTuningIterations = nTuningIterations;
   _TrainDataset = TrainDataset;
   _pTnorm = pTnorm ? pTnorm->clone() : nullptr;
   _pRulebase = nullptr;
   _pModyfikator = nullptr;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const int nRules, 
                                            const int nClusteringIterations, 
                                            const int nTuningIterations, 
                                            const double dbLearingCoefficient, 
                                            const bool bNormalisation, 
                                            const ksi::t_norm& tnorma)
: _nRules(nRules),
  _nClusteringIterations(nClusteringIterations),
  _nTuningIterations (nTuningIterations),
  _dbLearningCoefficient (dbLearingCoefficient),
  _bNormalisation (bNormalisation)
{
  _pTnorm = tnorma.clone();
//   debug(_pTnorm);
}


ksi::neuro_fuzzy_system::neuro_fuzzy_system(const std::string & trainDataFile, 
                                            const std::string & testDataFile, 
                                            const std::string & resultsFile,
                                            const ksi::partitioner & p
                                           )
{
    _train_data_file = trainDataFile;
    _test_data_file = testDataFile;
    _output_file = resultsFile;
    _pPartitioner = p.clone();
    _pModyfikator = nullptr;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const std::string & trainDataFile, 
                                            const std::string & testDataFile, 
                                            const std::string & resultsFile)
{
    _train_data_file = trainDataFile;
    _test_data_file = testDataFile;
    _output_file = resultsFile;
    _pPartitioner = nullptr;
    _pModyfikator = nullptr;
}


ksi::neuro_fuzzy_system::neuro_fuzzy_system(const std::string & trainDataFile, 
                                            const std::string & testDataFile, 
                                            const std::string & resultsFile, 
                                            const ksi::partitioner & p, 
                                            const ksi::data_modifier & modifier)
: neuro_fuzzy_system(trainDataFile, testDataFile, resultsFile, p)
{
     _pModyfikator = std::shared_ptr<ksi::data_modifier> (modifier.clone());
     
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const ksi::data_modifier& modifier)
{
     _pModyfikator = std::shared_ptr<ksi::data_modifier> (modifier.clone());
}



ksi::neuro_fuzzy_system::neuro_fuzzy_system(
    const std::string& trainDataFile, 
    const std::string& testDataFile, 
    const std::string& resultsFile, 
    const ksi::partitioner& p, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation)
 : neuro_fuzzy_system (trainDataFile, testDataFile, resultsFile, p)
{
    _nRules = nNumberOfRules;
    _nClusteringIterations = nNumberOfClusteringIterations;
    _nTuningIterations = nNumberofTuningIterations;
    _dbLearningCoefficient = dbLearningCoefficient;
    _bNormalisation = bNormalisation;
    _pModyfikator = nullptr;
}



std::string ksi::neuro_fuzzy_system::get_nfs_description() const
{
   return _description_of_neuro_fuzzy_system; 
}
 
std::string ksi::neuro_fuzzy_system::get_nfs_name() const
{
   return _name_of_neuro_fuzzy_system;
}

void ksi::neuro_fuzzy_system::printRulebase(std::ostream & ss)
{
    if (_pRulebase)
        _pRulebase->print(ss);
}

ksi::neuro_fuzzy_system::~neuro_fuzzy_system()
{
   delete _pTnorm;
   _pTnorm = nullptr;
   
   delete _pRulebase;
   _pRulebase = nullptr;
   
   delete _pPartitioner;
   _pPartitioner = nullptr;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system()
{
   _pTnorm = nullptr;
   _pRulebase = nullptr;
   
   _pPartitioner = nullptr;
   _pModyfikator = nullptr;
   
   _name_of_neuro_fuzzy_system = std::string("");
   _description_of_neuro_fuzzy_system = std::string ("");
   
//    debug(__FUNCTION__);
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(const ksi::neuro_fuzzy_system & wzor) : generative_model (wzor), discriminative_model (wzor)
{
   if (wzor._pTnorm)
      _pTnorm = wzor._pTnorm->clone();
   else
      _pTnorm = nullptr;
   
   _pRulebase = (wzor._pRulebase) ? wzor._pRulebase->clone() : nullptr;
   _pPartitioner = wzor._pPartitioner ? wzor._pPartitioner->clone() : nullptr;
   _pModyfikator = wzor._pModyfikator ? std::shared_ptr<ksi::data_modifier>(wzor._pModyfikator->clone()) : nullptr;
   
   
   copy_fields(wzor);
      
}

ksi::neuro_fuzzy_system & ksi::neuro_fuzzy_system::operator=(const ksi::neuro_fuzzy_system & wzor)
{
   if (this == & wzor)
      return *this;
   
   discriminative_model::operator= (wzor);
   generative_model::operator=(wzor);
   
   delete _pTnorm;
   _pTnorm = (wzor._pTnorm) ? wzor._pTnorm->clone() : nullptr;
   
   delete _pRulebase;
   _pRulebase = (wzor._pRulebase) ? wzor._pRulebase->clone() : nullptr;
   
   delete _pPartitioner;
   _pPartitioner = wzor._pPartitioner ? wzor._pPartitioner->clone() : nullptr;
   
   _pModyfikator = wzor._pModyfikator ? std::shared_ptr<ksi::data_modifier>(wzor._pModyfikator->clone()) : nullptr;
   
   copy_fields(wzor);
   
   return *this;
}

ksi::neuro_fuzzy_system::neuro_fuzzy_system(ksi::neuro_fuzzy_system&& wzor) : discriminative_model (wzor), generative_model (wzor)
{
   std::swap (_pTnorm, wzor._pTnorm);
   std::swap (_pRulebase, wzor._pRulebase);
   std::swap (_pPartitioner, wzor._pPartitioner);
   std::swap (_pModyfikator, wzor._pModyfikator);
   
   copy_fields(wzor);
}

ksi::neuro_fuzzy_system & ksi::neuro_fuzzy_system::operator=(ksi::neuro_fuzzy_system && wzor)
{
   if (this == & wzor)
      return *this;
   
   discriminative_model::operator= (wzor);
   generative_model::operator=(wzor);
   
   std::swap (_pTnorm, wzor._pTnorm);
   std::swap (_pRulebase, wzor._pRulebase); 
   std::swap (_pPartitioner, wzor._pPartitioner);
   std::swap (_pModyfikator, wzor._pModyfikator);
   
   copy_fields(wzor);
   
   return *this;
}

void ksi::neuro_fuzzy_system::copy_fields(const ksi::neuro_fuzzy_system & wzor)
{
   _nRules = wzor._nRules;
   _nClusteringIterations = wzor._nClusteringIterations;
   _dbFrobeniusEpsilon = wzor._dbFrobeniusEpsilon;
   _nTuningIterations = wzor._nTuningIterations;
   _dbLearningCoefficient = wzor._dbLearningCoefficient;
   _bNormalisation = wzor._bNormalisation;
   _TrainDataset = wzor._TrainDataset;
   _TestDataset = wzor._TestDataset;
   _name_of_neuro_fuzzy_system = wzor._name_of_neuro_fuzzy_system;
   _description_of_neuro_fuzzy_system = wzor._description_of_neuro_fuzzy_system;
   
   _train_data_file = wzor._train_data_file;
   _test_data_file = wzor._test_data_file; 
   _output_file = wzor._output_file;
   _positive_class = wzor._positive_class;
   _negative_class = wzor._negative_class;
   _threshold_type = wzor._threshold_type;
   _minimal_typicality = wzor._minimal_typicality;
   
   _original_size_of_training_dataset = wzor._original_size_of_training_dataset;
   _reduced_size_of_training_dataset = wzor._reduced_size_of_training_dataset;
}

ksi::result ksi::neuro_fuzzy_system::experiment_classification_core()
{
    return experiment_classification_core(_TrainDataset,
                                          _TestDataset,
                                          _train_data_file, 
                                          _test_data_file,
                                          _output_file,
                                          _nRules,
                                          _nClusteringIterations,
                                          _nTuningIterations,
                                          _dbLearningCoefficient,
                                          _bNormalisation,
                                          _positive_class,
                                          _negative_class,
                                          _threshold_type);
}


ksi::result ksi::neuro_fuzzy_system::experiment_classification()
{
     
    return experiment_classification(_train_data_file, 
                              _test_data_file,
                              _output_file,
                              _nRules,
                              _nClusteringIterations,
                              _nTuningIterations,
                              _dbLearningCoefficient,
                              _bNormalisation,
                              _positive_class,
                              _negative_class,
                              _threshold_type);
}

ksi::result ksi::neuro_fuzzy_system::experiment_classification(const std::string& trainDataFile, const std::string& testDataFile, const std::string& outputFile)
{
    return experiment_classification(trainDataFile, 
                              testDataFile,
                              outputFile,
                              _nRules,
                              _nClusteringIterations,
                              _nTuningIterations,
                              _dbLearningCoefficient,
                              _bNormalisation,
                              _positive_class,
                              _negative_class,
                              _threshold_type);
}


ksi::result ksi::neuro_fuzzy_system::experiment_regression()
{
    return experiment_regression(_train_data_file,
                          _test_data_file,
                          _output_file,
                          _nRules,
                          _nClusteringIterations,
                          _nTuningIterations,
                          _dbLearningCoefficient,
                          _bNormalisation);
}

ksi::result ksi::neuro_fuzzy_system::experiment_regression(const std::string& trainDataFile, const std::string& testDataFile, const std::string& outputFile)
{
    return experiment_regression(trainDataFile,
                          testDataFile,
                          outputFile,
                          _nRules,
                          _nClusteringIterations,
                          _nTuningIterations,
                          _dbLearningCoefficient,
                          _bNormalisation);
}


double ksi::neuro_fuzzy_system::elaborate_threshold_value(
    std::vector<double>& Expected, 
    std::vector<double>& Elaborated, 
    double positiveClassvalue, 
    double negativeClassvalue, 
    const ksi::roc_threshold & type)
{
    roc ROC;
    auto progi = ROC.calculate_ROC_points(Expected, Elaborated, positiveClassvalue, negativeClassvalue);
    
    switch (type)
    {
      case ksi::roc_threshold::mean:
         _threshold_value = (positiveClassvalue + negativeClassvalue) / 2.0;
         break;
      case ksi::roc_threshold::minimal_distance:
         _threshold_value = progi.Minimal_distance_threshold;
         break;
      case ksi::roc_threshold::youden:
         _threshold_value = progi.Youden_threshold;
    }
    
    return _threshold_value;
}


std::pair<double, double> ksi::neuro_fuzzy_system::answer_classification(const ksi::datum& item) const
{
    auto numeric = answer(item);
    auto Class   = numeric > _threshold_value ? _positive_class : _negative_class;

    return {numeric, Class};
}


ksi::result ksi::neuro_fuzzy_system::experiment_classification_core(
    const ksi::dataset& trainDataset, 
    const ksi::dataset& testDataset, 
    const std::string & trainDataFile,
    const std::string & testDataFile,
    const std::string& outputFile, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation, 
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold threshold_type)
{
   _TrainDataset =  trainDataset;
   _TestDataset  =  testDataset;
   
   ksi::result wynik;
   
   _train_data_file = trainDataFile;
   _test_data_file  = testDataFile;
   _nRules = nNumberOfRules;
   _dbLearningCoefficient = dbLearningCoefficient;
   _bNormalisation = bNormalisation;

   if (_bNormalisation)
   {
      ksi::data_modifier_normaliser normaliser;
      normaliser.modify(_TrainDataset);
      normaliser.modify(_TestDataset);   
   }
   
   if (_pModyfikator)
       _pModyfikator->modify(_TrainDataset);
   
   ksi::clock zegar;
   zegar.start();
   createFuzzyRulebase(nNumberOfClusteringIterations,
                       nNumberofTuningIterations, dbLearningCoefficient,
                       _TrainDataset);
   zegar.stop();

   if (_pRulebase)
   {
        if (not _pRulebase->validate())
            throw std::string ("rule base not valid");   
   }
/*
   auto XYtest  = _TestDataset.splitDataSetVertically(_TestDataset.getNumberOfAttributes() - 1);
   auto XYtrain = _TrainDataset.splitDataSetVertically(_TrainDataset.getNumberOfAttributes() - 1);
   std::size_t nXtest  = _TestDataset.getNumberOfData();
   std::size_t nXtrain = _TrainDataset.getNumberOfData();
   */

   /*
   for (std::size_t i = 0; i < nXtest; i++)
   {
       wYtestExpected.push_back(XYtest.second.get(i, 0));
       wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
   }
   */
   
   ksi::directory::create_directory_for_file(outputFile);      
   std::ofstream model (outputFile);
   if (not model)
   {
       std::stringstream ss;
       ss << "I cannot open \"" << outputFile << "\" file!";
       
       throw ss.str();
   }
   
   std::vector<double> wYtestExpected,  wYtestElaboratedClass,  wYtestElaboratedNumeric,
                       wYtrainExpected, wYtrainElaboratedClass, wYtrainElaboratedNumeric;
   
   get_answers_for_train_classification();
   for (const auto answer : _answers_for_train)
   {
       double expected, el_numeric;
       std::tie(expected, el_numeric, std::ignore) = answer;
       wYtrainExpected.push_back(expected);
       wYtrainElaboratedNumeric.push_back(el_numeric);       
   }
   
   model << classification_intro() << std::endl;
   model << "classification threshold type: " << ksi::to_string(threshold_type) << std::endl;
   _threshold_value = elaborate_threshold_value (wYtrainExpected, wYtrainElaboratedNumeric, 
                                         dbPositiveClass, dbNegativeClass,
                                         threshold_type);
   
/*   
   auto progi = ROC.calculate_ROC_points(wYtrainExpected, wYtrainElaborated, 
                                         dbPositiveClass, dbNegativeClass);
   
   
   switch (threshold_type)
   {
      case ksi::roc_threshold::mean:
         _threshold_value = (dbPositiveClass + dbNegativeClass) / 2.0;
//         model << " mean of (+) and (-) labels";
         break;
      case ksi::roc_threshold::minimal_distance:
         _threshold_value = progi.Minimal_distance_threshold;
//          model << " minimal distance";
         break;
      case ksi::roc_threshold::youden:
         _threshold_value = progi.Youden_threshold;
//          model << " Youden";
   }
   model << std::endl;
  */


   
   wYtrainElaboratedClass.clear();
   wYtrainElaboratedNumeric.clear();
   wYtrainExpected.clear();
   
   get_answers_for_train_classification();
   for (const auto answer : _answers_for_train)
   {
       double expected, el_numeric, el_class;
       std::tie(expected, el_numeric, el_class) = answer;
       wYtrainExpected.push_back(expected);
       wYtrainElaboratedNumeric.push_back(el_numeric); 
       wYtrainElaboratedClass.push_back(el_class);
   }
   
   wYtestElaboratedClass.clear();
   wYtestElaboratedNumeric.clear();
   wYtestExpected.clear();
   
   get_answers_for_test_classification();
   for (const auto answer : _answers_for_test)
   {
       double expected, el_numeric, el_class;
       std::tie(expected, el_numeric, el_class) = answer;
       wYtestExpected.push_back(expected);
       wYtestElaboratedNumeric.push_back(el_numeric);       
       wYtestElaboratedClass.push_back(el_class);
   }
    
    
    /*
   for (std::size_t i = 0; i < nXtest; i++)
   {
       auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtest.first.getDatum(i)));
       wYtestExpected.push_back(XYtest.second.get(i, 0));
//        wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
       wYtestElaboratedClass.push_back(elaborated_class);
       wYtestElaboratedNumeric.push_back (elaborated_numeric);
   }
   
   for (std::size_t i = 0; i < nXtrain; i++)
   {
       auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtrain.first.getDatum(i)));
       wYtrainExpected.push_back(XYtrain.second.get(i, 0));
//        wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
       wYtrainElaboratedClass.push_back(elaborated_class);
       wYtrainElaboratedNumeric.push_back (elaborated_numeric);
   }
   */

   model << get_classification_threshold_value();
   
   model << "fuzzy rule base creation time: ";
   if (zegar.elapsed_seconds() > 10)
       model << zegar.elapsed_seconds() << " [s]";
   else 
       model << zegar.elapsed_milliseconds() << " [ms]";
   model << std::endl;

   ///////////////// confusion matrices 
   confusion_matrix con_test;
   int TP {0}, TN {0}, FP {0}, FN {0};
   
   model << std::endl;
   model << "confusion matrix for test data" << std::endl;
   con_test.calculate_statistics(wYtestExpected, wYtestElaboratedClass,
                                 dbPositiveClass, dbNegativeClass,
                                 TP, TN, FP, FN);
   
   wynik.TestPositive2Positive = TP;
   wynik.TestPositive2Negative = FN;
   wynik.TestNegative2Negative = TN;
   wynik.TestNegative2Positive = FP;
   
   model << con_test.print(TP, TN, FP, FN);
   model << std::endl;
   
   //----------------
   model << std::endl;
   model << "confusion matrix for train data" << std::endl;
   con_test.calculate_statistics(wYtrainExpected, wYtrainElaboratedClass,
                                 dbPositiveClass, dbNegativeClass,
                                 TP, TN, FP, FN);
   wynik.TrainPositive2Positive = TP;
   wynik.TrainPositive2Negative = FN;
   wynik.TrainNegative2Negative = TN;
   wynik.TrainNegative2Positive = FP;
   
   
   model << con_test.print(TP, TN, FP, FN);
   model << std::endl;
   
   ///////////////////////
   
   model << std::endl << std::endl;      
   model << "fuzzy rule base" << std::endl;       
     
   printRulebase (model);
   
   model << std::endl << std::endl;      
   model << "answers for the train set" << std::endl;
   model << "expected\telaborated_numeric\telaborated_class" << std::endl;
   
   for (const auto answer : _answers_for_train)
   {
       double expected, el_numeric, el_class;
       std::tie(expected, el_numeric, el_class) = answer;
       model << expected << "   " << el_numeric <<  "  " << el_class <<  std::endl;
   }
   
   /*
   for (std::size_t i = 0; i < nXtest; i++)
   {
       double expected =  wYtrainExpected[i];
       double elaborated_numeric = wYtrainElaboratedNumeric[i];
       double elaborated_class   = wYtrainElaboratedClass[i];
       model << expected << "   " << elaborated_numeric <<  "  " << elaborated_class <<  std::endl;
       _answers_for_train.push_back({expected, elaborated_numeric, elaborated_class});
       
   }
   */
   
   model << std::endl << std::endl;      
   model << "answers for the test set" << std::endl;
   model << "expected\telaborated_numeric\telaborated_class" << std::endl;
   
   for (const auto answer : _answers_for_test)
   {
       double expected, el_numeric, el_class;
       std::tie(expected, el_numeric, el_class) = answer;
       model << expected << "   " << el_numeric <<  "  " << el_class <<  std::endl;
   }
   
   /*
   for (std::size_t i = 0; i < nXtest; i++)
   {
       double expected =  wYtestExpected[i];
       double elaborated_numeric = wYtestElaboratedNumeric[i];
       double elaborated_class   = wYtestElaboratedClass[i];
       model << expected << "   " << elaborated_numeric <<  "  " << elaborated_class <<  std::endl;
       _answers_for_test.push_back({expected, elaborated_numeric, elaborated_class});
       
   }
   */
   model.close();
   return wynik;
}


ksi::result ksi::neuro_fuzzy_system::experiment_classification (
                                  const std::string & trainDataFile,
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
    try 
    {
        ksi::reader_complete czytacz;
        auto zbiorTrain = czytacz.read(trainDataFile);
        auto zbiorTest  = czytacz.read(testDataFile);
        
        return experiment_classification_core(zbiorTrain, zbiorTest, trainDataFile, testDataFile, outputFile, nNumberOfRules, nNumberOfClusteringIterations, nNumberofTuningIterations, dbLearningCoefficient, bNormalisation, dbPositiveClass, dbNegativeClass, threshold_type);
    }
    CATCH;
}
 
 
std::string ksi::neuro_fuzzy_system::extra_report() const
{
    return std::string();
}
 
 
ksi::result ksi::neuro_fuzzy_system::experiment_regression(const std::string & trainDataFile, 
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
       
      ksi::result experiment_results;
      ksi::reader_complete czytacz;
      auto zbiorTrain = czytacz.read(trainDataFile);
      auto zbiorTest  = czytacz.read(testDataFile);
            
      if (bNormalisation)
      {
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(zbiorTrain);
         normaliser.modify(zbiorTest);   
      }
      
      if (_pModyfikator)
       _pModyfikator->modify(zbiorTrain);
      
      ksi::clock zegar;
      zegar.start();
      
      createFuzzyRulebase(nNumberOfClusteringIterations,
                        nNumberofTuningIterations, dbLearningCoefficient,
                        zbiorTrain);
      zegar.stop();
      
      if (not _pRulebase->validate())
          throw std::string ("rule base not valid");
      
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      auto XYtrain = zbiorTrain.splitDataSetVertically(zbiorTrain.getNumberOfAttributes() - 1);
      std::size_t nXtest  = zbiorTest.getNumberOfData();
      std::size_t nXtrain = zbiorTrain.getNumberOfData();
      
      ///////////////////////////
		std::vector<double> wYtestExpected (nXtest),  wYtestElaborated (nXtest);
      std::vector<double> wYtrainExpected(nXtrain), wYtrainElaborated(nXtrain);
     
	   #pragma omg parallel for
      for (std::size_t i = 0; i < nXtest; i++)
      {
         wYtestExpected[i] = XYtest.second.get(i, 0);
         wYtestElaborated[i] = answer(*(XYtest.first.getDatum(i)));
      }
      
	   #pragma omg parallel for
      for (std::size_t i = 0; i < nXtrain; i++)
      {
         wYtrainExpected[i] = XYtrain.second.get(i, 0);
         wYtrainElaborated[i] = answer(*(XYtrain.first.getDatum(i)));
      }
      ///////////////////////////

		ksi::error_RMSE rmse; 
      double blad_rmse_test  = rmse.getError(wYtestElaborated, wYtestExpected);
      double blad_rmse_train = rmse.getError(wYtrainElaborated, wYtrainExpected);
      ksi::error_MAE mae;
      double blad_mae_test   = mae.getError(wYtestElaborated, wYtestExpected);
      double blad_mae_train  = mae.getError(wYtrainElaborated, wYtrainExpected);
      
      experiment_results.mae_test = blad_mae_test;
      experiment_results.mae_train = blad_mae_train;
      experiment_results.rmse_test = blad_rmse_test;
      experiment_results.rmse_train = blad_rmse_train;
      
      ksi::directory::create_directory_for_file(outputFile);
      std::ofstream model (outputFile);
      if (not model)
      {
            std::stringstream ss;
            ss << "I cannot open \"" << outputFile << "\" file!";
            
            throw ss.str();
      }
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << get_nfs_description() << std::endl;
      model << get_nfs_name() << std::endl;
      
      if (nNumberOfRules > 0)
          model << "number of rules:     " << nNumberOfRules << std::endl;
      if (nNumberOfClusteringIterations > 0)
         model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
      
      if (nNumberofTuningIterations > 0)
          model << "number of tuning interations:    " << nNumberofTuningIterations << std::endl;
      
      if (dbLearningCoefficient > -1)
          model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      
      if (_pPartitioner)
          model << "partitioner: " << _pPartitioner->getAbbreviation() << std::endl;
      auto report = extra_report ();
      if (not report.empty())
          model << report << std::endl;
      
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
      if (_pModyfikator)
       model << "train data set modifier(s): " << _pModyfikator->print() << std::endl;
      
      model << "RMSE for train data: " << blad_rmse_train << std::endl;
      model << "RMSE for test data:  " << blad_rmse_test  << std::endl;
      
      model << "MAE  for train data: " << blad_mae_train << std::endl;
      model << "MAE  for test data:  " << blad_mae_test  << std::endl;
      model << "fuzzy rule base creation time: ";
      if (zegar.elapsed_seconds() > 10)
          model << zegar.elapsed_seconds() << " [s]";
      else 
          model << zegar.elapsed_milliseconds() << " [ms]";
      model << std::endl;
      model << std::endl << std::endl;      
      model << "fuzzy rule base" << std::endl;       
      printRulebase (model);
      
      _answers_for_test.clear();
      _answers_for_train.clear();
      
      model << std::endl << std::endl << std::endl;      
      model << "train data" << std::endl;
      model << "expected\telaborated" << std::endl;
      model << "===========================" << std::endl;
      ////////////
		_answers_for_train.resize(nXtrain);
      #pragma omp parallel for 
		for (std::size_t i = 0; i < nXtrain; i++)
      {
          double expected   =  wYtrainExpected[i];
          double elaborated =  wYtrainElaborated[i];
          model << expected << '\t' << elaborated << std::endl;
         _answers_for_train[i] = {expected, elaborated, elaborated};
      }
      //////////////
      model << std::endl << std::endl;      
      model << "test data" << std::endl;
      model << "expected\telaborated" << std::endl;
      model << "===========================" << std::endl;

		////////////////////
      _answers_for_test.resize(nXtest);
      #pragma omp parallel for 
		for (std::size_t i = 0; i < nXtest; i++)
      {
//           model << wYtestExpected[i] << '\t' << wYtestElaborated[i] << std::endl;
          
          double expected   =  wYtestExpected[i];
          double elaborated =  wYtestElaborated[i];
          model << expected << '\t' << elaborated << std::endl;
          _answers_for_test[i] = {expected, elaborated, elaborated};
      }
		/////////////////
      
      model.close();
      return experiment_results;
   }
   CATCH;
} 

ksi::datum ksi::neuro_fuzzy_system::get_random_datum(std::default_random_engine& engine)
{
    try 
    {
         throw std::string ("not implemented");        
    }
    CATCH;
}

void ksi::neuro_fuzzy_system::train_generative_model(const ksi::dataset& ds)
{
    try 
    {
        throw std::string ("not implemented");
    }
    CATCH;
}

std::string ksi::neuro_fuzzy_system::to_string()
{
    std::stringstream ss;
    printRulebase(ss);
    
    return ss.str();
}

double ksi::neuro_fuzzy_system::elaborate_rmse_for_dataset(const ksi::dataset& ds)
{
    auto split = ds.cufOffLastAttribute();
    auto train_data = split.first;
    auto train_decision = split.second;
    auto train_size = train_data.getNumberOfData();
    auto decision_matrix = train_decision.getMatrix();
    
	 //////////////////
	 std::vector<double> elaborated(train_size), expected(train_size);
    #pragma omp parallel for 
    for (std::size_t i = 0; i < train_size; i++)
    {
        expected[i] = decision_matrix[i][0];
        elaborated[i] = answer(*(train_data.getDatum(i)));
    }
    //////////////////
    ksi::error_RMSE errator;
    
    return errator.getError(expected, elaborated);
}


void ksi::neuro_fuzzy_system::set_test_dataset(const ksi::dataset& ds)
{
    _TestDataset = ds;
}

void ksi::neuro_fuzzy_system::set_train_dataset(const ksi::dataset& ds)
{
    _TrainDataset = ds;
}

void ksi::neuro_fuzzy_system::createFuzzyRulebase(const ksi::dataset& train, const ksi::dataset& test)
{
    createFuzzyRulebase(_nClusteringIterations, _nTuningIterations, _dbLearningCoefficient, train);
}

std::vector<std::tuple<double, double, double> > ksi::neuro_fuzzy_system::get_answers_for_train_classification()
{
   _answers_for_train.clear();

   auto XYtrain  = _TrainDataset.splitDataSetVertically(_TrainDataset.getNumberOfAttributes() - 1);
   std::size_t nXtrain  = _TrainDataset.getNumberOfData();

   _answers_for_train.resize(nXtrain);
#pragma omp parallel for 
   for (std::size_t i = 0; i < nXtrain; i++)
   {
       auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtrain.first.getDatum(i)));
       auto expected = XYtrain.second.get(i, 0);

//        _answers_for_train.push_back({expected, elaborated_numeric, elaborated_class});
       _answers_for_train[i] = {expected, elaborated_numeric, elaborated_class}; 
   }
	
   return _answers_for_train;
}

std::vector<std::tuple<double, double, double> > ksi::neuro_fuzzy_system::get_answers_for_test_classification() 
{
   _answers_for_test.clear(); 

   auto XYtest  = _TestDataset.splitDataSetVertically(_TestDataset.getNumberOfAttributes() - 1);
   std::size_t nXtest  = _TestDataset.getNumberOfData();

   _answers_for_test.resize(nXtest);
   #pragma omp parallel for 
   for (std::size_t i = 0; i < nXtest; i++)
   {
       auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtest.first.getDatum(i)));
       auto expected = XYtest.second.get(i, 0);

       // _answers_for_test.push_back({expected, elaborated_numeric, elaborated_class});
       _answers_for_test[i] = {expected, elaborated_numeric, elaborated_class}; 
   }

   return _answers_for_test;
}

double ksi::neuro_fuzzy_system::get_threshold_value() const
{
    return _threshold_value;
}

ksi::roc_threshold ksi::neuro_fuzzy_system::get_threshold_type() const
{
    return _threshold_type;
}


void ksi::neuro_fuzzy_system::set_train_data_file(const std::string& file)
{
    _train_data_file = file;
}

void ksi::neuro_fuzzy_system::set_test_data_file(const std::string& file)
{
    _test_data_file = file;
}

void ksi::neuro_fuzzy_system::set_output_file(const std::string& file)
{
    _output_file = file;
}

std::string ksi::neuro_fuzzy_system::get_classification_threshold_value() const
{
    std::stringstream ss;
    ss << "threshold value: " << _threshold_value << std::endl;
    return ss.str();
}


std::string ksi::neuro_fuzzy_system::classification_intro() const
{
    try 
    {
        std::stringstream model;
        
        model << "EXPERIMENT" << std::endl;
        model << "==========" << std::endl;
        model << getDateTimeNow() << std::endl;
        model << std::endl;
        model << get_nfs_description() << std::endl;
        model << get_nfs_name() << std::endl;
        
        model << "number of rules:     " << _nRules << std::endl;
        model << "number of clustering iterations: " << _nClusteringIterations << std::endl;
        model << "number of tuning interations:    " << _nTuningIterations << std::endl;
        model << "learning coefficient: " << _dbLearningCoefficient << std::endl;
        model << "train data file: " << _train_data_file << std::endl;
        model << "test  data file: " << _test_data_file << std::endl;
        model << "normalisation:   " << std::boolalpha << _bNormalisation << std::endl;
        if (_pModyfikator)
            model << "train data set modifier(s): " << _pModyfikator->print() << std::endl;
        
        auto report = extra_report ();
            if (not report.empty())
                model << report << std::endl;
            
        return model.str();   
    }
    CATCH;
}
