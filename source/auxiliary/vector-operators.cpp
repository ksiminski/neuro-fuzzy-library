/** @file */

#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>


#include "../auxiliary/vector-operators.h"
#include "../auxiliary/matrix.h"
#include "../auxiliary/definitions.h"
#include "../service/debug.h"


namespace ksi 
{
 /*   
   std::ostream & operator << (std::ostream & ss, const std::vector<double> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << "  ";
      ss << "]";
      return ss;
   }
   */
   std::ostream & operator << (std::ostream & ss, const std::vector<std::vector<double>> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << std::endl;
      ss << "]";
      return ss;
   }

   
   std::vector<double> operator + (const std::vector<double> & l, 
                                   const std::vector<double> & p)
   {
       try 
       {
           if (l.size() != p.size())
               throw std::string ("The sizes of vectors do not match! (") + std::to_string(l.size()) + std::string(" != ") + std::to_string(p.size()) + std::string (")");
           
           std::vector<double> res (l.size());
           for (std::size_t i = 0; i < l.size(); i++)
              res[i] = l[i] + p[i];
           
           return res;
       }
       CATCH;
   }
   
   std::vector<double> operator - (const std::vector<double> & l, 
                                   const std::vector<double> & p)
   {
       try 
       {
           return l + (p * -1.0);
       }
       CATCH;
   }
   
   std::vector<double> & operator += (std::vector<double> & l, 
                                      const std::vector<double> & p)
   {
       l = l + p;
       return l;
   }
   
   std::vector<double> & operator -= (std::vector<double> & l, 
                                      const std::vector<double> & p)
   {
       l = l - p;
       return l;
   }

   
   
   std::vector<double> operator * (const std::vector<double> & l, 
                                   const double v)
   {
       try 
       {
           std::vector<double> res (l);
           for (auto & d : res)
               d *= v;
           
           return res;
       }
       CATCH;
   }
   
   std::vector<double> operator / (const std::vector<double> & l, 
                                   const double v)
   {
       try 
       {
           return l * (1.0 / v);
       }
       CATCH;
   }

   
   std::vector<double> operator + (const std::vector<double> & l, 
                                   const double v)
   {
       try 
       {
           std::vector<double> res (l);
           for (auto & d : res)
               d += v;
           
           return res;
       }
       CATCH;
   }
   
   bool is_valid (const std::vector<double> & l)
   {
       return std::all_of(l.begin(), l.end(), 
                          [] (double d) 
                          { return std::isfinite(d); }
                         );
   }

   bool is_valid (const ksi::Matrix<double> & m)
   {
       return std::all_of(m.begin(), m.end(),
                          [](const std::vector<double> &d)
                          {
                              return std::all_of(d.begin(), d.end(),
                              [] (double d)
                              {
                                 return std::isfinite(d); 
                              });
                          });
   }

   bool is_valid (const std::vector<ksi::Matrix<double>> & l)
   {
       return std::all_of(l.begin(), l.end(), 
                          [] (const auto m) 
                          { return is_valid(m);}
                         );
   }
   /*
   std::ostream & operator << (std::ostream & ss, const std::vector<std::pair<double, double>> & we)
   {
      ss << "[  ";
      for (const auto & d : we)
         ss << d << "  ";
      ss << "]";
      return ss;
   }
   */
   /*
   std::ostream & operator << (std::ostream & ss, const std::pair<double, double> & we)
   {
      ss << "{ " << we.first << ", " << we.second << " }";
      return ss;
   }
   */
} 
 
std::vector<double> ksi::get_uniform_unit_random_vector (const std::size_t size)
{
    static std::default_random_engine silnik (std::chrono::system_clock::now().time_since_epoch().count());
    
    std::uniform_real_distribution<double> distro (0.0, 1.0);
    
    std::vector<double> w (size);
    
    std::generate(w.begin(), w.end(), [&distro] () { return distro(silnik);});
    
    return w;   
    
}

double ksi::scalar_product (const std::vector<double> & l,
                            const std::vector<double> & p)
{
    try 
    {
        if (l.size() != p.size())
        {
            std::stringstream ss;
            ss << "The sizes of vectors do not match! left: " << l.size()
               << ", right: " << p.size();
            throw ksi::exception(ss.str());
        }
        
        auto size = l.size();
        double result { 0 };
        for (std::size_t i = 0; i < size; i++)
        {
            result += l[i] * p[i];
        }
        return result;
    }
    CATCH;
}
