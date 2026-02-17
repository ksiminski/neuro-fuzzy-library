
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
#include "../neuro-fuzzy/three_way_decision_nfs.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../auxiliary/tempus.h"
#include "../service/debug.h"
#include "../auxiliary/confusion-matrix.h"

ksi::three_way_decision_nfs::three_way_decision_nfs ()
{
    _threshold_type = ksi::roc_threshold::none;
}

ksi::three_way_decision_nfs::three_way_decision_nfs(const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> >& cascade) : _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> > & cascade, 
    const std::string                                            & train, 
    const std::string                                            & test,
    const std::string                                            & result,
    const double                                                   maximal_deviation
  ) : ksi::neuro_fuzzy_system(train, test, result), _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    _noncommitment_widths = std::vector<double> (cascade.size(), maximal_deviation);
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> > & cascade, 
    const std::string                                            & train, 
    const std::string                                            & test,
    const std::string                                            & result,
    const std::vector<double>                                    & maximal_deviations
  ) : ksi::neuro_fuzzy_system(train, test, result), _cascade(cascade), _noncommitment_widths(maximal_deviations)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    
    try 
    {
        if (cascade.size() != maximal_deviations.size())
        {
            std::stringstream sos;
            sos << "The lenght of the cascade (" << _cascade.size() << ") and the number of maximal_deviations (" << _noncommitment_widths.size() << ") do not match.";
            throw sos.str();
        }
    }
    CATCH;
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> > & cascade, 
    const std::string                                            & train, 
    const std::string                                            & validation,
    const std::string                                            & test,
    const std::string                                            & result,
    const double                                                   maximal_deviation
  ) : ksi::neuro_fuzzy_system(train, validation, test, result), _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    _noncommitment_widths = std::vector<double> (cascade.size(), maximal_deviation);
}

ksi::three_way_decision_nfs::three_way_decision_nfs(const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade, const double maximal_deviation)
: _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    _noncommitment_widths = std::vector<double> (cascade.size(), maximal_deviation);
}

ksi::three_way_decision_nfs::three_way_decision_nfs(const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade, const std::vector<double> & maximal_deviations)
: _cascade(cascade), _noncommitment_widths(maximal_deviations)
{
    try 
    {
        if (cascade.size() != maximal_deviations.size())
        {
            std::stringstream sos;
            sos << "The lenght of the cascade (" << _cascade.size() << ") and the number of maximal_deviations (" << _noncommitment_widths.size() << ") do not match.";
            throw sos.str();
        }
       set_positive_class(cascade[0]->get_positive_class());
       set_negative_class(cascade[0]->get_negative_class()); 
    }
    CATCH;
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> >& cascade, 
    const ksi::dataset& train, 
    const ksi::dataset& test, 
    const std::string& result, 
    const double maximal_deviation
) : ksi::neuro_fuzzy_system(train, test, result), _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    _noncommitment_widths = std::vector<double> (cascade.size(), maximal_deviation);
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> >& cascade, 
    const ksi::dataset& train, 
    const ksi::dataset& test, 
    const std::string& result, 
    const std::vector<double> & maximal_deviations
) : ksi::neuro_fuzzy_system(train, test, result), _cascade(cascade), _noncommitment_widths(maximal_deviations)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none; 
    
    try 
    {
        if (cascade.size() != maximal_deviations.size())
        {
            std::stringstream sos;
            sos << "The lenght of the cascade (" << _cascade.size() << ") and the number of maximal_deviations (" << _noncommitment_widths.size() << ") do not match.";
            throw sos.str();
        }
    }
    CATCH;
}

ksi::three_way_decision_nfs::three_way_decision_nfs(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system> >& cascade, 
    const ksi::dataset & train, 
    const ksi::dataset & validation,
    const ksi::dataset & test, 
    const std::string  & result, 
    const double maximal_deviation
) : ksi::neuro_fuzzy_system(train, validation, test, result), _cascade(cascade)
{
    set_positive_class(cascade[0]->get_positive_class());
    set_negative_class(cascade[0]->get_negative_class()); 
    _threshold_type = ksi::roc_threshold::none;
    _noncommitment_widths = std::vector<double> (cascade.size(), maximal_deviation);
}

void ksi::three_way_decision_nfs::three_copy_fields(const ksi::three_way_decision_nfs& _3wnfs)
{
    _positive_class = _3wnfs._positive_class;
    _negative_class = _3wnfs._negative_class;
    _threshold_type = _3wnfs._threshold_type;
    _noncommitment_widths = _3wnfs._noncommitment_widths;
    
    _dbTestAverageNumerOfRulesUsed = _3wnfs._dbTestAverageNumerOfRulesUsed;
    _dbTrainAverageNumerOfRulesUsed = _3wnfs._dbTrainAverageNumerOfRulesUsed;
    _number_of_rules_used = _3wnfs._number_of_rules_used;
    _number_of_data_items = _3wnfs._number_of_data_items;
}

ksi::three_way_decision_nfs::~three_way_decision_nfs ()
{
   // delete what is to delete
}

ksi::three_way_decision_nfs::three_way_decision_nfs (const ksi::three_way_decision_nfs & wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // copy what is to copy
   for (const auto & s : wzor._cascade)
		_cascade.push_back(std::shared_ptr<neuro_fuzzy_system> (s->clone()));
   
   three_copy_fields(wzor);
}

ksi::three_way_decision_nfs & ksi::three_way_decision_nfs::operator= (const ksi::three_way_decision_nfs & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate
   for (const auto & s : wzor._cascade)
		_cascade.push_back(std::shared_ptr<neuro_fuzzy_system> (s->clone()));
   
   three_copy_fields(wzor);

   return *this;
}

ksi::three_way_decision_nfs::three_way_decision_nfs (ksi::three_way_decision_nfs && wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // swap what is to swap
   std::swap(_cascade, wzor._cascade);
   three_copy_fields(wzor);
}

ksi::three_way_decision_nfs & ksi::three_way_decision_nfs::operator= (ksi::three_way_decision_nfs && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap
   std::swap(_cascade, wzor._cascade);
   three_copy_fields(wzor);
   
   return *this;
}

ksi::neuro_fuzzy_system * ksi::three_way_decision_nfs::clone() const
{
    return new ksi::three_way_decision_nfs(*this);
}

ksi::discriminative_model * ksi::three_way_decision_nfs::clone_discriminant() const
{
    return new ksi::three_way_decision_nfs(*this);
}

ksi::generative_model * ksi::three_way_decision_nfs::clone_generator() const
{
    throw (std::string ("not implemented"));
    return nullptr;
}

double ksi::three_way_decision_nfs::discriminate(const ksi::datum& d)
{
    throw (std::string ("not implemented"));
    return 0;
}

void ksi::three_way_decision_nfs::train_discriminative_model(const ksi::dataset& ds)
{
    throw (std::string ("not implemented")); // interface pollution
}

void ksi::three_way_decision_nfs::createFuzzyRulebase(int, int, double, const ksi::dataset& train, const ksi::dataset& validate)
{
    createFuzzyRulebase(train, this->_TestDataset, validate); 
}

void ksi::three_way_decision_nfs::createFuzzyRulebase(const ksi::dataset& train, const ksi::dataset & test, const ksi::dataset & validation)
{
    try 
    {
        auto zbior_treningowy = train;
        auto nAttributes = zbior_treningowy.getNumberOfAttributes(); 
        bool remove_system = false;
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            if (remove_system)
            {
                _cascade[i] = nullptr;
            }
            else 
            {
                auto & pSystem = _cascade[i];
                pSystem->set_train_data_file(this->_train_data_file);
                pSystem->set_validation_data_file (this->_validation_data_file);
                pSystem->set_test_data_file (this->_test_data_file);
                pSystem->set_output_file(this->_output_file + std::to_string(i));
                pSystem->set_train_dataset(zbior_treningowy);
                pSystem->set_validation_dataset(validation);
                pSystem->set_test_dataset(test);
                pSystem->experiment_classification_core(); 
                
                // wydzielenie tych danych, które są zbyt bliskie progowi 
                auto results_train = pSystem->get_answers_for_train_classification();
                auto threshold_value = pSystem->get_threshold_value();
                
                // zapisanie do zbioru_treningowego danych bliskich progowi
                zbior_treningowy = extract_poor_results(zbior_treningowy, results_train, threshold_value, _noncommitment_widths[i]); 
                  
                if (zbior_treningowy.size() < nAttributes)
                {
                    // wszystkie nastepne systemy trzeba skasowac
                    remove_system = true;  
                }
            }   
        }
        _cascade.erase(
            std::remove_if(_cascade.begin(), _cascade.end(),
                [](std::shared_ptr<ksi::neuro_fuzzy_system> p) {return not p;}),
            _cascade.end()
        );
    }
    CATCH;
}

double ksi::three_way_decision_nfs::answer(const ksi::datum& item) const
{
    try 
    {
        double result = std::numeric_limits<double>::signaling_NaN();
        
        std::size_t number_of_rules = 0;
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            auto & pSystem = _cascade[i];
            number_of_rules += pSystem->get_number_of_rules();
            result = pSystem->answer(item);
            auto threshold_value = pSystem->get_threshold_value();
            
            if (std::fabs(result - threshold_value) > _noncommitment_widths[i])
            {
                _number_of_rules_used += number_of_rules;
                return result;
            }
        }
        return result; 
    }
    CATCH;
}

std::vector<std::tuple<double, double, double>> ksi::three_way_decision_nfs::get_answers_for_train_classification()
{
    _number_of_rules_used = 0;
    _number_of_data_items = 0;
    auto result = ksi::neuro_fuzzy_system::get_answers_for_train_classification();
    auto data_size = _TrainDataset.size();
    _dbTrainAverageNumerOfRulesUsed = 1.0 * _number_of_rules_used / _number_of_data_items;
    return result;
}


std::vector<std::tuple<double, double, double>> ksi::three_way_decision_nfs::get_answers_for_test_classification()
{
    _number_of_rules_used = 0;
    _number_of_data_items = 0;
    auto result = ksi::neuro_fuzzy_system::get_answers_for_test_classification();
    auto data_size = _TestDataset.size();
    _dbTestAverageNumerOfRulesUsed = 1.0 * _number_of_rules_used / _number_of_data_items;
    return result;
}

double ksi::three_way_decision_nfs::get_train_F1score_for_part_of_the_cascade(const std::size_t depth) 
{
    std::vector<double> vExpected, vClass;
    //  expected, elaborated_numeric, elaborated_class
    auto expected_elaborated_class = get_answers_for_train_classification(depth);
    for (auto & [expected, _, elaborated_class] : expected_elaborated_class)
    {
        vExpected.push_back(expected);
        vClass.push_back(elaborated_class);
    }
    
    int p2p, n2n, n2p, p2n;
    ksi::confusion_matrix cm; 
    cm.calculate_statistics(vExpected, vClass, this->_positive_class, this->_negative_class, p2p, n2n, n2p, p2n);
    ksi::result r;
    r.TrainPositive2Positive = p2p;
    r.TrainPositive2Negative = p2n;
    r.TrainNegative2Negative = n2n;
    r.TrainNegative2Positive = n2p;

    return cm.TrainF1score(r);
}

double ksi::three_way_decision_nfs::get_test_F1score_for_part_of_the_cascade(const std::size_t depth)
{
    std::vector<double> vExpected, vClass;
    //  expected, elaborated_numeric, elaborated_class
    auto expected_elaborated_class = get_answers_for_test_classification(depth);
    for (auto & [expected, _, elaborated_class] : expected_elaborated_class)
    {
        vExpected.push_back(expected);
        vClass.push_back(elaborated_class);
    }
    
    int p2p, n2n, n2p, p2n;
    ksi::confusion_matrix cm; 
    cm.calculate_statistics(vExpected, vClass, this->_positive_class, this->_negative_class, p2p, n2n, n2p, p2n);
    ksi::result r;
    r.TestPositive2Positive = p2p;
    r.TestPositive2Negative = p2n;
    r.TestNegative2Negative = n2n;
    r.TestNegative2Positive = n2p;

    return cm.TestF1score(r);
}

std::vector<std::tuple<double, double, double> > ksi::three_way_decision_nfs::get_answers_for_train_classification(const std::size_t cascade_depth)
{
    _number_of_rules_used = 0;
    _number_of_data_items = 0;
    
    _answers_for_train.clear();
    
    auto XYtrain = _TrainDataset.splitDataSetVertically(_TrainDataset.getNumberOfAttributes() - 1);
    std::size_t nXtrain  = _TrainDataset.getNumberOfData();
    
    _answers_for_train.resize(nXtrain);
    #pragma omp parallel for 
    for (std::size_t i = 0; i < nXtrain; i++)
    {
        auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtrain.first.getDatum(i)), cascade_depth);
        auto expected = XYtrain.second.get(i, 0);
        
        // _answers_for_train.push_back({expected, elaborated_numeric, elaborated_class});
        _answers_for_train[i] = {expected, elaborated_numeric, elaborated_class}; 
    }
    
    auto data_size = _TrainDataset.size();
    _dbTrainAverageNumerOfRulesUsed = 1.0 * _number_of_rules_used / _number_of_data_items;
    return _answers_for_train;
}

std::vector<std::tuple<double, double, double> > ksi::three_way_decision_nfs::get_answers_for_test_classification(const std::size_t cascade_depth)
{
    _number_of_rules_used = 0;
    _number_of_data_items = 0;
    
    _answers_for_test.clear(); 
    
    auto XYtest  = _TestDataset.splitDataSetVertically(_TestDataset.getNumberOfAttributes() - 1);
    std::size_t nXtest  = _TestDataset.getNumberOfData();
    
    _answers_for_test.resize(nXtest);
    #pragma omp parallel for 
    for (std::size_t i = 0; i < nXtest; i++)
    {
        auto [ elaborated_numeric, elaborated_class ] = answer_classification(*(XYtest.first.getDatum(i)), cascade_depth);
        auto expected = XYtest.second.get(i, 0);
        
        // _answers_for_test.push_back({expected, elaborated_numeric, elaborated_class});
        _answers_for_test[i] = {expected, elaborated_numeric, elaborated_class}; 
    }
    auto data_size = _TestDataset.size();
    _dbTestAverageNumerOfRulesUsed = 1.0 * _number_of_rules_used / _number_of_data_items;
    return _answers_for_test;
}

std::vector<std::tuple<std::vector<double>, std::size_t, size_t>> ksi::three_way_decision_nfs::get_answers_for_test_classification_depth(bool useTestDataset) const
{
    _number_of_rules_used = 0;
    _number_of_data_items = 0;
    
    ksi::dataset dataset_to_use = useTestDataset ? _TestDataset : _TrainDataset;

    auto XYtest  = dataset_to_use.splitDataSetVertically(dataset_to_use.getNumberOfAttributes() - 1);
    std::size_t nXtest  = dataset_to_use.getNumberOfData();

    std::vector<std::tuple<std::vector<double>, std::size_t, std::size_t>> answers_for_test(nXtest);
    #pragma omp parallel for 
    for (std::size_t i = 0; i < nXtest; i++)
    {
        const ksi::datum* d = XYtest.first.getDatum(i);
        auto [ elaborated_numeric, elaborated_class, classifier_number ] = answer_classification_with_cascade_depth(*d);
        //auto expected = XYtest.second.get(i, 0);
        //;
        // _answers_for_test.push_back({expected, elaborated_numeric, elaborated_class});
        answers_for_test[i] = std::make_tuple(d->getVector(), classifier_number, elaborated_class); 
    }
    auto data_size = _TestDataset.size();
    _dbTestAverageNumerOfRulesUsed = 1.0 * _number_of_rules_used / _number_of_data_items;
    return answers_for_test;
}


/*
std::pair<double, double> ksi::three_way_decision_nfs::answer_classification(const ksi::datum& item) const
{
    try 
    {
       auto nan = std::numeric_limits<double>::signaling_NaN();
       auto result = std::make_pair (nan, nan);
       std::size_t number_of_rules = 0;

       for (std::size_t i = 0; i < _cascade.size(); i++)
       {
          auto & pSystem = _cascade[i];
          result = pSystem->answer_classification(item);
          number_of_rules += pSystem->get_number_of_rules();
          auto threshold_value = pSystem->get_threshold_value();
          auto numeric = result.first;
          if (std::fabs(numeric - threshold_value) > _noncommitment_widths[i])
          {
             ++_number_of_data_items;
             _number_of_rules_used += number_of_rules;
             return result;
          }
       }
       ++_number_of_data_items;
       _number_of_rules_used += number_of_rules;
       return result; 
    }
    CATCH;
}
*/

std::pair<double, double> ksi::three_way_decision_nfs::answer_classification(const ksi::datum& item) const
{
    constexpr std::size_t MAX {std::numeric_limits<std::size_t>::max()};
    return ksi::three_way_decision_nfs::answer_classification(item, MAX);
}

std::pair<double, double> ksi::three_way_decision_nfs::answer_classification(const ksi::datum& item, const std::size_t cascade_depth) const
{
    try 
    {
        auto nan = std::numeric_limits<double>::signaling_NaN();
        auto result = std::make_pair (nan, nan);
        std::size_t number_of_rules = 0;
        
        auto depth = std::min(cascade_depth, _cascade.size() - 1);
        for (std::size_t i = 0; i < depth + 1; i++)
        {
            auto & pSystem = _cascade[i];
            result = pSystem->answer_classification(item);
            number_of_rules += pSystem->get_number_of_rules();
            auto threshold_value = pSystem->get_threshold_value();
            auto numeric = result.first;
            if ((i == depth) or (std::fabs(numeric - threshold_value) > _noncommitment_widths[i]))
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return result;
            }
        }
        ++_number_of_data_items;
        _number_of_rules_used += number_of_rules;
        return result; 
    }
    CATCH;
}

std::tuple<double, double, std::size_t> ksi::three_way_decision_nfs::answer_classification_with_cascade_depth(const ksi::datum& item) const
{
    try 
    {
        auto nan = std::numeric_limits<double>::signaling_NaN();
        auto result = std::make_pair (nan, nan);
        auto _final_result = std::make_tuple (nan, nan, 0);

        std::size_t number_of_rules = 0;
        
        auto depth = std::min(std::numeric_limits<std::size_t>::max(), _cascade.size() - 1);
        for (std::size_t i = 0; i < depth + 1; i++)
        {
            auto & pSystem = _cascade[i];
            result = pSystem->answer_classification(item);
            std::get<2>(_final_result) = i + 1;

            number_of_rules += pSystem->get_number_of_rules();
            auto threshold_value = pSystem->get_threshold_value();
            auto numeric = result.first;
            std::get<0>(_final_result) = result.first;
            std::get<1>(_final_result) = result.second;
            if ((i == depth) or (std::fabs(numeric - threshold_value) > _noncommitment_widths[i]))
            {
                ++_number_of_data_items;
                _number_of_rules_used += number_of_rules;
                return _final_result;
            }
        }
        ++_number_of_data_items;
        _number_of_rules_used += number_of_rules;
        return _final_result; 
    }
    CATCH;
}


ksi::dataset ksi::three_way_decision_nfs::extract_poor_results(
    const ksi::dataset & data, 
    const std::vector<std::tuple<double, double, double>> & answers, 
    const double threshold_value, 
    const double maximal_deviation)
{
    try 
    {
        std::vector<std::size_t> indices;
        
        for (std::size_t i = 0; i < answers.size(); i++)
        {
            double elaborated;
            std::tie(std::ignore, elaborated, std::ignore) = answers[i];
            if (fabs(threshold_value - elaborated) < maximal_deviation)
                indices.push_back(i);
        }
        
        ksi::dataset poor_data;
        for (const auto i : indices)
        {
            poor_data.addDatum(*data.getDatum(i));
        }
        return poor_data;    
    }
    CATCH;
}

ksi::number ksi::three_way_decision_nfs::elaborate_answer(const ksi::datum& d) const
{
    ///@todo
    throw (std::string ("not implemented"));
}

std::string ksi::three_way_decision_nfs::get_nfs_description() const
{
    std::stringstream ss;
    std::string description {"three way decision neuro-fuzzy classifier"};
    ss << description << " composed of systems:";
    for (const auto & s : _cascade)
    {
        ss << " " << s->get_nfs_description();
    }
    return ss.str();
}

std::string ksi::three_way_decision_nfs::get_nfs_name() const
{
    std::string description {"3wdnfs-classifier"};
    
    std::stringstream ss;
    ss << description << get_cascade_names();
    return ss.str();
}

std::string ksi::three_way_decision_nfs::get_brief_nfs_name() const
{
    std::string description {"3wd"};
    
    std::stringstream ss;
    ss << description << get_brief_cascade_names();
    return ss.str();
}

std::string ksi::three_way_decision_nfs::get_cascade_names() const
{
   std::stringstream ss;
   for (const auto & s : _cascade)
   {
      ss << "-" << s->get_nfs_name();
   }
   return ss.str();
}

std::string ksi::three_way_decision_nfs::get_brief_cascade_names() const
{
   std::stringstream ss;
   for (const auto & s : _cascade)
   {
      ss << "-" << s->get_brief_nfs_name();
   }
   return ss.str();
}

std::string ksi::three_way_decision_nfs::print_f1scores_cascade() const 
{
    try 
    {
       const int PRECISION { 8}; 
       const int WIDTH_FLT {12};
       const int WIDTH_INT { 2};

       std::stringstream ss;
       // ---------------
       // Print the F1scores for all cascade depths:
       ss << "-------------------------" << std::endl;
       ss << "F1scores for the cascade:" << std::endl;
       ss << "depth\ttrain\ttest"<< std::endl;
       auto size = _cascade.size();
       auto train = _cascade_F1score_train.size();
       auto test  = _cascade_F1score_test.size();

       for (std::size_t i = 0; i < size; ++i)
       { 
          ss << std::setw(WIDTH_INT) << std::right <<  i + 1;

          if (i < train)
             ss << std::fixed << std::setw(WIDTH_FLT) << std::setprecision(PRECISION) << _cascade_F1score_train[i];
          else 
             ss << std::fixed << std::setw(WIDTH_FLT) << std::setprecision(PRECISION) << "---";

          if (i < test)
             ss << std::fixed << std::setw(WIDTH_FLT) << std::setprecision(PRECISION) << _cascade_F1score_test[i];
          else 
             ss << std::fixed << std::setw(WIDTH_FLT) << std::setprecision(PRECISION) << "---";
          ss << std::endl;
       }
       ss << "-------------------------" << std::endl;
       return ss.str();
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs::extra_report() const
{
    try 
    {
        std::stringstream ss;
        ss << *this << std::endl;
        ss << print_f1scores_cascade() << std::endl;

        return ss.str();
    }
    CATCH;
}

std::string ksi::three_way_decision_nfs::classification_intro() const
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
        
      //  model << "number of rules:     " << _nRules << std::endl;
      //  model << "number of clustering iterations: " << _nClusteringIterations << std::endl;
      //  model << "number of tuning interations:    " << _nTuningIterations << std::endl;
      //  model << "learning coefficient: " << _dbLearningCoefficient << std::endl;
        model << "train      data file: " << _train_data_file << std::endl;
        model << "validation data file: " << _validation_data_file << std::endl;
        model << "test       data file: " << _test_data_file << std::endl;
     //   model << "normalisation:   " << std::boolalpha << _bNormalisation << std::endl;
     //   if (_pModyfikator)
     //       model << "train data set modifier(s): " << _pModyfikator->print() << std::endl;
        
        auto report = extra_report ();
        if (not report.empty())
           model << report << std::endl;
          
        return model.str();   
    }
    CATCH;
}


void ksi::three_way_decision_nfs::printRulebase(std::ostream& ss)
{
    try
    {
        ss << std::endl;
        ss << "Rulebases of neuro-fuzzy systems in the cascade" << std::endl;
        ss << "-----------------------------------------------" << std::endl;
            
        ss << std::endl;
        ss << "number of classifiers: " << _cascade.size() << std::endl;
        
        
        std::size_t i = 1;
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            auto & p = _cascade[i];
            ss << std::endl;
            ss << "classifier: " << i << std::endl;
            ss << p->get_nfs_name() << std::endl;
            ss << "number of rules:              " << p->get_number_of_rules() << std::endl;
            ss << "threshold type:               " << ksi::to_string(p->get_threshold_type()) << std::endl;
            double threshold = p->get_threshold_value();
            ss << "threshold value:              " << threshold << std::endl;
            double delta = _noncommitment_widths[i]; 
            ss << "noncommitment width:          " << delta << std::endl;
            ss << "noncommintment interval:      [" << threshold - delta << ", " << threshold + delta << "]" << std::endl;         
            ss << "size of train dataset:        " << p->get_train_dataset_size() << std::endl;
            ss << "cardinality of train dataset: " << p->get_train_dataset_cardinality() << std::endl;
            ss << "--------------------------------------" << std::endl;
            ss << std::endl;       
            ss << "fuzzy rule base" << std::endl;       
            p->printRulebase(ss);
            ss << std::endl;       
            ss << "linguistic description of fuzzy rule base" << std::endl;       
            p->printLinguisticDescriptionRulebase(ss);
        }
        ss << "-----------------------------------------------" << std::endl;        
    }
    CATCH;
}

double ksi::three_way_decision_nfs::elaborate_threshold_value(
    std::vector<double>& Expected, 
    std::vector<double>& Elaborated, 
    double positiveClassvalue, 
    double negativeClassvalue, 
    const ksi::roc_threshold& type)
{
//     try 
//     {
//        throw std::string ("Do not use this method! This NFS has a cascade of NFSs. Each of them has its own threshold value."); 
//     }
//     CATCH;
    return 0.0;
}

std::string ksi::three_way_decision_nfs::get_classification_threshold_value() const
{
    return std::string {}; // empty string
}

double ksi::three_way_decision_nfs::get_number_of_rules () const
{
   return _dbTestAverageNumerOfRulesUsed;
}

std::string ksi::three_way_decision_nfs::report_average_number_of_rules_for_test() const 
{
    std::string stringified;
    if (std::isnan(_dbTestAverageNumerOfRulesUsed))
      stringified = "NaN";
    else 
       stringified = std::to_string(_dbTestAverageNumerOfRulesUsed);
           
    return std::string {"average number of rules used for one test  data item: "} + stringified;
}

std::string ksi::three_way_decision_nfs::report_average_number_of_rules_for_train() const 
{
    std::string stringified;
    if (std::isnan(_dbTrainAverageNumerOfRulesUsed))
      stringified = "NaN";
    else 
       stringified = std::to_string(_dbTrainAverageNumerOfRulesUsed);
           
    return std::string {"average number of rules used for one train data item: "} + stringified;
}

namespace ksi
{
    std::ostream & operator<< (std::ostream & ss, const ksi::three_way_decision_nfs & system)
    {
        ss << std::endl;
        ss << "Three way decision system" << std::endl;
        ss << "-------------------------" << std::endl;
        
        ss << std::endl;
        ss << "number of classifiers: " << system._cascade.size() << std::endl;
         
        for (std::size_t i = 0; i < system._cascade.size(); ++i)
        {
            auto & p = system._cascade[i];
            ss << "classifier: " << i << std::endl;
     //       ss << p->printRulebase() << std::endl;
            ss << p->get_nfs_name() << std::endl;
            ss << "number of rules:       " << p->get_number_of_rules() << std::endl;
            ss << "threshold type:        " << to_string(p->get_threshold_type()) << std::endl;
            double threshold = p->get_threshold_value();
            ss << "threshold value:              " << threshold << std::endl;
            double delta = system._noncommitment_widths[i]; 
            ss << "noncommitment width:          " << delta << std::endl;
            ss << "noncommintment interval:      [" << threshold - delta << ", " << threshold + delta << "]" << std::endl;         
            ss << "size of train dataset:        " << p->get_train_dataset_size() << std::endl;
            ss << "cardinality of train dataset: " << p->get_train_dataset_cardinality() << std::endl;
            ss << std::endl;
        }
        ss << "-------------------------" << std::endl;
        return ss;
    }
}

void ksi::three_way_decision_nfs::elaborate_cascade_f1scores()
{
    _cascade_F1score_train.clear();
    _cascade_F1score_test.clear();
    
    for (std::size_t i = 0; i < _cascade.size(); ++i)
    {
       _cascade_F1score_train.push_back(get_train_F1score_for_part_of_the_cascade(i)); 
       _cascade_F1score_test.push_back(get_test_F1score_for_part_of_the_cascade(i)); 
    }
}

void ksi::three_way_decision_nfs::run_extra_activities_for_the_model()
{
   ksi::three_way_decision_nfs::elaborate_cascade_f1scores();
}

ksi::three_way_decision_nfs_WP::three_way_decision_nfs_WP(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> &cascade,
    const std::string &train,
    const std::string &validation,
    const std::string &test,
    const std::string &result,
    std::function<std::tuple<double,double>(const std::vector<std::tuple<double, double, double>> &, const double& )> fitnessFunction
)
: three_way_decision_nfs(cascade, train, validation, test, result, 0.0)
, m_fitnessFunction(fitnessFunction) {
}

void ksi::three_way_decision_nfs_WP::createFuzzyRulebase(
    const ksi::dataset &train, const ksi::dataset &test, const ksi::dataset &validation)
{
    try 
    {
        auto zbior_treningowy = train;
        auto nAttributes = zbior_treningowy.getNumberOfAttributes(); 
        bool remove_system = false;
        for (std::size_t i = 0; i < _cascade.size(); i++)
        {
            if (remove_system)
            {
                _cascade[i] = nullptr;
                continue;
            }
            auto& pSystem = _cascade[i];
            pSystem->set_train_data_file(this->_train_data_file);
            pSystem->set_validation_data_file (this->_validation_data_file);
            pSystem->set_test_data_file (this->_test_data_file);
            pSystem->set_output_file(this->_output_file + std::to_string(i));
            pSystem->set_train_dataset(zbior_treningowy);
            pSystem->set_validation_dataset(validation);
            pSystem->set_test_dataset(test);
            pSystem->experiment_classification_core(); 
            
            // wydzielenie tych danych, które są zbyt bliskie progowi 
            auto results_train = pSystem->get_answers_for_train_classification();
            auto threshold_value = pSystem->get_threshold_value();
            auto [a, b] = m_fitnessFunction(results_train, threshold_value);
            _noncommitment_widths[i] = (b - a) / 2;
            auto new_threshold = (a + b) / 2;
            pSystem->set_threshold_value(new_threshold);
            pSystem->set_threshold_type(ksi::roc_threshold::manual);
            // zapisanie do zbioru_treningowego danych bliskich progowi
            zbior_treningowy = extract_poor_results(zbior_treningowy, results_train, threshold_value, _noncommitment_widths[i]); 
              
            if (zbior_treningowy.size() < nAttributes)
            {
                // wszystkie nastepne systemy trzeba skasowac
                remove_system = true;  
            }
        }
        _cascade.erase(
            std::remove_if(_cascade.begin(), _cascade.end(),
                [](std::shared_ptr<ksi::neuro_fuzzy_system> p) {return not p;}),
            _cascade.end()
        );
    }
    CATCH;
}
namespace WP{
    using numeric_response = double;
    using expected_class = double;
    using _ = double;
    std::map<double, std::tuple<int,int>> create_prefixes(const std::vector<std::tuple<expected_class, numeric_response, double>> & data)
    {
        auto data_copied = data;
        std::sort(data_copied.begin(), data_copied.end(),
            [](const auto & a, const auto & b) {return std::get<1>(a) < std::get<1>(b);});

        std::map<numeric_response, std::array<int, 2>> values_map;
        for (const auto&d : data_copied)
        {
            auto value = std::get<1>(d);
            if (values_map.find(value) == values_map.end())
            {
                values_map[value] = {0, 0};
            }
            values_map[value][(int)std::get<0>(d)]++;
        }
        std::map<double, std::tuple<int, int>> prefixes;
        std::array<int, 2> previous = {0, 0};
        std::size_t i = 0;
        for (auto it = values_map.begin(); it != values_map.end(); it++)
        {
            previous[0] += it->second[0];
            previous[1] += it->second[1];
            prefixes[it->first] = {previous[0], previous[1]};
            i++;
        }
        return prefixes;
        //std::vector<double> intervals(data.size());
        //auto prev = values_map.begin()->first;
        //for(auto i = 1; i < values_map.size(); i++)
        //{
        //    intervals[i-1] = std::next(values_map.begin(), i)->first + prev;
        //    prev = std::next(values_map.begin(), i)->first;
        //    intervals[i-1] /= 2;
        //}
        //intervals[values_map.size()-1] = std::next(values_map.begin(), values_map.size()-1)->first + 0.01;
        //std::map<double, std::tuple<int, int>> prefixes;
        //std::array<int, 2> previous = {0, 0};
        //std::size_t i = 0;
        //for (auto it = values_map.begin(); it != values_map.end(); it++)
        //{
        //    previous[0] += it->second[0];
        //    previous[1] += it->second[1];
        //    prefixes[intervals[i]] = {previous[0], previous[1]};
        //    i++;
        //}
        return prefixes;
    }

  double get_key_for_value(const std::map<double, std::tuple<int, int>>& prefixes, const double& value)
    {
        for (auto it = prefixes.rbegin(); it != prefixes.rend(); ++it) {
            if (it->first <= value) {
                return it->first;
            }
        }

        return prefixes.begin()->first;
    }

    double f1_score(const std::map<double, std::tuple<int, int>>& prefixes, const double& beginning, const double& end)
    {
        double tp = std::get<1>((prefixes.rbegin())->second) - std::get<1>(prefixes.at(end)); // @TODO ??
        double fp = std::get<0>((prefixes.rbegin())->second) - std::get<0>(prefixes.at(end));
        double fn = std::get<1>(prefixes.at(beginning));
        //std::cout << "For values: " << beginning << " and " << end << " TP: " << tp << " FP: " << fp << " FN: " << fn << std::endl;
        return 2*tp/(2*tp+fp+fn+std::numeric_limits<double>::epsilon());
    }
    double get_no_points_between(const std::map<double, std::tuple<int, int>>& prefixes, const double& beginning, const double& end)
    {
        auto no_0 = std::get<0>(prefixes.at(get_key_for_value(prefixes, end))) - std::get<0>(prefixes.at(get_key_for_value(prefixes, beginning)));
        auto no_1 = std::get<1>(prefixes.at(get_key_for_value(prefixes, end))) - std::get<1>(prefixes.at(get_key_for_value(prefixes, beginning)));
        return no_0 + no_1;
    }
    std::tuple<std::size_t, std::size_t> retrieve_initial(const std::map<double, std::tuple<int, int>>& prefixes)
    {
        std::size_t beginning = 0, end = prefixes.size() - 1;
        auto no = end;
        for(auto it = prefixes.begin(); it != prefixes.end(); it++)
        {
            if (!std::get<1>(std::next(it,1)->second))
            {
                beginning++;
            }
            else
            {
                break;
            }
        }
        for(auto it = prefixes.rbegin(); it != prefixes.rend(); it++)
        {
            if (!(std::get<0>(std::next(prefixes.rend(),1)->second)-std::get<0>(std::next(it,1)->second)))
            {
                end--;
            }
            else
            {
                break;
            }
        }
        return {beginning, end};
    }
    std::tuple<double,double> get_noncommitment_based_on_threshold(const std::vector<std::tuple<double, double, double>> & data, const double& threshold)
    {
        auto prefixes = create_prefixes(data);
        //for (const auto& [key, value] : prefixes)
        //{
        //    std::cout << "r_i: " << key << " c_n: " << std::get<0>(value) << " c_p:" << std::get<1>(value) << std::endl;
        //}
        auto best_score_so_far = std::numeric_limits<double>::max();
        double delta = threshold - prefixes.begin()->first;
        auto best_delta = delta;
        try 
        {
            while(delta > 0)
            {
                auto beginning_value = get_key_for_value(prefixes, threshold-delta);
                auto end_value = get_key_for_value(prefixes, threshold+delta);
                auto f1 = f1_score(prefixes, beginning_value, end_value);
                auto frac_between = get_no_points_between(prefixes, beginning_value, end_value)/data.size();
                auto score = 1/(f1+std::numeric_limits<double>::epsilon()) + pow(frac_between,2);
                //std::cout<< "Score for delta = " << delta << " is " << score << " Number between is:" << frac_between*data.size() << " F1 score is:" << f1 << std::endl;
                if (score < best_score_so_far)
                {
                    best_score_so_far = score;
                    best_delta = delta;
                }
                delta -= 0.01;
            }
        }
        catch(std::exception& es)
        {
            std::cerr << es.what() << std::endl;
        }
        //std::cout << "Best delta is: " << best_delta << std::endl;
        return {threshold-best_delta, threshold+best_delta};
    }
    std::tuple<double,double> get_noncommitment_based_on_threshold_hard_penalize(const std::vector<std::tuple<double, double, double>> & data, const double& threshold)
    {
        auto prefixes = create_prefixes(data);
        auto best_score_so_far = std::numeric_limits<double>::max();
        double delta = threshold - prefixes.begin()->first;
        auto best_delta = delta;
        try 
        {
            while(delta > 0)
            {
                auto beginning_value = get_key_for_value(prefixes, threshold-delta);
                auto end_value = get_key_for_value(prefixes, threshold+delta);
                auto f1 = f1_score(prefixes, beginning_value, end_value);
                auto frac_between = get_no_points_between(prefixes, beginning_value, end_value)/data.size();
                auto score = 1/(f1+std::numeric_limits<double>::epsilon()) + 0.5*pow(frac_between,2);
                if (score < best_score_so_far)
                {
                    best_score_so_far = score;
                    best_delta = delta;
                }
                delta -= 0.01;
            }
        }
        catch(std::exception& es)
        {
            std::cerr << es.what() << std::endl;
        }
        return {threshold-best_delta, threshold+best_delta};
    }
    std::tuple<double,double> get_noncommitment(const std::vector<std::tuple<double, double, double>> & data, const double& threshold)
    {
        throw std::runtime_error("SHOULD NOT BE USED");
        auto prefixes = create_prefixes(data);
        auto [beginning, end] = retrieve_initial(prefixes);
        auto best_score_so_far = 1000000.0;
        auto best_end = end;
        auto best_beginning = beginning;
        for(auto i = beginning; i <= end; ++i)
        {
            for (auto j = i; j <= end; ++j)
            {
                auto beginning_value = std::next(prefixes.begin(),i)->first;
                auto end_value = std::next(prefixes.begin(),j)->first;
                auto f1 = f1_score(prefixes, beginning_value, end_value);
                auto frac_between = get_no_points_between(prefixes, beginning_value, end_value)/data.size();
                auto score = 1/(f1+0.00001) + pow(frac_between,2);
                if (score < best_score_so_far)
                {
                    best_score_so_far = score;
                    best_beginning = i;
                    best_end = j;
                }
            }
        }
        return {std::next(prefixes.begin(),beginning)->first, std::next(prefixes.begin(),end)->first};
    }
}

// ============================================================================
// Implementation of three_way_decision_nfs_meta
// ============================================================================

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta() : three_way_decision_nfs()
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade
) : three_way_decision_nfs(cascade), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const std::string& train, 
    const std::string& test, 
    const std::string& result
) : three_way_decision_nfs(cascade, train, test, result, 0.0), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const std::string& train,
    const std::string& validation, 
    const std::string& test, 
    const std::string& result
) : three_way_decision_nfs(cascade, train, validation, test, result, 0.0), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const ksi::dataset& train, 
    const ksi::dataset& test, 
    const std::string& result
) : three_way_decision_nfs(cascade, train, test, result, 0.0), _meta_classifiers(meta_cascade)
{
}

ksi::three_way_decision_nfs_meta::three_way_decision_nfs_meta(
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
    const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
    const ksi::dataset& train,
    const ksi::dataset& validation, 
    const ksi::dataset& test, 
    const std::string& result
) : three_way_decision_nfs(cascade, train, validation, test, result, 0.0), _meta_classifiers(meta_cascade)
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
    const ksi::dataset& train, 
    const ksi::dataset& test, 
    const ksi::dataset& validation
)
{
    try 
    {
        auto zbior_treningowy = train;
        auto nAttributes = zbior_treningowy.getNumberOfAttributes(); 
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
                // Train primary classifier
                auto& pSystem = _cascade[i];
                pSystem->set_train_data_file(this->_train_data_file);
                pSystem->set_validation_data_file(this->_validation_data_file);
                pSystem->set_test_data_file(this->_test_data_file);
                pSystem->set_output_file(this->_output_file + "-primary-" + std::to_string(i));
                pSystem->set_train_dataset(zbior_treningowy);
                pSystem->set_validation_dataset(validation);
                pSystem->set_test_dataset(test);
                pSystem->experiment_classification_core(); 
                
                // Get results from primary classifier
                auto results_train = pSystem->get_answers_for_train_classification();
                
                // Train meta-classifier for this level (except for the last level)
                if (i < _meta_classifiers.size())
                {
                    auto& pMetaSystem = _meta_classifiers[i];
                    
                    // Create meta-training data: label 1.0 if correct, -1.0 if incorrect
                    auto meta_train_data = create_meta_training_data(zbior_treningowy, results_train);
                    
                    // Set positive and negative classes for meta-classifier
                    pMetaSystem->set_positive_class(1.0);   // correct predictions
                    pMetaSystem->set_negative_class(0.0);  // incorrect predictions
                    
                    // Use Youden index for meta-classifier threshold
                    pMetaSystem->set_threshold_type(ksi::roc_threshold::youden);
                    
                    pMetaSystem->set_train_data_file(this->_train_data_file);
                    pMetaSystem->set_validation_data_file(this->_validation_data_file);
                    pMetaSystem->set_test_data_file(this->_test_data_file);
                    pMetaSystem->set_output_file(this->_output_file + "-meta-" + std::to_string(i));
                    pMetaSystem->set_train_dataset(meta_train_data);
                    pMetaSystem->set_validation_dataset(validation);
                    pMetaSystem->set_test_dataset(test);
                    pMetaSystem->experiment_classification_core();
                    
                    // Get meta-classifier predictions on training data
                    auto meta_results = pMetaSystem->get_answers_for_train_classification();
                    
                    // Get meta-classifier's Youden threshold
                    auto meta_threshold = pMetaSystem->get_threshold_value();
                    
                    // Extract items that meta-classifier predicts will be incorrectly classified
                    // These are items where numeric score < threshold (predicting class -1.0)
                    std::vector<std::size_t> indices_for_next_level;
                    for (std::size_t j = 0; j < meta_results.size(); j++)
                    {
                        double meta_elaborated_numeric;
                        std::tie(std::ignore, meta_elaborated_numeric, std::ignore) = meta_results[j];
                        
                        // If meta-classifier predicts incorrect (numeric < threshold), pass to next level
                        if (meta_elaborated_numeric < meta_threshold)
                            indices_for_next_level.push_back(j);
                    }
                    
                    // Create dataset for next level
                    ksi::dataset next_level_data;
                    for (const auto j : indices_for_next_level)
                    {
                        next_level_data.addDatum(*zbior_treningowy.getDatum(j));
                    }
                    
                    zbior_treningowy = next_level_data;
                }
                
                // Check if we have enough data to continue
                if (zbior_treningowy.size() < nAttributes)
                {
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

