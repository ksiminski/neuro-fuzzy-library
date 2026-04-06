/** @file */

#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

#include <vector>
#include <string>

#include "../common/result.h"

namespace ksi
{
   /** This class calculates statistics and prints confusion matrix.  */
   class confusion_matrix
   {
        public:
            
        /** The method calculates the statistics.
            * @param expected a vector with expected values
            * @param elaborated a vector with corresponding elaborated values
            * @param PositiveClassLabel label of positive class
            * @param NegativeClassLabel label of negative class
            * @param[out] nTruePositives  true positives, TP
            * @param[out] nTrueNegatives  true negatives, TN
            * @param[out] nFalsePositives false positives, FP
            * @param[out] nFalseNegatives false negatives, FN
            * @param dbThreshold     a threshold to tell positives from negatives
            */   
        void calculate_statistics (const std::vector<double> & expected, 
                                   const  std::vector<double> & elaborated,
                                    double PositiveClassLabel,
                                    double NegativeClassLabel,
                                    int & nTruePositives,
                                    int & nTrueNegatives,
                                    int & nFalsePositives,
                                    int & nFalseNegatives,
                                    double dbThreshold);
        
        /** The method calculates the statistics.
            * @param expected_classes a vector with expected classes
            * @param elaborated_classes a vector with corresponding elaborated classes
            * @param PositiveClassLabel label of positive class
            * @param NegativeClassLabel label of negative class
            * @param[out] nTruePositives  true positives, TP
            * @param[out] nTrueNegatives  true negatives, TN
            * @param[out] nFalsePositives false positives, FP
            * @param[out] nFalseNegatives false negatives, FN
            * @date 2021-09-28
            */  
        void calculate_statistics (const std::vector<double> & expected_classes, 
                                   const std::vector<double> & elaborated_classes,
                                   double PositiveClassLabel,
                                   double NegativeClassLabel,
                                   int & nTruePositives,
                                   int & nTrueNegatives,
                                   int & nFalsePositives,
                                   int & nFalseNegatives
                                   );
        
        /** The method prints values of a confusion matrix. It prints all values and a nice matrix.
            * @param nTruePositives  true positives, TP
            * @param nTrueNegatives  true negatives, TN
            * @param nFalsePositives false positives, FP
            * @param nFalseNegatives false negatives, FN
            */
        std::string print (int nTruePositives,
                            int nTrueNegatives,
                            int nFalsePositives,
                            int nFalseNegatives);
        
        /** The method prints values of a confusion matrix. It prints all values and a nice matrix.
         * @param results
         * @param print_for_test if true, the method print a confusion matrix for test data, otherwise -- for train data.
         * @date 2024-03-12
         */
        std::string print (const ksi::result results, const bool print_for_test = true);
        
        protected:
        /** prints a double values with precision to fit the table */
        std::string ul(double d);
        /** prints an integer value with width to fit the table    */
        std::string ca(int    n);
        
        /** @return true if abs(left - right) < EPSILON
            EPSILON = 0.0001 */
        bool equal (const double left, const double right);

        /** @return quiet_NaN if division impossible, otherwise a legal quotient
         * @date 2024-04-01 */ 
        double safe_division(const double number, const double divisor);

        /** @return quiet_NaN if number is zero, otherwise the number itself
         * @date 2024-04-01 */ 
        double safe(const double number);
        
        public:
        /** @return f1-score for the test results
         * @date 2024-03-28
         * @author Krzysztof Siminski */ 
        static double TestF1score (const ksi::result & r);

        /** @return f1-score for the train results
         * @date 2024-03-28
         * @author Krzysztof Siminski */ 
        static double TrainF1score (const ksi::result & r);


   };
   
}

#endif
