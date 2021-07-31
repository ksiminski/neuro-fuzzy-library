/** @file */ 

#ifndef SFCM_H
#define SFCM_H

 
#include <vector> 
#include "../auxiliary/definitions.h"
#include "partitioner.h"
#include "partition.h"
#include "../common/dataset.h"
#include "fcm.h"


namespace ksi
{
   /** The class implements Subspace Fuzzy C-means clustering algorithm. 
    Subspace fuzzy c-means algorithm is a clustering algorithm that assings each data items with its memberships to clusters and in each cluster it assings weight to each attributes. The algorithm has been described in detail in papers:


    Krzysztof Siminski, Clustering in Fuzzy Subspaces, [in] Theoretical and Applied Informatics, 2012, volume 24, number 4, pp. 313-326. doi: 10.2478/v10179-012-0019-y
    
    Krzysztof Siminski, Neuro-fuzzy system with weighted attributes, [in] Soft Computing, 2014, volume 18, number 2, pp. 285-297. doi: 10.1007/s00500-013-1057-z

    * CITATION REQUEST
    If you use this algorithm, please cite the paper:
    <pre>
    ARTICLE{id:Siminski2014Neuro,
      author = {Krzysztof Siminski},
      title = {Neuro-fuzzy system with weighted attributes},
      journal = {Soft Computing},
      volume = {18}, 
      number = {2}, 
      pages = {285--297}, 
      year = {2014},
      doi = {10.1007/s00500-013-1057-z},
      abstract = {The paper presents the neuro-fuzzy system with weighted attributes.
                  Its crucial part is the fuzzy rule base composed of fuzzy rules
                  (implications). In each rule the attributes have their own weights.
                  In our system the weights of the attributes are numbers from the
                  interval $[0, 1]$ and they are not global: each fuzzy rule has its
                  own attributes' weights, thus it exists in its own weighted
                  subspace. The theoretical description is accompanied by  results
                  of experiments on real life data sets. They show that 
                  the neuro-fuzzy system  with weighted attributes can elaborate 
                  more precise results than the system that does not apply  weights
                  to attributes. Assigning weights to attributes can also discover 
                  knowledge about importance of attributes and their relations.},
    }
    </pre>
    */
   class sfcm : virtual public fcm
   {
   protected:
      double _weight_exponent = 2.0;
      
      std::vector<std::vector<double>> modifyPartitionMatrix (
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector<std::vector<double>> & mZ);
      
      std::vector<std::vector<double>> modifyAttributeWeights (
         const std::vector<std::vector<double>> & mV, 
         const std::vector<std::vector<double>> & mX, 
         const std::vector<std::vector<double>> & mU);
      
   public: 
      /** The method sets the weight expoment **/
      void setWeigthExponent (double WeightExponent);
      virtual partition doPartition(const ksi::dataset & ds);
      virtual partitioner * clone () const;
      virtual ~sfcm ();  
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
      
      sfcm ();
      sfcm (const int nClusters, const int nClusteringIterations);
      
      sfcm (const sfcm & wzor);
      sfcm (sfcm && wzor);
      sfcm & operator = (const sfcm & wzor);
      sfcm & operator = (sfcm && wzor);
   };

}

#endif

