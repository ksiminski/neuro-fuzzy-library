
#include <vector>
#include <cmath>

#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/prototype_minkowski_regression.h"
#include "../common/datum.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../metrics/metric-minkowski-weighted.h"

ksi::prototype_minkowski_regression::prototype_minkowski_regression (const double m) : ksi::prototype_minkowski(m)
{
}

ksi::prototype_minkowski_regression::~prototype_minkowski_regression ()
{
   // delete what is to delete

}
/*
ksi::prototype_minkowski_regression::prototype_minkowski_regression (const ksi::prototype_minkowski_regression & wzor) : ksi::prototype(wzor)
{
   // copy what is to copy

}

ksi::prototype_minkowski_regression & ksi::prototype_minkowski_regression::operator= (const ksi::prototype_minkowski_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_minkowski::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_minkowski_regression::prototype_minkowski_regression (ksi::prototype_minkowski_regression && wzor) : ksi::prototype(wzor)
{
   // swap what is to swap

}

ksi::prototype_minkowski_regression & ksi::prototype_minkowski_regression::operator= (ksi::prototype_minkowski_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_minkowski::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/

ksi::premise * ksi::prototype_minkowski_regression::clone() const
{
    return new ksi::prototype_minkowski_regression(*this);
}

 

std::ostream & ksi::prototype_minkowski_regression::Print(std::ostream& ss) const
{
    ss << "prototype for regression with Minkowski metric" << std::endl;
    ss << "exponent: m = " << _m << std::endl;
    ss << "centre:   " << _centre  << std::endl;
    ss << "weights:  " << _weights << std::endl; 
    
    return ss;
} 

std::string ksi::prototype_minkowski_regression::get_name() const
{
    return std::string("Prot-Mink-regression");
}

std::string ksi::prototype_minkowski_regression::get_description() const
{
    return std::string ("Minkowski prototype for regression");
}
 
std::pair<std::vector<double>, std::vector<double> > ksi::prototype_minkowski_regression::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double> & Y)
{
    try 
    {
        if (X.size() != Y.size())
            throw std::string { "Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};
        
        // wyznaczenie kardynalnosci prototypu, 
        //             sredniej wartosci atrybutu decyzyjnego
        //             podobienstw do prototypu dla danych
        auto [kardynalnosc, srednia_y, similarities] = cardinality_similarities(X, Y);
        
        // wyznaczenie rozniczek podobienstwa:
        auto [dsim_da, dsim_dz] = similarity_differentials (X);
                      
        // wyznaczenie rozniczek atrybutu decyzyjnego
        auto [dysrednia_da, dysrednia_dz] = decision_attribute_average_differentials(Y, dsim_da, dsim_dz, kardynalnosc);
        
        // wyznaczenie rozniczek kardynalnosci i wariancji:
        auto [rozniczki_a, rozniczki_z] = cardinality_variance_differentials(Y, similarities,  dysrednia_da, dysrednia_dz, dsim_da, dsim_dz, srednia_y, kardynalnosc);
                
        // no i gotowe :-)
        return { rozniczki_a, rozniczki_z };        
    }
    CATCH;
} 
