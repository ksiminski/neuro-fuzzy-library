
#include <vector>
#include <cmath>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../common/datum.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../metrics/metric-minkowski-weighted.h"

ksi::prototype_minkowski::prototype_minkowski (const double m) : ksi::prototype(), _m(m)
{
}

ksi::prototype_minkowski::~prototype_minkowski ()
{
   // delete what is to delete

}
/*
ksi::prototype_minkowski::prototype_minkowski (const ksi::prototype_minkowski & wzor) : ksi::prototype(wzor)
{
   // copy what is to copy

}

ksi::prototype_minkowski & ksi::prototype_minkowski::operator= (const ksi::prototype_minkowski & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_minkowski::prototype_minkowski (ksi::prototype_minkowski && wzor) : ksi::prototype(wzor)
{
   // swap what is to swap

}

ksi::prototype_minkowski & ksi::prototype_minkowski::operator= (ksi::prototype_minkowski && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/

// ksi::premise * ksi::prototype_minkowski::clone() const
// {
//     return new ksi::prototype_minkowski(*this);
// }

 

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
        /*
        auto size = _centre.size();
        
        if (size != data.size())
            throw std::string {"Vector sizes do not match (" + std::to_string(size) + " != " + std::to_string(data.size()) + "."};
        
        double sum = 0;
        for (std::size_t i = 0; i < size; i++)
        {
            sum += pow( std::fabs (_centre[i] - data[i]), _m);
        }
        return pow(sum, 1.0 / _m);
        */
    }
    CATCH;
}

void ksi::prototype_minkowski::addDescriptor(const ksi::descriptor & d)
{
    _centre.push_back(d.getCoreMean());
    auto s = d.getFuzzification();
    _weights.push_back(1.0 / s);
    
}

void ksi::prototype_minkowski::cummulate_differentials(std::vector<double> X, 
                                                       double partial_differential)
{
    try 
    {
        auto similarity = last_firingStrength;
        auto suma {0.0};
        
        auto size = X.size();
        
        for (std::size_t i = 0; i < size; i++)
        {
            auto roznica = std::fabs(X[i] - _centre[i]);
            suma += pow(roznica, _m);
        }
        auto suma_do_m_1 = pow(suma, (1.0 / _m) - 1.0);
        
        auto czynnik { similarity * (1.0 / _m) * suma_do_m_1 } ;
        for (std::size_t i = 0; i < size; i++)
        {
            auto roznica = std::fabs(X[i] - _centre[i]);
            auto znak = ksi::utility_math::signum(X[i] - _centre[i]);
            
            _d_centre[i]  += partial_differential * czynnik * _m * pow(roznica, _m - 1) * znak;
            _d_weights[i] += partial_differential * czynnik *      pow(roznica, _m)     * (-1);
        }
    } CATCH;
}


void ksi::prototype_minkowski::reset_differentials()
{
    auto size = _centre.size();
    
    _d_centre  = std::vector<double> (size, 0.0);
    _d_weights = std::vector<double> (size, 0.0);
}

std::ostream & ksi::prototype_minkowski::Print(std::ostream& ss) const
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
            if (_weights[i] < 0)
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
//     return std::string ("Minkowski prototypes");
// }

void ksi::prototype_minkowski::justified_granularity_principle(const std::vector<std::vector<double> >& X, const std::vector<double>& Y)
{
    try 
    {
        std::size_t nAtrybut = _centre.size();
        
        std::vector<double> rozniczki_centre (nAtrybut, 0);
        std::vector<double> rozniczki_wag    (nAtrybut, 0);
        
        double ETA { 0.0000001 };
        const int nIteracje { 50 };
        
//         debug(nIteracje);
        auto criterion_prev = 0.0;
        
//         debug("=========================================================");
        for (int i = 0; i < nIteracje; i++)
        {
            //// dopasowanie ETY
            auto criterion = debug_criterion_function(X, Y);
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
                rozniczki_centre += diffs_centre;
            if (is_valid(diffs_weight))
                rozniczki_wag    += diffs_weight;
            
            auto previous_weights = _weights;
        
            _centre  += rozniczki_centre * ETA;
            _weights += rozniczki_wag    * ETA;

//             _centre  -= rozniczki_centre * ETA;
//             _weights -= rozniczki_wag    * ETA;
            
            for (std::size_t a = 0; a < nAtrybut; a++)
            {
                if (_weights[a] < 0)
                    _weights[a] = previous_weights[a];
            }
//             debug(debug_criterion_function(X, Y));
        }
    } CATCH;
}

std::tuple<double, double, std::vector<double>> ksi::prototype_minkowski::cardinality_similarities
(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const 
{
    try 
    {
        auto nKrotka = X.size();
        
        double kardynalnosc = 0;
        double srednia_y_licznik = 0;
        std::vector<double> similarities(nKrotka, 0);
            
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            auto sim = get_similarity(X[x]);
            similarities[x] = sim;
            kardynalnosc += sim;
            srednia_y_licznik += sim * Y[x];  
        }
        auto srednia_y = srednia_y_licznik / kardynalnosc;  // srednia atrybutu decyzyjnego dla prototypu
        
        return { kardynalnosc, srednia_y, similarities };
    } CATCH;
}

std::pair<ksi::Matrix<double>, ksi::Matrix<double>> ksi::prototype_minkowski::similarity_differentials(const std::vector<std::vector<double>>& X)
{
    try 
    {
        auto nAtrybut = _centre.size();  // liczba atrybutow
        auto nKrotka  = X.size();        // liczba danych
            
        ksi::Matrix<double> dsim_da(nKrotka, nAtrybut);  // rozniczki podobienstwa
        ksi::Matrix<double> dsim_dz(nKrotka, nAtrybut);
            
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            double nawias = 0;
            for (std::size_t i = 0; i < nAtrybut; i++)
            {
                nawias += _weights[i] * pow( std::fabs (_centre[i] - X[x][i]), _m);
            }
            auto nawias_1_m   = pow(nawias, 1.0 / _m);
            auto nawias_1_m_1 = pow(nawias, (1.0 / _m ) - 1.0);
            auto czynnik = exp(- nawias_1_m) * (-1) / _m * nawias_1_m_1; 
            
            
            for (std::size_t a = 0; a < nAtrybut; a++)
            {
                auto roznica = X[x][a] - _centre[a];
                dsim_da(x, a) = czynnik * _weights[a] * _m * pow(std::fabs(roznica), _m - 1) * (-1) * ksi::utility_math::signum(roznica); 
                
                dsim_dz(x, a) = czynnik * pow(std::fabs(roznica), _m);
            }
        }
        return { dsim_da, dsim_dz };
    } CATCH;
}
 
       
std::pair<std::vector<double>, std::vector<double>> ksi::prototype_minkowski::   decision_attribute_average_differentials (const std::vector<double> & Y,                                                                                                                           const ksi::Matrix<double> & dsim_da,                                                                                                                           const ksi::Matrix<double> & dsim_dz,                                                                                                                           const double kardynalnosc)
{
    try 
    {
        auto nAtrybut = _centre.size();  // liczba atrybutow
        auto nKrotka  = Y.size();        // liczba danych
        
        std::vector<double> dysrednia_da (nAtrybut, 0.0);
        std::vector<double> dysrednia_dz (nAtrybut, 0.0);
        
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            for (std::size_t a = 0; a < nAtrybut; a++)
            {
                dysrednia_da[a] += Y[x] * dsim_da.get_value(x, a);
                dysrednia_dz[a] += Y[x] * dsim_dz.get_value(x, a);
            }
        }
        
        for (auto & d : dysrednia_da)
            d /= kardynalnosc * kardynalnosc;
        for (auto & d : dysrednia_dz)
            d /= kardynalnosc * kardynalnosc;
        
        return { dysrednia_da, dysrednia_dz };
    } CATCH;
}

std::pair<std::vector<double>, std::vector<double>> ksi::prototype_minkowski::cardinality_variance_differentials (
    const std::vector<double> & Y,
    const std::vector<double> & similarities,
    const std::vector<double> & dysrednia_da,
    const std::vector<double> & dysrednia_dz,
    const ksi::Matrix<double> & dsim_da, 
    const ksi::Matrix<double> & dsim_dz, 
    const double & srednia_y, 
    const double & kardynalnosc)
{
    try 
    {
        auto nAtrybut = _centre.size();  // liczba atrybutow
        auto nKrotka  = Y.size();        // liczba danych
        // suma pomocniczna:
        double suma_iloczynu_kwadratow_roznic_podobienstwa {0.0};
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            double roznica = Y[x] - srednia_y;
            suma_iloczynu_kwadratow_roznic_podobienstwa += roznica * roznica * similarities[x];
        }
        
        // wyznaczenie rozniczek kardynalnosci (kappa)
        // wyznaczenie rozniczek wariancji     (zeta)
        
        auto dodawacz = [] (const double a, const double b) {return a + b;};
        std::vector<double> dkappa_da (nAtrybut);
        std::vector<double> dkappa_dz (nAtrybut);
        
        std::vector<double> dzeta_da (nAtrybut);
        std::vector<double> dzeta_dz (nAtrybut);
        
        for (std::size_t a = 0; a < nAtrybut; a++)
        {
            dkappa_da[a] = dsim_da.accumulate_column(a, 0.0, dodawacz);
            dkappa_dz[a] = dsim_dz.accumulate_column(a, 0.0, dodawacz);
            
            double suma_dla_a {0};
            double suma_dla_z {0};
            
            for (std::size_t x = 0; x < nKrotka; x++)
            {
                double roznica = Y[x] - srednia_y;
                suma_dla_a += -2 * roznica * dysrednia_da[a] * similarities[x] 
                            + roznica * roznica * dsim_da.get_value(x, a);
                suma_dla_z += -2 * roznica * dysrednia_dz[a] * similarities[x] 
                            + roznica * roznica * dsim_dz.get_value(x, a);
            }
            
            dzeta_da[a] = (kardynalnosc * suma_dla_a - dkappa_da[a] * suma_iloczynu_kwadratow_roznic_podobienstwa) / (kardynalnosc * kardynalnosc); 
            
            dzeta_dz[a] = (kardynalnosc * suma_dla_z - dkappa_dz[a] * suma_iloczynu_kwadratow_roznic_podobienstwa) / (kardynalnosc * kardynalnosc); 
        }          
        
        std::vector<double> rozniczki_a = dkappa_da - dzeta_da;
        std::vector<double> rozniczki_z = dkappa_dz - dzeta_dz;
        
        return {rozniczki_a, rozniczki_z};
    } CATCH;
}

// std::pair<std::vector<double>, std::vector<double> > ksi::prototype_minkowski::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X,
//                                                                                                                            const std::vector<double> & Y)
// {
//     try 
//     {
//         if (X.size() != Y.size())
//             throw std::string { "Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};
//         
//         // wyznaczenie kardynalnosci prototypu, 
//         //             sredniej wartosci atrybutu decyzyjnego
//         //             podobienstw do prototypu dla danych
//         auto [kardynalnosc, srednia_y, similarities] = cardinality_similarities(X, Y);
//         
//         // wyznaczenie rozniczek podobienstwa:
//         auto [dsim_da, dsim_dz] = similarity_differentials (X);
//                       
//         // wyznaczenie rozniczek atrybutu decyzyjnego
//         auto [dysrednia_da, dysrednia_dz] = decision_attribute_average_differentials(Y, dsim_da, dsim_dz, kardynalnosc);
//         
//         // wyznaczenie rozniczek kardynalnosci i wariancji:
//         auto [rozniczki_a, rozniczki_z] = cardinality_variance_differentials(Y, similarities,  dysrednia_da, dysrednia_dz, dsim_da, dsim_dz, srednia_y, kardynalnosc);
//                 
//         // no i gotowe :-)
//         return { rozniczki_a, rozniczki_z };        
//     }
//     CATCH;
// }


double ksi::prototype_minkowski::debug_criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const
{
    try 
    {
        // wyznaczam kardynalnosc
        auto [kardynalnosc, srednia_y, similarities] = cardinality_similarities(X, Y);
        
        // wyznaczam jeszcze wariancje
        auto size = Y.size();
        double suma = 0;
        for (std::size_t i = 0; i < size; i++)
        {
            auto roznica = srednia_y - Y[i];
            suma += roznica * roznica * similarities[i];
        }
        auto wariancja = suma / kardynalnosc;
        
//         debug(kardynalnosc);
//         debug(wariancja);
        return kardynalnosc - wariancja;
//         return wariancja / kardynalnosc;
    } CATCH;
}

