/** @file */

#include <vector>

#include "matrix.h"
#include "least-error-squares-regression.h"
#include "../service/debug.h"
 


const double ksi::least_square_error_regression::BIG_NUMBER = 1'000'000'000;


std::vector<std::vector<double>> ksi::least_square_error_regression::matrix_multiplication (
         const std::vector<std::vector<double>> & left,
         const std::vector<std::vector<double>> & right)
{
   std::size_t lRows = left.size();
   std::size_t lCols = left[0].size();
   std::size_t rRows = right.size();
   std::size_t rCols = right[0].size();
   
   std::vector<std::vector<double>> res (lRows);
   for (auto & w : res)
      w = std::vector<double> (rCols);
   
   for (std::size_t w = 0; w < lRows; w++)
   {
      for (std::size_t k = 0; k < rCols; k++)
      {
         double suma = 0.0;
         for (std::size_t i = 0 ; i < lCols; i++)
            suma += left[w][i] * right[i][k];
         res[w][k] = suma;
      }
   }
   return res;
}


std::vector<std::vector<double>> ksi::least_square_error_regression::matrix_multiplication (
         const std::vector<std::vector<double>> & left, double right)
{
   std::size_t lRows = left.size();
   std::size_t lCols = left[0].size();
   
   std::vector<std::vector<double>> res (left);
   
   for (std::size_t w = 0; w < lRows; w++)
   {
      for (std::size_t k = 0; k < lCols; k++)
      {
         res[w][k] *= right;
      }
   }
   return res;
}

std::vector<double> ksi::least_square_error_regression::recursive_weighted_linear_regression (
         const std::vector<std::vector<double>> & X, 
         const std::vector<double> & Y,
         const std::vector<double> & W
      )
{
   //const double BIG_NUMBER = 1'000'000'000;
   Matrix<double> mX (X);

   int nAttr = mX.getCols();
   Matrix<double> theta (nAttr, 1);
   Matrix<double> R (nAttr, nAttr);

   for (int w = 0; w < nAttr; w++)
      R(w, w) = BIG_NUMBER;
   

   int nData = X.size();
   for (int i = 0; i < nData; i++)
   {
      auto xT = mX.getRow(i); // row matrix
      auto x  = !xT;          // column matrix
      
      auto waga = W[i];
      auto wspolczynnik = (1.0 / (1.0 + (xT * R * x) (0, 0) * waga));
      // actualisation of theta:
      theta = theta + R * x * (waga * wspolczynnik) * (Y[i] - (xT * theta)(0, 0));
      // actualisation of R: 
      R = R - R * x * xT * R * waga * wspolczynnik;
      
      // wszystko :-)
   }
   
   std::vector<double> wynik (theta.getRows());

   for (int i = 0 ; i < theta.getRows(); i++)
      wynik[i] = theta(i, 0);

   return wynik;
}

ksi::least_square_error_regression::least_square_error_regression (std::size_t nAttr)
{
   theta = Matrix<double>  (nAttr, 1);
   
   R = Matrix<double> (nAttr, nAttr);
   for (int w = 0; w < nAttr; w++)
      R(w, w) = BIG_NUMBER;
   
   wTheta = std::vector<double> (nAttr, 1);
   wR = std::vector<std::vector<double>> (nAttr);
   for (int a = 0; a < nAttr; a++)
   {
      wR[a] = std::vector<double> (nAttr, 0.0);
      wR[a][a] = BIG_NUMBER;
   }
   
}

void ksi::least_square_error_regression::read_data_item (
   const std::vector<double> & X, const double Y)
{
   //read_data_item(X, Y, 1.0); // waga = 1
   
   {
      std::size_t nAttr = X.size();
      std::vector<double> Rx (nAttr, 0.0);
      for (std::size_t a = 0; a < nAttr; a++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
            Rx[a] += wR[a][k] * X[k];
      }

      double xTRx = 0.0;
      for (std::size_t a = 0; a < nAttr; a++)
         xTRx += X[a] * Rx[a];
      
      auto wspolczynnik = (1.0 / (1 + xTRx));
      
      double xTTheta = 0.0;
      for (std::size_t a = 0; a < nAttr; a++)
         xTTheta += X[a] * wTheta[a];
      
      for (std::size_t a = 0; a < nAttr; a++)
         wTheta[a] += (Rx[a] * wspolczynnik * (Y - xTTheta));
      
      auto RxxT = wR;
      for (std::size_t w = 0; w < nAttr; w++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
         {
            RxxT[w][k] = Rx[w] * X[k];
         }
      }
      
      auto RxxTR = matrix_multiplication(RxxT, wR);
      for (std::size_t w = 0; w < nAttr; w++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
            wR[w][k] -= (RxxTR[w][k] * wspolczynnik);
      }
   }
    
   /*
   Matrix<double> xT = Matrix<double>::RowMatrix (X); // row matrix
   Matrix<double> x  = Matrix<double>::ColumnMatrix(X); // 
   auto Rx = R * x;
   auto wspolczynnik = (1.0 / (1 + (xT * Rx) (0, 0)));
   // actualisation of theta:
   theta = theta + Rx * wspolczynnik * (Y - (xT * theta)(0, 0));
   // actualisation of R: 
   R -= Rx * xT * R * wspolczynnik;
   
   std::cout << theta << std::endl;
   */
}

void ksi::least_square_error_regression::read_data_item (
   const std::vector<double> & X, const double Y, const double W)
{
    
   {
      std::size_t nAttr = X.size();
      std::vector<double> Rx (nAttr, 0.0);
      for (std::size_t a = 0; a < nAttr; a++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
            Rx[a] += wR[a][k] * X[k];
      }

      double xTRx = 0.0;
      for (std::size_t a = 0; a < nAttr; a++)
         xTRx += X[a] * Rx[a];
      
      auto wspolczynnik = (1.0 / (1.0 + W * xTRx));
      
      double xTTheta = 0.0;
      for (std::size_t a = 0; a < nAttr; a++)
         xTTheta += X[a] * wTheta[a];
      
      for (std::size_t a = 0; a < nAttr; a++)
         wTheta[a] += (W * Rx[a] * wspolczynnik * (Y - xTTheta));
      
      auto RxxT = wR;
      for (std::size_t w = 0; w < nAttr; w++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
         {
            RxxT[w][k] = Rx[w] * X[k];
         }
      }
      
      auto RxxTR = matrix_multiplication(RxxT, wR);
      for (std::size_t w = 0; w < nAttr; w++)
      {
         for (std::size_t k = 0; k < nAttr; k++)
            wR[w][k] -= (W * RxxTR[w][k] * wspolczynnik);
      }
   }
}



std::vector<double> ksi::least_square_error_regression::get_regression_coefficients()
{
   return wTheta;
}



std::vector<double> ksi::least_square_error_regression::recursive_linear_regression 
(const std::vector<std::vector<double>> & X, 
 const std::vector<double> & Y)
{
   
   Matrix<double> mX (X);

   int nAttr = mX.getCols();
   Matrix<double> theta (nAttr, 1);
   Matrix<double> R (nAttr, nAttr);

   for (int w = 0; w < nAttr; w++)
      R(w, w) = BIG_NUMBER;
   

   int nData = X.size();
   for (int i = 0; i < nData; i++)
   {
      auto xT = mX.getRow(i); // row matrix
      auto x  = !xT;          // column matrix
      
      auto wspolczynnik = (1.0 / (1 + (xT * R * x) (0, 0))); // liczba
      // actualisation of theta:
      theta = theta + R * x * wspolczynnik * (Y[i] - (xT * theta)(0, 0));
      // actualisation of R: 
      R = R - R * x * xT * R * wspolczynnik;
      
      // wszystko :-)
   }
   
   std::vector<double> wynik (theta.getRows());

   for (int i = 0 ; i < theta.getRows(); i++)
      wynik[i] = theta(i, 0);

   return wynik;
}



std::vector<double> ksi::least_square_error_regression::linear_regression (const std::vector<std::vector<double>> & X, const std::vector<double> & Y)
{
    try 
    {
        Matrix<double> mX (X);
        Matrix<double> mY (Y.size(), 1);

        for (size_t i = 0; i < Y.size(); i++)
            mY(i, 0) = Y[i];
        // mam macierze juz utworzone, teraz trzeba wyznaczyc regresje liniowa

        Matrix<double> mXT = !mX;
        Matrix<double> mXTX = mXT * mX;

        int blad;
        Matrix<double> A = mXTX.invert(blad) * mXT * mY;
        
        std::vector<double> wynik (A.getRows());

        for (int i = 0 ; i < A.getRows(); i++)
            wynik[i] = A(i, 0);

        return wynik;
    }
    catch (const std::string & s)
    {
        std::cout << s << std::endl;
    }
    return {};
} 


std::vector<double> ksi::least_square_error_regression::weighted_linear_regression (
   const std::vector<std::vector<double>> & X, 
   const std::vector<double> & Y, 
   const std::vector<double> & W)
{
    Matrix<double> mX (X);
    Matrix<double> mY (Y.size(), 1);
    Matrix<double> mW (Y.size(), Y.size(), 0.0);
    
    for (size_t i = 0; i < Y.size(); i++)
    {
        mY(i, 0) = Y[i];
        mW(i, i) = W[i];
    }
    // mam macierze juz utworzone, teraz trzeba wyznaczyc regresje liniowa

    Matrix<double> mXT = !mX;
    Matrix<double> mXTWX = mXT * mW * mX;

    int blad;
    Matrix<double> A = mXTWX.invert(blad) * mXT * mW * mY;

    std::vector<double> wynik (A.getRows());

    for (int i = 0 ; i < A.getRows(); i++)
        wynik[i] = A(i, 0);

    return wynik;

}

