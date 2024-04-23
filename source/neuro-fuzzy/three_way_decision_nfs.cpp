
#include <memory>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>
#include <syncstream>

#include "../neuro-fuzzy/three_way_decision_nfs.h"
#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../auxiliary/tempus.h"
#include "../service/debug.h"

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


void ksi::three_way_decision_nfs::copy_fields(const ksi::three_way_decision_nfs& _3wnfs)
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
   
   copy_fields(wzor);
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
   
   copy_fields(wzor);

   return *this;
}

ksi::three_way_decision_nfs::three_way_decision_nfs (ksi::three_way_decision_nfs && wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // swap what is to swap
   std::swap(_cascade, wzor._cascade);
   copy_fields(wzor);
}

ksi::three_way_decision_nfs & ksi::three_way_decision_nfs::operator= (ksi::three_way_decision_nfs && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap
   std::swap(_cascade, wzor._cascade);
   copy_fields(wzor);
   
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
    throw (std::string ("not implemented"));
}

void ksi::three_way_decision_nfs::createFuzzyRulebase(int, int, double, const ksi::dataset& train, const ksi::dataset& validate)
{
    createFuzzyRulebase(train, this->_TestDataset, validate); 
}


/// @todo Po co test tutaj?
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
        std::erase_if(_cascade, [](std::shared_ptr<ksi::neuro_fuzzy_system> p) {return not p;});
    }
    CATCH;
}

/** @todo Tutaj jest problem. 3WNFS powinien zwracać już gotową klasę, a zwraca wartość numeryczną. Ale przecież każdy z systemów w kaskadzie ma swój własny próg. To trzeba jakoś fikuśnie przerobić */
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

ksi::dataset ksi::three_way_decision_nfs::extract_poor_results(
    const ksi::dataset & data, 
    const std::vector<std::tuple<double, double, double>> & results_train, 
    const double threshold_value, 
    const double maximal_deviation)
{
    try 
    {
        std::vector<std::size_t> indices;
        
        for (std::size_t i = 0; i < results_train.size(); i++)
        {
            double elaborated;
            std::tie(std::ignore, elaborated, std::ignore) = results_train[i];
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

std::string ksi::three_way_decision_nfs::extra_report() const
{
    try 
    {
        std::stringstream ss;
        ss << *this << std::endl;
        
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
            ss << "threshold value:              " << p->get_threshold_value() << i << std::endl;
            ss << "noncommitment width:          " << _noncommitment_widths[i] << std::endl;
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
        
        
         
        for (std::size_t i = 0; i < system._cascade.size(); i++)
        {
            auto & p = system._cascade[i];
            ss << "classifier: " << i << std::endl;
     //       ss << p->printRulebase() << std::endl;
            ss << p->get_nfs_name() << std::endl;
            ss << "number of rules:       " << p->get_number_of_rules() << std::endl;
            ss << "threshold type:        " << to_string(p->get_threshold_type()) << std::endl;
            ss << "threshold value:       " << p->get_threshold_value() << std::endl; 
            ss << "noncommitment width:   " << system._noncommitment_widths[i] << std::endl;
            ss << std::endl;
        }
        ss << "-------------------------" << std::endl;
        return ss;
    }
}
