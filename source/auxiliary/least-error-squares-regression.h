/** @file */

#ifndef LEAST_ERROR_SQUARES_REGRESSION_H
#define LEAST_ERROR_SQUARES_REGRESSION_H

#include <vector>
#include "matrix.h"

namespace ksi
{

   class least_square_error_regression
   {
      /** matrix for calculation of regression model */
      Matrix<double> R;
      /** matrix for calculation of regression model, the same as R, but as
       *  a vector of vectors */
      std::vector<std::vector<double>> wR;
      /** approximation of regression coefficients */
      Matrix<double> theta;
      /** approximation of regression coefficients, the same as theta, but as
       *  a vector */
      std::vector<double> wTheta;
      
      /** big number on diagonal of R matrix */
      static const double BIG_NUMBER;
      
   public: 
      /** Constructor :-)
       * @param nAttr number of attributes of a data item
       * @date 2018-01-26
       * @author Krzysztof Siminski
       */
      least_square_error_regression (std::size_t nAttr);
      
   public:
      /** The method reads one data item for recursive regression algorithm.
       * @param X data item
       * @param Y corresponding expected output
       * @date 2018-01-26
       * @author Krzysztof Siminski
       */
      void read_data_item (const std::vector<double> & X, const double Y);

   public:
      /** The method reads one data item for recursive regression algorithm.
       * @param X data item
       * @param Y corresponding expected output
       * @param W data item's weight
       * @date 2022-05-05
       * @author Krzysztof Siminski
       */
      void read_data_item (const std::vector<double> & X, const double Y, const double W);
      
   public:
      /** The method returns regression coefficients.
       * @return a vector of elaborated coefficients
       * @date 2018-01-26
       * @author Krzysztof Siminski
       */
      std::vector<double> get_regression_coefficients ();
    public:
      /** A method for calculating parameter for linear regression: X * A = Y.
       * The method applies matrix inversion.
       * @param X two dimensional array of values, each row represents a data item
       * @param Y a vector with y values, Y[i] corresponds with X[i] data item
       * @return a vector A with parameters for linear regression
       * @date 2018-01-14
       * @author Krzysztof Siminski
       */ 
      static std::vector<double> linear_regression (
         const std::vector<std::vector<double>> & X, 
         const std::vector<double> & Y
      ); 
   public:
      /** A method for calculating parameter for linear regression: X * A = Y.
       * The method avoids matrix inversion by applying the recursive least 
       * square method.
       * @param X two dimensional array of values, each row represents a data item
       * @param Y a vector with y values, Y[i] corresponds with X[i] data item
       * @return a vector A with parameters for linear regression
       * @date 2018-01-14
       * @author Krzysztof Siminski
       */ 
      static std::vector<double> recursive_linear_regression (
         const std::vector<std::vector<double>> & X, 
         const std::vector<double> & Y
      );
      
   public:
      /** A method for calculating parameter for weighted linear regression.
       * The method applies matrix inversion.
       * @param X two dimensional array of values, each row represents a data item
       * @param Y a vector with y values, Y[i] corresponds with X[i] data item
       * @param W a vector with weights, W[i] corresponds with X[i] data item
       * @return a vector A with parameters for linear regression
       * @date 2018-01-19
       * @author Krzysztof Siminski
       */ 
      static std::vector<double> weighted_linear_regression (
         const std::vector<std::vector<double>> & X, 
         const std::vector<double> & Y,
         const std::vector<double> & W
      ); 
      
   public:
      /** A method for calculating parameter for weighted linear regression.
       * The method avoids matrix inversion by applying the recursive least 
       * square method.
       * @param X two dimensional array of values, each row represents a data item
       * @param Y a vector with y values, Y[i] corresponds with X[i] data item
       * @param W a vector with weights, W[i] corresponds with X[i] data item
       * @return a vector A with parameters for linear regression
       * @date 2018-01-19
       * @author Krzysztof Siminski
       */ 
      static std::vector<double> recursive_weighted_linear_regression (
         const std::vector<std::vector<double>> & X, 
         const std::vector<double> & Y,
         const std::vector<double> & W
      );
      
   private:
      /** Method for multiplication of two matrices. The method does not 
          check the dimensions of the matrices to multiply.
          @param left left matrix
          @param right right matrix
          @return left * right
          */
      std::vector<std::vector<double>> matrix_multiplication (
         const std::vector<std::vector<double>> & left,
         const std::vector<std::vector<double>> & right);

      /** The method multiplies of elements of a matrix by a number
       @param left matrix to multiply by  ...
       @param right ... a number */
      std::vector<std::vector<double>> matrix_multiplication (
         const std::vector<std::vector<double>> & left, double right);

 
      
   };
}

#endif
