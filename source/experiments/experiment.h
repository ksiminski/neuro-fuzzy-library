/** @file */

#ifndef EXPERIMENT_H
#define EXPERIMENT_H


namespace ksi
{
   /** This class is designed for executing an experiment. */
   class experiment
   {
      /** The method executes an experiment. */
      virtual void execute () = 0;
   };
}

#endif 