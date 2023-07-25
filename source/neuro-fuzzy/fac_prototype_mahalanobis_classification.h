
#ifndef FAC_PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H
#define FAC_PROTOTYPE_MAHALANOBIS_CLASSIFICATION_H

#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"

namespace ksi
{
   class fac_prototype_mahalanobis_classification : public fac_prototype_mahalanobis
   {
    public:
      fac_prototype_mahalanobis_classification ();
      fac_prototype_mahalanobis_classification (const Matrix<double> & A, const double positive_class_label, const double negative_class_label);
      fac_prototype_mahalanobis_classification (const fac_prototype_mahalanobis_classification & wzor) = default;
      fac_prototype_mahalanobis_classification (fac_prototype_mahalanobis_classification && wzor) = default;
      fac_prototype_mahalanobis_classification & operator= (const fac_prototype_mahalanobis_classification & wzor) = default;
      fac_prototype_mahalanobis_classification & operator= (fac_prototype_mahalanobis_classification && wzor) = default;
      virtual ~fac_prototype_mahalanobis_classification ();
      
      
   public:
      virtual std::shared_ptr<prototype> get_prototype() const override; 
      virtual std::shared_ptr<prototype> get_prototype_for_cluster(const cluster & cl) override;
//       virtual std::shared_ptr<metric> get_metric() const override;
      virtual std::shared_ptr<fac_prototype> clone () const override;

      protected:
      double _positive_class;  ///< label of the positive class
      double _negative_class;  ///< label of the negative class
   };
}


#endif
