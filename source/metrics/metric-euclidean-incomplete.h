/** @file */ 

#ifndef METRIC_EUCLIDEAN_INCOMPLETE_H
#define METRIC_EUCLIDEAN_INCOMPLETE_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"
#include "../metrics/metric-euclidean.h"

namespace ksi
{
   /** Class for calculating an Euclidean distance between incomplete data.
    * @date 2018-01-04
    * 
     */
   class metric_euclidean_incomplete : virtual public metric_euclidean
   {
   protected:
      
   public:
      virtual ~metric_euclidean_incomplete();  
      /** Just calculates a metric :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      /** @throw The method always throws an exception, because it is impossible to put missing values in a vector. */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      /** method for cloning an object */
      virtual std::shared_ptr<metric> clone () const;
      
      /** @return abbreviation of the metric 
       @date 2021-02-01 */
      virtual std::string getAbbreviation() const;
   };
}

#endif

