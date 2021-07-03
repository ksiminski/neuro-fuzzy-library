/** @file */

/*
#include "./readers/reader-complete.h"
#include "./readers/reader-incomplete.h"
#include "./common/data-modifier-normaliser.h"
#include "./common/data-modifier-standardiser.h"
#include "./common/data-modifier-marginaliser.h"
#include "./common/data-modifier-imputer.h"
#include "./common/data-modifier-imputer-average.h"
#include "./common/data-modifier-imputer-median.h"
#include "./common/data-modifier-imputer-knn-average.h"
#include "./common/data-modifier-imputer-knn-median.h"
#include "./common/data-modifier-imputer-values-from-knn.h"
#include "./common/dataset.h"
#include "./common/error-RMSE.h"
#include "./partitions/partitioner.h"
#include "./partitions/rfcm.h"
#include "./partitions/fcm.h"
#include "./partitions/fcm-conditional.h"
#include "./partitions/fcm-possibilistic.h"
#include "./partitions/sfcm.h"
#include "./descriptors/descriptor-triangular.h"
#include "./descriptors/descriptor-semitriangular.h"
#include "./descriptors/descriptor-trapezoidal.h"
#include "./descriptors/descriptor-gaussian.h"
#include "./descriptors/descriptor-gaussian-subspace.h"
#include "./descriptors/descriptor-sigmoidal.h"
#include "./descriptors/descriptor-singleton.h"
#include "./neuro-fuzzy/premise.h"
#include "./tnorms/t-norm-product.h"
#include "./tnorms/t-norm-min.h"
#include "./tnorms/t-norm-lukasiewicz.h"
#include "./tnorms/t-norm-drastic.h"
#include "./tnorms/t-norm-fodor.h"
#include "./tnorms/t-norm-einstein.h"
#include "./implications/imp-lukasiewicz.h"
#include "./implications/imp-fodor.h"
#include "./implications/imp-goedel.h"
#include "./implications/imp-goguen.h"
#include "./implications/imp-kleene-dienes.h"
#include "./implications/imp-reichenbach.h"
#include "./implications/imp-rescher.h"
#include "./implications/imp-zadeh.h"
#include "./neuro-fuzzy/rulebase.h"
#include "./neuro-fuzzy/rule.h"
#include "./neuro-fuzzy/logicalrule.h"
#include "./neuro-fuzzy/consequence-MA.h"
#include "./neuro-fuzzy/consequence-CL.h"
#include "./neuro-fuzzy/annbfis.h"
#include "./neuro-fuzzy/subspace-annbfis.h"
#include "./neuro-fuzzy/random-neuro-fuzzy-forest.h"
#include "./neuro-fuzzy/tsk.h"
#include "./neuro-fuzzy/ma.h"
#include "./auxiliary/matrix.h"
#include "./auxiliary/least-error-squares-regression.h"
#include "./auxiliary/confusion-matrix.h"
#include "./auxiliary/roc.h"
#include "./service/debug.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
*/

#include <string>


#include <iostream>
#include <vector>

#include "./experiments/exp-001.h"
#include "./experiments/exp-002.h"
#include "./experiments/exp-003.h"
#include "./experiments/exp-004.h"
#include "./experiments/exp-005.h"
#include "./experiments/exp-006.h"
#include "./experiments/exp-007.h"
#include "./experiments/exp-008.h"

 
#include "./service/debug.h"

 
  

int main ()
{
   try
   {
      
//      ksi::exp_001 experiment; 
     ksi::exp_002 experiment;   
//      ksi::exp_003 experiment;   
//      ksi::exp_004 experiment; 
//      ksi::exp_005 experiment; 
//      ksi::exp_006 experiment; 
//      ksi::exp_007 experiment;
//      ksi::exp_008 experiment;
      
      experiment.execute();
       
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
      
   return 0;
} 


