/** @file */ 

#ifndef METRIC_MANHATTAN_H
#define METRIC_MANHATTAN_H

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
   class metric_manhattan: virtual public metric 
   {
   protected:
      
   public:
      virtual ~metric_manhattan();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      /** method for cloning an object */
      std::shared_ptr< ksi::metric > clone() const;
      
      /** @return abbreviation of the metric 
       @date 2021-02-01 */
      virtual std::string getAbbreviation() const override;
   };
}

#endif

