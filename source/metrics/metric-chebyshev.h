/** @file */ 

#ifndef METRIC_CHEBYSHEV_H
#define METRIC_CHEBYSHEV_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"

namespace ksi
{
   /** Class implementing the Chebyshev metric.
    * @date 2023-10-12
    * @author Maksymilian Broja
     */
   class metric_chebyshev : virtual public metric 
   {
   protected:
      
   public:
      virtual ~metric_chebyshev ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const override;
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const override;
      /** method for cloning an object */
      std::shared_ptr< ksi::metric > clone() const;
      
      /** @return abbreviation of the metric */
      virtual std::string getAbbreviation() const override;
   };
}

#endif

