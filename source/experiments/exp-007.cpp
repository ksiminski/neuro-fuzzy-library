/** @file */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric> // std::iota
#include <random> 
#include <chrono>
 
#include "../service/debug.h"
#include "../auxiliary/utility-string.h"
#include "../heuristics/ridders-test.h"
#include "../heuristics/ridders-gaussian-m.h"
#include "../heuristics/ridders-gaussian-s.h"
#include "../heuristics/simulated-annealing-gaussian.h"

#include "../experiments/exp-007.h"

#include <fstream>
#include <map>

void ksi::exp_007::execute()
{
   try
   {  
//       ksi::ridders_test t;
//       double result = t.run(0, 1.5, 0.000001);
//       std::cout << result << std::endl;
      
      
      
      const int N = 10000;
      const double X_MIN = -50;
      const double X_MAX =  50;
      const double M = 10;
      const double S = 2;
      const double DELTA_M = 30;
      const double M_MIN = M - DELTA_M;
      const double M_MAX = M + DELTA_M;
      const double M_STEP = 2 * DELTA_M / 1000;
      const double S_MIN =  0;
      const double S_MAX =  10;
      const double EPSILON = 0.00001;
      
      const int MAX_ITER = 10000;
      const int MAX_ITER_CONST_TEMP = 100;
      
      const int WIDTH = 20;
      const double TEMP = 10;
      const double TEMP_DECREASE = 0.99;
      
      // wygenerowanie punktów:
      std::default_random_engine silnik;
      silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
      std::uniform_real_distribution<double> rozklad (X_MIN, X_MAX);
      
      
      std::vector<std::pair<double, double>> punkty;
      for (int i = 0; i < N; i++)
      {
         double x = rozklad(silnik);
         punkty.push_back ({ x, gauss(x, M, S) });
      }
      
      simulated_annealing_gaussian sag (TEMP, TEMP_DECREASE, 
                                        MAX_ITER, MAX_ITER_CONST_TEMP,
                                        punkty);
      
      auto results = sag.run();
      
      auto xs = results.first;
      auto fxs = results.second;
      auto m = xs[0];
      auto s = xs[1];
      
      debug(m);
      debug(s);
      debug(fxs);
      
      
      // a teraz zrobmy inaczej, tak bardziej standardowo:
      
      // wyznaczam srednia wazona
      double sumaWartosci = 0.0;
      double sumaWag = 0.0;
      for (const auto & p : punkty)
      {
         sumaWartosci += (p.first * p.second);
         sumaWag += p.second;
      }
      
      double srednia = sumaWartosci / sumaWag;
      
      debug(srednia);
      
      // no i odchylenie
      double sumaOdchylen = 0.0;
      for (const auto & p : punkty)
      {
         auto odchylka = p.first - srednia;
         sumaOdchylen += (p.second * odchylka * odchylka);
      }
      
      double odchylka = sqrt(sumaOdchylen / sumaWag);
      
      debug(odchylka);
      
      
//       double m_stary;
//       double s_stary;
//       double elaborated_m = M * 100; 
//       double elaborated_s = S / 5;

//       {
//          ksi::ridders_gaussian_s rs (punkty, elaborated_m);
//          for (double s = S_MIN; s < S_MAX; s += 0.1)
//             std::cout << "s " << s << " : " << rs.f(s) << std::endl;
//       }
      
      
//          {
//             std::sort(punkty.begin(), punkty.end(), [](std::pair<double, double> & l, std::pair<double, double> & p) { return l.first < p.first; });
//             for (auto & p : punkty)
//                std::cerr << std::setw(WIDTH) << std::fixed << p.first << std::setw(WIDTH) << std::fixed << p.second << std::setw(WIDTH) << p.second << std::endl;   
//          }
      
//       {
//          ksi::ridders_gaussian_m rs (punkty, elaborated_s);
//          
//          std::cerr << "# m   f(m)   sgn(f(m))" << std::endl << std::endl;
//          for (double m = M_MIN; m < M_MAX; m += M_STEP)
//          {
//             int znak = 0;
//             double fm = rs.f(m);
//             znak = fm > 0 ? 1 : -1;
//             std::cerr << std::setw(WIDTH) << std::fixed << m << std::setw(WIDTH) << std::fixed << fm << std::setw(WIDTH) << znak << std::endl;
//          }
//       }
      
//          {
//             for (double m = M_MIN; m < M_MAX; m += M_STEP)
//             {
//                auto err = blad (punkty, m, S);
//                std::cerr << std::setw(WIDTH) << std::fixed << m << std::setw(WIDTH) << std::fixed << err << std::setw(WIDTH) << err << std::endl;  
//             }
            
            
//        }
      
//       {
//          std::cerr << "# d   F(d)" << std::endl << std::endl;
//          const double D_MIN = -10;
//          const double D_MAX =  10;
//          const int N = 1000;
//          const double STEP = (D_MAX - D_MIN) / N;
//          for (double d = D_MIN; d < D_MAX; d += STEP)
//          {
//             std::cerr << std::setw(WIDTH) << std::fixed << d << std::setw(WIDTH) << std::fixed << F(d) << std::setw(WIDTH) << std::fixed << Fprim(d) << std::endl;
//          }
//       }
      
//       double blad_stary = std::numeric_limits<double>::max();
//       double blad_nowy  = blad_stary;
//       double blad_najnizszy = blad_stary;
//       double najlepsze_m;
//       double najlepsze_s;
//       
//       int iter = 0;
//       do 
//       {
//          m_stary = elaborated_m;
//          s_stary = elaborated_s;
// 
//          elaborated_m = wyzarz_m(punkty, M_MIN, M_MAX, elaborated_s, EPSILON, TEMP);
//          elaborated_s = wyzarz_s(punkty, S_MIN, S_MAX, elaborated_m, EPSILON, TEMP);
//          
//          blad_stary = blad_nowy;
//          blad_nowy = blad (punkty, elaborated_m, elaborated_s);
//          debug(elaborated_m);
//          debug(elaborated_s);
//          debug(blad_nowy);
//          
//          if (blad_nowy < blad_najnizszy)
//          {
//             blad_najnizszy = blad_nowy;
//             najlepsze_m = elaborated_m;
//             najlepsze_s = elaborated_s;
//          }
//          
// //          ksi::ridders_gaussian_m rm (punkty, elaborated_s);
// //          elaborated_m = rm.run(M_MIN, M_MAX, EPSILON);
// //          
// //          ksi::ridders_gaussian_s rs (punkty, elaborated_m);
// //          elaborated_s = rs.run(S_MIN, S_MAX, EPSILON);
//          
//          
//       } while (iter++ < MAX_ITER);
//       //while (fabs (blad_stary - blad_nowy) > EPSILON);
//       
//       //while (fabs (m_stary - elaborated_m) > EPSILON or 
//         //       fabs (s_stary - elaborated_s) > EPSILON);
//      
//       debug(najlepsze_m);
//       debug(najlepsze_s);
//       debug(blad_najnizszy);

      
   }
   catch (...)
   {
         
      throw;
   }
   
   return;
}

double ksi::exp_007::gauss(double x, double m, double s)
{
   double roznica = x - m;
   return exp ( - (roznica * roznica) / (2 * s * s));
}

double ksi::exp_007::F (double d)
{
   const int N = 1000;
   const double X_MIN = -100;
   const double X_MAX =  100;
   const double STEP = (X_MAX - X_MIN) / N;
   const double M = 0;
   const double S = 1;
   
   double suma = 0.0;
   
   for (double x = X_MIN; x < X_MAX; x += STEP)
   {
      double roznica = gauss (x, M, S) - gauss (x, M + d, S);
      suma += (roznica * roznica);
   }
   return suma;
}

double ksi::exp_007::Fprim (double d)
{
   const int N = 1000;
   const double X_MIN = -100;
   const double X_MAX =  100;
   const double STEP = (X_MAX - X_MIN) / N;
   const double M = 0;
   const double S = 1;
   
   double suma = 0.0;
   
   for (double x = X_MIN; x < X_MAX; x += STEP)
   {
      double fl = gauss (x, M,     S);
      double fp = gauss (x, M + d, S);
      double roznica = fl - fp ;
      suma += (2 * roznica * fp * (M + d - x) / (S * S));
   }
   return suma;
}

double ksi::exp_007::blad(const std::vector<std::pair<double, double>> & punkty, double m, double s)
{
   double suma {0};
   for (auto p : punkty)
   {
      auto x = p.first;
      auto u = p.second;
      
      auto fx = gauss (x, m, s);
      
      auto froz = u - fx;
      suma += ( froz * froz  );
   }
   return suma;   
}

double ksi::exp_007::wyzarz_m( const std::vector<std::pair<double, double>> & punkty, 
                               const double M_MIN, 
                               const double M_MAX, 
                               const double s, 
                               const double EPSILON, 
                               const double TEMPERATURA)
{
   const double ETA_T = 0.99;
   const int ITER_T = 10;
   const int MAX_ITER = 1000;
   const double M_RANGE = M_MAX - M_MIN;
   
   std::default_random_engine silnik;
   silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_real_distribution<double> rozklad (M_MIN, M_MAX);
   std::uniform_real_distribution<double> rozklad_sadziedztwa (- M_RANGE / 10, M_RANGE / 10);
   
   std::uniform_real_distribution<double> rozklad_przyjecia (0, 1);
   
   double stare_m = 0;
   double stare_F = blad(punkty, stare_m, s);
   double nowe_m = rozklad(silnik);
   double nowe_F;
   bool koniec = false;
   double najlepsze_m = nowe_m;
   double najlepsze_F = blad(punkty, nowe_m, s);
   
   int iter = 0;
   int iter_t = 0;
   
   double t = TEMPERATURA;
   while (not koniec)
   {
      nowe_m = stare_m + rozklad_sadziedztwa(silnik);
      nowe_F = blad(punkty, nowe_m, s);
      
//       debug(iter);
//       debug(stare_m);
//       debug(nowe_m);
//       debug(stare_F);
//       debug(nowe_F);
      
      if (nowe_F < stare_F)
      {
         stare_m = nowe_m;
         stare_F = nowe_F;
//          debug("poprawa");
         
      }
      else 
      {
         // sprawdzam prawdopodobiestwa
         auto p = exp ((stare_F - nowe_F) / t); 
//          debug(stare_F - nowe_F);
//          debug(t);
//          debug(p);
         if (p > rozklad_przyjecia(silnik))
         { // przyjmujemy
            stare_m = nowe_m;
            stare_F = nowe_F;
//             debug("przyjmujemy");
            
         }
         else 
         { // nie przyjmujemy
//             debug("nie przyjmujemy");
            
         }
      }
      
      if (iter++ > MAX_ITER)
         koniec = true;
      iter_t++;
      if (iter_t > ITER_T)
      {
         iter_t = 0;
         t *= ETA_T;
      }
      
      if (nowe_F < najlepsze_F)
      {
         najlepsze_F = nowe_F;
         najlepsze_m = nowe_m;
      }
   }
   return najlepsze_m;   
}

double ksi::exp_007::wyzarz_s( const std::vector<std::pair<double, double>> & punkty, 
                               const double S_MIN, 
                               const double S_MAX, 
                               const double M, 
                               const double EPSILON, 
                               const double TEMPERATURA)
{
   const double ETA_T = 0.99;
   const int ITER_T = 10;
   const int MAX_ITER = 1000;
   const double S_RANGE = S_MAX - S_MIN;
   
   std::default_random_engine silnik;
   silnik.seed(std::chrono::system_clock::now().time_since_epoch().count());
   std::uniform_real_distribution<double> rozklad (S_MIN, S_MAX);
   std::uniform_real_distribution<double> rozklad_sadziedztwa (- S_RANGE / 10, S_RANGE / 10);
   
   std::uniform_real_distribution<double> rozklad_przyjecia (0, 1);
   
   double stare_s = 3;
   double stare_F = blad(punkty, M, stare_s);
   double nowe_s = rozklad(silnik);
   double nowe_F;
   bool koniec = false;
   double najlepsze_s = nowe_s;
   double najlepsze_F = blad(punkty, M, nowe_s);
   
   int iter = 0;
   int iter_t = 0;
   
   double t = TEMPERATURA;
   while (not koniec)
   {
      nowe_s = stare_s + rozklad_sadziedztwa(silnik);
      nowe_F = blad(punkty, M, nowe_s);
      
      //       debug(iter);
      //       debug(stare_m);
      //       debug(nowe_m);
      //       debug(stare_F);
      //       debug(nowe_F);
      
      if (nowe_F < stare_F)
      {
         stare_s = nowe_s;
         stare_F = nowe_F;
         //          debug("poprawa");
         
      }
      else 
      {
         // sprawdzam prawdopodobiestwa
         auto p = exp ((stare_F - nowe_F) / t); 
         //          debug(stare_F - nowe_F);
         //          debug(t);
         //          debug(p);
         if (p > rozklad_przyjecia(silnik))
         { // przyjmujemy
            stare_s = nowe_s;
            stare_F = nowe_F;
            //             debug("przyjmujemy");
            
         }
         else 
         { // nie przyjmujemy
            //             debug("nie przyjmujemy");
            
         }
      }
      
      if (iter++ > MAX_ITER)
         koniec = true;
      iter_t++;
      if (iter_t > ITER_T)
      {
         iter_t = 0;
         t *= ETA_T;
      }
      
      if (nowe_F < najlepsze_F)
      {
         najlepsze_F = nowe_F;
         najlepsze_s = nowe_s;
      }
   }
   return najlepsze_s;   
}

