/** @file */ 

#ifndef METRIC_COSINE_H
#define METRIC_COSINE_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"
#include "../metrics/metric.h"

namespace ksi
{
   /** Class implementing the cosine metric.
    * @date 2023-10-12
    * @author Maksymilian Broja
    * 
     */
   class metric_cosine : virtual public metric 
   {
   protected:
      
   public:
      virtual ~metric_cosine ();
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

