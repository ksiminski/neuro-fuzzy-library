
#ifndef THREE_WAY_DECISION_NFS_WITH_AUTOMATIC_NONCOMMITMENT_H
#define THREE_WAY_DECISION_NFS_WITH_AUTOMATIC_NONCOMMITMENT_H

#include <vector>
#include <memory>
#include <map>

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../neuro-fuzzy/three_way_decision_nfs.h"

namespace ksi
{
    std::map<double, std::tuple<int,int>> create_prefixes(const std::vector<std::tuple<double, double, double>> & data);
    std::tuple<double,double> get_noncommitment(const std::vector<std::tuple<double, double, double>> & data, const double& threshold);
    std::tuple<double,double> get_noncommitment_based_on_threshold(const std::vector<std::tuple<double, double, double>> & data, const double& threshold);
    std::tuple<double,double> get_noncommitment_based_on_threshold_hard_penalize(const std::vector<std::tuple<double, double, double>> & data, const double& threshold);

    class three_way_decision_nfs_with_automatic_noncommitment : public three_way_decision_nfs
    {
        protected:
        std::function<std::tuple<double,double>(const std::vector<std::tuple<double, double, double>> &, const double&)> m_fitnessFunction;
    public:
        three_way_decision_nfs_with_automatic_noncommitment (const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> & cascade, 
                              const std::string & train, 
                              const std::string & validation,
                              const std::string & test, 
                              const std::string & result,
                              std::function<std::tuple<double,double>(const std::vector<std::tuple<double, double, double>> &, const double&)> fitnessFunction);
        ~three_way_decision_nfs_with_automatic_noncommitment() override = default;
        void createFuzzyRulebase(const ksi::dataset& train, const ksi::dataset & test, const ksi::dataset & validation) override;
    };

}

#endif
