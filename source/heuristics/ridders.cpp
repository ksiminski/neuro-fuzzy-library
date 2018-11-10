/** @file */

#include <string>
#include <cmath>

#include "../service/debug.h"
#include "../auxiliary/utility-math.h"
#include "ridders.h"




double ksi::ridders::run()
{
   try 
   { 
      if (f(_minimum) * f(_maximum) > 0)
         throw std::string ("Function values for both ends of the interval have the same sign.");
      
      double root = 0;
      double previous_root = 0;
      double left = _minimum;
      double right = _maximum;
      double middle;
      
      bool stop = false;
      int iteration = 0;
      
      while (not stop)
      {
         middle = (left + right) / 2.0;
         double d = middle - left;
         double F_left = f(left);
         double F_middle = f(middle);
         double F_right = f(right);
         
//          debug(left);
//          debug(F_left);
//          debug(middle);
//          debug(F_middle);
//          debug(right);
//          debug(F_right);
         
         previous_root = root;
         
         /*
         double F_middle_F_left = F_middle / F_left;
         root = middle + d * (F_middle_F_left) / (sqrt (F_middle_F_left * F_middle_F_left - F_right / F_left));
         
         */
         double inv_sqrt_W = 1.0 / (sqrt (F_middle * F_middle - F_left * F_right));
         root = middle + sign(F_left) * d * F_middle * inv_sqrt_W;
         
         ///////////////
         double F_root = f(root);
         debug(root);
         debug(F_root);
         
         if (root < middle)
         {
            if (F_left * F_root < 0)
               right = root;
            else
            {
               left = root;
               right = middle;
            }
         }
         else
         {
            if (F_right * F_root < 0)
               left = root;
            else
            {
               right = root;
               left = middle;
            }
         }
         
            
         iteration++;
         if (_useEpsilon)
         {
            if (fabs(previous_root - root) < _epsilon)
               stop = true;
         }
         else
         {
            if (iteration >= _steps)
               stop = true;
         }
         
      }
      return root;
   }
   CATCH;
}

double ksi::ridders::run(double minimum, double maximum, double epsilon)
{
   try 
   {
      if (epsilon <= 0.0)
         throw std::string ("Epsilon should be positive.");
      
      _minimum = minimum;
      _maximum = maximum;
      _epsilon = epsilon;
      _useEpsilon = true;
      
      return run();
   }
   CATCH;
}

double ksi::ridders::run(double minimum, double maximum, int nSteps)
{
   try 
   {
      if (nSteps <= 0)
         throw std::string ("Number of steps should be positive.");
      
      _minimum = minimum;
      _maximum = maximum;
      _steps = nSteps;
      _useEpsilon = false;
      
      return run();
   }
   CATCH;
   
}

 

ksi::ridders::ridders()
{
}

ksi::ridders::~ridders()
{
}

ksi::ridders & ksi::ridders::operator=(const ksi::ridders& wzor)
{
   if (this == &wzor)
      return *this;
   
   _epsilon = wzor._epsilon;
   _maximum = wzor._maximum;
   _minimum = wzor._minimum;
   _steps = wzor._steps;
   _useEpsilon = wzor._useEpsilon;
   
   return *this;
}

ksi::ridders & ksi::ridders::operator=(ksi::ridders && wzor)
{
   if (this == &wzor)
      return *this;
   
   std::swap(_epsilon, wzor._epsilon);
   std::swap(_maximum, wzor._maximum);
   std::swap(_minimum, wzor._minimum);
   std::swap(_steps, wzor._steps);
   std::swap(_useEpsilon, wzor._useEpsilon);
   
   return *this;
}

ksi::ridders::ridders (const ksi::ridders & wzor)
{
   _epsilon = wzor._epsilon;
   _maximum = wzor._maximum;
   _minimum = wzor._minimum;
   _steps = wzor._steps;
   _useEpsilon = wzor._useEpsilon;
   
}

ksi::ridders::ridders (ksi::ridders && wzor)
{
   std::swap(_epsilon, wzor._epsilon);
   std::swap(_maximum, wzor._maximum);
   std::swap(_minimum, wzor._minimum);
   std::swap(_steps, wzor._steps);
   std::swap(_useEpsilon, wzor._useEpsilon);
}


double ksi::ridders::sign (double x)
{
   if (x > 0)
      return 1.0;
   if (x < 0)
      return -1.0;
   else 
      return 0.0;
}
