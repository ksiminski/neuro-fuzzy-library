    /** @file */ 

#ifndef FUBI_H
#define FUBI_H



#include "../partitions/partition.h"
#include "../partitions/partitioner.h"
#include "../common/dataset.h"


namespace ksi
{
   /** Fuzzy biclustering algorithm.
    *  @date 2020-08-16
    *  @author Krzysztof Siminski 
    
    
     * CITATION REQUEST
    *  The algorithm has been described in detail in papers:

    Krzysztof Siminski, FuBiNFS – fuzzy biclustering neuro-fuzzy system, [in] Fuzzy Sets and Systems, 2021. doi: 10.1016/j.fss.2021.07.009

    If you use this neuro-fuzzy system, please cite the paper:
    <pre>
    @article{id:Siminski2021FuBiNFS,
	abstract = "In data sets some attributes may have higher or lower importance. One of the tools used for data analysis of such datasets are subspace neuro-fuzzy systems. They elaborate fuzzy rules to describe data sets. In subspace neuro-fuzzy systems fuzzy rules exists in subspaces defined with subsets of attributes. In the paper we propose a novel fuzzy biclustering algorithm that groups both objects and attributes in fuzzy clusters. In that way we create a subspace fuzzy rule base for a subspace fuzzy system. The paper is accompanied with numerical examples that show this approach can lead to better generalisation (and thus lower data prediction errors) with preserved interpretation of fuzzy models.",
	author = "Krzysztof Siminski",
	doi = "10.1016/j.fss.2021.07.009",
	issn = "0165-0114",
	journal = "Fuzzy Sets and Systems",
	keywords = "Neuro-fuzzy system; Biclustering; Subspace clustering; Subspace neuro-fuzzy system; Attribute weights",
	title = "{FuBiNFS} – fuzzy biclustering neuro-fuzzy system",
	url = "https://www.sciencedirect.com/science/article/pii/S0165011421002499",
	year = "2021"
}
    </pre>
    * 
    */
   class fubi : public partitioner
   { 
       int _number_of_clusters;           ///< number of clusters 
       int _number_of_iterations;         ///< number of iterations 
       std::size_t _number_of_attributes; ///< number of attributes of data 
       std::size_t _number_of_data;       ///< number of data 
       double _m = 2.0;                   ///< clustering parameter 
       
       const double EPSILON { 0.0001 };   ///< indistiguishability threshold for distance (if the distance for a cluster is lower that EPSILON, we assume an example is exactly in the centre of the cluster)
       
       
       /** The method creates a 3D matrix with random values from uniform distribution [0,1]. 
        * The indices are: number of clusters, number of data, and number of attributes.
        @param number_of_clusters number of clusters
        @param number_of_data number of data
        @param number_of_attributes number of attributes
        */
       std::vector<std::vector<std::vector<double>>> randomise (
           const int number_of_clusters,
           const std::size_t number_of_data,
           const std::size_t number_of_attributes);
       
       /** The method normalises the partition matrix U
       * \f[ 
       *  \forall_{k \in K} \forall_{d \in D} \sum_{c =1}^{C} u_{ckd} = 1,
       * \f] 
       * where: <br/>
       * \f$ k \f$ -- data item<br/>
       * \f$ K \f$ -- set of data items<br/>
       * \f$ d \f$ -- attribute<br/>
       * \f$ D \f$ -- set of attributes<br/>
       * \f$ c \f$ -- cluster<br/>
       * \f$ C \f$ -- set of clusters<br/>
       * \f$ u_{ckd} \f$ -- membership value of the \f$d\f$-th attribute for the \f$k\f$-th data item in the \f$c\f$-th cluster<br/>
        @param U partition matrix to normalise
        @return normalised partition matrix */
       std::vector<std::vector<std::vector<double>>> normalise (const std::vector<std::vector<std::vector<double>>> & U);
       
       /** The method elaborates cluster centres with regard to data.
       * \f[ 
       * v_{cd}^{(k)} = \frac{\sum_{k=1}^{K} u_{ckd} x_{kd} }{\sum_{k=1}^{K} u_{ckd} } ,
       * \f] 
       * where: <br/>
       * \f$ k \f$ -- data item<br/>
       * \f$ K \f$ -- set of data items<br/>
       * \f$ d \f$ -- attribute<br/>
       * \f$ D \f$ -- set of attributes<br/>
       * \f$ c \f$ -- cluster<br/>
       * \f$ C \f$ -- set of clusters<br/>
       * \f$ u_{ckd} \f$ -- membership value of the \f$d\f$-th attribute for the \f$k\f$-th data item in the \f$c\f$-th cluster<br/>
       * \f$ x_{kd} \f$ -- value of \f$d\f$-th attribute for the \f$k\f$-th data item<br/>
        @param X data set
        @param _U membership matrix
        @return a matrix of cluster centres: each row represents a cluster, each column – an a data item.
        */
       std::vector<std::vector<double>> cluster_centres_for_data (
           const std::vector<std::vector<double>> & X, 
           const std::vector<std::vector<std::vector<double>>> & _U);

       /** The method elaborates cluster centres with regard to attributes.
       * \f[ 
       * v_{ck}^{(d)} = \frac{\sum_{d=1}^{D} u_{ckd} x_{kd} }{\sum_{d=1}^{D} u_{ckd} } ,
       * \f] 
       * where: <br/>
       * \f$ k \f$ -- data item<br/>
       * \f$ K \f$ -- set of data items<br/>
       * \f$ d \f$ -- attribute<br/>
       * \f$ D \f$ -- set of attributes<br/>
       * \f$ c \f$ -- cluster<br/>
       * \f$ C \f$ -- set of clusters<br/>
       * \f$ u_{ckd} \f$ -- membership value of the \f$d\f$-th attribute for the \f$k\f$-th data item in the \f$c\f$-th cluster<br/>
       * \f$ x_{kd} \f$ -- value of \f$d\f$-th attribute for the \f$k\f$-th data item<br/>
        @param X data set
        @param _U membership matrix
        @return a matrix of cluster centres: each row represents a cluster, each column – an attribute.
        */
       std::vector<std::vector<double>> cluster_centres_for_attibutes (
           const std::vector<std::vector<double>> & X, 
           const std::vector<std::vector<std::vector<double>>> & _U);
       
       
       /** The method updates the membership matrix.
        @param U membership matrix
        @param X data set
        @param V_data matrix of cluster centres with regard to data 
        @param V_attr matrix of cluster centres with regard to attributes
        @return updated membership matrix
        */
       
       std::vector<std::vector<std::vector<double>>> update_membership_matrix (
           const std::vector<std::vector<std::vector<double>>> & U,
           const std::vector<std::vector<double>> & X, 
           const std::vector<std::vector<double>> & V_data, 
           const std::vector<std::vector<double>> & V_attr);
       
       /** @return The method returns the distance defined as 
       * \f[ 
       * \xi_{ckd} = \left( x_{kd} - v_{cd}^{(k)}\right)^2 
       *           + \left( x_{kd} - v_{ck}^{(d)}\right)^2  ,
       * \f] 
       * where: <br/>
       * \f$ x_{kd} \f$ -- value of \f$d\f$-th attribute for the \f$k\f$-th data item<br/>
        */
       inline double ksi  (
           const std::vector<std::vector<double>> & X, 
           const std::vector<std::vector<double>> & V_data, 
           const std::vector<std::vector<double>> & V_attr,
           int c,
           std::size_t k,
           std::size_t d);
       
       /** @return The method returns fuzzification of clusters with regard to data. Each row represents a cluster, each column -- an attribute.
       * \f[ 
       * s_{cd} = \sqrt{ \frac{\sum_{i=1}^X u^m_{cid} \left(x_{id} - v_{cd}^{(k)}\right)^2}{\sum_{i=1}^X u^m_{cid}} }
        * \f] 
       * where: <br/>
       * \f$ s_{cd} \f$ -- fuzzification of \f$d\f$-th attribute in the \f$c\f$-th cluster<br/>
        * 
         */
       std::vector<std::vector<double>> calculateClusterFuzzification(
           const std::vector<std::vector<std::vector<double>>> & U, 
           const std::vector<std::vector<double>> & V_data, 
           const std::vector<std::vector<double>> & X);
       
       /** @return The method returns weights of attributes in clusters with regard to data. Each row represents a cluster, each column -- an attribute.
       * \f[ 
       * z_{cd} = \frac{\sum_{i=1}^X u^m_{cid} }{\sum_{g=1}^D\sum_{i=1}^X u^m_{cig}} 
        * \f] 
       * where: <br/>
       * \f$ z_{cd} \f$ -- weight of \f$d\f$-th attribute in the \f$c\f$-th cluster<br/>
        * 
         */
       std::vector<std::vector<double>> calculateAttributeWeights(
           const std::vector<std::vector<std::vector<double>>> & U, 
           const std::vector<std::vector<double>> & V_data, 
           const std::vector<std::vector<double>> & X);

       
   public:
       fubi (const int NUMBER_OF_CLUSTERS,
             const int NUMBER_OF_ITERATIONS);
       
       fubi (const fubi & wzor) = default;
       fubi (fubi && wzor) = default;
       
       virtual ~fubi();
      
      /** Virtual method for partition of dataset.
       * @param ds dataset to partition 
       * @return returns a elaborated partition (clusters with descriptors)
       */
      virtual partition doPartition(const dataset & ds);
      /** The method clones a partitioner and return a pointer to a cloned 
       *  object. This method is implemented in derived classes.
       **/
      
      
      
      virtual partitioner * clone () const;
      
      /** @return an abbreviation of a method */
      virtual std::string getAbbreviation () const;
   };
}

#endif

