
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
      
      virtual std::string get_name() const = 0;
      virtual std::string get_description() const = 0;
      
      
      
   protected:
       /** The method transforms distance to similarity.
        @param distance the distance to transform
        @return similarity 
        @date 2021-01-28
        */
       virtual double distance_to_similarity (const double distance) const;
       
      
   };
}


#endif
