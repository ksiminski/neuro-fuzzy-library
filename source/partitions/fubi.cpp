/** @file */  

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>


#include "../partitions/partitioner.h" 
#include "../partitions/partition.h"
#include "../common/dataset.h"
#include "../service/debug.h"
#include "../partitions/fubi.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/print.h"
#include "../descriptors/descriptor-gaussian-subspace.h"


std::string ksi::fubi::getAbbreviation () const
{
    return std::string ("fubi");
}

ksi::partitioner * ksi::fubi::clone() const
{
    return new ksi::fubi(*this);
}


ksi::fubi::~fubi()
{
}


ksi::fubi::fubi(const int NUMBER_OF_CLUSTERS, const int NUMBER_OF_ITERATIONS)
  : _number_of_clusters (NUMBER_OF_CLUSTERS), 
    _number_of_iterations (NUMBER_OF_ITERATIONS)
{
}


 
std::vector<std::vector<std::vector<double>>> ksi::fubi::randomise (
    const int number_of_clusters, 
    const std::size_t number_of_data, 
    const std::size_t number_of_attributes)
{
    std::vector<std::vector<std::vector<double>>> u;
    for (int c = 0; c < number_of_clusters; c++)
    {
        std::vector<std::vector<double>> kd;
        for (int x = 0; x < number_of_data; x++)
        {
            kd.push_back(ksi::get_uniform_unit_random_vector(number_of_attributes));
        }    
        u.push_back(kd);
    }
    return u;
} 

std::vector<std::vector<std::vector<double> > > ksi::fubi::normalise(
    const std::vector<std::vector<std::vector<double>>> & U)
{
    std::vector<std::vector<std::vector<double>>> norm_U(U);
     
    for (std::size_t a = 0; a < _number_of_attributes; a++)
    {
        for (std::size_t x = 0; x < _number_of_data; x++)
        {
            double suma {0};
            for (std::size_t c = 0; c < _number_of_clusters; c++)
            {
                suma += U[c][x][a];
            }
            for (std::size_t c = 0; c < _number_of_clusters; c++)
            {
                norm_U[c][x][a] = U[c][x][a] / suma;
                 //debug(suma);
                 if (std::isnan(suma))
                 {
                     debug(a);
                     debug(x);
                 }
            }
        }
    }
    

    return norm_U;
}

std::vector<std::vector<double>> ksi::fubi::cluster_centres_for_data (
    const std::vector<std::vector<double>> & X, 
    const std::vector<std::vector<std::vector<double>>> & _U)
{
    std::vector<std::vector<double>> V (_number_of_clusters,
                                        std::vector<double> (_number_of_attributes,0));
    
    for (std::size_t c = 0; c < _number_of_clusters; c++)
    {
        for (std::size_t a = 0; a < _number_of_attributes; a++)
        {
            double sum_membership {0};
            double sum_membership_times_value {0};
            for (std::size_t x = 0; x < _number_of_data; x++)
            {
                sum_membership += _U[c][x][a];
                sum_membership_times_value += _U[c][x][a] * X[x][a];
            }
            V[c][a] = sum_membership_times_value / sum_membership;
        }
    }
    return V;
}


std::vector<std::vector<double>> ksi::fubi::cluster_centres_for_attibutes (
    const std::vector<std::vector<double>> & X, 
    const std::vector<std::vector<std::vector<double>>> & _U)
{
    std::vector<std::vector<double>> V (_number_of_clusters,
                                        std::vector<double> (_number_of_data,0));
    
    for (std::size_t c = 0; c < _number_of_clusters; c++)
    {
        for (std::size_t x = 0; x < _number_of_data; x++)
        {
            double sum_membership {0};
            double sum_membership_times_value {0};
            for (std::size_t a = 0; a < _number_of_attributes; a++)
            {
                sum_membership += _U[c][x][a];
                sum_membership_times_value += _U[c][x][a] * X[x][a];
            }
            
            auto iloraz = sum_membership_times_value / sum_membership;
            if (not std::isnan(iloraz))
               V[c][x] = iloraz;
        }
    }
    return V;
}

double ksi::fubi::ksi(
    const std::vector<std::vector<double>> & X, 
    const std::vector<std::vector<double>> & V_data, 
    const std::vector<std::vector<double>> & V_attr,
    int c,
    std::size_t k,
    std::size_t d)
{
    return pow((X[k][d] - V_data[c][d]), 2) + pow((X[k][d] - V_attr[c][k]), 2);   
}


std::vector<std::vector<std::vector<double>>> 
ksi::fubi::update_membership_matrix(
    const std::vector<std::vector<std::vector<double>>> & U, 
    const std::vector<std::vector<double>> & X, 
    const std::vector<std::vector<double>> & V_data, 
    const std::vector<std::vector<double>> & V_attr)
{
    auto U_new = U;
    
    const double expo = (1.0 / (1.0 - _m));
    
    for (std::size_t x = 0; x < _number_of_data; x++)
    {
        for (std::size_t a = 0; a < _number_of_attributes; a++)
        {
            double sum {0};
            for (std::size_t c = 0; c < _number_of_clusters; c++)
            {
                auto xi = ksi (X, V_data, V_attr, c, x, a);
                sum += pow (xi, expo);   
            }

            for (std::size_t c = 0; c < _number_of_clusters; c++)
            {
                auto new_value = pow (ksi (X, V_data, V_attr, c, x, a), expo)  / sum;  
                
                U_new[c][x][a] = std::isnan(new_value) ? 1.0 : new_value;
            }
        }
    }
    
    return U_new;
}


ksi::partition ksi::fubi::doPartition(const ksi::dataset& ds)
{
    const double EPSILON = 1e-6;
       
    _number_of_attributes = ds.getNumberOfAttributes();
    _number_of_data       = ds.getNumberOfData();
    
    // macierz przynaleznosci jest trojwymiarowa: _U[klaster][dana][atrybut]
    std::vector<std::vector<std::vector<double>>> _U = randomise(_number_of_clusters, _number_of_data, _number_of_attributes);
    
    _U = normalise(_U);
    
    auto X = ds.getMatrix();
    
    for (int iter = 0 ; iter < _number_of_iterations; iter++)
    {
        // wyznacz srodki klastrow dla danych i dla atrybutow
//         debug(iter);
        
        auto V_data = cluster_centres_for_data (X, _U);
//         debug(V_data);
        auto V_attr = cluster_centres_for_attibutes (X, _U);
//         debug(V_attr);
        
        _U = update_membership_matrix (_U, X, V_data, V_attr);
        _U = normalise(_U);
        
    }
    
    auto V_data = cluster_centres_for_data (X, _U);
    auto mS = calculateClusterFuzzification(_U, V_data, X);
    auto mZ = calculateAttributeWeights(_U, V_data, X);
//     
//     // przeksztalcenie do postaci zbiorow gaussowskich
    ksi::partition part;
    for (int c = 0; c < _number_of_clusters; c++)
    {
        ksi::cluster cl; 
        for (std::size_t a = 0; a < _number_of_attributes; a++)
        {
            ksi::descriptor_gaussian_subspace d (V_data[c][a], std::max(mS[c][a], EPSILON), mZ[c][a]);
            cl.addDescriptor(d);
        }
        part.addCluster(cl);
    }
    
    return part;
}

std::vector<std::vector<double> > ksi::fubi::calculateClusterFuzzification(
    const std::vector<std::vector<std::vector<double>>> & U, 
    const std::vector<std::vector<double>> & V_data, 
    const std::vector<std::vector<double>> & X)
{
    auto S (V_data);
    
    for (int c = 0; c < _number_of_clusters; c++)
    {
        for (std::size_t d = 0; d < _number_of_attributes; d++)
        {
            double sum_numerator {0.0},
                   sum_denominator {0.0};
                
            for (std::size_t i = 0; i < _number_of_data; i++)
            {
                auto um = pow(U[c][i][d], _m);
                
                sum_numerator += (um * pow (X[i][d] - V_data[c][d], 2));
                sum_denominator += um;
            }
            S[c][d] = std::sqrt(sum_numerator / sum_denominator);
        }      
    }
    return S;
}


std::vector<std::vector<double> > ksi::fubi::calculateAttributeWeights(
    const std::vector<std::vector<std::vector<double>>> & U, 
    const std::vector<std::vector<double>> & V_data, 
    const std::vector<std::vector<double>> & X)
{
    auto Z (V_data);
    
    for (int c = 0; c < _number_of_clusters; c++)
    {
        double sum_of_all {0.0};
        for (std::size_t d = 0; d < _number_of_attributes; d++)
        {
            for (std::size_t i = 0; i < _number_of_data; i++)
            {
                auto um = pow(U[c][i][d], _m);
                
                sum_of_all += um;
            }
        }
        
        for (std::size_t d = 0; d < _number_of_attributes; d++)
        {
            double sum {0.0};
            for (std::size_t i = 0; i < _number_of_data; i++)
            {
                auto um = pow(U[c][i][d], _m);
                
                sum += um;
            }
            
            Z[c][d] = sum / sum_of_all;
        }
    }
    return Z;
}

