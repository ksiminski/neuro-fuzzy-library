
#include <memory>
#include <cmath>

#include "../metrics/metric.h" 
#include "../metrics/metric_mahalanobis.h"
#include "../auxiliary/matrix.h"

 

ksi::metric_mahalanobis::metric_mahalanobis(const Matrix<double>& A)
{
   _A = A;
}

ksi::metric_mahalanobis::metric_mahalanobis(const std::vector<std::vector<double>>& A)
{
   _A = ksi::Matrix<double> (A);
}


ksi::metric_mahalanobis::~metric_mahalanobis ()
{
   // delete what is to delete

}

/*
ksi::metric_mahalanobis::metric_mahalanobis (const ksi::metric_mahalanobis & wzor) : ksi::metric(wzor)
{
   // copy what is to copy
   
}

ksi::metric_mahalanobis & ksi::metric_mahalanobis::operator= (const ksi::metric_mahalanobis & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::metric::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::metric_mahalanobis::metric_mahalanobis (ksi::metric_mahalanobis && wzor) : ksi::metric(wzor)
{
   // swap what is to swap

}

ksi::metric_mahalanobis & ksi::metric_mahalanobis::operator= (ksi::metric_mahalanobis && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::metric::operator=(wzor);

   // swap what is to swap

   return *this;
}
*/

std::shared_ptr<ksi::metric> ksi::metric_mahalanobis::clone () const
{
   // prototype design pattern
   return std::shared_ptr<ksi::metric> (new ksi::metric_mahalanobis(*this));
}

std::string ksi::metric_mahalanobis::getAbbreviation() const
{
   return "Mahalanobis";
}


std::string ksi::metric_mahalanobis::get_info() const
{
   return "Malahanobis distance";
}

double ksi::metric_mahalanobis::calculateDistance(const ksi::datum& l, const ksi::datum& p) const
{
   try
   {
       return calculateDistance(l.getVector(), p.getVector());
   }
   CATCH;
}


double ksi::metric_mahalanobis::calculateDistance(const std::vector<double>& l, const std::vector<double>& p) const
{
   try 
   {
      auto X = ksi::Matrix<double>::ColumnMatrix(l);
      auto V = ksi::Matrix<double>::ColumnMatrix(p);
      
      auto X_V = X - V;
      
      auto X_V_tr = X_V.transpose();
      
      return std::sqrt((X_V_tr * _A * X_V).get_value(0, 0));
   }
   CATCH;
}


ksi::Matrix<double> ksi::metric_mahalanobis::get_A_matrix() const
{
   return _A;
}
