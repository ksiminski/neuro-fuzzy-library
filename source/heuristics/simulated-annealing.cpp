/** @file */

#include <string>
#include <cmath>
#include <random>
#include <chrono>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "simulated-annealing.h"



std::pair<std::vector<double>, double> ksi::simulated_annealing::run()
{
   try
   {
      //if (_minimal_parameter_values.empty() or _maximal_parameter_values.empty())
      //   throw std::string ("empty parameters");
      //if (_minimal_parameter_values.size() != _maximal_parameter_values.size())
      //   throw std::string ("minimal and maximal paramter numbers do not match");
      
      std::default_random_engine randomizer;      
      std::uniform_real_distribution<double> distro_for_worse_points (0, 1);
      
      /*
      auto parameter_ranges = _maximal_parameter_values;
      auto size = _maximal_parameter_values.size();
      for (std::size_t i = 0; i < size; i++)
         parameter_ranges[i] -= _minimal_parameter_values[i];
      */
      std::vector<double> old_xs = get_first_point();
      std::vector<double> new_xs;
      
      double old_fxs = f(old_xs);
      double new_fxs;
      
      _the_best_point = old_xs;
      _f_the_best_point = old_fxs;
      
      double t = _temperature;
      
      bool finish = false;
      
      int iter = 0;   // number of iteration
      int iter_t = 0; // number of iteration with the same temperature 
      
      while (not finish)
      {
         new_xs = get_next_point(old_xs);
         new_fxs = f(new_xs);
         
         //debug(old_fxs);
         //debug(new_fxs);
         
         if (new_fxs < old_fxs)
         {
            old_xs = new_xs;
            old_fxs = new_fxs;
            
         }
         else 
         {
            // the worst point is not always rejected
            auto p = exp ((old_fxs - new_fxs) / t); 
            if (p > distro_for_worse_points(randomizer))
            { 
               // accept worse point!
               old_xs = new_xs;
               old_fxs = new_fxs;
            }
            else 
            {  
               // reject worse point
            }
         }
         
         if (iter++ > _max_iterations)
            finish = true;
         iter_t++;
         if (iter_t > _max_iteration_for_temperature)
         {
            iter_t = 0;
            t *= _temperature_descrease_ratio;
         }
         
         if (new_fxs < _f_the_best_point)
         {
            _f_the_best_point = new_fxs;
            _the_best_point = new_xs;
         }
         
      }
      
      
      return { _the_best_point, _f_the_best_point };
      
   }
   CATCH;
}
 
ksi::simulated_annealing::~simulated_annealing()
{
}


ksi::simulated_annealing::simulated_annealing(const ksi::simulated_annealing & wzor)
{
   _temperature = wzor._temperature;
   _temperature_descrease_ratio = wzor._temperature_descrease_ratio;
   _max_iterations = wzor._max_iterations;
   _max_iteration_for_temperature = wzor._max_iteration_for_temperature;
   _the_best_point = wzor._the_best_point;
   _f_the_best_point = wzor._f_the_best_point; 
}

ksi::simulated_annealing::simulated_annealing(ksi::simulated_annealing && wzor)
{
   std::swap(_temperature, wzor._temperature);
   std::swap(_temperature_descrease_ratio, wzor._temperature_descrease_ratio);
   std::swap(_max_iterations, wzor._max_iterations);
   std::swap(_max_iteration_for_temperature, wzor._max_iteration_for_temperature);
   std::swap(_the_best_point, wzor._the_best_point);
   std::swap(_f_the_best_point, wzor._f_the_best_point);   
}

ksi::simulated_annealing & ksi::simulated_annealing::operator=(const ksi::simulated_annealing& wzor)
{
   if (this == & wzor)
      return *this;
   
   _temperature = wzor._temperature;
   _temperature_descrease_ratio = wzor._temperature_descrease_ratio;
   _max_iterations = wzor._max_iterations;
   _max_iteration_for_temperature = wzor._max_iteration_for_temperature;
   _the_best_point = wzor._the_best_point;
   _f_the_best_point = wzor._f_the_best_point; 
   
   
   return *this;
}


ksi::simulated_annealing & ksi::simulated_annealing::operator=(ksi::simulated_annealing && wzor)
{
   if (this == & wzor)
      return *this;
   
   std::swap(_temperature, wzor._temperature);
   std::swap(_temperature_descrease_ratio, wzor._temperature_descrease_ratio);
   std::swap(_max_iterations, wzor._max_iterations);
   std::swap(_max_iteration_for_temperature, wzor._max_iteration_for_temperature);
   std::swap(_the_best_point, wzor._the_best_point);
   std::swap(_f_the_best_point, wzor._f_the_best_point); 
   
   return *this;
}

 
ksi::simulated_annealing::simulated_annealing(const double initial_temperature, 
                                              const double temperature_descrease_ratio, 
                                              const int maximal_number_of_iterations, 
                                              const int maximal_number_of_iterations_without_temperature_descrease
                                              )
: _temperature (initial_temperature), 
  _temperature_descrease_ratio (temperature_descrease_ratio),
  _max_iterations (maximal_number_of_iterations),
  _max_iteration_for_temperature (maximal_number_of_iterations_without_temperature_descrease)                    
{
}

 
