/** @file */ 
#ifndef OWA_H
#define OWA_H

#include <iostream>

namespace ksi
{
   /** ordered weighted averaging
    @date 2018-05-20
    */
   class owa
   {
   protected:
      /** number of data */ 
      std::size_t _N;
   public:
      owa ();
      owa (std::size_t N);
      
      owa (const owa & wzor);
      owa & operator= (const owa & wzor);
      owa (owa && wzor);
      owa & operator= (owa && wzor);
       
      /** @return value of OWA */
      virtual double value (std::size_t n) const = 0;
      
      /** cloning method */
      virtual owa * clone() const = 0; 
      virtual ~owa();
      
      virtual std::ostream & Print (std::ostream & ss) const = 0;
      
      /** @return name of modifiers in chain */
      virtual std::string print () const ;
      
      /** The method sets a number of data items (_N).
       @param N parameter to set 
       @date 2019-12-22
       */
      void set_number_of_data_items (const std::size_t & N);
      
      /** @return parameters of the owa */
      virtual std::string print_owa_parameters() const = 0;
      
      /** @return false if parameters are not valid  */
      virtual bool are_parameters_valid() const = 0;
      
   };
}

#endif
