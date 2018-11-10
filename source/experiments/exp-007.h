/** @file */

#ifndef EXP_007_H
#define EXP_007_H


#include "../experiments/experiment.h"

namespace ksi
{
   /** EXPERIMENT 007  <br/>
    * 
    An experiment with Ridders approximation algorithm
    
    @date 2018-09-09
    
    
    */
   class exp_007 : virtual public experiment
   {
   
   protected:

      double F (double m);
      double Fprim (double m);
      
      double gauss (double x, double m, double s);
      double blad (const std::vector<std::pair<double, double>> & punkty, double m, double s);
      double wyzarz_m (const std::vector<std::pair<double, double>> & punkty, const double M_MIN, const double M_MAX, const double s, const double EPSILON, const double temp);
      double wyzarz_s (const std::vector<std::pair<double, double>> & punkty, const double S_MIN, const double S_MAX, const double m, const double EPSILON, const double temp);
      
   public:
      /** The method executes an experiment. */
      virtual void execute ();
   };
}

#endif 
