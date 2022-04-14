/** @file */ 

#ifndef DATUM_H
#define DATUM_H

#include <vector>
#include <utility>

#include "number.h"
#include "../service/debug.h"

namespace ksi
{
   class datum
   {
   protected:
      
      /** missing value symbol for printing */
      char MISSING_VALUE_SYMBOL = '?';
      
      /** attributes of a datum */
      std::vector<number *> attributes;
      /** decision value */
      number * pDecision = nullptr;
      /** weight of a datum item, default value 1.0 */
      double _weight = 1.0;
      /** typicality of data item */
      double _typicality;      
      /** typicality is valid and should be printed */
      bool _typicalityON = false;
      /** data ID, each datum has its own id in a dataset */
      long int _id = -1;
      /** ID of an incomplete data item this item imputes. If a data
       item imputes no other datum _id_incomplete == -1, otherwise
       it imputes the datum with ID == _id_incomplete. */
      long int _id_incomplete = -1;
      
   public:
      virtual ~datum();
      datum ();
      datum (const datum & d);
      datum (datum && d);
      datum & operator = (const datum & d);
      datum & operator = (datum && d);
      
      /** The method pushes back a number without allocation of memory.*/
      void push_back (number * p);
      /** The method pushes back a copy of number (allocates memory!) */
      void push_back (const number & d);
      /** The method sets decision. The previous decision is deleted and new set. The parameter is copied. 
       @param p decision to set */
      void setDecision (const number * p);
      /** The method sets decision. The previous decision is deleted and new set. The parameter is copied. 
       @param p decision to set */
      void setDecision (const number & p);
      /** The method get decision.
       @return a constant pointer to decision */
      const number * getDecision () const;
      
      virtual datum * clone() const;
      
      std::size_t getNumberOfAttributes() const ;
      
      /** @return returns a pointer to an attribute 
          @exception ksi::exception is attr in not a valid index
          */
      number * at (std::size_t attr) const;   
      
      
      /** The method returns attributes as a vector.
       * @return a vector of attributes' values
       * @date 2018-01-28
       * @author Krzysztof Siminski
       */
      std::vector<double> getVector() const;
      
      /** The method returns a weight value of a datum.
       * @date 2018-03-05
       * @author Krzysztof Siminski       
       * @return datum's weight
       */
      double getWeight() const;
      
      /** The method sets a weight value of a datum.
       * @date 2018-03-05
       * @author Krzysztof Siminski       
       * @param weight new value of weight. If the weight if less than 
       * 0, it is cut to 0.0; if the weight if greater than
       * 1, it it cut to 1.0.
       */
      void setWeight (double weight);
      
      /** The method returns a typicality of a datum.
       * @date 2018-05-14
       * @author Krzysztof Siminski       
       * @return datum's typicality
       */
      double getTypicality () const;
      
      /** The method sets a typicality value of a datum.
       * @date 2018-05-14
       * @author Krzysztof Siminski       
       * @param typicality new value of typicality. If the typicality if less than 
       * 0, it is cut to 0.0; if the typicality if greater than
       * 1, it it cut to 1.0.
       */
      void setTypicality (double typicality);
      
      /** The method switches printing typicality on and off.
       * @date 2018-05-22
       * @param on true -- switches on; false -- switches off. 
       */
      void switchTypicality (bool on);
      
      
      /** @return true, if typicality is on;
                  false, if typicality is off*/
      bool isTypicalityOn () const ;
     
      
      /** The method splits the datum into two data.
       * The first datum has attributes 0 .. last_index.
       * The second datum has attributes last_index + 1, .. number_of_attributes - 1. The original datum is not modified.
       * @param last_index index of the last attribute in the first datum to return
       * @return a pair of data  
       */
      std::pair<datum, datum> splitDatum(std::size_t last_index) const ;
      
      
      /** The method cuts off the last attribute.
       * The first datum has attributes 0 .. number_of_attributes - 2.
       * The second datum has attribute number_of_attributes - 1. The original datum is not modified.
       * @return a pair of data: first with all but last attribute and second with the last attribute  
       * @date 2019-07-18
       */
      std::pair<datum, datum> cutOffLastAttribute() const ;
      
      /** The method sets _id. */
      void setID (std::size_t id);
      
      /** @return data item _id */
      long int getID () const ;
      
      /** The method sets id of incomplete data item this datum imputes. */
      void setIDincomplete (long int id_incomplete);
      
      /** @return id of incomplete data item this datum imputes */
      long int getIDincomplete () const ;
      
      
      /** The method returns a string with values of all attributes of a datum.
       @date 2022-04-13*/
      std::string to_string() const;
      
      /** Output stream operator
        @date 2018-05-13
        */
      friend std::ostream & operator << (std::ostream & ss, const datum & d);
   };
}

#endif

