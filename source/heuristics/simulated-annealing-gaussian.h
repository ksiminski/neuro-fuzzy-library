/** @file */

#ifndef SIMULATED_ANNEALING_GAUSSIAN_H
#define SIMULATED_ANNEALING_GAUSSIAN_H

#include <vector>
#include <utility>
#include <random>
#include "../service/debug.h"
#include "simulated-annealing.h"

namespace ksi
{
   /** Simulated annealing for minimalisation of Gaussian approximation. The class elaborates
    * parameters of a Gaussian function: m (mean) and s (fuzzyfication).
    */ 
   class simulated_annealing_gaussian : public simulated_annealing
   {
   protected:
      /** Defines experimental data in form of a pair: \f$\langle x, y\rangle\f$.
       */
      std::vector<std::pair<double, double>> _experimental_data;
      
      /** minimum and maximum value of x */
      std::pair<double, double> _x_extr;
      /** x range = max_x - min_x */
      double _x_range;
      
      
      std::default_random_engine engine;
      std::uniform_real_distribution<double> distro;
      
      /** @return a vector of two items: initial m and s. */
      virtual std::vector<double> get_first_point ();
      /** @return a neighbour of point (parameter) vector of two items: m and s.
          @param point a vector { m, s } 
       */
      virtual std::vector<double> get_next_point (const std::vector<double> & point);
      
      
      /** Implements a function \f$g\f$ defined as
       \f[  
           g(x) = \exp \left( - \frac{(x - m)^2}{2 s^2} \right)
       \f]
       */
      double gauss (double x, double m, double s) const;
      
      /** Calculates an error for the whole data set with formula
       \f[
            E = \sum_{i = 1}^N \left( g(x_i) - y_i \right)^2
       \f]
       */
      double error (const std::vector<std::pair<double, double>> & punkty, double m, double s) const;
      
       
   public:   
      /** The method implements a function whose root is searched. 
       @param x is a vector of two items: m (mean value) and s (fuzzyfication) */
      virtual double f (std::vector<double> x) const;
 
      
       
      simulated_annealing_gaussian (const double initial_temperature,
                           const double temperature_descrease_ratio,
                           const int maximal_number_of_iterations,
                           const int maximal_number_of_iterations_without_temperature_descrease,
                           const std::vector<std::pair<double, double>> & experimental_data
      );
       
      simulated_annealing_gaussian (const simulated_annealing_gaussian & wzor);
      simulated_annealing_gaussian (simulated_annealing_gaussian && wzor);
       
      virtual ~simulated_annealing_gaussian ();
      
      simulated_annealing_gaussian & operator= (const simulated_annealing_gaussian & wzor);
      simulated_annealing_gaussian & operator= (simulated_annealing_gaussian && wzor);
       
      virtual simulated_annealing * clone () const;
      
   };
}
#endif
