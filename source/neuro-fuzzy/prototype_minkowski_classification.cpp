
#include <vector>
#include <cmath>

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/prototype_minkowski_classification.h"
#include "../common/datum.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../metrics/metric-minkowski-weighted.h"
#include "../partitions/cluster.h"

ksi::prototype_minkowski_classification::prototype_minkowski_classification (const double m, const double positive_class_label, const double negative_class_label) : ksi::prototype_minkowski(m), _positive_class_label (positive_class_label), _negative_class_label(negative_class_label)
{
}

ksi::prototype_minkowski_classification::prototype_minkowski_classification (const cluster & cl, const double m, const double positive_class_label, const double negative_class_label) : ksi::prototype_minkowski(cl, m), _positive_class_label (positive_class_label), _negative_class_label(negative_class_label)
{
}


ksi::prototype_minkowski_classification::~prototype_minkowski_classification ()
{
   // delete what is to delete
} 

ksi::premise * ksi::prototype_minkowski_classification::clone() const
{
    return new ksi::prototype_minkowski_classification(*this);
}

std::ostream & ksi::prototype_minkowski_classification::Print(std::ostream& ss) const
{
    ss << "prototype for classification with Minkowski metric" << std::endl;
    ss << "exponent: m = " << _m << std::endl;
    ss << "centre:   " << _centre  << std::endl;
    ss << "weights:  " << _weights << std::endl; 
    
    return ss;
} 

std::string ksi::prototype_minkowski_classification::get_name() const
{
    return std::string("Prot-Mink-classification");
}

std::string ksi::prototype_minkowski_classification::get_description() const
{
    return std::string ("Minkowski prototype for classification");
}

std::pair<std::vector<double>, std::vector<double>> ksi::prototype_minkowski_classification::cardinality_differentials(
    const ksi::Matrix<double>& dsim_da, 
    const ksi::Matrix<double>& dsim_dz,
    const std::size_t nKrotka                                                                                                                      )
{
    auto nAtrybut = _centre.size();  // liczba atrybutow
    
    auto dodawacz = [] (const double a, const double b) {return a + b;};
    std::vector<double> dkappa_da (nAtrybut);
    std::vector<double> dkappa_dz (nAtrybut);
    
    std::vector<double> dzeta_da (nAtrybut);
    std::vector<double> dzeta_dz (nAtrybut);
    
    for (std::size_t a = 0; a < nAtrybut; a++)
    {
        dkappa_da[a] = dsim_da.accumulate_column(a, 0.0, dodawacz);
        dkappa_dz[a] = dsim_dz.accumulate_column(a, 0.0, dodawacz);
    }
    return { dkappa_da, dkappa_dz };
}

std::pair<std::vector<double>, std::vector<double> > ksi::prototype_minkowski_classification::probability_differentials(
    const std::vector<double>& similarities,
    const std::vector<double>& classes, 
    const ksi::Matrix<double>& dsim_da, 
    const ksi::Matrix<double>& dsim_dz, 
    const double cardinality, 
    const std::vector<double>& dkappa_da, 
    const std::vector<double>& dkappa_dz,
    const double class_label)
{
     auto nAtrybut = _centre.size();  // liczba atrybutow
     auto nItems = dsim_da.getRows(); // liczba danych
     
     std::vector<double> ds_da (nAtrybut);
     std::vector<double> ds_dz (nAtrybut);
 
     std::vector<double> sim_sum (nAtrybut);
  
     std::vector<double> P_da (nAtrybut);
     std::vector<double> P_dz (nAtrybut);
     
     for (std::size_t a = 0; a < nAtrybut; a++)
     {
         for (std::size_t i = 0; i < nItems; i++)
         {
             if (classes[i] == class_label)
             {
                ds_da[a] += dsim_da.get_value(i, a);
                ds_dz[a] += dsim_da.get_value(i, a);
                
                sim_sum[a] += similarities[i];
             }
         }
         P_da[a] = (cardinality * ds_da[a] - dkappa_da[a] * sim_sum[a]) / cardinality * cardinality;
         
         P_dz[a] = (cardinality * ds_dz[a] - dkappa_dz[a] * sim_sum[a]) / cardinality * cardinality;
         
     }
     return { P_da, P_dz };
}


double ksi::prototype_minkowski_classification::debug_criterion_function(const std::vector<std::vector<double> >& X, const std::vector<double>& Y) const
{
    // trzeba wyznaczyc kardynalnosc:
    
     auto [cardinality, 
           probability_positive,
           probability_negative, 
           similarities] = cardinality_class_probabilities_similarities(X, Y, _positive_class_label, _negative_class_label);
    
     auto specificity = 1 - Gini_values(probability_positive, probability_negative);
     
//      debug(cardinality);
//      debug(specificity);
     return cardinality * specificity;
    
}

 
std::pair<std::vector<double>, std::vector<double> > ksi::prototype_minkowski_classification::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double> & Y)
{
    ///@todo zaimplementować tę metodę
    try 
    {    
        
        
        if (X.size() != Y.size())
            throw std::string { "Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};
        
        // wyznaczenie kardynalnosci prototypu, 
        //             prawdopodobienstwa klasy pozytywnej
        //             prawdopodobienstwa klasy negatywnej
        //             podobienstw do prototypu dla danych
        auto [cardinality, 
              probability_positive,
              probability_negative, 
              similarities] = cardinality_class_probabilities_similarities(X, Y, _positive_class_label, _negative_class_label);
        
        // wyznaczenie rozniczek podobienstwa:
        auto [dsim_da, dsim_dz] = similarity_differentials (X);
                      
        // wyznaczanie rozniczek kardynalnosci
        auto [dkappa_da, dkappa_dz] = cardinality_differentials(dsim_da, dsim_dz, Y.size());
                
        // wyznaczenie rozniczek prawdopodobienstw ...
        // ... dla klasy pozytywnej
        auto [dPpos_da, dPpos_dz] = probability_differentials(
            similarities, 
            Y,
            dsim_da, dsim_dz,
            cardinality,
            dkappa_da,
            dkappa_dz,
            _positive_class_label);
        
        // ... dla klasy negatywnej
        auto [dPneg_da, dPneg_dz] = probability_differentials(
            similarities, 
            Y,
            dsim_da, dsim_dz,
            cardinality,
            dkappa_da,
            dkappa_dz,
            _negative_class_label);
        
        // wyznaczenie rozniczki wspolczynnika Giniego
        auto [dG_da, dG_dz] = Gini_differentials(
            probability_positive, 
            probability_negative, 
            dPpos_da, dPpos_dz,
            dPneg_da, dPneg_dz);
        
         
        auto dsigma_da = dG_da * -1;
        auto dsigma_dz = dG_dz * -1;
        
        auto gini = 1 - probability_positive * probability_positive - probability_negative * probability_negative;
        
        auto specificity = 1 - gini;
        
        auto [dI_da, dI_dz] = final_differentials(
            dkappa_da, dkappa_dz, specificity, cardinality, dsigma_da, dsigma_dz);
        
        // no i gotowe :-)
        return { dI_da, dI_dz };
    }
    CATCH;
} 

std::pair<std::vector<double>, std::vector<double>> 
ksi::prototype_minkowski_classification::final_differentials(
            const std::vector<double> & dkappa_da, 
            const std::vector<double> & dkappa_dz, 
            const double specificity, 
            const double cardinality, 
            const std::vector<double> & dsigma_da, 
            const std::vector<double> & dsigma_dz)
{
    auto nAtrybut = _centre.size();  // liczba atrybutow
    std::vector<double> dI_da (nAtrybut);
    std::vector<double> dI_dz (nAtrybut);
    
    for (std::size_t a = 0; a < nAtrybut; a++)
    {
        dI_da[a] = dkappa_da[a] * specificity + cardinality * dsigma_da[a];
        dI_dz[a] = dkappa_dz[a] * specificity + cardinality * dsigma_dz[a];
    }
    
    return { dI_da, dI_dz };
}

std::pair<std::vector<double>, std::vector<double> > ksi::prototype_minkowski_classification::Gini_differentials(
    const double probability_positive, 
    const double probability_negative, 
    const std::vector<double>& dPpos_da, 
    const std::vector<double>& dPpos_dz, 
    const std::vector<double>& dPneg_da, 
    const std::vector<double>& dPneg_dz)
{
     auto nAtrybut = _centre.size();  // liczba atrybutow
     std::vector<double> dG_da (nAtrybut);
     std::vector<double> dG_dz (nAtrybut);
     
     
     for (std::size_t a = 0; a < nAtrybut; a++)
     {
         dG_da[a] = -2 * probability_positive * dPpos_da[a] 
                    -2 * probability_negative * dPneg_da[a];
         dG_dz[a] = -2 * probability_positive * dPpos_dz[a] 
                    -2 * probability_negative * dPneg_dz[a];
                    
     }
          
     return { dG_da, dG_dz };
}

double ksi::prototype_minkowski_classification::Gini_values(const double probability_positive, const double probability_negative) const 
{
    return 1 - probability_positive * probability_positive - probability_negative * probability_negative;
}

 


std::tuple<double, double, double, std::vector<double>> ksi::prototype_minkowski_classification::cardinality_class_probabilities_similarities
(const std::vector<std::vector<double>>& X, 
 const std::vector<double> & Y,
 const double positive_class, 
 const double negative_class
) const 
{
    try 
    {
        auto nKrotka = X.size();
        double kardynalnosc = 0;
        std::vector<double> similarities(nKrotka, 0);
        
        double sum_similarities_positive = 0;
        double sum_similarities_negative = 0;
            
        for (std::size_t x = 0; x < nKrotka; x++)
        {
            auto sim = get_similarity(X[x]);
            similarities[x] = sim;
            kardynalnosc += sim;
            if (utility_math::double_equal(Y[x], positive_class))
                sum_similarities_positive += sim;
            else if (utility_math::double_equal(Y[x], negative_class)) 
                sum_similarities_negative += sim;
        }
        
        return { kardynalnosc, 
                 sum_similarities_positive / kardynalnosc,
                 sum_similarities_negative / kardynalnosc, 
                 similarities };
    } CATCH;
}
