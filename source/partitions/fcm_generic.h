/** @file */ 

#ifndef FCM_GENERIC_H
#define FCM_GENERIC_H

 
#include <vector> 
#include <memory>

#include "../auxiliary/definitions.h"
#include "../partitions/partitioner.h"
#include "../partitions/partition.h"
#include "../partitions/fcm-T.h"
#include "../common/dataset.h"
#include "../metrics/metric.h"

namespace ksi
{
   /** The class implements Fuzzy C-means clustering algorithm. */
   class fcm_generic : public fcm_T<double>
   {
   protected:
       std::shared_ptr<ksi::metric> _pMetric; ///< metric object
   public: 
      fcm_generic (const ksi::metric & metric_object);
      /** @param nClusters number of clusters to cluster data into
          @param nClusteringIterations number of iterations of clutering procedure 
          @date 2019-12-24*/
      fcm_generic (const int nClusters, const int nClusteringIterations, const ksi::metric & metric_object);
      fcm_generic (const fcm_generic & wzor); 
      fcm_generic (fcm_generic && wzor); 
      
      fcm_generic & operator = (const fcm_generic & wzor); 
      fcm_generic & operator = (fcm_generic && wzor); 
 
      virtual partitioner * clone () const;
      virtual ~fcm_generic ();  
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
      
      virtual double calculateDistance(const std::vector<double> & x, const std::vector<double> & y) override;
   };

}

#endif

