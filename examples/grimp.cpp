/** @file Minimal GrIMP example without external data files. */

#include <iostream>
#include <vector>

#include "../source/common/data-modifier-imputer-granular.h"
#include "../source/partitions/fcm.h"
#include "../source/tnorms/t-norm-product.h"

int main()
{
   try
   {
      ksi::dataset data(std::vector<std::vector<double>>{
         {0.0, 10.0}, {2.0, 20.0}, {5.0, 30.0}, {1.0, 0.0}});
      data.getDatumNonConst(3)->make_attribute_incomplete(1);

      ksi::fcm partitioner(1, 10); // one granule, ten clustering iterations
      ksi::t_norm_product tnorm;
      ksi::data_modifier_imputer_granular grimp(partitioner, tnorm);
      grimp.modify(data);

      std::cout << grimp.print() << '\n'
                << "Imputed value: " << data.get(3, 1) << '\n'; // 20
   }
   catch (const std::exception& error)
   {
      std::cerr << error.what() << '\n';
      return 1;
   }
}
