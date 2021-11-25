/** @file */ 

#ifndef METRIC_H
#define METRIC_H

#include <vector>
#include <memory>

#include "../common/number.h"
#include "../common/datum.h"

namespace ksi
{
   /** Class for calculating a distance between data.
    * @date 2018-01-04
    * 
     */
   class metric 
   {
   protected:
      
   public:
      virtual ~metric ();
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const datum & l, const datum & p) const = 0;
      
      /** Just calculates a distance :-) */
      virtual double calculateDistance(const std::vector<double> & l, const std::vector<double> & p) const = 0;
      
      /** method for cloning an object */
      virtual std::shared_ptr<metric> clone () const = 0;
      
      /** @return abbreviation of the metric 
        * @date 2021-02-01 */
      virtual std::string getAbbreviation() const = 0;
      
      /** @return metric info
        * @date   2021-08-13       
       */
      virtual std::string get_info() const;
   };
}

#endif

