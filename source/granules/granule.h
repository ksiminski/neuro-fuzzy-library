/** @file */


#ifndef GRANULE_H
#define GRANULE_H

#include <random>
#include <chrono>

#include "../common/datum.h"
#include "../common/number.h"
 

namespace ksi
{
    class rule;
    
    /** A class representing a data granule. 
     @date 2019-04-25
     */
    class granule
    {
    protected:
        
        static std::default_random_engine _engine;
        
        /** cardinality of granule (number of items covered by the granule) */
        double _cardinality;
        /** quality of granule, 0.0 -- the lowest quality, 1.0 -- the highest quality */
        double _quality;
        /** error of the granule */
        double _error;
        
    public:
        
        granule ();
        granule (const granule & wzor);
        granule (granule && wzor);
        granule & operator= (const granule & wzor);
        granule & operator= (granule && wzor);
        
        
        /** The method clones a granule and returns a pointer to a copy. */
        virtual granule * clone_granule () const = 0;
        
        /** The method elaborates quality of the granule. */
        virtual void elaborate_quality () = 0;
        
        /** @return The method returns cardinality of the granule */
        virtual const double get_cardinality () const;
        
        /** The method sets cardinality of the granule.
         @param cardinality the cardinality value to set. 
         If provided value is less than 0, cardinality is set to 0.*/
        virtual void set_cardinality (const double cardinality);
        
        /** The method resets cardinality to zero. */
        virtual void reset_cardinality ();
        
        /** @return The method returns the quality of the granule. */
        virtual double get_quality () const;
        
        /** The method sets quality of the data item.
         @param quality the quality value to set. If provided value is less than 0, quality is set to 0, if value is greater than 1, quality is set to 1.
         */
        virtual void set_quality (const double quality);
        
        /** The method gets the error of the granule. Just a getter.
         @return error of the granule (_error field) */
        virtual double get_error () const;
        
        /** The method sets the error of the granule. Just a setter.
         @param error value to set */
        virtual void set_error (const double error);
        
        
        /** @return The method returns a data_item represented by the data granule. */
        virtual datum get_data_item () = 0;
        
        /** @return The method returns a decision for a datum.
         *  @param  d the datum to elaborated answer for .*/
        virtual const number get_answer (const datum & d) = 0;
        
        /** @return  The method return a pointer to a copy of rule, a granule can be transformed into. If it is impossible, nullptr is returned.
         The method allocates memory. */
        virtual rule * get_rule ()  const;
        
        virtual ~granule ();
    };

}

#endif
