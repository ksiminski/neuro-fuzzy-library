/** @file */

#ifndef RIDDERS_H
#define RIDDERS_H

#include <vector>
#include "../service/debug.h"

namespace ksi
{
   /** The class finds a single real root of a function. 
    * The algorithm is described in 
    * C. J. F. Ridders, A new algorithm for computing a single root of a real continuous
    * function, IEEE Transactions on circuits and systems, vol. cas-26, no. 11, 1979
    * 
    * For your function derive a new class from this one and implement an f(double x) method.
    */
   class ridders
   {
      /** left end of an interval to search in */
      double _minimum;
      /** right end of an interval to search in */
      double _maximum;
      /** number of steps of algorithm */
      int _steps;
      /** maximal allowed difference between roots in consecutive iterations */
      double _epsilon;
      /** true if epsilon used */
      bool _useEpsilon;
       
      /** implements Ridders's algorithm */
      double run ();
      
      /** @return sign of a number, if x == 0, returns 0 */
      double sign (double x);
       
   public:   
      /** The method implements a function whose root is searched. */
      virtual double f (double x) = 0;
   public:
      /** The method runs the Ridders's algorithm.
       * The function tries to find a root in the interval 
       * [minimum, maximum] with nSteps steps.
       @param minimum a left limit of an interval to search
       @param maximum a right limit of an interval to search
       @param nSteps number of steps of the algorithm
       */
      double run (double minimum, double maximum, int nSteps);
      
      /** The method runs the Ridders's algorithm.
       * The function tries to find a root in the interval 
       * [minimum, maximum] with nSteps steps.
       @param minimum a left limit of an interval to search   *
       @param maximum a right limit of an interval to search
       @param epsilon maximal allowed difference between calculated roots in consecutive 
                       iterations, if difference less than epsilon, algorithm stops
       */
       double run (double minimum, double maximum, double epsilon);
       
       
       ridders ();
       
       ridders (const ridders & wzor);
       ridders (ridders && wzor);
       
       virtual ~ridders ();
       
       ridders & operator= (const ridders & wzor);
       ridders & operator= (ridders && wzor);
       
       virtual ridders * clone () const = 0 ;
       
   };
}
#endif
