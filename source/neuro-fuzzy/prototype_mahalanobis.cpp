
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

ksi::prototype_mahalanobis::prototype_mahalanobis () 
{
}

ksi::prototype_mahalanobis::prototype_mahalanobis (const ksi::Matrix<double> A) : ksi::prototype(), _A(A)
{
}

ksi::prototype_mahalanobis::prototype_mahalanobis (const cluster & cl)
{
   try
   {
      _A = cl.get_A_matrix();
      if (_A.empty())
      {
         throw std::string {"Empty matrix!"};
      }

      auto nAttr = cl.get_number_of_desciptors();
      for (std::size_t a = 0; a < nAttr; a++)
      {
         auto p = cl.getAddressOfDescriptor(a);
         addDescriptor(*p);
      }
   }
   CATCH;
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
     return get_similarity(metryka.calculateDistance(_centre, data));
   }
   CATCH;
}

double ksi::prototype_mahalanobis::get_similarity(const double distance) const
{
   return distance_to_similarity(distance);
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
      double dist = maha.calculateDistance(_centre, X);
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

std::ostream & ksi::prototype_mahalanobis::print(std::ostream& ss) const
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
      if (ksi::is_valid(_d_centre))
      {
         for (std::size_t i = 0; i < csize; i++)
         {
            _centre[i] -= (eta * _d_centre[i]);
         }
         _d_centre = std::vector<double>(csize, 0.0);
      }
      if (ksi::is_valid(_d_A))
      {
         _A -= (_d_A * eta);
         _d_A = ksi::Matrix<double> (csize, csize, 0.0);
      }
   }
   CATCH; 
}

std::string ksi::prototype_mahalanobis::get_name() const
{
   return std::string("Prot-Mahalanobis");
}

std::string ksi::prototype_mahalanobis::get_description() const
{
   return std::string ("Mahalanobis prototype");
}

void ksi::prototype_mahalanobis::justified_granularity_principle(const std::vector<std::vector<double> >& X, const std::vector<double>& Y)
{
   return ;
   try 
   {
      std::size_t nAtrybut = _centre.size();

      std::vector<double> differentials_centre (nAtrybut, 0);
      ksi::Matrix<double> differentials_matrix (nAtrybut, nAtrybut, 0.0);

      double ETA { 0.0000001 };
      const int nIteration { 5 };
      //const int nIteration { 0 };

      //         debug(nIteration);
      //auto criterion_prev = 0.0;

      for (int i = 0; i < nIteration; i++)
      {
         /*
         //// dopasowanie ETY
         auto criterion = criterion_function(X, Y);
         debug(criterion);
         
         if (criterion < criterion_prev)
            ETA *= 0.1;
         else 
            ETA /= 0.1;
         criterion_prev = criterion;
         */         
         //// koniec dopasowania ETY
         //             debug(debug_criterion_function(X, Y));
         //debug(i);
         //debug(_centre);

         auto [diffs_centre, diffs_matrix] = differentials_justified_granularity_principle(X, Y);

         if (is_valid(diffs_centre))
            differentials_centre  += diffs_centre;
         if (is_valid(diffs_matrix))
            differentials_matrix += diffs_matrix;

         //debug(diffs_centre);
         //debug(diffs_matrix);
         if (ksi::is_valid(differentials_centre))
            _centre  += differentials_centre * ETA;
         if (ksi::is_valid(differentials_matrix))
            _A += differentials_matrix * ETA;
      }
   } CATCH;
}


std::pair<std::vector<std::vector<double>>, std::vector<ksi::Matrix<double>>> ksi::prototype_mahalanobis::similarity_differentials(const std::vector<std::vector<double>>& X)
{
   try 
   {
      auto nAttributes = _centre.size();  // number of attributes 
      auto nDataItems  = X.size();        // number of data items

      std::vector<std::vector<double>> ds_dp_x(nDataItems, std::vector<double>(nAttributes));  // differentials of similarity with regard to each attribute for each data item
      std::vector<ksi::Matrix<double>> ds_daij_x (nDataItems); // differentials of similarity with regard to each element of the covariance matrix for each each data item
      ksi::metric_mahalanobis Metric (_A); // Mahalobis matrix with covariance matrix _A
      double dri_dpi = -1;  // 

      for (std::size_t x = 0; x < nDataItems; x++)
      {
         // similarity of x-th data item and the centre of the prototype:
         const auto & dataitem = X[x];
         // squared distance:
         double d = Metric.calculateDistance(_centre, dataitem);
         if (d < 0)
            throw ksi::exception("Negative distance!");

         double s = get_similarity(d);
         double d2 = d * d;
         double ds_dt = -s;
         double dt_dd2 = 0.5 / d;

         double ds_dd2 = ds_dt * dt_dd2;

         ksi::Matrix ds_daij (nAttributes, nAttributes, 0.0);
         for (std::size_t i = 0; i < nAttributes; i++)
         {
            double dd2_dri = 0;
            for (std::size_t k = 0; k < nAttributes; k++)
            {
               double rk = dataitem[k] - _centre[k];
               dd2_dri += rk * (_A(k, i) + _A(i, k));
            }

            double ds_dpi = ds_dd2 * dd2_dri * dri_dpi;// ver:ok 
            ds_dp_x[x][i] = ds_dpi;


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
      auto nAttributes = _centre.size();  // number of attributes 
      auto nDataItems  = Y.size();        // number of data items 

      std::vector<double> dymean_dp (nAttributes, 0.0);
      ksi::Matrix<double> dymean_da (nAttributes, nAttributes, 0.0);

      for (std::size_t x = 0; x < nDataItems; x++)
      {
         for (std::size_t i = 0; i < nAttributes; i++)
         {
            dymean_dp[i] += Y[x] * dsim_dp[x][i];
            for (std::size_t j = 0; j < nAttributes; j++)
            {

               dymean_da(i, j) += Y[x] * dsim_aij[x].get_value(i, j);
            }
         }
      }

      double cardinality_2 = cardinality * cardinality;
      for (auto & d : dymean_dp)
         d /= cardinality_2;
      dymean_da /= cardinality_2; // operator /= is implemented for matrices :-)

      return { dymean_dp, dymean_da };
   } CATCH;
}

std::pair<std::vector<double>, ksi::Matrix<double>> ksi::prototype_mahalanobis::cardinality_variance_differentials (
      const std::vector<double> & Y,
      const std::vector<double> & similarities,
      const std::vector<double> & dymean_dp,
      const ksi::Matrix<double> & dymean_da,
      const std::vector<std::vector<double>> & dsim_dp, 
      const std::vector<ksi::Matrix<double>> & dsim_da, 
      const double & mean_y, 
      const double & cardinality)
{
   try 
   {
      auto nAttributes = _centre.size();  // number of attributes
      auto nDataItems = Y.size();        // number of data items
      
      // elaboration of cardinality differentials (kappa)
      //                variance differentials    (zeta)
    
      std::vector<double> dzeta_dp (nAttributes, 0.0);
      ksi::Matrix<double> dzeta_daij (nAttributes, nAttributes, 0.0);

      auto [ dkappa_dp, dkappa_daij ] = cardinality_differentials (dsim_dp, dsim_da);

      // dkappa_dp and dkappa_da: done
      // ddzeta_dp and ddzeta_da: to do
      for (std::size_t i = 0; i < nAttributes; i++)
      {
         double first_sum_for_dzeta_dp {0};
         double second_sum_for_dzeta_dp {0};
         
         for (std::size_t x = 0; x < nDataItems; x++)
         {
            double difference = Y[x] - mean_y;
            double difference_squared = difference * difference;
            // ddzeta_dp:
            
            // the first sum
            auto sum1 = similarities[x] * difference * dymean_dp[i];                 
            first_sum_for_dzeta_dp += sum1;
            
            // the second sum
            auto sum2 = difference_squared * dsim_dp[x][i]; 
            second_sum_for_dzeta_dp += sum2;
            
            // ddzeta_da

         }
         dzeta_dp[i] = 2 * first_sum_for_dzeta_dp - second_sum_for_dzeta_dp;
      }

      for (std::size_t i = 0; i < nAttributes; i++)
      {

         for (std::size_t j = 0; j < nAttributes; j++)
         {
            double first_sum_for_dzeta_da{0};
            double second_sum_for_dzeta_da{0};

            for (std::size_t x = 0; x < nDataItems; x++)
            {
               double difference = Y[x] - mean_y;
               double difference_squared = difference * difference;

               // the first sum
               auto sum1 = similarities[x] * difference * dymean_da.get_value(i, j);                 
               first_sum_for_dzeta_da += sum1;

               // the second sum
               auto sum2 = difference_squared * dsim_da[x].get_value(i, j); 
               second_sum_for_dzeta_da += sum2;
            }
            dzeta_daij(i, j) = 2 * first_sum_for_dzeta_da - second_sum_for_dzeta_da;
         }
      }

      //debug(dkappa_dp);
      //debug(dzeta_dp);
      std::vector<double> diffs_p = dkappa_dp + dzeta_dp;  /// @todo Dlaczego? Czy tu nie powinna być suma?
      //debug(diffs_p);
      ksi::Matrix<double> diffs_ai = dkappa_daij + dzeta_daij;   /// @todo Dlaczego? Czy tu nie powinna być suma?

      return {diffs_p, diffs_ai};
   } 
   CATCH;
}
/*
std::pair<std::vector<double>, ksi::Matrix<double>> ksi::prototype_mahalanobis::cardinality_variance_differentials (
      const std::vector<double> & Y,
      const std::vector<double> & similarities,
      const std::vector<double> & dymean_dp,
      const ksi::Matrix<double> & dymean_da,
      const std::vector<std::vector<double>> & dsim_dp, 
      const std::vector<ksi::Matrix<double>> & dsim_da, 
      const double & mean_y, 
      const double & cardinality)
{
   try 
   {
      auto nAttributes = _centre.size();  // number of attributes
      auto nDataItems = Y.size();        // number of data items
      
      // elaboration of cardinality differentials (kappa)
      //                variance differentials    (zeta)

      auto adder = [] (const double a, const double b) {return a + b;};
    
      std::vector<double> dzeta_dp (nAttributes, 0.0);
      ksi::Matrix<double> dzeta_daij (nAttributes, nAttributes, 0.0);

      auto [ dkappa_dp, dkappa_daij ] = cardinality_differentials (dsim_dp, dsim_da);

      // dkappa_dp and dkappa_da: done
      // ddzeta_dp and ddzeta_da: to do
      // ddzeta_dp:
      for (std::size_t i = 0; i < nAttributes; i++)
      {
         double first_sum {0};
         double second_sum {0};
         
         for (std::size_t x = 0; x < nDataItems; x++)
         {
            double difference = Y[x] - mean_y;
            double difference_squared = difference * difference;
            
            // the first sum
            auto p_s = difference * (difference * dsim_dp[x][i] - 2 * dymean_dp[i] * similarities[x]);                 
            first_sum += p_s;
            
            // the second sum
            auto dr_s = difference_squared * similarities[x]; 
            second_sum += dr_s;
         }
         
         dzeta_dp[i] = (-1) * (cardinality * first_sum - dkappa_dp[i] * second_sum) / (cardinality * cardinality);
      }

      // ddzeta_da
      for (std::size_t i = 0; i < nAttributes; i++)
      {

         for (std::size_t j = 0; j < nAttributes; j++)
         {
            double first_sum{0};
            double second_sum{0};

            for (std::size_t x = 0; x < nDataItems; x++)
            {
               double difference = Y[x] - mean_y;
               double difference_squared = difference * difference;

               // the first sum
               auto p_s = difference * (difference * dsim_da[x].get_value(i, j) - 2 * dymean_da.get_value(i, j) * similarities[x]);
               first_sum += p_s;

               // the second sum
               auto dr_s = difference_squared * similarities[x];
               second_sum += dr_s;
            }

            dzeta_daij(i, j) = (-1) * (cardinality * first_sum - dkappa_daij.get_value(i, j)* second_sum) / (cardinality * cardinality);

         }
      }

      std::vector<double> diffs_p = dkappa_dp + dzeta_dp;  /// @todo Dlaczego? Czy tu nie powinna być suma?
      ksi::Matrix<double> diffs_ai = dkappa_daij + dzeta_daij;   /// @todo Dlaczego? Czy tu nie powinna być suma?

      return {diffs_p, diffs_ai};
   } 
   CATCH;
}
*/
std::pair<std::vector<double>, ksi::Matrix<double>>  ksi::prototype_mahalanobis::cardinality_differentials (const std::vector<std::vector<double>> & dsim_dp, const std::vector<ksi::Matrix<double>> & dsim_da)
{
   try
   {
      auto nKrotka = dsim_dp.size();
      auto nAtrybut = dsim_dp[0].size();
      std::vector<double> dkappa_dp(nAtrybut, 0.0);
      ksi::Matrix<double> dkappa_daij(nAtrybut, nAtrybut, 0.0);
      for (std::size_t x = 0; x < nKrotka; ++x)
      {
         for (std::size_t i = 0; i < nAtrybut; ++i)
         {
            dkappa_dp[i] += dsim_dp[x][i];
            for (std::size_t j = 0; j < nAtrybut; ++j)
            {
               dkappa_daij(i, j) += dsim_da[x].get_value(i, j);
               // double similarity = similarities[x];
            }
         }
      }
      return {dkappa_dp, dkappa_daij};
   }
   CATCH;
}
