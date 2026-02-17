
#ifndef DATA_MODIFIER_OUTLIER_REMOVE_GRANULAR_H
#define DATA_MODIFIER_OUTLIER_REMOVE_GRANULAR_H

#include <memory>
#include "../common/data-modifier.h"
#include "../partitions/partitioner.h"
#include "../tnorms/t-norm.h"
#include "../snorms/s-norm.h"

namespace ksi
{
   class data_modifier_outlier_remove_granular : public data_modifier
   {
    public:
      data_modifier_outlier_remove_granular (const ksi::partitioner & Partitioner, const ksi::t_norm & Tnorm, const ksi::s_norm & Snorm, const double threshold);
      data_modifier_outlier_remove_granular (const data_modifier_outlier_remove_granular & other);
      data_modifier_outlier_remove_granular (data_modifier_outlier_remove_granular && other);
      data_modifier_outlier_remove_granular & operator= (const data_modifier_outlier_remove_granular & other);
      data_modifier_outlier_remove_granular & operator= (data_modifier_outlier_remove_granular && other);
      virtual ~data_modifier_outlier_remove_granular ();

      // data_modifier_outlier_remove_granular () = default;
      // data_modifier_outlier_remove_granular (const data_modifier_outlier_remove_granular & other) = default;
      // data_modifier_outlier_remove_granular (data_modifier_outlier_remove_granular && other) = default;
      // data_modifier_outlier_remove_granular & operator= (const data_modifier_outlier_remove_granular & other) = default;
      // data_modifier_outlier_remove_granular & operator= (data_modifier_outlier_remove_granular && other) = default;
      // virtual ~data_modifier_outlier_remove_granular () = default;

      // virtual std::shared_ptr<data_modifier> clone () const;  // prototype design pattern
      virtual data_modifier * clone () const override;  // prototype design pattern
      
      
      void modify(dataset & ds) override;
      
   protected:
      std::shared_ptr<partitioner> _pPartitioner = nullptr;
      std::shared_ptr<t_norm> _pTnorm = nullptr;
      std::shared_ptr<s_norm> _pSnorm = nullptr;
      
      double _threshold {0.0};
   };
}


#endif
