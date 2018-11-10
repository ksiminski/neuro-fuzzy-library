/** @file */

#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <utility>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "simulated-annealing.h"
#include "simulated-annealing-gaussian.h"


double ksi::simulated_annealing_gaussian::error(const std::vector<std::pair<double, double>> & punkty, double m, double s) const 
{
   double suma {0};
   for (auto p : punkty)
   {
      auto x = p.first;
      auto u = p.second;
      
      auto fx = gauss (x, m, s);
      
      auto froz = u - fx;
      suma += ( froz * froz  );
   }
   return suma;   
}

double ksi::simulated_annealing_gaussian::gauss(double x, double m, double s) const
{
   double roznica = x - m;
   return exp ( - (roznica * roznica) / (2 * s * s));
}

ksi::simulated_annealing_gaussian::~simulated_annealing_gaussian  ()
{
}
 
 
ksi::simulated_annealing_gaussian::simulated_annealing_gaussian(
   const double initial_temperature, 
   const double temperature_descrease_ratio, 
   const int maximal_number_of_iterations, 
   const int maximal_number_of_iterations_without_temperature_descrease,  
   const std::vector<std::pair<double, double>> & experimental_data)
: ksi::simulated_annealing (initial_temperature, temperature_descrease_ratio, 
                            maximal_number_of_iterations, 
                            maximal_number_of_iterations_without_temperature_descrease 
                           ) 
{
    _experimental_data = experimental_data; 
    
    engine = std::default_random_engine();
    engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
    
    distro = std::uniform_real_distribution<double> (-1, 1);
}
 

double ksi::simulated_annealing_gaussian::f(std::vector<double> x) const
{
   return error(_experimental_data, x[0], // m
                                    x[1]  // s
              );
}
 
 

std::vector<double> ksi::simulated_annealing_gaussian::get_first_point()
{
   try 
   {
      if (_experimental_data.size() == 0)
         throw std::string ("no data!");
      
      double suma = 0.0;
      double sumaKwadratow = 0.0;
      double x_min = std::numeric_limits<double>::max();
      double x_max = std::numeric_limits<double>::lowest();  
      
      for (const auto & p : _experimental_data)
      {
         double x = p.first;
         suma += x;
         sumaKwadratow += (x * x);
         
         if (x < x_min)
            x_min = x;
         if (x > x_max)
            x_max = x;
      }
      
      auto size = _experimental_data.size();
      double m = suma / size;
      double s = sqrt ( sumaKwadratow / size - m * m );
      
      _x_extr = std::pair<double, double> { x_min, x_max };
      _x_range = x_max - x_min;
      
      //debug(m);
      //debug(s);
       
      return { m, s };
   }
   CATCH;
}

std::vector<double> ksi::simulated_annealing_gaussian::get_next_point(const std::vector<double>& point)  
{
   const double SCALE = 0.1;
   
   double los;
   
   los = distro(engine);
   
   double m = point[0] + SCALE * los * _x_range;
   
   los = distro(engine);
   double s = point[1] * (1 + SCALE * los);
   
   //debug(m);
   //debug(s);   
   return {m, s};
}

ksi::simulated_annealing_gaussian::simulated_annealing_gaussian(const ksi::simulated_annealing_gaussian& wzor)
: ksi::simulated_annealing (wzor)
{
   _experimental_data = wzor._experimental_data;
   _x_extr = wzor._x_extr;
   _x_range = wzor._x_range;
   
   engine = wzor.engine;
   distro = wzor.distro;
   
}


ksi::simulated_annealing_gaussian::simulated_annealing_gaussian(ksi::simulated_annealing_gaussian && wzor) 
: ksi::simulated_annealing (wzor)
{
   std::swap (_experimental_data, wzor._experimental_data);
   std::swap ( _x_extr, wzor._x_extr);
   std::swap (_x_range, wzor._x_range);
   std::swap (engine, wzor.engine);
   std::swap (distro, wzor.distro);
   
}

ksi::simulated_annealing_gaussian & ksi::simulated_annealing_gaussian::operator=(const ksi::simulated_annealing_gaussian& wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::simulated_annealing::operator= (*this);
   
   _experimental_data = wzor._experimental_data;
   _x_extr = wzor._x_extr;
   _x_range = wzor._x_range;
   
   engine = wzor.engine;
   distro = wzor.distro;
   
   return *this;
}

ksi::simulated_annealing_gaussian & ksi::simulated_annealing_gaussian::operator=(ksi::simulated_annealing_gaussian && wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::simulated_annealing::operator= (*this);
   
   std::swap (_experimental_data, wzor._experimental_data);
   std::swap (_x_extr, wzor._x_extr);
   std::swap (_x_range, wzor._x_range);
   std::swap (engine, wzor.engine);
   std::swap (distro, wzor.distro);
   
   return *this;
   
}


ksi::simulated_annealing * ksi::simulated_annealing_gaussian::clone() const 
{
   return new ksi::simulated_annealing_gaussian (*this);
}
