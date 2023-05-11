
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>

#include "../auxiliary/multiclass_confusion_matrix.h"
#include "../service/debug.h"

std::string ksi::multiclass_confusion_matrix::print(const std::vector<std::string>& expected, const std::vector<std::string>& elaborated)
{
   try 
   {
      if (expected.size() != elaborated.size())
      {
         std::stringstream ss;
         ss << "The sizes of vectors do not match (" << expected.size() << " != " << elaborated.size() << ").";
         throw ss.str();
      }
      
      auto labels = extract_labels(expected, elaborated);
      auto accuracies = elaborate_accuracy(labels, expected, elaborated);

      return print_matrix(accuracies);
   }
   CATCH;
   
   return "";
}

std::string ksi::multiclass_confusion_matrix::print_matrix(const std::map<std::string, std::map<std::string, double>> & resutls)
{
   std::stringstream ss;
   const std::size_t PRECISION_INTEGER { 0 };
   const std::size_t PRECISION_DOUBLE { 3 };
   const std::size_t WIDTH     { 6 };
   const std::size_t const_width { 2 };
   
   const std::string S_PRECISION  { "precision"  };
   const std::string S_RECALL     { "recall"     };
   const std::string S_ELABORATED { "elaborated" };
   const std::string S_EXPECTED   { "expected"   };
   const std::string S_ACCURACY   { "accuracy"   };
   
   
   std::size_t max_label_len = 0;
   std::vector<std::string> labels;
   for (const auto & a : resutls)
   {
      max_label_len = std::max(max_label_len, a.first.size());
      labels.push_back(a.first);
   }
   
   auto nLabels = labels.size();
   
   max_label_len = std::max(max_label_len, S_PRECISION.size());
   max_label_len = std::max(max_label_len, S_RECALL.size());
   max_label_len = std::max(max_label_len, S_EXPECTED.size());
   
   ss << "confusion matrix" << std::endl;
   ss << std::endl;
   
   const std::size_t width = std::max(max_label_len, WIDTH) + const_width;
   
   ss << ur("", PRECISION_INTEGER, width);
   ss << ul(S_ELABORATED, PRECISION_INTEGER, width) << std::endl;
   ss << ul(S_EXPECTED, PRECISION_INTEGER, width);
   for (const auto & s : labels)
      ss << ur(s, PRECISION_INTEGER, width);
//    ss << std::endl;
   ss << ur("", PRECISION_INTEGER, width);
   ss << ur(S_RECALL, PRECISION_INTEGER, width);
   ss << std::endl;
   
   std::map<std::string, double> rows, cols, diagonals, recalls, precisions, accuracies;
   
   double all_values = 0;
   
   for (const auto & s : labels)
   {
       
      ss << ur(s, PRECISION_INTEGER, width);
      for (const auto & t : labels)
      {
          auto res = resutls.at(s).at(t);
          all_values += res;
          if (s == t)
          {
              diagonals[s] = res;
              accuracies[s] += res;
          }
          rows[s] += res;
          cols[t] += res;
          ss << ur(res, PRECISION_INTEGER, width);
      }
      ss << ur("|", PRECISION_INTEGER, width);
      auto recall = diagonals[s] / rows[s];
      recalls[s] = recall;
      ss << ur(recall, PRECISION_DOUBLE, width);
      
      ss << std::endl;
   }
   
   // Matthews correlation coefficient (phi coefficient)
   double original_original {0}, predicted_predicted {0}, original_predicted {0}; 
   double diag_sum {0};
   for (const auto & s : labels)
   {
       original_original   += cols[s] * cols[s];
       predicted_predicted += rows[s] * rows[s];
       original_predicted  += rows[s] * cols[s];
       diag_sum            += diagonals[s];
   }
   
   double all_all = all_values * all_values;
   double mcc = (diag_sum * all_values - original_predicted) / (sqrt(all_all - original_original) * sqrt(all_all - predicted_predicted));
   
   
   /////////////////////////////
   
   
   ss << ur("", PRECISION_INTEGER, width);
   auto size = cols.size();
   ss << fill('-', width * size) << std::endl;
   
   ss << ul(S_PRECISION, PRECISION_INTEGER, width);
   for (const auto & col : cols)
   {
       auto precision = diagonals[col.first] / col.second;
       precisions[col.first] = precision;
       ss << ur(precision, PRECISION_DOUBLE, width);
       
   }
   
   
   ss << std::endl;
   ss << std::endl;
   ss << "Matthews correlation coefficient (MCC), phi coefficient = " << mcc << std::endl;
  
   
   for (const auto & s : labels)
   {
       accuracies[s] /= all_values;
   }
   
   ss << std::endl;
   ss << std::endl;
   ss << "measures for classes" << std::endl;
   
   for (const auto & s : labels)
   {
       ss << "CLASS: " << s << std::endl;
       ss << ul(S_PRECISION, PRECISION_INTEGER, width) << "\t" << ul(precisions[s], PRECISION_DOUBLE, width) << std::endl;
       ss << ul(S_RECALL, PRECISION_INTEGER, width)    << "\t" << ul(recalls[s], PRECISION_DOUBLE, width) << std::endl;
       ss << std::endl;
   }
   
   std::map<std::string, std::pair<double, double>> precisions_recalls;
   double sum_precision = 0;
   double sum_recall    = 0;
   double sum_diagonals = 0;
   int nPrecision = 0;
   int nRecall    = 0;
   for (const auto & s : labels)
   {
       double prec = precisions[s];
       if ((not std::isnan(prec)) and (not std::isinf(prec)))
       {
            sum_precision += prec;
            nPrecision++;    
       }

       double rec = recalls[s];
       if ((not std::isnan(rec)) and (not std::isinf(rec)))
       {
            sum_recall += rec;
            nRecall++;    
       }

       sum_diagonals += diagonals[s];
       precisions_recalls[s] = {precisions[s], recalls[s]};
   }
   
   double total_accuracy = sum_diagonals / all_values;
   double macro_average_precision = sum_precision / nPrecision;
   double macro_average_recall    = sum_recall / nRecall;
   
   detailed_results = { {total_accuracy, macro_average_precision, macro_average_recall}, precisions_recalls };
   
   
   ss << std::endl;
   ss << "total         " << ul(S_ACCURACY, PRECISION_INTEGER, width)   << "\t" << ul(total_accuracy, PRECISION_DOUBLE, width) << std::endl;
   ss << "macro average " << ul(S_PRECISION, PRECISION_INTEGER, width)  << "\t" << ul(macro_average_precision, PRECISION_DOUBLE, width) << std::endl;
   ss << "macro average " << ul(S_RECALL, PRECISION_INTEGER, width)     << "\t" << ul(macro_average_recall, PRECISION_DOUBLE, width) << std::endl;
   
   ss << std::endl;
   ss << "accuracy            = ([p -> p] + [n -> n]) / [->] = (true positive + true negative) / total population" << std::endl;
   ss << "sensitivity, recall = [p -> p] / [p ->]            = true positive / condition positive" << std::endl; 
   ss << "precision           = [p -> p] / [-> p]            = true positive / test outcome positive" << std::endl;
   
    
   return ss.str();
}

std::pair<std::vector<double>, std::map<std::string, std::pair<double, double> > > ksi::multiclass_confusion_matrix::get_detailed_results() const
{
    return detailed_results;
}


std::string ksi::multiclass_confusion_matrix::fill(const char c, const std::size_t width)
{
    std::stringstream ss;
    ss << std::setw(width) << std::setfill(c) << "";
    
    return ss.str();
}



std::map<std::string, std::map<std::string, double>> ksi::multiclass_confusion_matrix::elaborate_accuracy(const std::set<std::string>& labels, const std::vector<std::string>& expected, const std::vector<std::string>& elaborated)
{
   std::map<std::string, std::map<std::string, double>> accuracies;
   
   // inicjalizacja
   for (const auto & l1 : labels)
   {
      for (const auto & l2 : labels)
      {
         accuracies[l1][l2] = 0.0;
      }
   }
   
   // odczyt danych:
   auto size = expected.size();
   
   for (std::size_t i = 0; i < size; i++)
   {
      accuracies[expected[i]][elaborated[i]] += 1.0;
   }
   
   return accuracies;
}

 
std::set<std::string> ksi::multiclass_confusion_matrix::extract_labels(const std::vector<std::string>& expected, const std::vector<std::string>& elaborated)
{
   std::set<std::string> labels_expected   = read_labels(expected);
   std::set<std::string> labels_elaborated = read_labels(elaborated);
      
   std::set<std::string> labels = labels_expected;
   labels.merge(labels_elaborated);
   
   return labels;   
}
 
 
std::set<std::string> ksi::multiclass_confusion_matrix::read_labels(const std::vector<std::string>& input)
{
   std::set<std::string> labels;
   for (const auto & l : input)
      labels.insert(l);
   
   return labels;
}

 
 
ksi::multiclass_confusion_matrix::multiclass_confusion_matrix ()
{
}

ksi::multiclass_confusion_matrix::~multiclass_confusion_matrix ()
{
   // delete what is to delete

}

ksi::multiclass_confusion_matrix::multiclass_confusion_matrix (const ksi::multiclass_confusion_matrix & wzor)
{
   // copy what is to copy

}

ksi::multiclass_confusion_matrix & ksi::multiclass_confusion_matrix::operator= (const ksi::multiclass_confusion_matrix & wzor)
{
   if (this == & wzor)
      return *this;


   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::multiclass_confusion_matrix::multiclass_confusion_matrix (ksi::multiclass_confusion_matrix && wzor)
{
   // swap what is to swap

}

ksi::multiclass_confusion_matrix & ksi::multiclass_confusion_matrix::operator= (ksi::multiclass_confusion_matrix && wzor)
{
   if (this == & wzor)
      return *this;


   // swap what is to swap

   return *this;
}



