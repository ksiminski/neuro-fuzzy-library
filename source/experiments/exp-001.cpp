/** @file */

#include <iostream>
#include <vector>
#include <string>
 

 
#include "../readers/reader-complete.h"
#include "../readers/reader-incomplete.h"
#include "../common/data-modifier-marginaliser.h"
#include "../common/data-modifier-standardiser.h"
#include "../common/data-modifier-normaliser.h"
#include "../common/data-modifier-imputer.h"
#include "../common/data-modifier-imputer-average.h"
#include "../common/data-modifier-imputer-median.h"
#include "../common/data-modifier-imputer-knn.h"
#include "../common/data-modifier-imputer-knn-average.h"
#include "../common/data-modifier-imputer-knn-median.h"
#include "../common/data-modifier-imputer-values-from-knn.h"


#include "../experiments/exp-001.h"

#include <fstream>

void ksi::exp_001::execute()
{
   try
   {
      std::string Directory ("data/exp-001");
      
      
      // complete data
      {
         std::string CompleteDataset ("/complete");
         ksi::reader_complete DataReader;
         auto dane = DataReader.read(Directory + CompleteDataset);
         std::cout << "original data" << std::endl;
         std::cout << dane << std::endl;
         std::cout << std::endl;
         
         {
            auto data = dane;
            ksi::data_modifier_normaliser normaliser;
            normaliser.modify(data);
            std::cout << "normalised data" << std::endl;
            std::cout << data << std::endl;
            std::cout << std::endl;
         }

         {
            auto data = dane;
            ksi::data_modifier_standardiser standardiser;
            standardiser.modify(data);
            std::cout << "standarised data" << std::endl;
            std::cout << data << std::endl;
            std::cout << std::endl;
         }
      }
      
      
      // incomplete data
      {
         std::string IncompleteDataset ("/incomplete");
      
         ksi::reader_incomplete DataReader;
         auto dane = DataReader.read(Directory + IncompleteDataset);
         std::cout << "original incomplete data" << std::endl;
         std::cout << dane << std::endl;
         std::cout << std::endl;
         
         {
            auto marg = dane;
            ksi::data_modifier_marginaliser marginaliser;
            marginaliser.modify(marg);
            std::cout << "marginalization" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }

         {
            auto marg = dane;
            const double C = 3.14;
            ksi::data_modifier_imputer imputer(C);
            imputer.modify(marg);
            std::cout << "missing values imputed with constant " << C  << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         {
            auto marg = dane;
            ksi::data_modifier_imputer_average imputer;
            imputer.modify(marg);
            std::cout << "missing values imputed with averages of the attributes" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         {
            auto marg = dane;
            ksi::data_modifier_imputer_median imputer;
            imputer.modify(marg);
            std::cout << "missing values imputed with medians of the attributes" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         {
            auto marg = dane;
            int k = 3;
            ksi::data_modifier_imputer_knn_average imputer(k);
            imputer.modify(marg);
            std::cout << "missing values imputed with averages of " << k << " nearest neighbours" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         {
            auto marg = dane;
            int k = 3;
            ksi::data_modifier_imputer_knn_median imputer (k);
            imputer.modify(marg);
            std::cout << "missing values imputed with medians of " << k << " nearest neighbours" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         {
            auto marg = dane;
            int k = 3;
            ksi::data_modifier_imputer_values_from_knn imputer (k);
            imputer.modify(marg);
            std::cout << "missing values imputed with values from  " << k << " nearest neighbours" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
         }
         
         
         // chains of modifiers:
         {
            auto marg = dane;
            int k = 3;
            ksi::data_modifier_imputer_values_from_knn imputer (k);
            ksi::data_modifier_standardiser standardiser;
            imputer.addModifier(standardiser);
            imputer.modify(marg);
            std::cout << "missing values imputed with values from " << k << " nearest neighbours and then the imputed data set standardized" << std::endl;
            std::cout << marg << std::endl;
            std::cout << std::endl;
            std::cout << imputer.print() << std::endl;
            
         }
         
         {
            auto marg = dane;
            
            ksi::data_modifier_imputer dm1;
            ksi::data_modifier_normaliser dm2;
            ksi::data_modifier_standardiser dm3;
            ksi::data_modifier_imputer_average dm4;
            
            std::cout << dm1.print() << std::endl;
            std::cout << dm2.print() << std::endl;
            std::cout << dm3.print() << std::endl;
            std::cout << dm4.print() << std::endl;
            
            dm1.addModifier(dm2);
            std::cout << dm1.print() << std::endl;
            dm4.addModifier(dm3);
            std::cout << dm4.print() << std::endl;
            dm1.addModifier(dm4);
            
            dm1.modify(marg);
            
            std::cout << marg << std::endl;
            std::cout << std::endl;
            std::cout << dm1.print() << std::endl;
         }
      } 
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
