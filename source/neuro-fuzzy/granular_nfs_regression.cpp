
#include <numeric>
#include <vector>
#include <string>

#include "../service/debug.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/granular_nfs.h"
#include "../neuro-fuzzy/granular_nfs_regression.h"
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



ksi::granular_nfs_regression::granular_nfs_regression (
    const int number_of_data_to_read,
    const int minimal_number_of_granules_in_set,
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate
) 
: ksi::granular_nfs (number_of_data_to_read, 
                     minimal_number_of_granules_in_set, 
                     maximal_number_of_granules_in_set, 
                     number_of_data_to_generate)
{
//       debug(_pPartitioner); 
}


ksi::granular_nfs_regression::granular_nfs_regression(
    const int number_of_data_to_read, 
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set, 
    const int number_of_data_to_generate, 
    const ksi::partitioner& partitioner) 
  : 
    granular_nfs_regression  (number_of_data_to_read,
                              minimal_number_of_granules_in_set,
                              maximal_number_of_granules_in_set,
                              number_of_data_to_generate)
{
    _pPartitioner = partitioner.clone();
     debug(_pPartitioner); 
}


ksi::granular_nfs_regression::~granular_nfs_regression ()
{
   // delete what is to delete

}

ksi::granular_nfs_regression::granular_nfs_regression (const ksi::granular_nfs_regression & wzor) : ksi::granular_nfs (wzor)
{
   // copy what is to copy

}

ksi::granular_nfs_regression & ksi::granular_nfs_regression::operator= (const ksi::granular_nfs_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_nfs_regression::granular_nfs_regression (ksi::granular_nfs_regression && wzor) : ksi::granular_nfs (wzor)
{
   // swap what is to swap

}

ksi::granular_nfs_regression & ksi::granular_nfs_regression::operator= (ksi::granular_nfs_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::granular_nfs::operator=(wzor);

   // swap what is to swap

   return *this;
}


ksi::dataset ksi::granular_nfs_regression::generate_dataset_from_granules(
    const ksi::set_of_granules & granules, 
    const int NUMBER_OF_TRAIN_DATA)
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
        elaborate_quality_of_rules(*pGranules);
        
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

ksi::result ksi::granular_nfs_regression::experiment_regression(
    const std::string & trainDataFile, 
    const std::string & testDataFile, 
    const std::string & outputFile, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation)
{
   try 
   {
      ksi::clock zegar;
 
      zegar.start();
//       createFuzzyRulebaseHierarchical(trainDataFile, nNumberOfRules,
//                                       nNumberOfClusteringIterations,
//                                       nNumberofTuningIterations,
//                                       dbLearningCoefficient, bNormalisation);

      createFuzzyRulebaseByParts(trainDataFile, 
                                 nNumberOfRules,
                                 nNumberOfClusteringIterations,
                                 nNumberofTuningIterations,
                                 dbLearningCoefficient, 
                                 bNormalisation);
      
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
      std::size_t nXtest = zbiorTest.getNumberOfData();
      std::vector<double> wYtestExpected,  wYtestElaborated,
                        wYtrainExpected, wYtrainElaborated;                        
                        
      for (std::size_t i = 0; i < nXtest; i++)
      {
         wYtestExpected.push_back(XYtest.second.get(i, 0));
         wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
      }      
         
      ksi::error_RMSE rmse; 
      double blad_rmse_test  = rmse.getError(wYtestElaborated, wYtestExpected);
      ksi::error_MAE mae;
      double blad_mae_test   = mae.getError(wYtestElaborated, wYtestExpected);
      
      ksi::result wyniki;
      wyniki.rmse_test = blad_rmse_test;
      wyniki.mae_test = blad_mae_test;
      
      ksi::directory::create_directory_for_file(outputFile);
      std::ofstream model (outputFile);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << _description_of_neuro_fuzzy_system << std::endl;
      
      model << "number of rules:     " << nNumberOfRules << std::endl;
      model << "number of clustering iterations:   " << nNumberOfClusteringIterations << std::endl;
      model << "number of tuning interations:      " << nNumberofTuningIterations << std::endl;
      model << "number of data read in one part:   " << NUMBER_OF_DATA_TO_READ << std::endl;
      model << "minimal number of granules in set: " << MINIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "maximal number of granules in set: " << MAXIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "number of items to generate from a granule: " <<
      NUMBER_OF_DATA_TO_GENERATE << std::endl;
      model << "learning coefficient: " << dbLearningCoefficient << std::endl;
      model << "train data file: " << trainDataFile << std::endl;
      model << "test  data file: " << testDataFile << std::endl;
      model << "normalisation:   " << std::boolalpha << bNormalisation << std::endl;
      model << "RMSE for test data:  " << blad_rmse_test  << std::endl;
      model << "MAE  for test data:  " << blad_mae_test  << std::endl;
      model << "fuzzy rule base creation time: ";
      if (zegar.elapsed_seconds() > 0)
          model << zegar.elapsed_seconds() << " [s]";
      else 
          model << zegar.elapsed_milliseconds() << " [ms]";
      model << std::endl;
      model << std::endl << std::endl; 
      model << "fuzzy rule base" << std::endl;       
      
      printRulebase (model);
      
      model << std::endl << std::endl;      
      model << "test data" << std::endl;
      model << "expected\telaborated" << std::endl;
      model << "===========================" << std::endl;
      for (std::size_t i = 0; i < nXtest; i++)
         model << wYtestExpected[i] << '\t' << wYtestElaborated[i] << std::endl;
      
      model.close();
      
      return wyniki;
   }
   CATCH;
}

ksi::result ksi::granular_nfs_regression::experiment_regression()
{
   try 
   {
      ksi::clock zegar;
 
      zegar.start();
 

      createFuzzyRulebaseByParts(_train_data_file, 
                                 _nRules,
                                 _nClusteringIterations,
                                 _nTuningIterations,
                                 _dbLearningCoefficient, 
                                 _bNormalisation);
      
      zegar.stop();
      ksi::reader_complete czytacz;
      auto zbiorTest  = czytacz.read(_test_data_file);
      
      if (_bNormalisation)
      {
         ksi::data_modifier_normaliser normaliser;
         normaliser.modify(zbiorTest);   
      }
      if (not _pRulebase->validate())
          throw std::string ("rule base not valid");
      
      auto XYtest  = zbiorTest.splitDataSetVertically(zbiorTest.getNumberOfAttributes() - 1);
      std::size_t nXtest = zbiorTest.getNumberOfData();
      std::vector<double> wYtestExpected,  wYtestElaborated,
                        wYtrainExpected, wYtrainElaborated;                        
                        
      for (std::size_t i = 0; i < nXtest; i++)
      {
         wYtestExpected.push_back(XYtest.second.get(i, 0));
         wYtestElaborated.push_back(answer(*(XYtest.first.getDatum(i))));
      }      
         
      ksi::error_RMSE rmse; 
      double blad_rmse_test  = rmse.getError(wYtestElaborated, wYtestExpected);
      ksi::error_MAE mae;
      double blad_mae_test   = mae.getError(wYtestElaborated, wYtestExpected);
      
      ksi::result wyniki;
      wyniki.rmse_test = blad_rmse_test;
      wyniki.mae_test = blad_mae_test;
      
      std::ofstream model (_output_file);
      
      model << "EXPERIMENT" << std::endl;
      model << "==========" << std::endl;
      model << getDateTimeNow() << std::endl;
      model << std::endl;
      model << _description_of_neuro_fuzzy_system << std::endl;
      
      model << "number of rules:     " << _nRules << std::endl;
      model << "number of clustering iterations:   " << _nClusteringIterations << std::endl;
      model << "number of tuning interations:      " << _nTuningIterations << std::endl;
      model << "number of data read in one part:   " << NUMBER_OF_DATA_TO_READ << std::endl;
      model << "minimal number of granules in set: " << MINIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "maximal number of granules in set: " << MAXIMAL_NUMBER_OF_GRANULES_IN_SET << std::endl;
      model << "number of items to generate from a granule: " <<
      NUMBER_OF_DATA_TO_GENERATE << std::endl;
      model << "learning coefficient: " << _dbLearningCoefficient << std::endl;
      model << "train data file: " << _train_data_file << std::endl;
      model << "test  data file: " << _test_data_file << std::endl;
      model << "normalisation:   " << std::boolalpha << _bNormalisation << std::endl;
      model << "RMSE for test data:  " << blad_rmse_test  << std::endl;
      model << "MAE  for test data:  " << blad_mae_test  << std::endl;
      model << "fuzzy rule base creation time: ";
      if (zegar.elapsed_seconds() > 0)
          model << zegar.elapsed_seconds() << " [s]";
      else 
          model << zegar.elapsed_milliseconds() << " [ms]";
      model << std::endl;
      model << std::endl << std::endl; 
      model << "fuzzy rule base" << std::endl;       
      
      printRulebase (model);
      
      model << std::endl << std::endl;      
      model << "test data" << std::endl;
      model << "expected\telaborated" << std::endl;
      model << "===========================" << std::endl;
      for (std::size_t i = 0; i < nXtest; i++)
         model << wYtestExpected[i] << '\t' << wYtestElaborated[i] << std::endl;
      
      model.close();
      
      return wyniki;
   }
   CATCH;
}



void ksi::granular_nfs_regression::createFuzzyRulebase(
    int nClusteringIterations, 
    int nTuningIterations, 
    double dbLearningCoefficient, 
    const ksi::set_of_granules & train_granules,
    const ksi::set_of_granules & validation_granules
)
{
   try 
   {   
       // first prepare date:
       int number_of_items = NUMBER_OF_DATA_TO_GENERATE > train_granules.size() ? NUMBER_OF_DATA_TO_GENERATE : train_granules.size();
       
       auto train    = generate_dataset_from_granules(train_granules, number_of_items); 
       auto validate = generate_dataset_from_granules(validation_granules, number_of_items); 
       
       // then elaborate fuzzy rule base for the data:
       createFuzzyNonGranularRulebase(nClusteringIterations, 
           nTuningIterations, dbLearningCoefficient, train, validate);
            
       int nDataItem = train.getNumberOfData();
       
       auto nRules = _pRulebase->getNumberOfRules();
       
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
               X.pop_back();
               auto odp = r.getAnswerLocalisationWeight(X);
               double elaborated = odp.first;
               double weight     = odp.second;
               double diff = elaborated - Y->getValue();
               errors += weight * diff * diff;
               card += weight;
           }
           r.set_cardinality(card);
           r.set_error (sqrt (errors / card));
       }
       
    }
    CATCH;    
}

ksi::result ksi::granular_nfs_regression::experiment_classification(
    const std::string& , const std::string& , const std::string& ,     const int , const int , const int , const double , const bool ,    const double , const double , ksi::roc_threshold )
{
    try 
    {
        throw ksi::exception ("The method is not implemented and will not be implemented, because the class is responsible for regression and not for classification.");
    }
    CATCH;
}



