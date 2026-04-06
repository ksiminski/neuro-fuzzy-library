
#include <vector>
#include <cmath>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../common/datum.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../metrics/metric-minkowski-weighted.h"
#include "../partitions/cluster.h"
#include "../service/exception.h"

ksi::prototype_minkowski::prototype_minkowski (const double m) : ksi::prototype(), _m(m)
{
}

ksi::prototype_minkowski::prototype_minkowski (const cluster & cl, const double m) : _m (m)
{
   try 
   {
      auto nAttr = cl.get_number_of_desciptors();
      for (std::size_t a = 0; a < nAttr; a++)
      {
         auto p = cl.getAddressOfDescriptor(a);
         addDescriptor(*p);
      }       
   }
   CATCH;
}

ksi::prototype_minkowski::~prototype_minkowski ()
{
   // delete what is to delete

}

double ksi::prototype_minkowski::get_similarity(const ksi::datum & d) const
{
    try 
    {
        return get_similarity(d.getVector());
    }
    CATCH;
}

double ksi::prototype_minkowski::get_similarity(const std::vector<double>& data) const
{
    try 
    {
        ksi::metric_minkowski_weighted metryka (_m, _weights);
        return distance_to_similarity(metryka.calculateDistance(_centre, data));
    }
    CATCH;
}

void ksi::prototype_minkowski::addDescriptor(const ksi::descriptor & d)
{
    try 
    {
       _centre.push_back(d.getCoreMean());
       auto s = d.getFuzzification();
       _weights.push_back(1.0 / s);
    }
    CATCH;
}

void ksi::prototype_minkowski::cummulate_differentials(std::vector<double> X, double partial_differential)
{
    try 
    {
        auto similarity = last_firingStrength;
        auto suma {0.0};
        
        auto size = X.size();
        
        for (std::size_t i = 0; i < size; i++) // for each attribute
        {
            auto difference = std::fabs(X[i] - _centre[i]);
            suma += pow(difference, _m);
        }
        auto suma_do_m_1 = pow(suma, (1.0 / _m) - 1.0);
        
        auto factor { similarity * (1.0 / _m) * suma_do_m_1 } ;
        for (std::size_t i = 0; i < size; i++)
        {
            auto difference = std::fabs(X[i] - _centre[i]);
            auto signum = ksi::utility_math::signum(X[i] - _centre[i]);
            
            _d_centre[i]  += partial_differential * factor * _m * pow(difference, _m - 1) * signum;
            _d_weights[i] += partial_differential * factor *      pow(difference, _m)     * (-1);
        }
    } CATCH;
}

void ksi::prototype_minkowski::reset_differentials()
{
    auto size = _centre.size();
    
    _d_centre  = std::vector<double> (size, 0.0);
    _d_weights = std::vector<double> (size, 0.0);
}

std::ostream & ksi::prototype_minkowski::print(std::ostream& ss) const
{
    ss << "prototype with Minkowski metric" << std::endl;
    ss << "exponent: m = " << _m << std::endl;
    ss << "centre:   " << _centre  << std::endl;
    ss << "weights:  " << _weights << std::endl; 
    
    return ss;
}

void ksi::prototype_minkowski::actualise_parameters(double eta)
{
    try 
    {
        auto csize = _centre.size();
        for (std::size_t i = 0; i < csize; i++)
        {
            _centre[i] -= (eta * _d_centre[i]);
            
            auto stare = _weights[i];
            _weights[i] -= (eta * _d_weights[i]);
            if (_weights[i] < 0) // Weights cannot be negative.
                _weights[i] = stare;
        }
        
        _d_weights = _d_centre = std::vector<double> (csize, 0.0);
    } CATCH;
}

// std::string ksi::prototype_minkowski::get_name() const
// {
//     return std::string("Prot-Mink");
// }
// 
// std::string ksi::prototype_minkowski::get_description() const
// {
//     return std::string ("Minkowski prototype");
// }

void ksi::prototype_minkowski::justified_granularity_principle(const std::vector<std::vector<double> >& X, const std::vector<double>& Y)
{
    try 
    {
        std::size_t nAtrybut = _centre.size();
        
        std::vector<double> differentials_centre (nAtrybut, 0);
        std::vector<double> differentials_weights    (nAtrybut, 0);
        
        double ETA { 0.0000001 };
        const int nIteration { 50 };
        
//         debug(nIteration);
        auto criterion_prev = 0.0;
        
        for (int i = 0; i < nIteration; i++)
        {
            //// dopasowanie ETY
            auto criterion = criterion_function(X, Y);
//             debug(criterion);
            
            if (criterion < criterion_prev)
            {
                ETA *= 0.1;
//                 debug (ETA);
            }
            criterion_prev = criterion;
            
            //// koniec dopasowania ETY
//             debug(debug_criterion_function(X, Y));
//             debug(_centre);
//             debug(_weights);
            
            auto [diffs_centre, diffs_weight] = differentials_justified_granularity_principle(X, Y);
            if (is_valid(diffs_centre))
                differentials_centre  += diffs_centre;
            if (is_valid(diffs_weight))
                differentials_weights += diffs_weight;
            
            auto previous_weights = _weights;
        
            _centre  += differentials_centre  * ETA;
            _weights += differentials_weights * ETA;

            for (std::size_t a = 0; a < nAtrybut; a++)
            {
                if (_weights[a] < 0)
                    _weights[a] = previous_weights[a];
            }
        }
    } CATCH;
}

std::pair<ksi::Matrix<double>, ksi::Matrix<double>> ksi::prototype_minkowski::similarity_differentials(const std::vector<std::vector<double>>& X)
{
    try 
    {
        auto nAttributes = _centre.size();  // number of attributes
        auto nDataItems  = X.size();        // number of data items
            
        ksi::Matrix<double> dsim_da(nDataItems, nAttributes);  // differentials of similarity with regard to centres.
        ksi::Matrix<double> dsim_dz(nDataItems, nAttributes);  // differentials of similarity with regard to weights.
            
        for (std::size_t x = 0; x < nDataItems; x++)
        {
            double common_factor = 0;
            for (std::size_t i = 0; i < nAttributes; i++)
            {
                common_factor += _weights[i] * pow( std::fabs (_centre[i] - X[x][i]), _m);
            }
            auto common_factor_1_m   = pow(common_factor, 1.0 / _m);
            auto common_factor_1_m_1 = pow(common_factor, (1.0 / _m ) - 1.0);
            auto factor = exp(- common_factor_1_m) * (-1) / _m * common_factor_1_m_1; 
            
            
            for (std::size_t a = 0; a < nAttributes; a++)
            {
                auto difference = X[x][a] - _centre[a];
                dsim_da(x, a) = factor * _weights[a] * _m * pow(std::fabs(difference), _m - 1) * (-1) * ksi::utility_math::signum(difference); 
                
                dsim_dz(x, a) = factor * pow(std::fabs(difference), _m);
            }
        }
        return { dsim_da, dsim_dz };
    } CATCH;
}
 
       
std::pair<std::vector<double>, std::vector<double>> ksi::prototype_minkowski::decision_attribute_average_differentials (const std::vector<double> & Y, const ksi::Matrix<double> & dsim_da, const ksi::Matrix<double> & dsim_dz, const double cardinality)
{
    try 
    {
        auto nAttributes = _centre.size();  // number of attributes
        auto nDataItems  = Y.size();        // number of data items
        
        std::vector<double> dyaverage_da (nAttributes, 0.0);
        std::vector<double> dyaverage_dz (nAttributes, 0.0);
        
        for (std::size_t x = 0; x < nDataItems; x++)
        {
            for (std::size_t a = 0; a < nAttributes; a++)
            {
                dyaverage_da[a] += Y[x] * dsim_da.get_value(x, a);
                dyaverage_dz[a] += Y[x] * dsim_dz.get_value(x, a);
            }
        }
        
        for (auto & d : dyaverage_da)
            d /= cardinality * cardinality;
        for (auto & d : dyaverage_dz)
            d /= cardinality * cardinality;
        
        return { dyaverage_da, dyaverage_dz };
    } CATCH;
}

std::pair<std::vector<double>, std::vector<double>> ksi::prototype_minkowski::cardinality_variance_differentials (
    const std::vector<double> & Y,
    const std::vector<double> & similarities,
    const std::vector<double> & dyaverage_da,
    const std::vector<double> & dyaverage_dz,
    const ksi::Matrix<double> & dsim_da, 
    const ksi::Matrix<double> & dsim_dz, 
    const double & average_y, 
    const double & cardinality)
{
    try 
    {
        auto nAttributes = _centre.size();  // liczba atrybutow
        auto nDataItems  = Y.size();        // liczba danych
        // suma pomocniczna:
        double sum_of_product_of_squared_probability_differences {0.0};
        for (std::size_t x = 0; x < nDataItems; x++)
        {
            double difference = Y[x] - average_y;
            sum_of_product_of_squared_probability_differences += difference * difference * similarities[x];
        }
        
        // wyznaczenie rozniczek kardynalności (kappa)
        // wyznaczenie rozniczek wariancji     (zeta)
        
        auto adder = [] (const double a, const double b) {return a + b;};
        std::vector<double> dkappa_da (nAttributes);
        std::vector<double> dkappa_dz (nAttributes);
        
        std::vector<double> dzeta_da (nAttributes);
        std::vector<double> dzeta_dz (nAttributes);
        
        for (std::size_t a = 0; a < nAttributes; a++)
        {
            dkappa_da[a] = dsim_da.accumulate_column(a, 0.0, adder);
            dkappa_dz[a] = dsim_dz.accumulate_column(a, 0.0, adder);
            
            double suma_dla_a {0};
            double suma_dla_z {0};
            
            for (std::size_t x = 0; x < nDataItems; x++)
            {
                double difference = Y[x] - average_y;
                suma_dla_a += -2 * difference * dyaverage_da[a] * similarities[x] 
                            + difference * difference * dsim_da.get_value(x, a);
                suma_dla_z += -2 * difference * dyaverage_dz[a] * similarities[x] 
                            + difference * difference * dsim_dz.get_value(x, a);
            }
            
            dzeta_da[a] = (cardinality * suma_dla_a - dkappa_da[a] * sum_of_product_of_squared_probability_differences) / (cardinality * cardinality); 
            
            dzeta_dz[a] = (cardinality * suma_dla_z - dkappa_dz[a] * sum_of_product_of_squared_probability_differences) / (cardinality * cardinality); 
        }          
        
        std::vector<double> differentials_a = dkappa_da + dzeta_da;
        std::vector<double> differentials_z = dkappa_dz + dzeta_dz;
        
        return {differentials_a, differentials_z};
    } 
    CATCH;
}

