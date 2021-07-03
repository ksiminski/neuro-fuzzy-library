

#ifndef GENERATIVE_MODEL_H
#define GENERATIVE_MODEL_H

#include <random>

#include "../common/dataset.h"
#include "../common/datum.h"


namespace ksi
{
   class generative_model
   {
    public:
      generative_model ();
      generative_model (const generative_model & wzor);
      generative_model (generative_model && wzor);
      generative_model & operator= (const generative_model & wzor);
      generative_model & operator= (generative_model && wzor);
      virtual ~generative_model ();
      
      virtual generative_model * clone_generator () const = 0;
      
      /** The method returns a random data item. */
      virtual datum get_random_datum (std::default_random_engine & engine) = 0;
      
      /** The method trains the generative model. */
      virtual void train_generative_model (const dataset & ds) = 0;
      
      /** The method returns a string representing information on the generative model */
      virtual std::string to_string () = 0;
      
      /** @return The method return root mean square error (RMSE) for the dataset.
       *  @param ds dataset to elaborate RMSE for 
       *  @date 2019-07-18
       */
      virtual double elaborate_rmse_for_dataset (const dataset & ds) = 0;
      
   };
}


#endif
