
#ifndef METRIC_MAHALANOBIS_H
#define METRIC_MAHALANOBIS_H

#include <memory>

#include "../metrics/metric.h"
#include "../auxiliary/matrix.h"

namespace ksi
{
   class metric_mahalanobis : public metric
   {
   protected:
      Matrix<double> _A; 
    public:
      metric_mahalanobis (const Matrix<double> & A);
      metric_mahalanobis (const std::vector<std::vector<double>> & A);
      metric_mahalanobis (const metric_mahalanobis & wzor) = default;
      metric_mahalanobis (metric_mahalanobis && wzor) = default;
      metric_mahalanobis & operator= (const metric_mahalanobis & wzor) = default;
      metric_mahalanobis & operator= (metric_mahalanobis && wzor) = default;
      virtual ~metric_mahalanobis ();
      
      
      virtual std::string getAbbreviation() const override;
      virtual std::string get_info() const override;
      
      
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      
      virtual std::shared_ptr<metric> clone () const override;  // prototype design pattern
      
      /** @return The method returns the A matrix for the Mahalanobis metric.
       @date 2024-04-27 */
      Matrix<double> get_A_matrix() const;
   
   };
}


#endif
