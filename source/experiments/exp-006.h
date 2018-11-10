/** @file */

#ifndef EXP_006_H
#define EXP_006_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 006  <br/>
    * 
    An experiment with rough fuzzy c-means (RFCOM) clustering algorithm.
    
    @date 2018-07-31
    
    @todo No i trzeba zebrać i zrobić eksperymenty dla RFCOM
    1. wyniki w funkcji liczby danych nietypowych [done]
    2. wyniki w funkcji funkcji straty [done]
    3. wyniki w funkcji owa            [done]
    4. Jak wyglądają typowości? [całkiem przyzwoicie]
    5. wyniki w funkcji metody uzupełniania danych [done]
    
    */
   class exp_006 : virtual public experiment
   {
   
   protected:
      
      /** The method finds the Frobenius norm for difference of localisation
       *  of clusters. Because the permutation of the elaborated clusters
       *  and original may be different, the valid permutation is one with
       *  the lowest Frobenius norm.
       * @param original original (expected) localisation of clusters
       * @param elaborated elaborated localisation of clusters
       * @return a pair { localisation of clusters for the best fit, Frobenius norm for the best fit }
       */
      std::pair<std::vector<std::vector<double>>, double> bestFrobenius 
      (const std::vector<std::vector<double>> & original, 
       const std::vector<std::vector<double>> & elaborated); 
      
      /** Elaboration of cluster centres for various dissimilarity function. */
      void exp_6_dissimilarity_function ();
      
      /**  
          @date 2018-10-25
          */
      void exp_6_all();
      
      /** Chce sprawdzic dokladnie przypisywanie typowosci.
       @date 2018-10-24
       */
      void exp_6_jeden_jedyny_eksperyment();
      
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
