
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

// #include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/premise.h"
#include "../common/datum.h"

namespace ksi
{
   /** @date 2021-01-27 */ 
   class prototype : public premise
   {
      
    public:
      prototype ();
      prototype (const prototype & wzor);
      prototype (prototype && wzor);
      prototype & operator= (const prototype & wzor);
      prototype & operator= (prototype && wzor);
      virtual ~prototype ();
      
      /** @return similarity of a datum to the prototype
          @param d datum to elaborate similarity for */
      virtual double get_similarity (const ksi::datum & d) const = 0;
      
      /** @return similarity of a datum to the prototype
          @param d datum to elaborate similarity for */
      virtual double get_similarity (const std::vector<double> & X) const = 0;
      
      virtual double getFiringStrength(const std::vector<double> & X) override;
      
      virtual void addDescriptor (const descriptor & d) = 0;
      
      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      * @return the stream (ss -- parameter) the methods has printed into
      */
      virtual std::ostream & Print (std::ostream & ss) const override;
      
      /** @return white character free name of the prototype type */
      virtual std::string get_name() const = 0;
      
      /** @return description of the prototype type */
      virtual std::string get_description() const = 0;
      
      
      
   protected:
       /** The method transforms distance to similarity.
        @param distance the distance to transform
        @return similarity 
        @date 2021-01-28
        */
       virtual double distance_to_similarity (const double distance) const;
       
      
     /** The method elaborates  cardinality of the prototype, average value of decision attribute in the prototype, and similarities of add data to the prototype
      @param X dataset
      @param Y decision attribute
      @return cardinality of the prototype, average value of decision attribute in the prototype, and similarities of the data to the prototype
      @date 2023-07-05
      */
     std::tuple<double, double, std::vector<double>> cardinality_similarities (const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const;

  /** The method elaborates the Gini index.
        @param probability_positive probability of positive class
        @param probability_negative probability of negative class
        @return Gini index */
      double Gini_values(const double probability_positive, const double probability_negative) const;
   };
}


#endif
