/** @file */

#ifndef  DATA_MODIFIER_H
#define  DATA_MODIFIER_H

#include <string>

#include "dataset.h"

namespace ksi
{
   /** Class for modification of data.
    * The class implements a decorator design pattern.
    * @author Krzysztof Siminski
    * @date   2017-12-29
    */
   class data_modifier
   {
      
   protected:
      /** the next data_modifier (or derivative) */
      data_modifier * pNext;
      
      /** text description of the modifier */
      std::string description;
   public:
      /** just a constructor */
      data_modifier ();
      /** copy constructor */
      data_modifier (const data_modifier & dm);
      /** move constructor */
      data_modifier (data_modifier && dm);
      /** assignment operator */
      data_modifier & operator = (const data_modifier & dm);
      /** move assignment operator */
      data_modifier & operator = (data_modifier && dm);
      /** virtual destructor */
      virtual ~data_modifier();
      
      /** The method modifies the dataset.
       * This is an empty method (no modifications). Child classes implement 
       * modifications. It only calles the modify method of the next data_modifier.
        @param  ds dataset to modify
        @author Krzysztof Siminski
        @date   2017-12-29
        */
      virtual void modify (dataset & ds) = 0;     
      
      /** cloning method 
       @return returns a pointer to cloned object
       */
      virtual data_modifier * clone() const = 0;
      
      /** The method adds the dm modifier at the end of the chain of modifiers
          of this object. */ 
      void addModifier (data_modifier & dm);
      
      /** @return name of modifiers in chain */
      virtual std::string print () const ;
      
   };
}

#endif
