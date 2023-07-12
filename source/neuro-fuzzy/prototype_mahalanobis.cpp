
#include <vector>
#include <cmath>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../common/datum.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../metrics/metric_mahalanobis.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis::prototype_mahalanobis (const ksi::Matrix<double> A) : ksi::prototype(), _A(A)
{
}

ksi::prototype_mahalanobis::prototype_mahalanobis (const cluster & cl, const ksi::Matrix<double> A) : _A (A)
{
    auto nAttr = cl.get_number_of_desciptors();
    for (std::size_t a = 0; a < nAttr; a++)
    {
        auto p = cl.getAddressOfDescriptor(a);
        addDescriptor(*p);
    }
}

ksi::prototype_mahalanobis::~prototype_mahalanobis ()
{
   // delete what is to delete
}

 

double ksi::prototype_mahalanobis::get_similarity(const ksi::datum & d) const
{
    try 
    {
        return get_similarity(d.getVector());
    }
    CATCH;
}

double ksi::prototype_mahalanobis::get_similarity(const std::vector<double>& data) const
{
    try 
    {
        ksi::metric_mahalanobis metryka (_A);
        return distance_to_similarity(metryka.calculateDistance(_centre, data));
    }
    CATCH;
}

void ksi::prototype_mahalanobis::addDescriptor(const ksi::descriptor & d)
{
   try 
   {
        _centre.push_back(d.getCoreMean()); 

   } CATCH;
}

void ksi::prototype_mahalanobis::cummulate_differentials(std::vector<double> X, double partial_differential)
{
    try 
    {
        auto similarity = last_firingStrength;
        ksi::metric_mahalanobis maha(_A); 

        auto size = X.size();
        double dist = maha.calculateDistance(this->_centre, X);
        double sim_dist = similarity / (2.0 * dist);
        
        for (std::size_t d = 0; d < size; d++) // for each attribute:
        {
            double sum {0};
            for (std::size_t k = 0; k < size; k++) 
            {
                // differentials for ds_dcentre:
                double r = X[k] - _centre[k];
                double aa = _A(k, d) + _A(d, k);
                sum += (r * aa);
                
                // differentials for ds_daij:
                double rd = X[d] - _centre[d];
                double rk = X[k] - _centre[k];

                _d_A(d, k) = -1 * partial_differential * rd * rk;
            }
            // differentials for ds_dcentre:
            _d_centre[d] += partial_differential * sim_dist * sum;
        }
    } CATCH;
}


void ksi::prototype_mahalanobis::reset_differentials()
{
    auto size = _centre.size();
    
    _d_centre  = std::vector<double> (size, 0.0);
    _d_A       = ksi::Matrix<double> (_A.getRows(), _A.getCols(), 0.0);
}

std::ostream & ksi::prototype_mahalanobis::Print(std::ostream& ss) const
{
    ss << "prototype with Mahalanobis metric" << std::endl;
    ss << "centre:             " << _centre  << std::endl;
    ss << "covariance matrix:  " << _A << std::endl; 
    
    return ss;
}

void ksi::prototype_mahalanobis::actualise_parameters(double eta)
{
    try 
    {
        auto csize = _centre.size();
        for (std::size_t i = 0; i < csize; i++)
        {
            _centre[i] -= (eta * _d_centre[i]);
        }
        _d_centre = std::vector<double> (csize, 0.0);

        _A += (_d_A * eta);
        _d_A = ksi::Matrix<double> (csize, csize, 0.0);
    }
    CATCH; 
}

std::string ksi::prototype_mahalanobis::get_name() const
{
    return std::string("Prot-Mahalanobis");
}

std::string ksi::prototype_mahalanobis::get_description() const
{
    return std::string ("Mahalanobis prototypes");
}

void ksi::prototype_mahalanobis::justified_granularity_principle(const std::vector<std::vector<double> >& X, const std::vector<double>& Y)
{
    try 
    {
        std::size_t nAtrybut = _centre.size();
        
        std::vector<double> differentials_centre (nAtrybut, 0);
        ksi::Matrix<double> differentials_matrix (nAtrybut, nAtrybut, 0.0);

        double ETA { 0.0000001 };
        const int nIteration { 50 };
        
//         debug(nIteration);
        auto criterion_prev = 0.0;
        
//         debug("=========================================================");
        for (int i = 0; i < nIteration; i++)
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
            
            auto [diffs_centre, diffs_matrix] = differentials_justified_granularity_principle(X, Y);
            
            if (is_valid(diffs_centre))
                differentials_centre  += diffs_centre;
            if (is_valid(diffs_matrix))
                differentials_matrix += diffs_matrix;
        
            _centre  += differentials_centre * ETA;
            _A       += differentials_matrix * ETA;

        }
    } CATCH;
}


std::pair<std::vector<std::vector<double>>, std::vector<ksi::Matrix<double>>> ksi::prototype_mahalanobis::similarity_differentials(const std::vector<std::vector<double>>& X)
{
    try 
    {
        auto nAttributes = _centre.size();  // liczba atrybutow
        auto nDataItems  = X.size();        // liczba danych
            
        std::vector<std::vector<double>> ds_dp_x(nDataItems, std::vector<double>(nAttributes));  // rozniczki podobienstwa
       std::vector<ksi::Matrix<double>> ds_daij_x (nDataItems);
        ksi::metric_mahalanobis metryka (_A);
        double dr_dp = -1;

        for (std::size_t x = 0; x < nDataItems; x++)
        {
            // similarity of data x-th item and the centre of the prototypy:
            const auto & dataitem = X[x];
            double s = get_similarity(dataitem);
            // squared distance:
            double d2 = metryka.calculateDistance(_centre, dataitem);
            double ds_dt = -s;
            double dt_dd2 = 0.5 * std::pow(d2, -0.5);

            double ds_dd2 = ds_dt * dt_dd2;

            for (std::size_t i = 0; i < nAttributes; i++)
            {
                double dd2_dr = 0;
                for (std::size_t k = 0; k < nAttributes; k++)
                {
                    double rk = dataitem[k] - _centre[k];
                    dd2_dr += rk * (_A(k, i) + _A(i, k));
                }

                double ds_dp = ds_dd2 * dd2_dr * dr_dp;
                ds_dp_x[x][i] = ds_dp;


                ksi::Matrix ds_daij (nAttributes, nAttributes, 0.0);
                for (std::size_t j = i; j < nAttributes; j++)
                {
                    double ri = dataitem[i] - _centre[i];
                    double rj = dataitem[j] - _centre[j];
                    double dd2_daij = ri * rj;
                    ds_daij(i, j) = ds_daij(j, i) = ds_dd2 * dd2_daij;
                }
                ds_daij_x[x] = ds_daij;
            }
        }
        return {ds_dp_x, ds_daij_x};  
    } CATCH;
}
 
std::pair<std::vector<double>, ksi::Matrix<double>> ksi::prototype_mahalanobis::decision_attribute_average_differentials (const std::vector<double> & Y, const std::vector<std::vector<double>> & dsim_dp, const std::vector<ksi::Matrix<double>> & dsim_aij, const double cardinality)
{
    try 
    { 
        auto nAtrybut = _centre.size();  // liczba atrybutow
        auto nKrotka  = Y.size();        // liczba danych
        
        std::vector<double> dysrednia_dp (nAtrybut, 0.0);
        ksi::Matrix<double> dysrednia_da (nAtrybut, nAtrybut, 0.0);
        
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            for (std::size_t i = 0; i < nAtrybut; i++)
            {
                dysrednia_dp[i] += Y[x] * dsim_dp[x][i];
                for (std::size_t j = 0; j < nAtrybut; j++)
                {
                                
                   dysrednia_da(i, j) += Y[x] * dsim_aij[x].get_value(i, j);
                }
            }
        }
      
        double cardinality_2 = cardinality * cardinality;
        for (auto & d : dysrednia_dp)
            d /= cardinality_2;
        dysrednia_da /= cardinality_2; // operator /= is implemented for matrices :-)
        
        return { dysrednia_dp, dysrednia_da };
    } CATCH;
}

std::pair<std::vector<double>, ksi::Matrix<double>> ksi::prototype_mahalanobis::cardinality_variance_differentials (
    const std::vector<double> & Y,
    const std::vector<double> & similarities,
    const std::vector<double> & dysrednia_dp,
    const ksi::Matrix<double> & dysrednia_da,
    const std::vector<std::vector<double>> & dsim_dp, 
    const std::vector<ksi::Matrix<double>> & dsim_da, 
    const double & srednia_y, 
    const double & cardinality)
{
    try 
    {
        auto nAtrybut = _centre.size();  // liczba atrybutow
        auto nKrotka  = Y.size();        // liczba danych
        // suma pomocniczna:
        double suma_iloczynu_kwadratow_roznic_podobienstwa {0.0};
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            double difference = Y[x] - srednia_y;
            suma_iloczynu_kwadratow_roznic_podobienstwa += difference * difference * similarities[x];
        }
        
        // wyznaczenie rozniczek kardynalności (kappa)
        // wyznaczenie rozniczek wariancji     (zeta)
        
        auto dodawacz = [] (const double a, const double b) {return a + b;};
        std::vector<double> dkappa_dp (nAtrybut, 0.0);
        ksi::Matrix<double> dkappa_daij (nAtrybut, nAtrybut, 0.0);
        
        std::vector<double> dzeta_dp (nAtrybut, 0.0);
        ksi::Matrix<double> dzeta_daij (nAtrybut, nAtrybut, 0.0);
        
        for (std::size_t x = 0; x < nKrotka; ++x)
        {
            for (std::size_t i = 0; i < nAtrybut; ++i)
            {
                dkappa_dp[i] += dsim_dp[x][i];
                for (std::size_t j = 0; j < nAtrybut; ++j)
                {
                    dkappa_daij(i, j) += dsim_da[x].get_value(i, j);
                    double similarity = similarities[x];


                }
            }
        }

        // mamy dkappa_dp i dkappa_da
        // trzeba jeszcze policzyć ddzeta_dp i ddzeta_da:
        // ddzeta_dp:
        for (std::size_t i = 0; i < nAtrybut; i++)
        {
            double pierwsza_suma {0};
            double druga_suma {0};

            for (std::size_t x = 0; x < nKrotka; x++)
            {
                double difference = Y[x] - srednia_y;
                double difference_squared = difference * difference;

                // pierwsza suma
                auto p_s = difference * (difference * dsim_dp[x][i] - 2 * dysrednia_dp[i] * similarities[x]);                 
                pierwsza_suma += p_s;


                // druga suma
                auto dr_s = difference_squared * similarities[x]; 
                druga_suma += dr_s;
            }

            dzeta_dp[i] = (-1) * (cardinality * pierwsza_suma - dkappa_dp[i] * druga_suma) / (cardinality * cardinality);
        }

        // ddzeta_da
        for (std::size_t i = 0; i < nAtrybut; i++)
        {
            for (std::size_t j = 0; j < nAtrybut; i++)
            {
                double pierwsza_suma{0};
                double druga_suma{0};

                for (std::size_t x = 0; x < nKrotka; x++)
                {
                    double difference = Y[x] - srednia_y;
                    double difference_squared = difference * difference;

                    // pierwsza suma
                    auto p_s = difference * (difference * dsim_da[x].get_value(i, j) - 2 * dysrednia_da.get_value(i, j) * similarities[x]);
                    pierwsza_suma += p_s;

                    // druga suma
                    auto dr_s = difference_squared * similarities[x];
                    druga_suma += dr_s;
                }

                dzeta_daij(i, j) = (-1) * (cardinality * pierwsza_suma - dkappa_daij.get_value(i, j)* druga_suma) / (cardinality * cardinality);
            }
        }

        /*
        // do dokończnia !!!!!
        for (std::size_t a = 0; a < nAtrybut; a++)
        {
            dkappa_dp[a] = dsim_dp.accumulate_column(a, 0.0, dodawacz);
            dkappa_daij[a] = dsim_dz.accumulate_column(a, 0.0, dodawacz);
            
            double suma_dla_a {0};
            double suma_dla_z {0};
            
            for (std::size_t x = 0; x < nKrotka; x++)
            {
                double difference = Y[x] - srednia_y;
                suma_dla_a += -2 * difference * dysrednia_da[a] * similarities[x] 
                            + difference * difference * dsim_da.get_value(x, a);
                suma_dla_z += -2 * difference * dysrednia_dz[a] * similarities[x] 
                            + difference * difference * dsim_dz.get_value(x, a);
            }
            
            dzeta_dp[a] = (cardinality * suma_dla_a - dkappa_dp[a] * suma_iloczynu_kwadratow_roznic_podobienstwa) / (cardinality * cardinality); 
            
            dzeta_daij[a] = (cardinality * suma_dla_z - dkappa_daij[a] * suma_iloczynu_kwadratow_roznic_podobienstwa) / (cardinality * cardinality); 
        }          
        
        std::vector<double> rozniczki_a = dkappa_dp - dzeta_dp;
        std::vector<double> rozniczki_z = dkappa_daij - dzeta_daij;
        
        return {rozniczki_a, rozniczki_z};
        */
        std::vector<double> rozniczki_p = dkappa_dp - dzeta_dp;
        ksi::Matrix<double> rozniczki_aij = dkappa_daij - dzeta_daij;
        
        return {rozniczki_p, rozniczki_aij};
    } 
    CATCH;
}

// std::pair<std::vector<double>, std::vector<double> > ksi::prototype_mahalanobis::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X,
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
//         auto [cardinality, srednia_y, similarities] = cardinality_similarities(X, Y);
//         
//         // wyznaczenie rozniczek podobienstwa:
//         auto [dsim_da, dsim_dz] = similarity_differentials (X);
//                       
//         // wyznaczenie rozniczek atrybutu decyzyjnego
//         auto [dysrednia_da, dysrednia_dz] = decision_attribute_average_differentials(Y, dsim_da, dsim_dz, cardinality);
//         
//         // wyznaczenie rozniczek kardynalnosci i wariancji:
//         auto [rozniczki_a, rozniczki_z] = cardinality_variance_differentials(Y, similarities,  dysrednia_da, dysrednia_dz, dsim_da, dsim_dz, srednia_y, kardynalnosc);
//                 
//         // no i gotowe :-)
//         return { rozniczki_a, rozniczki_z };        
//     }
//     CATCH;
// }

///@todo
double ksi::prototype_mahalanobis::debug_criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const
{
    try 
    {
        return 0;
    } CATCH;
}

/*
ksi::prototype_mahalanobis::prototype_mahalanobis (const ksi::prototype_mahalanobis & wzor) : ksi::prototype(wzor)
{
   // copy what is to copy

}

ksi::prototype_mahalanobis & ksi::prototype_mahalanobis::operator= (const ksi::prototype_mahalanobis & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_mahalanobis::prototype_mahalanobis (ksi::prototype_mahalanobis && wzor) : ksi::prototype(wzor)
{
   // swap what is to swap

}

ksi::prototype_mahalanobis & ksi::prototype_mahalanobis::operator= (ksi::prototype_mahalanobis && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/

// ksi::premise * ksi::prototype_mahalanobis::clone() const
// {
//     return new ksi::prototype_mahalanobis(*this);
// }
