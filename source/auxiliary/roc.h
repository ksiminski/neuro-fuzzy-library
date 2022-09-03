/** @file */

#ifndef ROC_H
#define ROC_H

#include <vector>
#include <utility> // pair
#include <string>


namespace ksi
{
   /** method of calculation of classification threshold */
   enum class roc_threshold 
   {
      mean,             ///< mean value of positive and negative class labels
      youden,           ///< Youden criterion
      minimal_distance, ///< minimal distance of ROC to point (0, 1) 
      none              ///< none
   };
   
   /** @return the name of the threshold */
   std::string to_string (const roc_threshold & th);
   
   struct results
   {
      std::vector<std::pair<double, double> > ROC_points;
      /** area under curve */
      double AUC; 
      /** Youden index */
      double Youden_index;
      /** Youden threshold */
      double Youden_threshold;
      /** threshold denoted by the closest point of ROC to the point (0, 1) */
      double Minimal_distance_threshold;  
      std::pair<double, double> Youden_cutoff_point;
      std::pair<double, double> Minimal_distance_cutoff_point;
       
   };
   class roc
   {
      double trapezoidArea(double x1, double x2, double y1, double y2);
   public :
      /** The method elaborates ROC points and indices.
       @param Expected vector of expected values
       @param Elaborated vector of elaborated values
       @param positiveClassvalue label of positive class
       @param negativeClassvalue label of negative class 
       */
      results calculate_ROC_points (std::vector<double> & Expected, 
                                    std::vector<double> & Elaborated, 
                                    double positiveClassvalue,
                                    double negativeClassvalue);
   };
}

#endif

