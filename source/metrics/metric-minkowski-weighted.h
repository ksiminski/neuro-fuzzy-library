/** @file */ 

#ifndef METRIC_MINKOWSKI_WEIGHTED_H
#define METRIC_MINKOWSKI_WEIGHTED_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"
#include "../metrics/metric-minkowski.h"

namespace ksi
{
   /** Class for calculating a distance in Minkowski metric
    * @date 2021-01-28
    * 
     */
   class metric_minkowski_weighted : public metric_minkowski
   {
   protected:
      std::vector<double> _weights;
   public:
      /** @param m exponent */ 
      metric_minkowski_weighted (double m, const std::vector<double> & weights); 
      
      metric_minkowski_weighted (const metric_minkowski_weighted &  ) = default;
      metric_minkowski_weighted (      metric_minkowski_weighted && ) = default;
            
      virtual ~metric_minkowski_weighted ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      /** method for cloning an object */
      virtual std::shared_ptr<metric> clone () const;
      
      /** @return abbreviation of the metric 
       @date 2021-02-01 */
      virtual std::string getAbbreviation() const;
   };
}

#endif

