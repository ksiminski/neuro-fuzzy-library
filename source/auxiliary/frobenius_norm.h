
#ifndef FROBENIUS_NORM_H
#define FROBENIUS_NORM_H

#include <memory>
#include <vector>

#include "../common/dataset.h"
#include "../auxiliary/matrix.h"

namespace ksi
{
   class frobenius_norm
   {
    public:
      // frobenius_norm ();
      // frobenius_norm (const frobenius_norm & other);
      // frobenius_norm (frobenius_norm && other);
      // frobenius_norm & operator= (const frobenius_norm & other);
      // frobenius_norm & operator= (frobenius_norm && other);
      // virtual ~frobenius_norm ();

      frobenius_norm () = default;
      frobenius_norm (const frobenius_norm & other) = default;
      frobenius_norm (frobenius_norm && other) = default;
      frobenius_norm & operator= (const frobenius_norm & other) = default;
      frobenius_norm & operator= (frobenius_norm && other) = default;
      virtual ~frobenius_norm () = default;


      double get_frobenius_norm (const std::vector<std::vector<double>> & left, const std::vector<std::vector<double>> & right) const;
      double get_frobenius_norm (const ksi::dataset & left, const ksi::dataset & right) const;
      double get_frobenius_norm (const ksi::Matrix<double> & left, const ksi::Matrix<double> & right) const;

   };
}


#endif
