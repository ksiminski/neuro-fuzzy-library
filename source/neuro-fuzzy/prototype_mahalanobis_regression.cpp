
#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"
#include "../neuro-fuzzy/prototype_mahalanobis_regression.h"
#include "../auxiliary/matrix.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::Matrix<double> m) : ksi::prototype_mahalanobis (m)
{
}

ksi::prototype_mahalanobis_regression::prototype_mahalanobis_regression (const ksi::cluster & cl) : ksi::prototype_mahalanobis (cl)
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
         throw std::string{"Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};

      // elaboration of the cardinality of the prototypes,  (double)
      //                    mean of the decision attributes in the prototype (double)
      //                    similarities of data to the prototype (std::vector<double>)
      auto [cardinality, mean_y, similarities] = cardinality_similarities(X, Y);

      // elaboration of similarity differentials:
      auto [dsim_dp, dsim_da] = similarity_differentials(X);
      // dsim_dp: vector of vectors of simiilarites (for each attribute for each data)
      // dsim_da: vector of matrices of differentials (for the covariance matrix for each data item)

      // elaboration of differential of the decision attribute
      auto [dymean_dp, dymean_da] = decision_attribute_average_differentials(Y, dsim_dp, dsim_da, cardinality);
      // dymean_dp: vector
      // dymean_da: matrix

      // elaboration of differential of cardinaty and variance
      auto [differentials_p, differentials_a] = cardinality_variance_differentials(Y, similarities, dymean_dp, dymean_da, dsim_dp, dsim_da, mean_y, cardinality);
      // differentials_p: vector
      // differentials_a: matrix

      // no i gotowe :-)
      return {differentials_p, differentials_a};
   }
   CATCH;
}

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
 
double ksi::prototype_mahalanobis_regression::criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) const
{
   try
    {
        auto [card, srednia_y, similarities] = cardinality_similarities(X, Y);

        // and the variance
        auto size = Y.size();
        double suma = 0;
        for (std::size_t i = 0; i < size; i++)
        {
            auto difference = srednia_y - Y[i];
            suma += difference * difference * similarities[i];
        }
        auto wariancja = suma / card;
        debug(card);
        debug(wariancja);
        return card - wariancja;
//         return wariancja / cardinality;
    } CATCH;
}
