
#ifndef GK_H
#define GK_H

#include "../partitions/fcm.h"
#include "../partitions/fcm_generic.h"
#include "../partitions/partitioner.h"
#include "../metrics/metric_mahalanobis.h"

namespace ksi
{
   /** Gustafson-Kessel clustering algorithm
    @date 2023-04-24
    @author Krzysztof Siminski
    */
   class gk : virtual public fcm
   {
   protected:
      std::vector<metric_mahalanobis> metrics_for_clusters;
      double _volume_rho = 1.0;  // cluster volume parameter
    public:
      gk ();
      gk (const double volume_rho);
      gk (const gk & wzor) = default;
      gk (gk && wzor) = default;
      gk & operator= (const gk & wzor) = default;
      gk & operator= (gk && wzor) = default;
      virtual ~gk ();
      virtual partitioner * clone () const override;  // prototype design pattern
      
   protected:
      std::vector<std::vector<double>> modifyPartitionMatrix(
               const std::vector<std::vector<double>> & mV, 
               const std::vector<std::vector<double>> & mX);
      
   protected:
      virtual double calculateDistance(const std::vector<double> & x, const std::vector<double> & y, const int cluster);
      
   protected:
      std::vector<Matrix<double>> calculateCovarianceMatrices(const std::vector<std::vector<double>> & mX, const std::vector<std::vector<double>> & mU, const std::vector<std::vector<double>> & mV);
      
   protected:
      /** The method updates the Mahalanobic metrics based on covariance matrices.
       * @date 2023-04-26 */
      void updateMetrics(const std::vector<Matrix<double>> & covariance_matrices, const int nAttr);
      
   protected:
      Matrix<double> getAMatrixForMetric(const Matrix<double> & covariance_matrix, const int nAttributes, const double volume_rho);
      
   protected:
      std::vector<Matrix<double>> get_A_matrices_from_metrics (const std::vector<metric_mahalanobis>& metrics);
      
   public:
      virtual ksi::partition doPartition(const ksi::dataset & ds) override;
      
   public:   
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const override;
   };
}


#endif
