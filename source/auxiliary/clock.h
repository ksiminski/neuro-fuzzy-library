/** @file */

#ifndef CLOCK_H
#define CLOCK_H


#include <chrono>

namespace ksi
{
   /** This class simplifies measurement of time. 
    @date 2018-04-07
    */
   class clock
   {
      std::chrono::high_resolution_clock _zegar;
      std::chrono::high_resolution_clock::time_point _start {};
      std::chrono::high_resolution_clock::time_point _stop  {};
      
   public:
      
      /** Starts the clock.
       * @return start time point
       @date 2018-04-07 */
      std::chrono::high_resolution_clock::time_point start ();
      
      /** Stops the clock.
       * @return stop time point 
       @date 2018-04-07 
       */
      std::chrono::high_resolution_clock::time_point stop ();
      
      /** @return elapsed seconds 
        * @date 2018-04-07 
        */
      std::size_t elapsed_seconds();
 
   };
}

#endif 