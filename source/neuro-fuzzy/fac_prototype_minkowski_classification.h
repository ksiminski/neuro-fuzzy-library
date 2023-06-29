
#ifndef FAC_PROTOTYPE_MINKOWSKI_CLASSIFICATION_H
#define FAC_PROTOTYPE_MINKOWSKI_CLASSIFICATION_H


#include <memory>

#include "../neuro-fuzzy/prototype.h"
#include "../metrics/metric.h"
#include "../neuro-fuzzy/fac_prototype_minkowski.h"
#include "../partitions/cluster.h"

namespace ksi
{
   class fac_prototype_minkowski_classification : public fac_prototype_minkowski
   {
//        double _m; ///< exponent for Minkowski metric
   protected:
       double _positive_class_label;
       double _negative_class_label;
    public:
      fac_prototype_minkowski_classification (const double m, const double possitive_class_label, const double negative_class_label);
      fac_prototype_minkowski_classification (const fac_prototype_minkowski_classification & wzor) = default;
      fac_prototype_minkowski_classification (fac_prototype_minkowski_classification && wzor) = default;
      fac_prototype_minkowski_classification & operator= (const fac_prototype_minkowski_classification & wzor) = default;
      fac_prototype_minkowski_classification & operator= (fac_prototype_minkowski_classification && wzor) = default;
      virtual ~fac_prototype_minkowski_classification ();
      
    public:
      virtual std::shared_ptr<prototype> get_prototype() const override; 
      virtual std::shared_ptr<prototype> get_prototype_for_cluster(const cluster & cl) override;
//       virtual std::shared_ptr<metric> get_metric() const override;
      virtual std::shared_ptr<fac_prototype> clone () const override;
   
       
    }; 
}


#endif
