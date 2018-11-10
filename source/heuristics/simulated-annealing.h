/** @file */

#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include "../service/debug.h"

namespace ksi
{
   /** The class executed simulated annealing opimisation heuristics – minimum search
    * 
    * 
    * For your function derive a new class from this one and implement an f(std::vector<double> x) method.
    */
   class simulated_annealing
   {
      /** temperature */
      double _temperature;
      
      /** temperature_descrease_ratio */
      double _temperature_descrease_ratio;
      
      /** maximal number of iterations */
      int _max_iterations;
      
      /** maximal number of iterations without decrease of temperature */
      int _max_iteration_for_temperature;
      
      /** the best point found in the whole heuristics */
      std::vector<double> _the_best_point;
      /** function value for the best point -- presumed global minimum */
      double _f_the_best_point;
      
      /** The method elaborates the first point for the heuristics. 
       * @return the first point */
      virtual std::vector<double> get_first_point () = 0;
      

      /** The method elaborates a new point from the neighbourhood.
       * Runs of the method for the same parameter have to return different results. 
       * Use some randomizer to do this. Otherwise the algorithm is likely to stuck
       * in one point for ever.
       @param point a point for which a neighbour is sought 
       @return a neighbour of a point (a parameter) */
      virtual std::vector<double> get_next_point (const std::vector<double> & point) = 0;
      
       
   public:   
      /** The method implements a function whose root is searched. */
      virtual double f (std::vector<double> x) const = 0;

      /** implements simulated_annealing heuristics
       @return a pair: the best point, value of the function for the best point
       */
      std::pair<std::vector<double>, double> run ();
      
       
      /** 
       @param initial_temperature   initial temperature for simulated annealing
       @param temperature_descrease_ratio temperature decrease ratio -- value from the interval [0, 1]
       @param maximal_number_of_iterations maximal number of iterations
       @param maximal_number_of_iterations_without_temperature_descrease maximal number of iterations with the same temperature
       @param minimal_parameter_values vector of minimal values in the task domain
       @param maximal_parameter_values vector of maximal values in the task domain
       */ 
      simulated_annealing (const double initial_temperature,
         const double temperature_descrease_ratio,
         const int maximal_number_of_iterations,
         const int maximal_number_of_iterations_without_temperature_descrease 
      );
       
      simulated_annealing (const simulated_annealing & wzor);
      simulated_annealing (simulated_annealing && wzor);
       
      virtual ~simulated_annealing ();
      
      simulated_annealing & operator= (const simulated_annealing & wzor);
      simulated_annealing & operator= (simulated_annealing && wzor);
       
      virtual simulated_annealing * clone () const = 0 ;
      
   };
}
#endif
