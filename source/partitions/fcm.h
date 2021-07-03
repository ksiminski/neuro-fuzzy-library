/** @file */ 

#ifndef FCM_H
#define FCM_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "../partitions/partitioner.h"
#include "../partitions/partition.h"
#include "../partitions/fcm_generic.h"
#include "../common/dataset.h"


namespace ksi
{
   /** The class implements Fuzzy C-means clustering algorithm.
    @date 2021-02-01*/
   class fcm : public fcm_generic
   {
   public: 
      fcm ();
      /** @param nClusters number of clusters to cluster data into
          @param nClusteringIterations number of iterations of clutering procedure 
          @date 2019-12-24*/
      fcm (const int nClusters, const int nClusteringIterations);
      fcm (const fcm & wzor); 
      fcm & operator = (const fcm & wzor); 
 
      virtual partitioner * clone () const;
      virtual ~fcm ();  
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };

}


// namespace ksi
// {
//    /** The class implements Fuzzy C-means clustering algorithm. */
//    class fcm : virtual public fcm_T<double>
//    {
//    public: 
//       fcm ();
//       /** @param nClusters number of clusters to cluster data into
//           @param nClusteringIterations number of iterations of clutering procedure 
//           @date 2019-12-24*/
//       fcm (const int nClusters, const int nClusteringIterations);
//       fcm (const fcm & wzor); 
//       fcm & operator = (const fcm & wzor); 
//  
//       virtual partitioner * clone () const;
//       virtual ~fcm ();  
//       
//       /** @return an abbreviation of a method */
//       virtual std::string getAbbreviation () const;
//    };
// 
// }

#endif

