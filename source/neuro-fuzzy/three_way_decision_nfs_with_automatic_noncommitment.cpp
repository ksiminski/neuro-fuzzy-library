#include "../neuro-fuzzy/three_way_decision_nfs_with_automatic_noncommitment.h"

ksi::three_way_decision_nfs_with_automatic_noncommitment::three_way_decision_nfs_with_automatic_noncommitment(
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

void ksi::three_way_decision_nfs_with_automatic_noncommitment::createFuzzyRulebase(
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
namespace ksi
{
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

