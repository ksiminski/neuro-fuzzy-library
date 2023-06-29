
#include "../neuro-fuzzy/fac_prototype.h"
#include "../neuro-fuzzy/fac_prototype_minkowski.h"
#include "../neuro-fuzzy/fac_prototype_minkowski_classification.h"

#include "../neuro-fuzzy/prototype.h"
#include "../neuro-fuzzy/prototype_minkowski.h"
#include "../neuro-fuzzy/prototype_minkowski_classification.h"


#include "../metrics/metric-minkowski.h"

ksi::fac_prototype_minkowski_classification::fac_prototype_minkowski_classification (const double m, const double positive_class_label, const double negative_class_label) : ksi::fac_prototype_minkowski (m), _positive_class_label(positive_class_label), _negative_class_label(negative_class_label)
{
}

ksi::fac_prototype_minkowski_classification::~fac_prototype_minkowski_classification ()
{
   // delete what is to delete

}

// ksi::fac_prototype_minkowski_classification::fac_prototype_minkowski_classification (const ksi::fac_prototype_minkowski_classification & wzor) : ksi::fac_prototype_minkowski(wzor)
// {
//    // copy what is to copy
// }
// 
// ksi::fac_prototype_minkowski_classification & ksi::fac_prototype_minkowski_classification::operator= (const ksi::fac_prototype_minkowski_classification & wzor)
// {
//    if (this == & wzor)
//       return *this;
// 
//    ksi::fac_prototype_minkowski::operator=(wzor);
// 
//    // remove what is to remove
// 
//    // allocate what is to allocate
//     
// 
//    return *this;
// }
// 
// ksi::fac_prototype_minkowski_classification::fac_prototype_minkowski_classification (ksi::fac_prototype_minkowski_classification && wzor) : ksi::fac_prototype_minkowski(wzor)
// {
//    // swap what is to swap 
// }
// 
// ksi::fac_prototype_minkowski_classification & ksi::fac_prototype_minkowski_classification::operator= (ksi::fac_prototype_minkowski_classification && wzor)
// {
//    if (this == & wzor)
//       return *this;
// 
//    ksi::fac_prototype_minkowski::operator=(wzor);
// 
//    // swap what is to swap 
// 
//    return *this;
// }


std::shared_ptr<ksi::prototype> ksi::fac_prototype_minkowski_classification::get_prototype() const
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_minkowski_classification (_m, _positive_class_label, _negative_class_label));
}

std::shared_ptr<ksi::prototype> ksi::fac_prototype_minkowski_classification::get_prototype_for_cluster(const ksi::cluster & cl) 
{
    return std::shared_ptr<ksi::prototype> (new ksi::prototype_minkowski_classification (cl, _m, _positive_class_label, _negative_class_label));
}

std::shared_ptr<ksi::fac_prototype> ksi::fac_prototype_minkowski_classification::clone() const
{
    return std::shared_ptr<ksi::fac_prototype> (new ksi::fac_prototype_minkowski_classification(*this));
}

// std::shared_ptr<ksi::metric> ksi::fac_prototype_minkowski_classification::get_metric() const
// {
//     return std::shared_ptr<ksi::metric_minkowski> (new ksi::metric_minkowski(_m));
// }
