#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <syncstream>
#include <algorithm>
#include <map>
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../auxiliary/tempus.h"
#include "../service/debug.h"
#include "../auxiliary/confusion-matrix.h"
#include "../neuro-fuzzy/meta_classifier_three_way_decision_nfs.h"

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta() : three_way_decision_nfs()
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const double stop_criterion_percentage
) : three_way_decision_nfs(cascade, 0.0, stop_criterion_percentage), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const std::string& train, 
    const std::string& test, 
    const std::string& result,
    const double stop_criterion_percentage
) : three_way_decision_nfs(cascade, train, test, result, 0.0, stop_criterion_percentage), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const std::string& train,
    const std::string& validation, 
    const std::string& test, 
    const std::string& result,
    const double stop_criterion_percentage
) : three_way_decision_nfs(cascade, train, validation, test, result, 0.0, stop_criterion_percentage), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const ksi::dataset& train, 
    const ksi::dataset& test, 
    const std::string& result,
    const double stop_criterion_percentage
) : three_way_decision_nfs(cascade, train, test, result, 0.0, stop_criterion_percentage), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const ksi::dataset& train,
    const ksi::dataset& validation, 
    const ksi::dataset& test, 
    const std::string& result,
    const double stop_criterion_percentage
) : three_way_decision_nfs(cascade, train, validation, test, result, 0.0, stop_criterion_percentage), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(const three_way_decision_nfs_meta& wzor) 
    : three_way_decision_nfs(wzor)
{
    for (const auto& s : wzor._meta_classifiers)
        _meta_classifiers.push_back(std::shared_ptr<ksi::neuro_fuzzy_system>(s->clone()));
    
    meta_copy_fields(wzor);
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(three_way_decision_nfs_meta&& wzor) 
    : three_way_decision_nfs(wzor)
{
    std::swap(_meta_classifiers, wzor._meta_classifiers);
    meta_copy_fields(wzor);
}

ksi::three_way_decision_nfs_meta& ksi::three_way_decision_nfs_meta::operator=(const three_way_decision_nfs_meta& wzor)
{
    if (this == &wzor)
        return *this;

    ksi::three_way_decision_nfs::operator=(wzor);
    
    _meta_classifiers.clear();
    for (const auto& s : wzor._meta_classifiers)
        _meta_classifiers.push_back(std::shared_ptr<ksi::neuro_fuzzy_system>(s->clone()));
    
    meta_copy_fields(wzor);
    
    return *this;
}

ksi::three_way_decision_nfs_meta& ksi::three_way_decision_nfs_meta::operator=(three_way_decision_nfs_meta&& wzor)
{
    if (this == &wzor)
        return *this;

    ksi::three_way_decision_nfs::operator=(wzor);
    
    std::swap(_meta_classifiers, wzor._meta_classifiers);
    meta_copy_fields(wzor);
    
    return *this;
}

ksi::three_way_decision_nfs_meta::~three_way_decision_nfs_meta()
{
}

ksi::neuro_fuzzy_system* ksi::three_way_decision_nfs_meta::clone() const
{
    return new ksi::three_way_decision_nfs_meta(*this);
}

void ksi::three_way_decision_nfs_meta::meta_copy_fields(const three_way_decision_nfs_meta& other)
{
    // Currently no additional fields to copy beyond what's in _meta_classifiers
}

ksi::dataset ksi::three_way_decision_nfs_meta::extract_incorrect_results(
    const ksi::dataset& data,
    const std::vector<std::tuple<double, double, double>>& answers
)
{
    try 
    {
        std::vector<std::size_t> indices;
        
        for (std::size_t i = 0; i < answers.size(); i++)
        {
            double expected, elaborated_class;
            std::tie(expected, std::ignore, elaborated_class) = answers[i];
            
            // Check if classification was incorrect
            if (std::fabs(expected - elaborated_class) > 0.001)
                indices.push_back(i);
        }
        
        ksi::dataset incorrect_data;
        for (const auto i : indices)
        {
            incorrect_data.addDatum(*data.getDatum(i));
        }
        return incorrect_data;    
    }
    CATCH;
}

ksi::dataset ksi::three_way_decision_nfs_meta::create_meta_training_data(
    const ksi::dataset& data,
    const std::vector<std::tuple<double, double, double>>& answers
)
{
    try 
    {
        ksi::dataset meta_data;
        
        for (std::size_t i = 0; i < answers.size(); i++)
        {
            double expected, elaborated_class;
            std::tie(expected, std::ignore, elaborated_class) = answers[i];
            
            // Create a copy of the datum
            auto datum_copy = *data.getDatum(i);
            
            // Set label: 1.0 if correct, 0.0 if incorrect
            double label = (std::fabs(expected - elaborated_class) < 0.001) ? 1.0 : 0.0;
            datum_copy.setDecision(label);
            
            meta_data.addDatum(datum_copy);
        }
        
        return meta_data;    
    }
    CATCH;
}

void ksi::three_way_decision_nfs_meta::createFuzzyRulebase(
    const ksi::dataset& train_ds, 
    const ksi::dataset& test,
    const ksi::dataset& validation
)
{
    try 
    {
        auto train_ = train_ds;
        auto validation_ = validation; 
        auto nSize = train_.size(); 
        bool remove_system = false;
        
        // Ensure we have the right number of meta-classifiers (one less than primary classifiers)
        if (_meta_classifiers.size() != _cascade.size() - 1)
        {
            throw std::string("Number of meta-classifiers must be one less than number of primary classifiers.");
        }
        
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            if (remove_system)
            {
                _cascade[i] = nullptr;
                if (i < _meta_classifiers.size())
                    _meta_classifiers[i] = nullptr;
            }
            else 
            {
                std::cout << "Training primary classifier " << i + 1 << "/" << _cascade.size() << " with " << train_.size() << " samples." << std::endl;
                // Train primary classifier
                auto& pSystem = _cascade[i];
                pSystem->set_train_data_file(this->_train_data_file);
                pSystem->set_threshold_type(ksi::roc_threshold::youden);
                pSystem->set_train_dataset(train_);
                pSystem->set_output_file(this->_output_file + "-primary-" + std::to_string(i));
                pSystem->experiment_classification_core(); 
                std::cout << "Finished training primary classifier " << i + 1 << "/" << _cascade.size() << "." << std::endl;
                // Get results from primary classifier
                
                // Train meta-classifier for this level (except for the last level)
                if (i < _meta_classifiers.size())
                {
                    auto& pMetaSystem = _meta_classifiers[i];
                    
                    // Create meta-training data: label 1.0 if correct, 0.0 if incorrect
                    auto answer_function =[](const ksi::dataset& dataset, std::shared_ptr<ksi::neuro_fuzzy_system> pSystem) {
                        std::vector<std::tuple<double, double>> results_validation(dataset.size());
                        auto XYvalidate  = dataset.splitDataSetVertically(dataset.getNumberOfAttributes() - 1);
                        std::size_t nXvalidate  = dataset.getNumberOfData();
                        for (std::size_t i = 0; i < nXvalidate; i++)
                        {
                            auto [ elaborated_numeric, elaborated_class ] = pSystem->answer_classification(*(XYvalidate.first.getDatum(i)));
                            auto expected = XYvalidate.second.get(i, 0);
                    
                            results_validation[i] = {expected, elaborated_class}; 
                        }
                    
                        return results_validation;
                    };
                    auto validation_results = answer_function(validation_, _cascade[i]);
                    std::cout << "Finished evaluating primary classifier " << i + 1 << "/" << _cascade.size() << " on validation set." << std::endl;
                    auto create_train_for_meta = [&]() {
                        ksi::dataset meta_train_data;
                        for (std::size_t i = 0; i < validation_.size(); i++)
                        {
                            auto datum_copy = *validation_.getDatum(i);
                            double expected, elaborated_class;
                            std::tie(expected, elaborated_class) = validation_results[i];
                            
                            // Set label: 1.0 if correct, 0.0 if incorrect
                            double label = (std::fabs(expected - elaborated_class) < 0.001) ? 1.0 : 0.0;
                            datum_copy.setDecision(label);
                            
                            meta_train_data.addDatum(datum_copy);
                        }
                        return meta_train_data;
                    };
                    auto meta_train_data = create_train_for_meta();
                    std::cout << "Created meta-training datafor meta-classifier " << i + 1 << "/" << _meta_classifiers.size() << "." << std::endl;
                    std::cout << "Size of meta-training data: " << meta_train_data.size() << " samples." << std::endl;
                    // Set positive and negative classes for meta-classifier
                    pMetaSystem->set_positive_class(1.0);   // correct predictions
                    pMetaSystem->set_negative_class(0.0);  // incorrect predictions
                    
                    // Use Youden index for meta-classifier threshold
                    pMetaSystem->set_threshold_type(ksi::roc_threshold::youden);
                    
                    pMetaSystem->set_train_dataset(meta_train_data);
                    pMetaSystem->set_output_file(this->_output_file + "-meta-" + std::to_string(i));
                    pMetaSystem->experiment_classification_core();

                    std::cout << "Finished training meta-classifier " << i + 1 << "/" << _meta_classifiers.size() << "." << std::endl;

                    // Get meta-classifier predictions on training data
                    auto meta_results_train = answer_function(train_, pMetaSystem);
                    auto meta_results_validation = answer_function(validation_, pMetaSystem);
                    
                    auto getDataForNextLevel = [](std::vector<std::tuple<double, double>> results, const ksi::dataset& dataset) {
                        std::vector<std::size_t> indices_for_next_level;
                        for (std::size_t j = 0; j < results.size(); j++)
                        {
                            double meta_elaborated_class;
                            std::tie(std::ignore, meta_elaborated_class) = results[j];

                            // If meta-classifier predicts incorrect (numeric < threshold), pass to next level
                            if (std::fabs(meta_elaborated_class) < 0.01)
                                indices_for_next_level.push_back(j);
                        }

                        // Create dataset for next level
                        ksi::dataset next_level_data;
                        for (const auto j : indices_for_next_level)
                        {
                            next_level_data.addDatum(*dataset.getDatum(j));
                        }
                        return next_level_data;
                    };

                    train_ = getDataForNextLevel(meta_results_train, train_);
                    std::cout << "Size of training data for next level after meta-classifier " << i + 1 << ": " << train_.size() << " samples." << std::endl;
                    validation_ = getDataForNextLevel(meta_results_validation, validation_);
                    std::cout << "Size of validation data for next level after meta-classifier " << i + 1 << ": " << validation_.size() << " samples." << std::endl;
                }
                
                // Check if we have enough data to continue
                if (train_.size() < nSize * get_stop_criterion_percentage())
                {
                    std::cout << "Stopping cascade early after level " << i + 1 << " due to insufficient data for next level (" << train_.size() << " samples remaining)." << std::endl;
                    std::cout << "Which is " << std::fixed << std::setprecision(2) << (100.0 * train_.size() / nSize) << "% of original training data." << std::endl;
                    std:: cout << "nSize: " << nSize << std::endl;
                    std::cout << "get_stop_criterion_percentage(): " << get_stop_criterion_percentage() << std::endl;
                    remove_system = true;  
                }
            }   
        }
        
        // Remove null systems
        _cascade.erase(
            std::remove_if(_cascade.begin(), _cascade.end(),
                [](std::shared_ptr<ksi::neuro_fuzzy_system> p) {return not p;}),
            _cascade.end()
        );
        _meta_classifiers.erase(
            std::remove_if(_meta_classifiers.begin(), _meta_classifiers.end(),
                [](std::shared_ptr<ksi::neuro_fuzzy_system> p) {return not p;}),
            _meta_classifiers.end()
        );
    }
    CATCH;
}

std::pair<double, double> ksi::three_way_decision_nfs_meta::answer_classification(const ksi::datum& item) const
{
    try 
    {
        auto nan = std::numeric_limits<double>::signaling_NaN();
        auto result = std::make_pair(nan, nan);
        std::size_t number_of_rules = 0;
        
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            auto& pSystem = _cascade[i];
            result = pSystem->answer_classification(item);
            number_of_rules += pSystem->get_number_of_rules();
            
            // If this is the last classifier, return its result
            if (i == _cascade.size() - 1)
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return result;
            }
            
            // Otherwise, check with meta-classifier
            auto& pMetaSystem = _meta_classifiers[i];
            auto meta_result = pMetaSystem->answer_classification(item);
            number_of_rules += pMetaSystem->get_number_of_rules();
            
            // Get meta-classifier's threshold (calculated using Youden index during training)
            auto meta_threshold = pMetaSystem->get_threshold_value();
            
            // If meta-classifier predicts correct (numeric score >= threshold), return primary result
            if (meta_result.first >= meta_threshold)
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return result;
            }
            
            // Otherwise, meta-classifier predicts incorrect, so continue to next level
        }
        
        // Should not reach here, but return last result just in case
        ++_number_of_data_items;
        _number_of_rules_used += number_of_rules;
        return result;
    }
    CATCH;
}

std::tuple<double, double, std::size_t> ksi::three_way_decision_nfs_meta::answer_classification_with_cascade_depth(const ksi::datum& item) const
{
    try 
    {
        auto nan = std::numeric_limits<double>::signaling_NaN();
        auto result = std::make_pair(nan, nan);
        auto final_result = std::make_tuple(nan, nan, std::size_t{0});
        std::size_t number_of_rules = 0;
        
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            auto& pSystem = _cascade[i];
            result = pSystem->answer_classification(item);
            number_of_rules += pSystem->get_number_of_rules();
            
            // Update result tuple with current level
            std::get<0>(final_result) = result.first;   // elaborated_numeric
            std::get<1>(final_result) = result.second;  // elaborated_class
            std::get<2>(final_result) = i + 1;          // cascade level (1-indexed)
            
            // If this is the last classifier, return its result
            if (i == _cascade.size() - 1)
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return final_result;
            }
            
            // Otherwise, check with meta-classifier
            auto& pMetaSystem = _meta_classifiers[i];
            auto meta_result = pMetaSystem->answer_classification(item);
            number_of_rules += pMetaSystem->get_number_of_rules();
            
            // Get meta-classifier's threshold (calculated using Youden index during training)
            auto meta_threshold = pMetaSystem->get_threshold_value();
            
            // If meta-classifier predicts correct (numeric score >= threshold), return primary result
            if (meta_result.first >= meta_threshold)
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return final_result;
            }
            
            // Otherwise, meta-classifier predicts incorrect, so continue to next level
        }
        
        // Should not reach here, but return last result just in case
        ++_number_of_data_items;
        _number_of_rules_used += number_of_rules;
        return final_result;
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs_meta::get_nfs_name() const
{
    try 
    {
        return std::string{"three-way-decision-neuro-fuzzy-system-meta-classifier"};
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs_meta::get_brief_nfs_name() const
{
    try 
    {
        return std::string{"3WDNFS-meta"};
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs_meta::get_nfs_description() const
{
    try 
    {
        std::stringstream ss;
        ss << "Three-way-decision neuro-fuzzy system with meta-classifiers" << std::endl;
        ss << "Primary cascade size: " << _cascade.size() << std::endl;
        ss << "Meta-classifier cascade size: " << _meta_classifiers.size() << std::endl;
        ss << "Meta-classifiers use Youden index for threshold determination" << std::endl;
        return ss.str();
    }
    CATCH;
}

void ksi::three_way_decision_nfs_meta::printRulebase(std::ostream& ss)
{
    try
    {
        ss << std::endl;
        ss << "Rulebases of neuro-fuzzy systems in the meta-aware cascade" << std::endl;
        ss << "============================================================" << std::endl;
            
        ss << std::endl;
        ss << "number of primary classifiers: " << _cascade.size() << std::endl;
        ss << "number of meta-classifiers:    " << _meta_classifiers.size() << std::endl;
        ss << std::endl;
        
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            auto & p = _cascade[i];
            ss << std::endl;
            ss << "===============================================" << std::endl;
            ss << "PRIMARY CLASSIFIER " << i << std::endl;
            ss << "===============================================" << std::endl;
            ss << p->get_nfs_name() << std::endl;
            ss << "number of rules:              " << p->get_number_of_rules() << std::endl;
            ss << "threshold type:               " << ksi::to_string(p->get_threshold_type()) << std::endl;
            double threshold = p->get_threshold_value();
            ss << "threshold value:              " << threshold << std::endl;
            ss << "size of train dataset:        " << p->get_train_dataset_size() << std::endl;
            ss << "cardinality of train dataset: " << p->get_train_dataset_cardinality() << std::endl;
            ss << "--------------------------------------" << std::endl;
            ss << std::endl;       
            ss << "fuzzy rule base" << std::endl;       
            p->printRulebase(ss);
            ss << std::endl;       
            ss << "linguistic description of fuzzy rule base" << std::endl;       
            p->printLinguisticDescriptionRulebase(ss);
            
            // Print meta-classifier for this level (if exists)
            if (i < _meta_classifiers.size())
            {
                auto & pMeta = _meta_classifiers[i];
                ss << std::endl;
                ss << "-----------------------------------------------" << std::endl;
                ss << "META-CLASSIFIER " << i << " (predicts correctness of primary classifier " << i << ")" << std::endl;
                ss << "-----------------------------------------------" << std::endl;
                ss << pMeta->get_nfs_name() << std::endl;
                ss << "positive class (correct):     " << pMeta->get_positive_class() << std::endl;
                ss << "negative class (incorrect):   " << pMeta->get_negative_class() << std::endl;
                ss << "number of rules:              " << pMeta->get_number_of_rules() << std::endl;
                ss << "threshold type:               " << ksi::to_string(pMeta->get_threshold_type()) << std::endl;
                double meta_threshold = pMeta->get_threshold_value();
                ss << "threshold value (Youden):     " << meta_threshold << std::endl;
                ss << "size of train dataset:        " << pMeta->get_train_dataset_size() << std::endl;
                ss << "cardinality of train dataset: " << pMeta->get_train_dataset_cardinality() << std::endl;
                ss << "--------------------------------------" << std::endl;
                ss << std::endl;       
                ss << "meta-classifier fuzzy rule base" << std::endl;       
                pMeta->printRulebase(ss);
                ss << std::endl;       
                ss << "meta-classifier linguistic description" << std::endl;       
                pMeta->printLinguisticDescriptionRulebase(ss);
            }
        }
        ss << std::endl;
        ss << "============================================================" << std::endl;        
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs_meta::get_cascade_names() const
{
    std::stringstream ss;
    for (std::size_t i = 0; i < _cascade.size(); i++)
    {
        ss << "-" << _cascade[i]->get_nfs_name();
        if (i < _meta_classifiers.size())
        {
            ss << "-meta-" << _meta_classifiers[i]->get_nfs_name();
        }
    }
    return ss.str();
}

std::string ksi::three_way_decision_nfs_meta::get_brief_cascade_names() const
{
    std::stringstream ss;
    for (std::size_t i = 0; i < _cascade.size(); i++)
    {
        ss << "-" << _cascade[i]->get_brief_nfs_name();
        if (i < _meta_classifiers.size())
        {
            ss << "-M" << _meta_classifiers[i]->get_brief_nfs_name();
        }
    }
    return ss.str();
}
