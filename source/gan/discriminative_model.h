
#ifndef DISCRIMINATIVE_MODEL_H
#define DISCRIMINATIVE_MODEL_H

#include "../common/dataset.h"

namespace ksi
{
   class discriminative_model
   {
    public:
      discriminative_model ();
      discriminative_model (const discriminative_model & wzor);
      discriminative_model (discriminative_model && wzor);
      discriminative_model & operator= (const discriminative_model & wzor);
      discriminative_model & operator= (discriminative_model && wzor);
      virtual ~discriminative_model ();
      
      virtual discriminative_model * clone_discriminant () const = 0;
      
      /** The method trains the discriminative model. */
      virtual void train_discriminative_model (const dataset & ds) = 0;
      
      /** The method elaborates the answer of the discriminative_model for a datum 
       @param d a datum to elaborate answer for
       @return just a value :-)
       */
      virtual double discriminate (const datum & d) = 0; 
      
      /** The method returns a string representing information on the discriminative model */
      virtual std::string to_string () = 0;
   };
}


#endif
