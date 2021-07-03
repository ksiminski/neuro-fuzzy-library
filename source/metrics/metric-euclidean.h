/** @file */ 

#ifndef METRIC_EUCLIDEAN_H
#define METRIC_EUCLIDEAN_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"

namespace ksi
{
   /** Class for calculating a distance between data.
    * @date 2018-01-04
    * 
     */
   class metric_euclidean : virtual public metric 
   {
   protected:
      
   public:
      virtual ~metric_euclidean ();
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

