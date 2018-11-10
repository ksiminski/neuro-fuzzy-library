/** @file */

#ifndef CONFUSION_MATRIX_H
#define CONFUSION_MATRIX_H

#include <vector>
#include <string>

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
   void calculate_statistics (std::vector<double> & expected, 
                              std::vector<double> & elaborated,
                              double PositiveClassLabel,
                              double NegativeClassLabel,
                              int & nTruePositives,
                              int & nTrueNegatives,
                              int & nFalsePositives,
                              int & nFalseNegatives,
                              double dbThreshold);
   
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
   
   private:
   /** prints a double values with precision to fit the table */
   std::string ul(double d);
   /** prints an integer value with width to fit the table    */
   std::string ca(int    n);
   };
   
}

#endif
