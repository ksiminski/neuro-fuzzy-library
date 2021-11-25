/** @file */ 

#ifndef METRIC_MINKOWSKI_H
#define METRIC_MINKOWSKI_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"

namespace ksi
{
   /** Class for calculating a distance in Minkowski metric
    * @date 2021-01-27
    * 
     */
   class metric_minkowski : virtual public metric 
   {
   protected:
      double _m; ///< exponent
   public:
      /** @param m exponent */ 
      metric_minkowski (double m); 
      
      metric_minkowski (const metric_minkowski &  ) = default;
      metric_minkowski (      metric_minkowski && ) = default;
            
      virtual ~metric_minkowski ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      /** method for cloning an object */
      virtual std::shared_ptr<metric> clone () const override;
      
      /** @return abbreviation of the metric 
       @date 2021-02-01 */
      virtual std::string getAbbreviation() const override;
      
      virtual std::string get_info() const override;
      
      
   };
}

#endif

