
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>

#include "../service/debug.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/granular_nfs.h"
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
#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/error-RMSE.h"
#include "../auxiliary/error-MAE.h"


 


ksi::granular_nfs::granular_nfs(
    const int number_of_data_to_read, 
    const int minimal_number_of_granules_in_set, 
    const int maximal_number_of_granules_in_set,
    const int number_of_data_to_generate
                               )
{
    NUMBER_OF_DATA_TO_READ = number_of_data_to_read;
    MINIMAL_NUMBER_OF_GRANULES_IN_SET = minimal_number_of_granules_in_set;
    MAXIMAL_NUMBER_OF_GRANULES_IN_SET = maximal_number_of_granules_in_set;
    NUMBER_OF_DATA_TO_GENERATE = number_of_data_to_generate;
    
//     debug(_pPartitioner);
}
 

ksi::granular_nfs::granular_nfs (const ksi::granular_nfs & wzor) : ksi::neuro_fuzzy_system (wzor)
{
}

ksi::granular_nfs::granular_nfs (ksi::granular_nfs && wzor) : ksi::neuro_fuzzy_system (wzor)
{
}

ksi::granular_nfs & ksi::granular_nfs::operator= (const ksi::granular_nfs & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::granular_nfs & ksi::granular_nfs::operator= (ksi::granular_nfs && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap

   return *this;
}

ksi::granular_nfs::~granular_nfs ()
{

   // delete what is to delete

}



/*

ksi::dataset ksi::granular_nfs::generate_dataset_from_granules(
    const ksi::granule_set & granules, 
    const int NUMBER_OF_TRAIN_DATA)
{
    
    try 
    {
        // This quite a long piece of code aims at elaboration of 
        // numbers of data items to generate from data granules
        // with use of their cardinalities
        
        std::size_t number_of_granules = granules.size();
        if (number_of_granules == 0)
            throw std::string ("empty set of granules");
        
        ksi::dataset train;
        
        ksi::granule_set Granules (granules);
        elaborate_quality_of_rules(Granules);
        
        
//         std::vector<double> cardinalities, errors, weights, weighted_cardinalities;
//         
//         for (std::size_t i = 0; i < number_of_granules; i++)
//         {
//             auto pGranule = granules.getGranule(i);
//             cardinalities.push_back(pGranule->get_cardinality());
//             errors.push_back(pGranule->get_error());
//         }
//         double total_errors = std::accumulate(errors.begin(), errors.end(), 0.0);
//         for (std::size_t i = 0; i < errors.size(); i++)
//         {
//             double weight = 1.0 - (errors[i] / total_errors);
//             weights.push_back(weight);
//             weighted_cardinalities.push_back(weight * cardinalities[i]);
//         }
        
        std::vector<double> weighted_cardinalities;
        
        for (std::size_t i = 0; i < Granules.size(); i++)
            weighted_cardinalities.push_back(Granules[i]->get_quality());
        
        double total_weighted_cardinality = std::accumulate(weighted_cardinalities.begin(), weighted_cardinalities.end(), 0.0);
        
        for (auto & card : weighted_cardinalities)
            card *= ((double) NUMBER_OF_TRAIN_DATA / total_weighted_cardinality);
        
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
                ksi::granule * p = (Granules.getGranule(g))->clone_granule();
                auto d = p->get_data_item();

                double answer = p->get_answer(d).getValue();
                delete p;
                
//                 double answer = _pRulebase ? _pRulebase->answer(d.getVector()) : p->get_answer(d).getValue();
                
                d.push_back(answer); // decision attribute  
                d.setDecision(answer); // decision attribute
                train.addDatum(d);
            }
        }
        return train;
    }
    CATCH;
}



*/

void ksi::granular_nfs::elaborate_quality_of_rules(ksi::set_of_granules & granules)
{
    try 
    {
        std::size_t number_of_granules = granules.size();
        if (number_of_granules == 0)
            throw std::string ("empty set of granules");
        
        std::vector<double> cardinalities, errors;
        
        for (std::size_t i = 0; i < number_of_granules; i++)
        {
            auto pGranule = granules.getGranule(i);
            cardinalities.push_back(pGranule->get_cardinality());
            errors.push_back(pGranule->get_error());
        }
        double total_errors = std::accumulate(errors.begin(), errors.end(), 0.0);
        double total_cardinality = std::accumulate(cardinalities.begin(), cardinalities.end(), 0.0);
        
        for (std::size_t i = 0; i < errors.size(); i++)
        {
            double weight = total_errors > 0 ? 1.0 - (errors[i] / total_errors) : 1.0;
            double cardy  = total_cardinality > 0 ? cardinalities[i] / total_cardinality : 0.0;
            granules.getGranuleNonConst(i)->set_quality(weight * cardy); 
        }
    }
    CATCH;
}

/*
const ksi::granule_set ksi::granular_nfs::reduce_granules_set(
    const ksi::granule_set & set_to_reduce, 
    const int numberOfGranules)
{
    ksi::granule_set results;
    
    std::vector<double> qualities;
    
    auto size = set_to_reduce.size();
    
    if (numberOfGranules > size)
        return set_to_reduce;
    
    
    for (std::size_t i = 0; i < size; i++)
        qualities.push_back (set_to_reduce.getGranule(i)->get_quality());
    
    std::nth_element(qualities.begin(), qualities.begin() + size - 1 - numberOfGranules, qualities.end());
    
    double less_value = qualities[numberOfGranules];
    
    for (std::size_t i = 0; i < size; i++)
    {
        auto p = set_to_reduce.getGranule(i);
        if (p->get_quality() > less_value)
           results.addGranule(set_to_reduce.getGranule(i)->clone_granule());
    }
    
    return results;
}
*/


void ksi::granular_nfs::createFuzzyRulebaseByParts(
    const std::string & trainDataFile, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation)
{
    try 
    {
       ksi::reader_complete_by_parts czytacz(trainDataFile);
       
       ksi::dataset zbiorTrain;
       ksi::set_of_granules * first_grade_granules = new ksi::rulebase;
       bool exist_more_data = true;
       int number_of_chunks = 1;
       
       
       while (exist_more_data) 
       {
           zbiorTrain = czytacz.read_part(NUMBER_OF_DATA_TO_READ);
           number_of_chunks++;
           
           if (zbiorTrain.getNumberOfData() > 0)
           {
               if (bNormalisation)
               {
                    ksi::data_modifier_normaliser normalizator;
                    normalizator.modify(zbiorTrain);
               }
               
               ksi::set_of_granules * granules = new ksi::set_of_standalone_granules();
               for (int i = 0; i < zbiorTrain.getNumberOfData(); i++)
               {
                   auto * p = zbiorTrain.getDatum(i);
                   std::size_t last_index = p->getNumberOfAttributes() - 1;
                   auto split = zbiorTrain.getDatum(i)->splitDatum(last_index);
                   ksi::data_item di (split.first, *(split.second.at(0)));
                   di.set_cardinality(1.0); // each item represents exactly one item from the data set 
                   di.set_quality(1.0); // the granule perfectly covers the datum
                   di.set_error(0.0);   // no error yet :-)
                   granules->addGranule(di);
               }
                
               createFuzzyRulebase(nNumberOfClusteringIterations,
                    nNumberofTuningIterations, dbLearningCoefficient, *granules,  *granules);  // validate == train
               delete granules;
               
               for (int i = 0; i < _nRules; i++)
                    first_grade_granules->addGranule(_pRulebase->operator[](i));
               //-----------------

               if (first_grade_granules->size() > MAXIMAL_NUMBER_OF_GRANULES_IN_SET)
               {
//                     debug("1 grade reduction");
                    createFuzzyRulebase(nNumberOfClusteringIterations,
                                        nNumberofTuningIterations, dbLearningCoefficient, *first_grade_granules, *first_grade_granules);  // validate == train
                    
                    ksi::set_of_granules * next_grade_granules = new ksi::rulebase;
                    for (int i = 0; i < _nRules; i++)
                        next_grade_granules->addGranule(_pRulebase->operator[](i));
                    
                    delete first_grade_granules;
                    first_grade_granules = next_grade_granules; 
               }
            }
            else 
               exist_more_data = false;
        }
        
//        debug(__LINE__);
        // all data already read 
        
        debug("all data read");
        
        if (first_grade_granules->size() > nNumberOfRules)
        {
            createFuzzyRulebase(nNumberOfClusteringIterations,
                                nNumberofTuningIterations, dbLearningCoefficient, 
                                * first_grade_granules, 
                                * first_grade_granules);  // validate == train

//             auto reduced = reduce_granules_set (_1_grade_granules, nNumberOfRules);
//             _pRulebase->clear();
//             
//             auto size = reduced.size();
//             for (std::size_t i = 0; i < size; i++)
//                 _pRulebase->addRule(*(reduced.getGranule(i)->get_rule()));
        }  
        
        // granule_sets.back() to reguly, ktore maja sie znalezc w bazie reguly
        // nic nie trzeba robic -- te reguly sa wlasnie w _pRulebase :-)
        
         delete first_grade_granules;
        
    }
    CATCH;
}



void ksi::granular_nfs::createFuzzyRulebaseHierarchical(
    const std::string & trainDataFile, 
    const int nNumberOfRules, 
    const int nNumberOfClusteringIterations, 
    const int nNumberofTuningIterations, 
    const double dbLearningCoefficient, 
    const bool bNormalisation)
{
    try 
    {
       
       ksi::reader_complete_by_parts czytacz(trainDataFile);
       std::vector<ksi::set_of_granules *> granule_sets; 
      
       ksi::dataset zbiorTrain;
       ksi::set_of_granules * first_grade_granules = new ksi::rulebase();
       bool exist_more_data = true;
       int number_of_chunks = 1;       
       
       while (exist_more_data) 
       {
           zbiorTrain = czytacz.read_part(NUMBER_OF_DATA_TO_READ);
           number_of_chunks++;
           
           if (zbiorTrain.getNumberOfData() > 0)
           {
               if (bNormalisation)
               {
                    ksi::data_modifier_normaliser normalizator;
                    normalizator.modify(zbiorTrain);
               }
               
                ksi::set_of_granules * granules = new ksi::set_of_standalone_granules;
                for (int i = 0; i < zbiorTrain.getNumberOfData(); i++)
                {
                    auto * p = zbiorTrain.getDatum(i);
                    std::size_t last_index = p->getNumberOfAttributes() - 1;
                    auto split = zbiorTrain.getDatum(i)->splitDatum(last_index);
                    ksi::data_item di (split.first, *(split.second.at(0)));
                    di.set_cardinality(1.0); // each item represents exactly one item from the data set 
                    di.set_quality(1.0); // the granule perfectly covers the datum
                     
                    granules->addGranule(di);
                }
                
                
                ///@todo Trzeba wyznaczyć próg podziału klasy (threshold_value).
                createFuzzyRulebase(nNumberOfClusteringIterations,
                    nNumberofTuningIterations, dbLearningCoefficient, *granules, *granules);   // validate == train
                
                delete granules;
                granules = nullptr;
                
                for (int i = 0; i < _nRules; i++)
                    first_grade_granules->addGranule(_pRulebase->operator[](i));
                
                if (granule_sets.empty())
                    granule_sets.push_back(first_grade_granules->clone_set_of_granules());
                else
                {
                    for (std::size_t i = 0; i < first_grade_granules->size(); i++)
                        granule_sets[0]->addGranule(first_grade_granules->getGranule(i));
                }
                
                delete first_grade_granules;
                first_grade_granules = new ksi::rulebase();
                
                //-----------------
                
                for (std::size_t it = 0; it < granule_sets.size(); it++)
                {
                    if (granule_sets[it]->size() > MAXIMAL_NUMBER_OF_GRANULES_IN_SET)
                    {
                        createFuzzyRulebase(nNumberOfClusteringIterations,
                                            nNumberofTuningIterations, 
                                            dbLearningCoefficient, 
                                            * granule_sets[it], 
                                            * granule_sets[it]); // validate == train
                        
                        ksi::set_of_granules * next_grade_granules = _pRulebase->clone_set_of_granules();
                        
                        if (it + 1 < granule_sets.size())
                        {
                            for (std::size_t i = 0; i < next_grade_granules->size(); i++)
                                granule_sets[it + 1]->addGranule(next_grade_granules->getGranule(i));
                            
                            delete (granule_sets[it]);
                            granule_sets[it] = new rulebase();

                            delete next_grade_granules;
                            next_grade_granules = nullptr;
                        }
                        else
                        {
                            granule_sets.push_back(next_grade_granules);
                        }
                    }
                }
            }
            else 
               exist_more_data = false;
        }
        
        // all data already read 
        for (std::size_t it = 0; it < granule_sets.size(); it++)
        {
            if (granule_sets[it]->size() > MINIMAL_NUMBER_OF_GRANULES_IN_SET)
            {
                createFuzzyRulebase(nNumberOfClusteringIterations,
                                    nNumberofTuningIterations, dbLearningCoefficient, * granule_sets[it], * granule_sets[it]);  // validate == train
                
                ksi::set_of_granules * next_grade_granules = _pRulebase->clone_set_of_granules();
                
                if (it + 1 < granule_sets.size())
                {
                    for (std::size_t i = 0; i < next_grade_granules->size(); i++)
                        granule_sets[it + 1]->addGranule(next_grade_granules->getGranule(i));

                    delete granule_sets[it];
                    granule_sets[it] = new rulebase();

                    delete next_grade_granules;
                    next_grade_granules = nullptr;
                }
                else
                    granule_sets.push_back(next_grade_granules);
            }
            else 
            {
                if (it + 1 < granule_sets.size())
                {
                    for (int i = 0; i < granule_sets[it]->size(); i++)
                        granule_sets[it + 1]->addGranule(granule_sets[it]->getGranule(i));
                }
            }
        }
        
        if (granule_sets.back()->size() > nNumberOfRules)
        {
            createFuzzyRulebase(nNumberOfClusteringIterations,
                                nNumberofTuningIterations, dbLearningCoefficient, *granule_sets.back(), *granule_sets.back());  // validate == train
            ksi::set_of_granules * next_grade_granules = new ksi::rulebase;
            for (int i = 0; i < _nRules; i++)
                next_grade_granules->addGranule(_pRulebase->operator[](i));
            granule_sets.push_back(next_grade_granules);
        }  
        
        // granule_sets.back() to reguly, ktore maja sie znalezc w bazie reguly
        // nic nie trzeba robic -- te reguly sa wlasnie w _pRulebase :-)
        
        for (auto p : granule_sets)
            delete p;
        
        delete first_grade_granules;
        first_grade_granules = nullptr;
        
    }
    CATCH;
}

