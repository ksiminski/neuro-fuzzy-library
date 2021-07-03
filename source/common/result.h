
#ifndef RESULT_H
#define RESULT_H

#include <utility>

namespace ksi
{
    struct result 
    {
        double rmse_train;  ///< root mean square error for train dataset
        double rmse_test;   ///< root mean square error for test  dataset
        double mae_train;   ///< mean absolute error for train dataset
        double mae_test;    ///< mean absolute error for test dataset
        
        std::size_t TrainPositive2Positive; ///< true positives
        std::size_t TrainPositive2Negative; ///< false negatives
        std::size_t TrainNegative2Negative; ///< true negatives
        std::size_t TrainNegative2Positive; ///< false positives        
        
        std::size_t TestPositive2Positive; ///< true positives
        std::size_t TestPositive2Negative; ///< false negatives
        std::size_t TestNegative2Negative; ///< true negatives
        std::size_t TestNegative2Positive; ///< false positives        
        
    };
}

#endif
