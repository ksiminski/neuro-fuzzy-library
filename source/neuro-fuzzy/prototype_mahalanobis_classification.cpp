
#include "../neuro-fuzzy/prototype_mahalanobis.h" 
#include "../neuro-fuzzy/prototype_mahalanobis_classification.h"
#include "../neuro-fuzzy/premise.h"

#include "../auxiliary/matrix.h"
#include "../auxiliary/utility-math.h"
#include "../auxiliary/vector-operators.h"
#include "../partitions/cluster.h"

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification () 
{
}

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (const Matrix<double> m, double positive_class_label, const double negative_class_label) : ksi::prototype_mahalanobis (m), _positive_class_label(positive_class_label), _negative_class_label(negative_class_label)
{
}

ksi::prototype_mahalanobis_classification::prototype_mahalanobis_classification (const ksi::cluster & cl, double positive_class_label, const double negative_class_label) : ksi::prototype_mahalanobis (cl), _positive_class_label(positive_class_label), _negative_class_label(negative_class_label)
{
}

ksi::prototype_mahalanobis_classification::~prototype_mahalanobis_classification ()
{
   // delete what is to delete

}

std::pair<std::vector<double>,  ksi::Matrix<double>> ksi::prototype_mahalanobis_classification::differentials_justified_granularity_principle(const std::vector<std::vector<double>>& X, const std::vector<double>& Y)
{
   try
   {
      if (X.size() != Y.size())
         throw std::string{"Number of tuples do not match (" + std::to_string(X.size()) + " != " + std::to_string(Y.size()) + ")."};

      // elabortion of the cardinality of the prototype,
      //                   probability of the positive class 
      //                   probability of the negative class 
      //                   similarities of data to the prototype 
      auto [cardinality, probability_positive, probability_negative, similarities] = cardinality_class_probabilities_similarities(X, Y, _positive_class_label, _negative_class_label);

      // elaboration of similarity differentials
      auto [dsim_dp, dsim_da] = similarity_differentials(X);

      // elaboration of cardinality differentials
      auto [dkappa_dp, dkappa_da] = cardinality_differentials(dsim_dp, dsim_da);

      // elaboration of probability differentials ...
      // ... for the positive class
      auto [dPpos_dp, dPpos_da] = probability_differentials(
            similarities,
            Y,
            dsim_dp, dsim_da,
            cardinality,
            dkappa_dp,
            dkappa_da,
            _positive_class_label);

      // ... for the negative class
      auto [dPneg_dp, dPneg_da] = probability_differentials(
            similarities,
            Y,
            dsim_dp, dsim_da,
            cardinality,
            dkappa_dp,
            dkappa_da,
            _negative_class_label);

      // elaboration of the Gini differentials 
      auto [dG_dp, dG_da] = Gini_differentials(
            probability_positive,
            probability_negative,
            dPpos_dp, dPpos_da,
            dPneg_dp, dPneg_da);

      auto dsigma_dp = dG_dp * -1;
      auto dsigma_da = dG_da * -1;

      auto gini = 1 - probability_positive * probability_positive - probability_negative * probability_negative;

      auto specificity = 1 - gini;

      auto [dI_dp, dI_da] = final_differentials(
            dkappa_dp, dkappa_da, specificity, cardinality, dsigma_dp, dsigma_da);

      // no i gotowe :-)
      return {dI_dp, dI_da};
   }
   CATCH;
}
std::tuple<double, double, double, std::vector<double>> ksi::prototype_mahalanobis_classification::cardinality_class_probabilities_similarities
(const std::vector<std::vector<double>>& X, 
 const std::vector<double> & Y,
 const double positive_class, 
 const double negative_class
 ) const 
{
   try 
   {
      auto nDataItems = X.size(); // number of data items
      double cardinality = 0;
      std::vector<double> similarities(nDataItems, 0);

      // elaboration of sums of similarities to the positive and negative classes
      double sum_similarities_positive = 0;
      double sum_similarities_negative = 0;

      for (std::size_t x = 0; x < nDataItems; x++)
      {
         auto sim = get_similarity(X[x]);
         similarities[x] = sim;
         cardinality += sim;
         if (ksi::utility_math::double_equal(Y[x], positive_class))
            sum_similarities_positive += sim;
         else if (ksi::utility_math::double_equal(Y[x], negative_class)) 
            sum_similarities_negative += sim;
      }

      return { cardinality, 
         sum_similarities_positive / cardinality,
         sum_similarities_negative / cardinality, 
         similarities };
   } CATCH;
}


ksi::premise * ksi::prototype_mahalanobis_classification::clone () const 
{
   // prototype design pattern
   return new ksi::prototype_mahalanobis_classification(*this);
}


std::pair<std::vector<double>, ksi::Matrix<double> > ksi::prototype_mahalanobis_classification::probability_differentials(
      const std::vector<double>& similarities,
      const std::vector<double>& classes, 
      const std::vector<std::vector<double>>& dsim_dp, 
      const std::vector<ksi::Matrix<double>>& dsim_da, 
      const double cardinality, 
      const std::vector<double>& dkappa_dp, 
      const ksi::Matrix<double>& dkappa_da,
      const double class_label)
{
   try
   {
      auto nAttributes = _centre.size(); // number of attributes
      auto nItems = dsim_dp.size();      // number of data items

      std::vector<double> ds_dp(nAttributes);
      ksi::Matrix<double> ds_da(nAttributes, nAttributes);

      std::vector<double> sim_sum(nAttributes);

      std::vector<double> P_dp(nAttributes);
      ksi::Matrix<double> P_da(nAttributes, nAttributes);

      // Elaboration of the sum of similarities of all data to the class whose label is class_label.
      double sum_sim_for_class{0};
      for (std::size_t i = 0; i < nItems; i++)
      {
         if (classes[i] == class_label)
            sum_sim_for_class += similarities[i];
      }

      double cardinality_2 = cardinality * cardinality;

      for (std::size_t d = 0; d < nAttributes; d++)
      {
         for (std::size_t i = 0; i < nItems; i++)
         {
            if (classes[i] == class_label)
            {
               ds_dp[d] += dsim_dp[i][d];
            }
         }
         P_dp[d] = (cardinality * ds_dp[d] - dkappa_dp[d] * sum_sim_for_class) / cardinality_2;
      }

      // And the same for aij:
      for (std::size_t i = 0; i < nAttributes; ++i)
      {
         for (std::size_t j = 0; j < nAttributes; ++j)
         {
            for (std::size_t x = 0; x < nItems; ++x)
            {
               if (classes[x] == class_label)
               {
                  ds_da(i, j) += dsim_da[x].get_value(i, j);
               }
            }
            P_da(i, j) = (cardinality * ds_da(i, j) - dkappa_da.get_value(i, j) * sum_sim_for_class) / cardinality_2;
         }
      }

      return {P_dp, P_da};
   }
   CATCH;
}


std::pair<std::vector<double>, ksi::Matrix<double>>
ksi::prototype_mahalanobis_classification::Gini_differentials(
      const double probability_positive, 
      const double probability_negative, 
      const std::vector<double> & dPpos_dp, 
      const ksi::Matrix<double> & dPpos_da,
      const std::vector<double> & dPneg_dp, 
      const ksi::Matrix<double> & dPneg_da)
{
   try
   {
      auto nAttributes = _centre.size();  // number of attributes
      std::vector<double> dG_dp (nAttributes);
      ksi::Matrix<double> dG_da (nAttributes, nAttributes);


      for (std::size_t i = 0; i < nAttributes; i++)
      {
         dG_dp[i] = -2 * probability_positive * dPpos_dp[i] 
                    -2 * probability_negative * dPneg_dp[i];

         for (std::size_t j = 0; j < nAttributes; j++)
         {
            dG_da(i, j) = -2 * probability_positive * dPpos_da.get_value(i, j)
                          -2 * probability_negative * dPneg_da.get_value(i, j);

         }
      }
      return { dG_dp, dG_da };
   }
   CATCH;
}

std::pair<std::vector<double>, ksi::Matrix<double>> 
ksi::prototype_mahalanobis_classification::final_differentials(
      const std::vector<double> & dkappa_dp, 
      const ksi::Matrix<double> & dkappa_da, 
      const double specificity, 
      const double cardinality, 
      const std::vector<double> & dsigma_dp, 
      const ksi::Matrix<double> & dsigma_da)   
{
   try
   {
      auto nAttributes = _centre.size(); // number of attributes
      std::vector<double> dI_dp(nAttributes);
      ksi::Matrix<double> dI_da(nAttributes, nAttributes);

      for (std::size_t i = 0; i < nAttributes; i++)
      {
         dI_dp[i] = dkappa_dp[i] * specificity + cardinality * dsigma_dp[i];
         for (std::size_t j = 0; j < nAttributes; j++)
         {
            dI_da(i, j) = dkappa_da.get_value(i, j) * specificity + cardinality * dsigma_da.get_value(i, j);
         }
      }
      return {dI_dp, dI_da};
   } 
   CATCH;
}


double ksi::prototype_mahalanobis_classification::criterion_function(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) const
{
   try
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
    } CATCH;
}
