
#ifndef DATA_ITEM_H
#define DATA_ITEM_H

#include "../common/datum.h"
#include "../common/number.h"
#include "../granules/granule.h"


namespace ksi
{

    class data_item : public granule
    {
    protected:
        datum * pDatum = nullptr;
        number _decision;
    public:
        data_item ();
        data_item (const datum & d);
        data_item (const datum & d, const number & decision);
        data_item (const data_item & wzor);
        data_item (data_item && wzor);
        data_item & operator= (const data_item & wzor);
        data_item & operator= (data_item && wzor);
        virtual ~data_item ();        
        
        // methods for granules
        virtual granule * clone_granule() const;
        
        /** The method elaborates quality of the granule. */
        virtual void elaborate_quality ();
        
        /** @return The method returns a data_item represented by the data granule. */
        virtual datum get_data_item ();
        
        /** @return The method returns a decision for a datum.
            @param  d the datum to elaborated answer for .*/
        virtual const number get_answer (const datum & d);
    };
}

#endif
