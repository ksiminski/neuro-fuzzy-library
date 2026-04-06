
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric>
#include <cmath>
#include <map>

#include "../service/debug.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/granular_nfs.h"
#include "../neuro-fuzzy/granular_nfs_classification.h"
#include "../granules/granule.h" 
#include "../granules/set_of_cooperating_granules.h"
#include "../granules/set_of_granules.h"
#include "../granules/set_of_standalone_granules.h"
#include "../granules/data_item.h"
#include "../readers/reader-complete.h"
#include "../readers/reader-complete-by-parts.h"
#include "../common/data-modifier-normaliser.h"
#include "../auxiliary/tempus.h"
#include "../auxiliary/clock.h"
#include "../auxiliary/roc.h"
#include "../auxiliary/directory.h"
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/error-RMSE.h"
#include "../auxiliary/error-MAE.h"


void ksi::granular_nfs_classification::copy_fields(const ksi::granular_nfs_classification & wzor)
{
     
    threshold_value = wzor.threshold_value;
}

void ksi::granular_nfs_classification::swap_fields(ksi::granular_nfs_classification & wzor)
{
     
    std::swap(threshold_value, wzor.threshold_value);
}



ksi::granular_nfs_classification::granular_nfs_classification (
    const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate,
    const double dbPositiveClass, 
    const double dbNegativeClass, 
    ksi::roc_threshold roc_threshold_type)
   :
    ksi::granular_nfs (number_of_data_to_read, 
                     minimal_number_of_granules_in_set, 
                     maximal_number_of_granules_in_set, 
                     number_of_data_to_generate)
{
     
    threshold_value = (dbPositiveClass + dbNegativeClass) / 2.0; // default: mean
}

ksi::granular_nfs_classification::~granular_nfs_classification ()
{
   // delete what is to delete

}

ksi::granular_nfs_classification::granular_nfs_classification (const ksi::granular_nfs_classification & wzor) : ksi::granular_nfs (wzor)
{
   // copy what is to copy
   copy_fields(wzor);
}

ksi::granular_nfs_classification & ksi::granular_nfs_classification::operator= (const ksi::granular_nfs_classification & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs::operator=(wzor);

   copy_fields(wzor);
   
   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_nfs_classification::granular_nfs_classification (ksi::granular_nfs_classification && wzor) : ksi::granular_nfs (wzor)
{
    // swap what is to swap
    swap_fields(wzor);
}

ksi::granular_nfs_classification & ksi::granular_nfs_classification::operator= (ksi::granular_nfs_classification && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs::operator=(wzor);

   // swap what is to swap
   swap_fields(wzor);

   return *this;
}


ksi::result ksi::granular_nfs_classification::experiment_regression(const std::string &, const std::string &, const std::string &, const int, const int, const int, const double, const bool)
{
    try 
    {
        throw ksi::exception ("The method is not implemented and will not be implemented, because the class is responsible for classification and not for regression.");
    }
    CATCH;
}



ksi::result ksi::granular_nfs_classification::experiment_classification(
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
    ksi::roc_threshold threshold_type)
{
   try 
   {
      
      ksi::clock zegar;
      zegar.start();
      createFuzzyRulebaseHierarchical(trainDataFile, nNumberOfRules,
                                      nNumberOfClusteringIterations,
                                      nNumberofTuningIterations,
                                      dbLearningCoefficient, bNormalisation); 
      zegar.stop(); 
       
      ksi::reader_complete czytacz;
      auto zbiorTest  = czytacz.read(testDataFile);
      
      if (bNormalisation)
      {
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(zbiorTest);   
      }
      
      if (not _pRulebase->validate())
          throw std::string ("rule base not valid");      
      
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      std::size_t nXtest  = zbiorTest.getNumberOfData();
      std::vector<double> wYtestExpected,  wYtestElaborated;
      for (std::size_t i = 0; i < nXtest; i++)
      {
         wYtestExpected.push_back(XYtest.second.get(i, 0));
         wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
      }
      
      ksi::directory::create_directory_for_file(outputFile);
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << _description_of_neuro_fuzzy_system << std::endl;
      
      model << "number of rules:     " << nNumberOfRules << std::endl;
      model << "number of clustering iterations: " << nNumberOfClusteringIterations << std::endl;
      model << "number of tuning interations:    " << nNumberofTuningIterations << std::endl;
      model << "number of data read in one part:   " << NUMBER_OF_DATA_TO_READ << std::endl;
      model << "minimal number of granules in set: " << MINIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "maximal number of granules in set: " << MAXIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
      
      model << "classification threshold type: ";
      roc ROC;
      
      double prog;
      switch (threshold_type)
      {
          default:
          case ksi::roc_threshold::mean:
            prog = (dbPositiveClass + dbNegativeClass) / 2.0;
            model << " mean of (+) and (-) labels";
            break;
          case ksi::roc_threshold::youden:
              model << " Youden";
              prog = threshold_value;
              break;
          case ksi::roc_threshold::minimal_distance:
              model << " minimal distance";
              prog = threshold_value;
              break;
      }
      
      
      model << std::endl;
      model << "threshold value: " << prog << std::endl;
      
      model << "fuzzy rule base creation time: ";
      if (zegar.elapsed_seconds() > 0)
          model << zegar.elapsed_seconds() << " [s]";
      else 
          model << zegar.elapsed_milliseconds() << " [ms]";
      model << std::endl;

      ///////////////// confusion matrices 
      ksi::confusion_matrix con_test;
      int TP, TN, FP, FN;
      
      
      model << std::endl;
      model << "confusion matrix for test data" << std::endl;
      con_test.calculate_statistics(wYtestExpected, wYtestElaborated,
                                    dbPositiveClass, dbNegativeClass,
                                    TP, TN, FP, FN, prog);
      
      ksi::result final_result;
      final_result.TestNegative2Negative = TN;
      final_result.TestPositive2Negative = FN;
      final_result.TestPositive2Positive = TP;
      final_result.TestNegative2Positive = FP;
      
      model << con_test.print(TP, TN, FP, FN);
      model << std::endl;
      
      //----------------
      model << std::endl;
      
      ///////////////////////
      
      model << std::endl << std::endl;      
      model << "fuzzy rule base" << std::endl;       
      
      printRulebase (model);
      
      model << std::endl << std::endl;      
      model << "answers for the test set" << std::endl;
      model << "expected\telaborated" << std::endl;
      for (std::size_t i = 0; i < nXtest; i++)
         model << wYtestExpected[i] << "   " << wYtestElaborated[i] << "  " << (wYtestElaborated[i] > prog ? dbPositiveClass : dbNegativeClass) << std::endl;
      
      
      model.close();
      return final_result;
   }
   CATCH;
}  

void ksi::granular_nfs_classification::createFuzzyRulebase(  
    int nClusteringIterations, 
    int nTuningIterations, 
    double dbLearningCoefficient, 
    const ksi::set_of_granules & train_granules,
    const ksi::set_of_granules & validation_granules)
{
   try 
   {   
       // first prepare date:
       int number_of_items = NUMBER_OF_DATA_TO_GENERATE > train_granules.size() ? NUMBER_OF_DATA_TO_GENERATE : train_granules.size();
       
       auto train = generate_dataset_from_granules(train_granules, number_of_items); 
       auto validate = generate_dataset_from_granules(validation_granules, number_of_items); 
       
       // then elaborate fuzzy rule base for the data:
       createFuzzyNonGranularRulebase(nClusteringIterations, 
           nTuningIterations, dbLearningCoefficient, train, validate);
       
       auto nRules = _pRulebase->getNumberOfRules();
            
       int nDataItem = train.getNumberOfData();
       
       std::vector<double> trainExpected, trainElaborated;
       trainExpected.reserve(nDataItem);
       trainElaborated.reserve(nDataItem);
       
       // jeszcze dla kazdej reguly trzeba wyznaczyc jej kardynalnosc
       for (std::size_t i = 0; i < nRules; i++)
       {
           ksi::rule & r = _pRulebase->operator[](i);
           double card = 0.0;
           double errors = 0.0;
           
           for (int i = 0; i < nDataItem; i++)
           {
               auto X = train.getDatum(i)->getVector();
               auto Y = train.getDatum(i)->getDecision();
               auto y = Y->getValue();
               X.pop_back();
               auto odp = r.getAnswerLocalisationWeight(X);
               double elaborated = odp.first;
               double weight     = odp.second;
               double diff = elaborated - Y->getValue();
               errors += weight * diff * diff;
               card += weight;
               
               trainExpected.push_back(y);
               trainElaborated.push_back(elaborated);
           }
           r.set_cardinality(card);
           r.set_error (sqrt (errors / card));
       }
       
       if (_threshold_type != ksi::roc_threshold::mean)
       {
            ksi::roc ROC;
            
            auto results = ROC.calculate_ROC_points(trainExpected, trainElaborated, 
                _positive_class, _negative_class);
            switch(_threshold_type)
            {
                case ksi::roc_threshold::youden:
                    threshold_value = results.Youden_threshold;
                    break;
                case ksi::roc_threshold::minimal_distance:
                    threshold_value = results.Minimal_distance_threshold;
                    break;
                default: 
                    break;
            }
       }
    }
    CATCH;    
}





ksi::dataset ksi::granular_nfs_classification::generate_dataset_from_granules(const ksi::set_of_granules & granules, const int NUMBER_OF_TRAIN_DATA)
{
    try 
    {
        // This quite a long piece of code aims at elaboration of 
        // numbers of data items to generate from data granules
        // with use of their cardinalities
        
        std::size_t number_of_granules = granules.size();
        if (number_of_granules == 0)
            throw ksi::exception ("empty set of granules");
        
        ksi::dataset train;
        
        ksi::set_of_granules * pGranules = granules.clone_set_of_granules();
        elaborate_quality_of_rules(*pGranules); ///@todo Czy to jest poprawne w przypadku klasyfikacji?
        
        std::vector<double> weighted_cardinalities;
        
        for (std::size_t i = 0; i < pGranules->size(); i++)
            weighted_cardinalities.push_back(pGranules->getGranule(i)->get_quality());

        double total_weighted_cardinality = std::accumulate(weighted_cardinalities.begin(), weighted_cardinalities.end(), 0.0);

        if (total_weighted_cardinality < 1)
        {
            auto nGranules = weighted_cardinalities.size();
            for (auto & card : weighted_cardinalities)
               card = ((double) NUMBER_OF_TRAIN_DATA / nGranules);
        }
        else
        {
            for (auto & card : weighted_cardinalities)
                card *= ((double) NUMBER_OF_TRAIN_DATA / total_weighted_cardinality);
        }
        
        std::vector<int> integer_cardinalities;
        for (auto & card : weighted_cardinalities)
            integer_cardinalities.push_back((int) card);
        
        double total_integer_cardinality = std::accumulate(
            integer_cardinalities.begin(),
            integer_cardinalities.end(), 0);
        
        int diff = NUMBER_OF_TRAIN_DATA - total_integer_cardinality;
        
        for (int i = 0; i < diff; i++)
            integer_cardinalities[i % number_of_granules]++;
        
        // creation of data examples
        for (int g = 0; g < number_of_granules; g++)
        {
            int max_card = integer_cardinalities[g];
            for (int card = 0; card < max_card; card++)
            {
                ksi::granule * p = (pGranules->getGranule(g))->clone_granule();
                auto d = p->get_data_item();
                double answer = pGranules->get_answer(d, p).getValue();
                delete p;
                
                answer = answer > threshold_value ? _positive_class : _negative_class;
      
                d.push_back(answer); // decision attribute  
                d.setDecision(answer); // decision attribute
                train.addDatum(d);
            }
        }
        
        delete pGranules;
        
        return train;
    }
    CATCH;    
}
