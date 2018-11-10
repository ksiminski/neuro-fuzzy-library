/** @file */ 
 

#include <iostream>
#include <utility>
#include "consequence-MA.h"


ksi::consequence_MA::consequence_MA(double support_min, double core, double support_max)
{
   _support_max = support_max;
   _support_min = support_min;
   _core = core;
}

std::pair<double, double> 
ksi::consequence_MA::getLocalisationWeight (const std::vector< double >& X, double firing) 
{
   const double H = 1.0;
   double M = _support_max;
   double m = _support_min;
   double c = _core;
   double F = firing;
   // wyznaczam wage:
   double waga = (M - m) * F * (2 * H - F) / (2 * H);
   double y = (m + c + M) / 3.0 - ((H - F) * (H - F) * (2 * c - m - M)) / (3 * H * (2 * H - F));
   /*
   // trzeba wyznaczyc polozenie 
   double podstawalewy  = (firing) * (_core - _support_min);
   double podstawaprawy = (firing) * (_support_max - _core);
   
   // srodki ciezkosci:
   // lewy trojkat
   double lewyPolozenie = _support_min + 2.0 * (podstawalewy) / 3.0;
   double lewyWaga      = firing * podstawalewy / 2.0;
   
   // prostokat:
   double prostokatSzerokosc = _support_max - podstawaprawy - (_support_min + podstawalewy);
   double prostokatPolozenie = (_support_max - podstawaprawy + _support_min + podstawalewy) / 2.0;
   double prostokatWaga      = firing * prostokatSzerokosc;
   
   // prawy trojkat
   double prawyPolozenie = _support_max - 2.0 * (podstawaprawy) / 3.0;
   double prawyWaga      = firing * podstawaprawy / 2.0;
   */
   std::pair<double, double> wynik;
   /*wynik.second = lewyWaga + prostokatWaga + prawyWaga;
   if (wynik.second == 0)
      wynik.first = 0;
   else
      wynik.first = (lewyWaga * lewyPolozenie + prostokatWaga * prostokatPolozenie + prawyWaga * prawyPolozenie) / wynik.second;
   */
   
   wynik.second = waga;
   if (wynik.second == 0)
      wynik.first = 0.0;
   else 
      wynik.first = y;
   return last_localisationWeight = wynik;
   
} 

ksi::consequence_MA::~consequence_MA()
{

}

double ksi::consequence_MA::getW() const
{
   return _support_max - _support_min;
}



ksi::consequence * ksi::consequence_MA::clone() const
{
   return new consequence_MA (_support_min, _core, _support_max);
}

std::ostream& ksi::consequence_MA::Print(std::ostream& ss)
{
   ss << "(" << _support_min << ", " << _core << ", " 
      << _support_max << ")";
     
   return ss;
}

void ksi::consequence_MA::cummulate_differentials(std::vector<double> X, 
                                                  double partial_differential, 
                                                  double secundary_partial_differential,
                                                  double firing)
{
   auto dw_dc = 0.0;
   double rozniczka = firing * (firing - 2.0) / (2.0);
   auto dw_dm = rozniczka;
   auto dw_dM = - rozniczka;
   
   auto dy_dm = (3.0 - 3.0 * firing + firing * firing) / (3.0 * (2.0 - firing));
   auto dy_dM = dy_dm;
   auto dy_dc = firing * (3.0 - 2.0 * firing) / (3.0 * (2.0 - firing));
   
   // no i teraz moge wreszcie wyznaczyc rozniczki:
   
   double dc = partial_differential * dw_dc + secundary_partial_differential * dy_dc;
   double dM = partial_differential * dw_dM + secundary_partial_differential * dy_dM;
   double dm = partial_differential * dw_dm + secundary_partial_differential * dy_dm;
   
   _sum_core += dc;
   _sum_support_max += dM;
   _sum_support_min += dm;
   
   
}

ksi::consequence_MA::consequence_MA(ksi::consequence_MA && wzor) : ksi::consequence (wzor)
{
   _support_min = wzor._support_min;
   _core = wzor._core;
   _support_max = wzor._support_max;
   _sum_support_min = wzor._sum_support_min;
   _sum_core = wzor._sum_core;
   _sum_support_max = wzor._sum_support_max;
}

ksi::consequence_MA::consequence_MA(const ksi::consequence_MA & wzor) : ksi::consequence (wzor)
{
   _support_min = wzor._support_min;
   _core = wzor._core;
   _support_max = wzor._support_max;
   _sum_support_min = wzor._sum_support_min;
   _sum_core = wzor._sum_core;
   _sum_support_max = wzor._sum_support_max;
}
