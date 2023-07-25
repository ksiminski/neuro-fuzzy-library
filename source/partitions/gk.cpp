
#include "../partitions/fcm.h"
#include "../partitions/partitioner.h"
#include "../metrics/metric-euclidean.h"
#include "../metrics/metric_mahalanobis.h"
#include "../partitions/gk.h"
#include "../auxiliary/matrix.h"


ksi::gk::gk () : fcm()
{
}

ksi::gk::~gk ()
{
   // delete what is to delete
}

/*
ksi::gk::gk (const ksi::gk & wzor) : ksi::fcm(wzor)
{
   // copy what is to copy

}

ksi::gk & ksi::gk::operator= (const ksi::gk & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fcm::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::gk::gk (ksi::gk && wzor) : ksi::fcm(wzor)
{
   // swap what is to swap

}

ksi::gk & ksi::gk::operator= (ksi::gk && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::fcm::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/

ksi::partitioner * ksi::gk::clone () const
{
   // prototype design pattern
   return new ksi::gk(*this);
}

double ksi::gk::calculateDistance(const std::vector<double>& x, const std::vector<double>& y, const int cluster)
{
   return metrics_for_clusters[cluster].calculateDistance(x, y);
}
 

 
std::vector<std::vector<double>> ksi::gk::modifyPartitionMatrix(const std::vector<std::vector<double>>& mV, const std::vector<std::vector<double>>& mX)
{
   try
   {
      std::vector<std::vector<double>> U (mV.size());
      std::size_t nClusters = mV.size();
      std::size_t nX = mX.size();
      double exponent = 2.0 / (1.0 - _m);
      
      if (nX > 0)
      {
         //std::size_t nAttr = mX[0].size();
         for (auto & u : U)
            u = std::vector<double> (nX);

         // distance matrix:
         std::vector<double>   Dmsums  (nX, 0.0);
         std::vector<int> Dmzeros (nX, 0.0);
         Dm = std::vector<std::vector<double>> (nClusters);
         for (std::size_t c = 0; c < nClusters; c++)
         {
            Dm[c] = std::vector<double> (nX);

            for (std::size_t x = 0; x < nX; x++)
            {
                
                Dm[c][x] = ksi::power(calculateDistance (mV[c], mX[x], c), exponent);
                if (Dm[c][x] == 0)
                  Dmzeros[x]++;
               Dmsums[x] += Dm[c][x];
            }
         }

//          for (std::size_t c = 0; c < nClusters; c++)
//          {
//             for (std::size_t x = 0; x < nX; x++)
//             {
//                if (Dm[c][x] == 0)
//                   Dmzeros[x]++;
//                Dmsums[x] += Dm[c][x];
//             }
//          }
         
         for (std::size_t c = 0; c < nClusters; c++)
         {
            for (std::size_t x = 0; x < nX; x++)
            {
               if (Dmzeros[x] > 0)
               {
                  if (Dm[c][x] == 0.0)
                     U[c][x] = 1.0 / Dmzeros[x];
                  else
                     U[c][x] = 0.0;
               }
               else
               {
                  U[c][x] = Dm[c][x] / Dmsums[x];
               }
            }
         }
      }
      return U;
   }
   CATCH;
}

ksi::partition ksi::gk::doPartition(const ksi::dataset& ds)
{
   try
   {
      if (_nClusters < 1)
         throw std::string ("unknown number of clusters");
      if (_nIterations < 1 and _epsilon < 0)
         throw std::string ("You should set a maximal number of iteration or "
         "minimal difference -- epsilon.");
      if (_nIterations > 0 and _epsilon > 0)
         throw std::string ("Both number of iterations and minimal epsilon set -- you should set either number of iterations or minimal epsilon.");
      
      double dummy {0.0};
      auto mX = ds.getMatrix(dummy);
      std::size_t nAttr = ds.getNumberOfAttributes();
      std::size_t nX    = ds.getNumberOfData();
      std::vector<std::vector<double>> mV;
      mU = std::vector<std::vector<double>> (_nClusters);
      
      for (auto & u : mU)
         u = std::vector<double> (nX);
      randomise(mU);
      normaliseByColumns(mU);
      
      if (_nIterations > 0)
      {
         for (int iter = 0; iter < _nIterations; iter++)
         {
            mV = calculateClusterCentres(mU, mX);
            std::vector<Matrix<double>> covariance_matrices = calculateCovarianceMatrices(mX, mU, mV);
            updateMetrics(covariance_matrices, nAttr);
          
            mU = modifyPartitionMatrix (mV, mX);
            normaliseByColumns(mU);
         }
      }
      else if (_epsilon > 0)
      {
         double frob {0.0};
         do 
         {
            mV = calculateClusterCentres(mU, mX);
            std::vector<Matrix<double>> covariance_matrices = calculateCovarianceMatrices(mX, mU, mV);
            updateMetrics(covariance_matrices, nAttr);
            
            auto mUnew = modifyPartitionMatrix (mV, mX);
            normaliseByColumns(mUnew);
            frob = Frobenius_norm_of_difference (mU, mUnew);
            mU = mUnew;
         } while (frob > _epsilon);
      }
            
      mV = calculateClusterCentres(mU, mX);
      std::vector<std::vector<double>> mS = calculateClusterFuzzification(mU, mV, mX);
      
      auto prototypes = elaborate_gaussian_prototypes (_nClusters, nAttr, mV, mS);
//       debug(prototypes);
      
      auto A_matrices = get_A_matrices_from_metrics(metrics_for_clusters);
            
      ksi::partition part = elaborate_gaussian_partition(_nClusters, nAttr, mV, mS); 
      part.set_A_Matrices(A_matrices);
      
      return part;
   }
   CATCH;
}

std::vector<ksi::Matrix<double>> ksi::gk::get_A_matrices_from_metrics(const std::vector<ksi::metric_mahalanobis>& metrics)
{
   std::vector<ksi::Matrix<double>> A_matrices;
   for (const auto & m : metrics)
      A_matrices.push_back(m.get_A_matrix());
            
   return A_matrices;
}


void ksi::gk::updateMetrics(const std::vector<Matrix<double>>& covariance_matrices, const int nAttr)
{
   metrics_for_clusters.clear();
   for (const auto & C : covariance_matrices)
   {
      auto m = metric_mahalanobis(getAMatrixForMetric(C, nAttr, _volume_rho));
      metrics_for_clusters.push_back(m);
   }
}

ksi::Matrix<double> ksi::gk::getAMatrixForMetric(const Matrix<double> & covariance_matrix, const int nAttributes, const double volume_rho)
{
   try 
   {
      int status = 0;
      auto C_inv = covariance_matrix.invert(status);
      if (status != 0)
      {
         std::stringstream s;
         s << "Inversion of matrix impossible!" << std::endl;
         s << "matrix: " << std::endl;
         s << covariance_matrix << std::endl;
         throw s.str();
         // throw std::string ("Inversion of matrix impossible!");
      }
      auto determinant = covariance_matrix.determinant(status);
      if (status != 0)
      {
         throw std::string ("Elaboration of determinant impossible!");
      }
            
      auto factor = std::pow( volume_rho * determinant , 1.0 / nAttributes);
      
      return C_inv * factor;
   }
   CATCH;
}

ksi::gk::gk(const double volume_rho) : _volume_rho(volume_rho)
{
}


std::vector<ksi::Matrix<double>> ksi::gk::calculateCovarianceMatrices(const std::vector<std::vector<double>>& mX, const std::vector<std::vector<double>>& mU, const std::vector<std::vector<double>>& mV)
{
   auto nClusters = mV.size();
   auto nDataItems = mU[0].size();
   auto nAttribute = mV[0].size();
   
   std::vector<ksi::Matrix<double>> covariance_matrices;
   
   for (std::size_t c = 0; c < nClusters; c++)
   {
      ksi::Matrix<double> numerator(nAttribute, nAttribute, 0.0);
      double denominator {0.0};
      
      
      for (std::size_t x = 0; x < nDataItems; x++)
      {
         // numerator:
         auto X = mX[x];
         auto V = mV[c];
         
         auto col_X = ksi::Matrix<double>::ColumnMatrix(X);
         auto col_V = ksi::Matrix<double>::ColumnMatrix(V);
         
         auto X_V = col_X - col_V;
         auto X_V_tr = X_V.transpose();
         
         auto u_m = std::pow(mU[c][x], _m);
         
         numerator += X_V * X_V_tr * u_m; 
         
         // denominator:
         denominator += u_m;
      }
      
      covariance_matrices.push_back(numerator / denominator);
      
   }
   
   
   return covariance_matrices;
}

