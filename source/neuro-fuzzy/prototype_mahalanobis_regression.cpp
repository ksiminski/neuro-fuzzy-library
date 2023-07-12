
#include "../neuro-fuzzy/prototype_mahalanobis_regression.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/premise.h"
#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (m)
{
}

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::cluster & cl, const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (cl, m)
{
}

ksi::prototype_mahalanobis_regression::~prototype_mahalanobis_regression ()
{
   // delete what is to delete

}

std::pair<std::vector<double>, ksi::Matrix<double>> ksi::prototype_mahalanobis_regression::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double>& Y)
{
    try 
    {
        if (X.size() != Y.size())
            throw std::string { "Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};
        
        // wyznaczenie kardynalnosci prototypu,  (double) 
        //             sredniej wartosci atrybutu decyzyjnego (double)
        //             podobienstw do prototypu dla danych (std::vector<double>)
        auto [kardynalnosc, srednia_y, similarities] = cardinality_similarities(X, Y);
        
        // wyznaczenie rozniczek podobienstwa:
        auto [dsim_dp, dsim_da] = similarity_differentials (X);
        // dsim_dp: wektor wektorów różniczek
        // dsim_da: wektor macierzy różniczek

        // wyznaczenie rozniczek atrybutu decyzyjnego
        auto [dysrednia_dp, dysrednia_da] = decision_attribute_average_differentials(Y, dsim_dp, dsim_da, kardynalnosc);
        // dysrednia_dp: wektor 
        // dysrednia_da: macierz

        // wyznaczenie rozniczek kardynalnosci i wariancji:
        auto [rozniczki_p, rozniczki_a] = cardinality_variance_differentials(Y, similarities,  dysrednia_dp, dysrednia_da, dsim_dp, dsim_da, srednia_y, kardynalnosc);
        // rozniczki_p: wektor
        // rozniczki_a: macierz
                
        // no i gotowe :-)
        return { rozniczki_p, rozniczki_a };        
    }
    CATCH;
}


/*
ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::prototype_mahalanobis_regression & wzor) : ksi::prototype_mahalanobis(wzor)
{
   // copy what is to copy

}

ksi::prototype_mahalanobis_regression & ksi::prototype_mahalanobis_regression::operator= (const ksi::prototype_mahalanobis_regression & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (ksi::prototype_mahalanobis_regression && wzor) : ksi::prototype_mahalanobis(wzor)
{
   // swap what is to swap

}

ksi::prototype_mahalanobis_regression & ksi::prototype_mahalanobis_regression::operator= (ksi::prototype_mahalanobis_regression && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::prototype_mahalanobis::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/
ksi::premise * ksi::prototype_mahalanobis_regression::clone () const
{
   // prototype design pattern
   return new ksi::prototype_mahalanobis_regression(*this);
}



std::string ksi::prototype_mahalanobis_regression::get_name() const
{
    return std::string("Prot-Maha-regression");
}

std::string ksi::prototype_mahalanobis_regression::get_description() const
{
    return std::string ("Mahalanobis prototype for regression");
}
 
