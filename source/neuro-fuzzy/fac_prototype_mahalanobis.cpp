
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_mahalanobis.h"

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_mahalanobis.h"

#include "../metrics/metric_mahalanobis.h"

#include "../auxiliary/matrix.h"

ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis () 
{
}

ksi::fac_prototype_mahalanobis::fac_prototype_mahalanobis (const ksi::Matrix<double> & A) : _A (A)
{
}

ksi::fac_prototype_mahalanobis::~fac_prototype_mahalanobis ()
{
   // delete what is to delete

}

std::shared_ptr<ksi::metric> ksi::fac_prototype_mahalanobis::get_metric() const
{
    return std::shared_ptr<ksi::metric_mahalanobis> (new ksi::metric_mahalanobis(_A));
}
