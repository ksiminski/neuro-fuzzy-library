
#ifndef GAN_H
#define GAN_H

#include "../common/dataset.h"
#include "../gan/generative_model.h"
#include "../gan/discriminative_model.h"

namespace ksi
{
   class gan
   {
    protected:
      generative_model     * _pGenerator     = nullptr;
      discriminative_model * _pDiscriminator = nullptr;
      
      /** number of iterations */
      int _nIterations;
      
      const int ORIGINAL = 1;
      const int FORGED   = 0;
       
    public:
        
      gan (const int number_of_iterations,
           const generative_model & p_gen,
           const discriminative_model & p_dis);
      
      
      gan (const gan & wzor);
      gan (gan && wzor);
      gan & operator= (const gan & wzor);
      gan & operator= (gan && wzor);
      virtual ~gan ();
      
      /** Jeszcze nie w pelni skonczona metoda tranujaca GAN 
       @param ds dataset with data to train
       @date  2019-07-14 (started)
       */
      void train (const dataset & ds);
      
      
   };
}


#endif
