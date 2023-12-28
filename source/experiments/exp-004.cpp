/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
 

#include "../neuro-fuzzy/premise.h"
#include "../descriptors/descriptor-constant.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../descriptors/descriptor-triangular.h"
#include "../descriptors/descriptor-semitriangular.h"
#include "../descriptors/descriptor_tanh.h"
#include "../descriptors/descriptor-singleton.h"
#include "../neuro-fuzzy/consequence-MA.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../tnorms/t-norm-lukasiewicz.h"
#include "../tnorms/t-norm-product.h"
#include "../tnorms/t-norm-min.h"
#include "../tnorms/t-norm-fodor.h"
#include "../auxiliary/definitions.h"

#include "../experiments/exp-004.h"

#include "../readers/reader-complete.h"
#include "../descriptors/DescriptorStatistics.h"
#include "../common/DatasetStatistics.h"

#include "../auxiliary/utility-math.h"

#include <fstream>

void ksi::exp_004::execute()
{
   try
   {
      // You can compose you own fuzzy system. Here is an example.
      
      {
      	/*ksi::descriptor_triangular     D11 (-0.5, 1, 7);*/
         ksi::descriptor_constant    D11(0.5);
         ksi::descriptor_triangular     D12 (2, 4, 5);

         /*ksi::descriptor_gaussian     D11(1, 0.5);
         ksi::descriptor_gaussian     D12(5.1, 0.5);*/

         ksi::descriptor_tanh D21 (7, 3);
         ksi::descriptor_singleton D22 (4); 
         
         // Each rule can have its own t-norm.
         ksi::t_norm_lukasiewicz Lukasiewicz;
         ksi::t_norm_min Min;  
         ksi::t_norm_product Product;
         ksi::t_norm_product Fodor;
         
         
         // 1st rule:
         ksi::premise P1;
         P1.addDescriptor(D11);
         P1.addDescriptor(D21);
         
         ksi::consequence_MA C1 (2, 6, 15);
         
         // Let's use product T-norm as an AND operator for descriptors.
         
         ksi::rule R1 (Product);
         R1.setPremise(P1);
         R1.setConsequence(C1);         
         
         // 2nd rule:
         ksi::premise P2;
         P2.addDescriptor(D11);
         P2.addDescriptor(D22);
         
         ksi::consequence_MA C2 (-4, -3, 0);
         
         ksi::rule R2 (Product);
         R2.setPremise(P2);
         R2.setConsequence(C2);
         
         // 3rd rule:
         ksi::premise P3;
         P3.addDescriptor(D12);
         P3.addDescriptor(D21);
         
         ksi::consequence_MA C3 (-5, -4.5, -4);
         
         ksi::rule R3 (Product);
         R3.setPremise(P3);
         R3.setConsequence(C3);
         
         // 4th rule:
         ksi::premise P4;
         P4.addDescriptor(D12);
         P4.addDescriptor(D22);
         
         ksi::consequence_MA C4 (8, 9, 10);
         
         ksi::rule R4 (Product);
         R4.setPremise(P4);
         R4.setConsequence(C4);
         
         
         
         // and finally let's add rules to a rulebase:         
         ksi::rulebase Rulebase;         
         
         Rulebase.addRule(R1);
         Rulebase.addRule(R2);
         Rulebase.addRule(R3);
         Rulebase.addRule(R4);
         
         // Let's elaborate answers:
         
         for (double x1 = 0; x1 < 6.1; x1 += 1)
         { 
            for (double x2 = 0; x2 < 4.1; x2 += 1)
            {
               std::vector<double> x {x1, x2};
               auto y = Rulebase.answer(x);
               std::cout << " x == " << x <<  ", y == " << y << std::endl;
            }
            std::cout << std::endl;
         }
         
         // and finally let's print the rulebase
         std::cout << std::endl;
         std::cout << "rulebase" << std::endl;
         std::cout << "========" << std::endl;
         Rulebase.print(std::cout);

         std::string dataDir("../data/exp-lab");

         std::string CompleteDataset("/train.txt");
         ksi::reader_complete DataReader;
         auto dane = DataReader.read(dataDir + CompleteDataset);

         auto datasetSTat = dane.calculateDatasetStatistics();
        
         Rulebase.printLinguisticDescription(std::cout, datasetSTat);
        
      }
    
   }
   catch (...)
   {
      throw;
   }
   
   return;
}
