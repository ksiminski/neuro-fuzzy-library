/** @file */

 

#include <string>
#include <iostream>
#include <vector>

#include "./experiments/exp-001.h"
#include "./experiments/exp-002.h"
#include "./experiments/exp-003.h"
#include "./experiments/exp-004.h"
#include "./experiments/exp-005.h"

 
int main (int argc, char ** params)
{
    if (argc == 1)
    {
        std::cout << "No experiment chosen." << std::endl;
        std::cout << "Provide number of an experiment as an only parameter, eg." << std::endl;
        std::cout << params[0] << " 2" << std::endl;
        std::cout << "to run the 2nd experiment." << std::endl;
    }   
    else 
    {
        int number = atoi(params[1]);
        try
        {
            switch(number)
            {
                case 1: { 
                    ksi::exp_001 experiment;
                    experiment.execute();
                    break;
                }
                case 2: { 
                    ksi::exp_002 experiment;
                    experiment.execute();
                    break;
                }
                case 3: { 
                    ksi::exp_003 experiment;
                    experiment.execute();
                    break;
                }
                case 4: { 
                    ksi::exp_004 experiment;
                    experiment.execute();
                    break;
                }
                case 5: { 
                    ksi::exp_005 experiment;
                    experiment.execute();
                    break;
                }
                default: {
                    std::cout << "unknown experiment" << std::endl;
                }
            }
        }
        catch (std::exception & w)
        {
            std::cout << w.what() << std::endl;
        }
        catch (std::string & w)
        {
            std::cout << w << std::endl;
        }
        catch (...)
        {
            std::cout << "unknown exception" << std::endl;
        }
    } 
   return 0;
} 


