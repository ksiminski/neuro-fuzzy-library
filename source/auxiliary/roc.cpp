/** @file */


#include <vector>
#include <utility>   // std::pair
#include <algorithm> // sort
#include <cmath>

#include "roc.h" 

  

double ksi::roc::trapezoidArea(double x1, double x2, double y1, double y2)
{
    return abs(x1 - x2) * (y1 + y2) / 2;
}

ksi::results ksi::roc::calculate_ROC_points (std::vector<double> & Out,
                                             std::vector<double> & Answer, 
                                             double positiveClassvalue,
                                             double negativeClassvalue)
{
    double AUC = 0;
    std::vector<std::pair<double, double> > mergeData, points;
    ksi::results res;
    
    if (Out.size() == Answer.size())
    {
        std::pair<double, double> para;
        int liczba = Out.size();
        for (int i = 0; i < liczba; i++)
        {
            para.first = Out[i];
            para.second = Answer[i];
            
            mergeData.push_back(para);
        }
        // teraz trzeba posortowac dane wg drugiej skladowej pary.
        struct comparator
        {
           bool operator() (std::pair<double, double>  left, std::pair<double, double>  right)
           {
              return left.second < right.second;
           }
        } comparator_obj;
        std::sort(mergeData.begin(), mergeData.end(), comparator_obj);
        
        // mam posortowane dane
        // teraz trzeba ladnie wygenerowac krzywa ROC
       
        // trzeba policzyc jaka jest poczatkowa wartosc TPrate i FPrate;
        int nPos = 0;
        int nNeg = 0;
        
        double epsilon = fabs(positiveClassvalue - negativeClassvalue) / 4;
        for (std::vector<double>::iterator iter = Out.begin();
             iter != Out.end();
             iter++)
        {
            if (abs(*iter - negativeClassvalue) < epsilon) // negative
               nNeg++;
            else
               nPos++;
        }
         
        int nTP = nPos;
        int nFP = nNeg;
        int nTP_prev = nPos;
        int nFP_prev = nNeg;
         
        for (std::vector<std::pair<double, double> >::iterator iter = mergeData.begin();
             iter != mergeData.end();
             iter++)
        {
            std::pair<double, double> punkt;
            AUC += trapezoidArea(nFP, nFP_prev, nTP, nTP_prev);
        
            nTP_prev = nTP;
            nFP_prev = nFP;
            
            punkt.first  = 1.0 * nFP / nNeg;
            punkt.second = 1.0 * nTP / nPos;
            //cerr << "punkt: (" << punkt.first << ", " << punkt.second << ")" << endl;
            points.push_back(punkt);
            
            
            if (abs(iter->first - negativeClassvalue) < epsilon) // negative
            {
               nFP--;
               //cerr << "n ";
            } 
            else
            {
               nTP--;
               //cerr << "p ";
            }   
            //cerr << iter->second << endl;
        }
        // jeszcze dodaje (0,0)
        std::pair<double, double> punkt;
        punkt.first  = 0;
        punkt.second = 0;
        points.push_back(punkt);       
        // no i juz :-)
        
        // jeszcze tylko AUC
        AUC += trapezoidArea(0, nFP_prev, 0, nTP_prev);
        AUC /= (nPos * nNeg);
        
        // trzeba jeszcze policzyc indeksy 
        std::pair<double, double> Min_point, Youden_point;
        double Min_threshold;
        double Youden_threshold;
        double Youden_index = -1;
        double Min_distance =  1; 
        double Min_index;
        unsigned int i = 0;
        
        
        for (std::vector<std::pair<double, double> >::iterator iter = points.begin();
             iter != points.end(); iter++, i++)
        {
            double x = iter->first;
            double y = iter->second;
            
            double distance = x * x + (1 - y) * (1 - y);
            if (distance < Min_distance)
            {
               Min_distance = distance;
               Min_threshold = mergeData[i].second;
               Min_point = *iter;
            }
            double youden = y - x;
            if (youden > Youden_index)
            {
               Youden_index = youden;
               Youden_threshold = mergeData[i].second;
               Youden_point = *iter;
            }
        }
        
        res.Youden_index = Youden_index;
        res.Youden_threshold = Youden_threshold;
        res.Youden_cutoff_point = Youden_point;        
        
        res.Minimal_distance_threshold = Min_threshold;
        res.Minimal_distance_cutoff_point = Min_point;
    }
    
    res.ROC_points = points;
    res.AUC = AUC;
    
    
    return res;
}
