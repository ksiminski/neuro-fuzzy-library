/** @file */ 

#ifndef MULTICLASS_CONFUSION_MATRIX_H
#define MULTICLASS_CONFUSION_MATRIX_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <sstream>

namespace ksi
{
   /** The class for operations of a multiclass confusion matrix.
    @date 2022-05-19
    @date 2022-08-21 (Matthews correlation coeffient added)
    @author Krzysztof Siminski */
   class multiclass_confusion_matrix
   {
    public:
      multiclass_confusion_matrix ();
      multiclass_confusion_matrix (const multiclass_confusion_matrix & wzor);
      multiclass_confusion_matrix (multiclass_confusion_matrix && wzor);
      multiclass_confusion_matrix & operator= (const multiclass_confusion_matrix & wzor);
      multiclass_confusion_matrix & operator= (multiclass_confusion_matrix && wzor);
      virtual ~multiclass_confusion_matrix ();
      
      /** The method prints a multiclass confusion matrix.
      @date 2022-05-19
      @author Krzysztof Siminski */
      std::string print (const std::vector<std::string> & expected, const std::vector<std::string> & elaborated);
      
      
   protected:
       /** @return a set of labels */
      std::set<std::string> read_labels(const std::vector<std::string>& labels);
       /** @return a set of unique labels */
      std::set<std::string> extract_labels(const std::vector<std::string> & expected, const std::vector<std::string> & elaborated);
      
      /** @return two-dimensional map, first index: expected label, second index: elaborated label, value: number of item than match expected and elaborated labels */
      std::map<std::string, std::map<std::string, double>> elaborate_accuracy (const std::set<std::string> & labels, const std::vector<std::string> & expected, const std::vector<std::string> & elaborated);
      
      /** @param results two-dimensional map, first index: expected label, second index: elaborated label, value: number of item than match expected and elaborated labels
       * @return a string with a matrix 
       */
      std::string print_matrix(const std::map<std::string, std::map<std::string, double>> & results);
      
      
      /** prints a double values with precision to fit the table */
      template<class T>
      std::string ur(const T & value, const std::size_t precision, const std::size_t width)
      {
         std::stringstream ss;
         ss << std::setw(width) << std::setprecision(precision) << std::fixed << value;
         return ss.str();
      }

      /** prints a double values with precision to fit the table */
      template<class T>
      std::string ul(const T & value, const std::size_t precision, const std::size_t width)
      {
         std::stringstream ss;
         ss << std::left << std::setw(width) << std::setprecision(precision) << std::fixed << value;
         return ss.str();
      }
      
      /** The method returns a string whose length is width filled with character c.
       @date 2022-05-21
       @author Krzysztof Siminski */
      std::string fill(const char c, const std::size_t width);
      
   protected:
       /** first:   total_accuracy, macro_average_precision, macro_average_recall,
        *  second:  precision and recall for each label (index: label, values: first: precision, second: recall */
       std::pair<std::vector<double>, std::map<std::string, std::pair<double, double>>> detailed_results;
       
   public:
       std::pair<std::vector<double>, std::map<std::string, std::pair<double, double>>> get_detailed_results () const;

      
   };
}


#endif
