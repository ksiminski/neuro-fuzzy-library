/** @file */

#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

#include "../service/debug.h"
#include "../auxiliary/mathematics.h"

namespace ksi
{

   /** Template of a class implementing an essential matrix. 
   * @author Krzysztof Siminski
   */
   template<class T>
   class Matrix
   {
      std::vector<std::vector<T> > data;
      int Rows, Cols;
      
      
   public:
      /** constructor of an empty matrix 
         * @param rows number of rows
         * @param cols number of columns
         */
      Matrix (int rows, int cols)  : Matrix ()
      {
         Rows = rows;
         Cols = cols;
         
         data = std::vector<std::vector<T> > (rows);
         int i;
         for (i = 0; i < rows; i++)
            data[i] = std::vector<T> (cols);         
      }  
   public:
      /** constructor of an initialised matrix 
         * @param rows number of rows
         * @param cols number of columns
         * @param initial initial value for data items 
         */
      Matrix (int rows, int cols, T initial) : Matrix ()
      {
         Rows = rows;
         Cols = cols;
         
         data = std::vector<std::vector<T> > (rows);
         int i;
         for (i = 0; i < rows; i++)
            data[i] = std::vector<T> (cols, initial);         
      }  

   
   public:
      /** Default parameterless constructor creates a matrix with no rows and no columns. */   
      Matrix () {} 
      
      public:
      /** copy constructor **/   
      Matrix (const Matrix & m)   
      {
         Rows = m.Rows;
         Cols = m.Cols;
         data = m.data;
          
      }

      public:
      /** move constructor **/   
      Matrix (Matrix && m)
      {
         std::swap (Rows, m.Rows);
         std::swap (Cols, m.Cols);
         std::swap (data, m.data); 
      }
      
      Matrix & operator = (const Matrix & m)
      {
         if (this == & m)
            return *this;
         
         Rows = m.Rows;
         Cols = m.Cols;
         data = m.data; 
         
         return *this;
      }
      
      Matrix & operator = (Matrix && m)
      {
         if (this == & m)
            return *this;
         
         std::swap (Rows, m.Rows);
         std::swap (Cols, m.Cols);
         std::swap(data, m.data); 
         
         return *this;
      }
      
      public:
      /** Constructor from a vector of vectors
      * @exception std::string with a comment when number of items in rows differ **/   
      Matrix (const std::vector<std::vector<T>> & t)  : Matrix ()
      {
         data = t;
         Rows = t.size();
         if (Rows == 0)
            Cols = 0;
         else
            Cols = t[0].size();
         
         
         // sprawdzenie, czy wszystkie wiersze maja tyle samo kolumn
         for (typename std::vector<std::vector<T>>::iterator iter = data.begin(); 
               iter != data.end(); iter++)
         {
               if (Cols != iter->size())
               {
                  std::stringstream ss;
                  ss << __FILE__ << " (" << __LINE__ << "): not a rectangular matrix (various numbers of items in rows): ";
                  throw ss.str();
               }
         }  
      }
      
   public:
      /** The method creates a column matrix from vector data.
       * @param w vector of values
       * @return column matrix (only one column)
       * @date 2018-01-26
       * @author Krzysztof Siminski
       */
      static Matrix ColumnMatrix (const std::vector<T> & w)
      {
         Matrix<double> res;
         res.Rows = w.size();
         res.Cols = 1;
         
         res.data = std::vector<std::vector<T>> (res.Rows);
         for (std::size_t i = 0; i < res.Rows; i++)
            res.data[i] = std::vector<T> {w[i]};
         return res;
      }
      
      
      
   public:
      /** The method creates a row matrix from vector data.
       * @param w vector of values
       * @return row matrix (only one row)
       * @date 2018-01-26
       * @author Krzysztof Siminski
       */
      static Matrix RowMatrix (const std::vector<T> & w)
      {
         Matrix<double> res;
         res.Rows = 1;
         res.Cols = w.size();
         
         res.data = std::vector<std::vector<T>> (1);
         res.data[0] = w;
         
         return res;
      }
      
   public:
      /** The method creates a diagonal matrix.
       * @param w vector of values to put in the main diagonal.
       * @return diagonal square matrix
       * @date 2023-04-28
       * @author Krzysztof Siminski
       */
      static Matrix DiagonalMatrix (const std::vector<T> & w)
      {
         auto size = w.size();
         Matrix<double> res(size, size, 0.0);
         for (std::size_t i = 0 ; i < size; i++)
            res.data[i][i] = w[i];
         return res;
      }
      
   public:
      /** The method creates an identity matrix.
       * @param size size of an identity matrix
       * @return identity matrix
       * @date 2023-04-28
       * @author Krzysztof Siminski
       */
      static Matrix IdentityMatrix (const std::size_t size)
      {
         Matrix<double> res(size, size, 0.0);
         for (std::size_t i = 0 ; i < size; i++)
            res.data[i][i] = 1.0;
         return res;
      }
      
   public:
      auto begin()
      {
         return data.begin();
      }

      auto end()
      {
         return data.end();
      }

      auto begin() const 
      {
         return data.begin();
      }

      auto end() const
      {
         return data.end();
      }

   public:
       /** The method shuffles the rows of the matrix 
        @date 2020-08-07 
        */
       void random_shuffle_rows()
       {
           std::random_shuffle(data.begin(), data.end());
       }
       
       /** The method shuffles the columns of the matrix 
        @date 2020-08-07 
        */
       void random_shuffle_columns()
       {
           auto mtr = !*this;
           mtr.random_shuffle_rows();
           data = (!mtr).data;
       }
      
      public:
      /** @return number of columns in the matrix */
      int getCols() const
      {
         return Cols;
      }
      
      public:
      /** @return number of rows in the matrix */   
      int getRows() const
      {
         return Rows;
      }
      
      public: 
      /** Method return a row.
         Rows indexed from 0 to nRows - 1.
         @param w -- number of row to return
         @throw string with message when row does not exist
      */ 
      Matrix<T> getRow(int w) const
      {
         if (w < 0 || w > Rows - 1)
         {
               std::stringstream ss;
               ss << __FILE__ << " (" << __LINE__ << "): Matrix<T> getRow(int w) -- requested row: " << w <<", number of rows: " << Rows << " (rows indexed from zero to max - 1)" ;
               throw ss.str();
         }
         
         Matrix<T> res (1, Cols);
         for (int i = 0; i < Cols; i++)
            res.data[0][i] = data[w][i];

         return res;
      }
      
      public: 
      /** Method return a column.
         Colums indexed from 0 to nCols - 1.
         @param k -- number of column to return
         @throw string with message when column does not exist
      */ 
      Matrix<T> getCol(int c) const 
      {
         if (c < 0 || c > Cols - 1)
         {
               std::stringstream ss;
               ss << __FILE__ << " (" << __LINE__ << "): Matrix<T> getRow(int c) -- requested column: " << c <<", number of colums: " << Cols << " (columns indexed from zero to max - 1)" ;
               throw ss.str();
         }
         
         Matrix<T> res (Rows, 1);
         for (int i = 0; i < Rows; i++)
            res.data[i][0] = data[i][c];

         return res;
      }
      
      public:
      /** @return The method returns a vector of rows (vectors of values) stored in the matrix
       *  @date 2020-08-07  
       */
          
      std::vector<std::vector<T>> getValues()
      {
          return data;
      }
      
   public:
      /** @return true if the matrix is empty.
          @date 2023-04-27 */
      bool empty() const 
      {
         return data.size() == 0;
      }
      
   public:
      /**
       * @param w index of a row (starting with 0)
       * @param f function that operates on two values and return a value
       * @return The method return accumulation of a row with function f. 
       * Eg. for summing up all items use lambda [] (T a, T b) {return a + b;} with initial_value = 0; for max search use lambda [] (T a, T b) {return std::max(a,b);} with initial_value = 0;
       * @throw std::string with a comment, when index of an invalid row
       * @date 2020-08-07
       */ 
      T accumulate_row (int w, T initial_value, const std::function<T (T, T)> & f) const
      {
         if (w < 0 || w >= Rows)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect row index: "
               << w << " (range: 0 .. " << Rows - 1 << ")";
            throw ss.str();
         }
         
         T wynik {initial_value};
         for (const auto & d : data[w])
         {
             wynik = f(d, wynik);
         }
         
         return wynik;
      }

   public:
      /**
       * @param w index of a row (starting with 0)
       * @param f function that operates on two values and return a value
       * @return The method return accumulation of a row with function f. 
       * Eg. for summing up all items use lambda [] (T a, T b) {return a + b;} with initial_value = 0; for max search use lambda [] (T a, T b) {return std::max(a,b);} with initial_value = 0; for summing up  squares of all items use lambda [](const double a, const double b){return a * a + b;}; with initial value = 0;   
       * @throw std::string with a comment, when index of an invalid row
       * @date 2020-08-07
       */ 
      T accumulate_column (int col, T initial_value, const std::function<T (T, T)> & f) const
      {
         if (col < 0 || col >= Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect column index: "
               << col << " (range: 0 .. " << Cols - 1 << ")";
            throw ss.str();
         }
         
         T wynik {initial_value};
         
         
         for (std::size_t r = 0; r < Rows; r++)
         {
             wynik = f(data[r][col], wynik);
         }
         
         return wynik;
      }
      
   public:
       /** @return sum of squared values in column c
        @param c column index */
       T sum_of_squared_values_in_column (const int c) const
       {
           auto lambda = [](const double a, const double b){return a * a + b;};
           return accumulate_column(c, T{}, lambda);
       }
      
   public: 
       /** The function scales all values to the interval [0, 1]. The minimum is mapped onto 0, the maximum onto 1. If minimum equals maximum, the matrix is filled with 0.5 */
       void normalise_by_columns_to_0_1_interval()
       {
           std::vector<T> minis, maxis;
           
           for (std::size_t r = 0; r < Rows; r++)
           {
               auto mini_maxi = std::minmax_element(data[r].begin(), data[r].end());
               minis.push_back(*(mini_maxi.first));
               maxis.push_back(*(mini_maxi.second));
           }
           
           double mini = *(std::min_element(minis.begin(), minis.end()));
           double maxi = *(std::max_element(minis.begin(), minis.end()));
           
           if (mini == maxi)
           {
                for (std::size_t c = 0; c < Cols; c++)
                {
                    for (std::size_t r = 0; r < Rows; r++)
                    {
                            data[r][c] = 0.5;
                    }
                }
           }
           else 
           {
                for (std::size_t c = 0; c < Cols; c++)
                {
                    for (std::size_t r = 0; r < Rows; r++)
                    {
                            data[r][c] = (data[r][c] - mini) / (maxi - mini);
                    }
                }
           }
       }

   public: 
       /** The function normalises each column so that the sum of all values is 1. */
       void normalise_by_columns_to_unit_sum()
       {
           
           std::vector<T> sums(Cols, 0.0);
           for (std::size_t c = 0; c < Cols; c++)
           {
               for (std::size_t r = 0; r < Rows; r++)
               {
                   sums[c] += data[r][c];
               }
               
               if (sums[c] == 0.0)
               {    
                    for (std::size_t r = 0; r < Rows; r++)
                    {
                        data[r][c] = 1.0 / Rows;
                    }
               }
               else
               {
                    for (std::size_t r = 0; r < Rows; r++)
                    {
                        data[r][c] /= sums[c];
                    }
               }
           }
       }
       
      
//       public:
//       /** access operator
//          * @param w index of a row (starting with 0)
//          * @param k index of a column (starting with 0)
//          * @return a reference to an item in the matrix 
//          * @throw std::string with a comment, when index of row or column invalid
//          */   
//       T & operator () (int w, int k) 
//       {
//          if (w < 0 || w >= Rows)
//          {
//             std::stringstream ss;
//             ss << __FILE__ << " (" << __LINE__ << "): incorrect row index: "
//                << w << " (range: 0 .. " << Rows - 1 << ")";
//             throw ss.str();
//          }
//          if (k < 0 || k >= Cols)
//          {
//             std::stringstream ss;
//             ss << __FILE__ << " (" << __LINE__ << "): incorrect column index: "
//                << k << " (range: 0 .. " << Cols - 1 << ")";
//             throw ss.str();
//          }
//          return data[w][k];
//       }

      public:
      /** access operator
         * @param w index of a row (starting with 0)
         * @param k index of a column (starting with 0)
         * @return a reference to an item in the matrix 
         * @throw std::string with a comment, when index of row or column invalid
         */  
      T & operator () (const std::size_t & w, const std::size_t & k) 
      {
         if (w >= Rows)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect row index: "
               << w << " (range: 0 .. " << Rows - 1 << ")";
            throw ss.str();
         }
         if (k >= Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect column index: "
               << k << " (range: 0 .. " << Cols - 1 << ")";
            throw ss.str();
         }
         return data[w][k];
      }
      
   public:
      /** get value
         * @param w index of a row (starting with 0)
         * @param k index of a column (starting with 0)
         * @return a reference to an item in the matrix 
         * @throw std::string with a comment, when index of row or column invalid
         */  
      const T & get_value (const std::size_t & w, const std::size_t & k) const
      {
         if (w >= Rows)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect row index: "
               << w << " (range: 0 .. " << Rows - 1 << ")";
            throw ss.str();
         }
         if (k >= Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect column index: "
               << k << " (range: 0 .. " << Cols - 1 << ")";
            throw ss.str();
         }
         return data[w][k];
      }
      
      

      public:
      /**  @param w index of a row (starting with 0)
         * @param k index of a column (starting with 0)
         * @return a copy of value to an item in the matrix 
         * @throw std::string with a comment, when index of row or column invalid
         */  
      T getItem (std::size_t w, std::size_t k)  const 
      {
         if (w >= Rows)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect row index: "
               << w << " (range: 0 .. " << Rows - 1 << ")";
            throw ss.str();
         }
         if (k >= Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incorrect column index: "
               << k << " (range: 0 .. " << Cols - 1 << ")";
            throw ss.str();
         }
         return data[w][k];
      }
      
      public:
      /** Operator returns a product of a matrix and constant value. All matrix items 
         * are multiplied by a constant value. The operator* for template type T must exist. Input matrix is not modified.
         * @param d a contant to multiply by
         * @return a multiplied matrix, input matrix is not modified  
      */   
      Matrix operator * (T d) const 
      {
         Matrix<T> res (*this);
         for (int w = Rows - 1; w >= 0; w--)
            for (int k = Cols - 1; k >= 0; k--)
               res.data[w][k] = data[w][k] * d;
               
         
         return res; 
      }

      public:
      /** Operator returns a sum of a matrix and constant value. All matrix items 
         * are summed with a constant value. The operator+ for template type T must exist. Input matrix is not modified.
         * @param d a contant to sum with
         * @return a summed matrix, input matrix is not modified  
      */   
      Matrix operator + (T d) const
      {
         Matrix<T> res (*this);
         for (int w = Rows - 1; w >= 0; w--)
            for (int k = Cols - 1; k >= 0; k--)
               res.data[w][k] = data[w][k] + d;
               
         
         return res; 
      }
      public:
      /** Operator returns a sum of two matrices. The operator+ for template type T must exist. Input matrix is not modified.
         * @param m right operand of summation
         * @return a summed matrix, input matrix is not modified  
         * @throw std::string with a comment, when dimensions of matrices do not match
      */
      Matrix operator + (const Matrix & m)
      {
         if (Rows != m.Rows || Cols != m.Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): different dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
      
         
         Matrix<T> res (Rows, Cols);
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
            {
               res.data[w][k] = data[w][k] + m.data[w][k];
               //res(w, k) = operator()(w, k) + m(w, k);
            } 
         }
         return res;        
      }

      public:
      /** Operator adds a right-hand matrix to a left-hand one. The operator+= for template type T must exist.            
         * @param m right operand of summation
         * @return a summed matrix, input matrix is modified  
         * @throw std::string with a comment, when dimensions of matrices do not match
         * @date 2023-04-25
      */
      Matrix & operator += (const Matrix & m)
      {
         if (Rows != m.Rows || Cols != m.Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): different dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
      
         
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
            {
               data[w][k] += m.data[w][k];
               //res(w, k) = operator()(w, k) + m(w, k);
            } 
         }
         return *this;        
      }
      
      
      /** Operator returns a difference of two matrices. The operator- for template type T must exist. Input matrix is not modified.
         * @param m right operand of subtraction
         * @return a difference of matrices
         * @throw std::string with a comment, when dimensions of matrices do not match
      */
      Matrix operator- (const Matrix & m)
      {
         if (Rows != m.Rows || Cols != m.Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): different dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
         
         Matrix res (*this);
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
               res.data[w][k] = data[w][k] - m.data[w][k];
         }
         return res;        
      }

      /** Operator that subtracts matrix from a matrix. The operator-= for template type T must exist. The original matrix is modified
         * @param m right operand of subtraction
         * @return a difference of matrices
         * @throw std::string with a comment, when dimensions of matrices do not match
      */
      Matrix & operator -= (const Matrix & m)
      {
         if (Rows != m.Rows || Cols != m.Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): different dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
         
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
               data[w][k] -= m.data[w][k];
         }
         return *this;        
      }

      Matrix & subtract_with_saturation (const Matrix & m)
      {
         if (Rows != m.Rows || Cols != m.Cols)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): different dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
         
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
            {
               auto v = data[w][k];
               auto delta = m.data[w][k];
               auto saturated_delta = ksi::saturate(delta, v, 1);
               // data[w][k] -= m.data[w][k];
               data[w][k] -= saturated_delta;
            }
         }
         return *this;        
      } 
      
      /** Operator returns a product of two matrices. The operator+ and operator* for template type T must exist. Input matrix is not modified.
         * @param m right operand of multiplication
         * @return a product of matices, input matrix is not modified  
         * @throw std::string with a comment, when dimensions of matrices do not match
      */
      Matrix operator * (const Matrix & m)  
      {
         if (Cols != m.Rows)
         {
            std::stringstream ss;
            ss << __FILE__ << " (" << __LINE__ << "): incompatible dimensions of matrices: "
               << "[" << Rows << " x " << Cols << "] and [" << m.Rows << " x " << m.Cols << "]";
            throw ss.str();
         }
               
         Matrix res (Rows, m.Cols);
         int w, k, i;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < m.Cols; k++)
            {
               res.data[w][k] = T();
               for (i = 0; i < Cols; i++) 
                  res.data[w][k] = res.data[w][k] + (data[w][i] * m.data[i][k]);
            } 
         }
         return res;        
      }
      
      /** Operator scales a matrix by a factor (double value). The operator* for template type T must exist. Input matrix is not modified.
         * @param m right operand of multiplication
         * @return a product of matices, input matrix is not modified  
         * @throw std::string with a comment, when dimensions of matrices do not match
      */
      Matrix operator * (const double factor)  
      {
               
         Matrix res (*this);
         int w, k;
         for (w = 0; w < res.Rows; w++)
         {
            for (k = 0; k < res.Cols; k++)
            {
               res.data[w][k] *= factor;
            } 
         }
         return res;        
      }
      
      /** Operator scales a matrix by a factor (double value). The operator/ for template type T must exist. Input matrix is not modified.
         * @param m right operand of multiplication
         * @return a product of matices, input matrix is not modified  
      */
      Matrix operator / (const double factor)  
      {
               
         Matrix res (*this);
         int w, k;
         for (w = 0; w < res.Rows; w++)
         {
            for (k = 0; k < res.Cols; k++)
            {
               res.data[w][k] /= factor;
            } 
         }
         return res;        
      }

      /** Operator scales a matrix by a factor (double value). The operator/ for template type T must exist. Input matrix is not modified.
         * @param m right operand of multiplication
         * @return a product of matices, input matrix is not modified  
         * @date 2023-07-09
      */
      Matrix & operator /= (const double factor)  
      {
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
            {
               data[w][k] /= factor;
            } 
         }
         return *this;        
      }

 
      
      /** A method returns a transposed matrix. Input matrix is not modified.
         * @return a transposed matrix, input matrix is not modified  
      */
      Matrix transpose() const
      {
         Matrix res(Cols, Rows);
         int w, k;
         for (w = 0; w < Rows; w++)
            for (k = 0; k < Cols; k++)
               res.data[k][w] = data[w][k];
         return res;
      }

      /** Operator returns a transposed matrix. Input matrix is not modified.
         * @return a transposed matrix, input matrix is not modified  
      */
      Matrix operator! () const
      {
         return transpose();
      }
      
      
      public:
      /** The method inverts a matrix with the Gauss-Jordan elimination algorithm. Original matrix in not modified.
       * @return inverted matrix 
       * @param[out] result_status -- result status:<BR>
            0    -- inversion possible<BR>
            1    -- square matrix, intersion impossible<BR>
            2    -- non-square matrix    
      */
      Matrix invert(int & result_status) const 
      {
         if (Cols != Rows)
         {
            result_status = 2; // non-square matrix
            return *this;
         }
         Matrix m (Rows, 2 * Cols);
         int w, k;
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
               m.data[w][k] = data[w][k];
            for (k = Cols; k < 2 * Cols; k++)
            {
               if (w == k - Cols)
                  m.data[w][k] = 1;
               else 
                  m.data[w][k] = 0;
            }
         }
         // teraz wlasciwa eliminacja Gaussa-Jordana
         for (w = 0; w < Rows; w++)
         {  // dla kazdego wiersza
            // dziele wartosci wiersza przez element na przekatnej:
            double naPrzekatnej = m(w, w);
            if (naPrzekatnej == 0)
            {
               // trzeba znalezc jakis wiersz z gory lub dolu i dodac do tego
               int ww;
               bool udalosie = false;
               for (ww = w; ww < Rows; ww++)
               {
                  if (m(ww, w) != 0) // znalezione niezero
                  {
                     // dodanie do wiersza tego znalezionego wiersza
                     for (k = 0; k < 2 * Cols; k++)
                        m.data[w][k] += m.data[ww][k];
                     
                     udalosie = true;
                     ww += Rows; // koniec petli
                     naPrzekatnej = m.data[w][w];
                  }
               }
               if (! udalosie)
               {
                  result_status = 1; // nie da sie odwrocic macierzy
                  return m;
               }
            }
            
            for (k = 0; k < 2 * Cols; k++)
               m.data[w][k] /= naPrzekatnej;
               
            // teraz trzeba odjac wartosci, jak zeby w kolumnie pod 
            // przekatna uzyskac zera
            int ww;
            for (ww = w + 1; ww < Rows; ww++)
            {
               // wartosc pod przekatna w kolumnie o indeksie w(!)
               double wartosc = m(ww, w);
               if (wartosc != 0) // gdy nie zero
               {
                  for (k = w; k < 2 * Cols; k++)
                  {
                     m.data[ww][k] -= (wartosc * m.data[w][k]);
                     //m(ww, k) -= (wartosc * m(w, k));
                  }
               } 
            } 
         }
         
         // jeszcze trzeba w druga strone -- wyzerowac nad przekatna
         for (w = Rows - 1; w >= 0; w--)
         {
            // teraz trzeba odjac wartosci, jak zeby w kolumnie nad 
            // przekatna uzyskac zera
            int ww;
            for (ww = w - 1; ww >= 0; ww--)
            {
               // wartosc pod przekatna w kolumnie o indeksie w(!)
               double wartosc = m(ww, w);
               if (wartosc != 0) // gdy nie zero
               {
                  for (k = w; k < 2 * Cols; k++)
                  {
                     m.data[ww][k] -= (wartosc * m.data[w][k]);
                     //m(ww, k) -= (wartosc * m(w, k));
                  }
               } 
            } 
         }
         
         // jeszcze tylko ekstrakcja wartosci macierzy odwroconej
         
         Matrix res (Rows, Cols);
         for (w = 0; w < Rows; w++)
         {
            for (k = 0; k < Cols; k++)
            {
               res.data[w][k] = m.data[w][k + Cols];
               //res(w, k) = m(w, k + Cols);
            }
         }
         
         result_status = 0; // OK
         return res;
      }
      
      
      public:
      /** The method elaborates a determinant of a matrix with the Gauss-Jordan elimination algorithm. Original matrix in not modified.
       * @return determinant 
       * @param[out] result_status -- result status:<BR>
            0    -- determinant calculated<BR>
            1    -- non-square matrix    
      */
      T determinant(int & result_status) const 
      {
         if (Cols != Rows)
         {
            result_status = 1; // non-square matrix
            return T{};
         }
         Matrix m (*this);
         
         int w, k;
         
         T wyznacznik {1.0};
         // teraz wlasciwa eliminacja Gaussa-Jordana
         for (w = 0; w < Rows; w++)
         {  // dla kazdego wiersza
            // dziele wartosci wiersza przez element na przekatnej:
            double naPrzekatnej = m(w, w);
            
            if (naPrzekatnej == 0)
            {
               // trzeba znalezc jakis wiersz z gory lub dolu i dodac do tego
               int ww;
               bool udalosie = false;
               for (ww = w; ww < Rows; ww++)
               {
                  if (m(ww, w) != 0) // znalezione niezero
                  {
                     // dodanie do wiersza tego znalezionego wiersza
                     for (k = 0; k < Cols; k++)
                        m.data[w][k] += m.data[ww][k];
                     
                     udalosie = true;
                     ww += Rows; // koniec petli
                     naPrzekatnej = m.data[w][w];
                  }
               }
               if (! udalosie)
               {
                  return T{};  // Wartosc wyznacznika wyniki zero.
               }
            }
            
            for (k = 0; k < Cols; k++)
               m.data[w][k] /= naPrzekatnej;
            
            // Dzielę wszystkie wartości w wierszu, zatem zmienia się wartość wyznacznika. 
            // Trzeba zatem to uwzględnić.
            wyznacznik *= naPrzekatnej;
            
            // teraz trzeba odjac wartosci, jak zeby w kolumnie pod 
            // przekatna uzyskac zera
            int ww;
            for (ww = w + 1; ww < Rows; ww++)
            {
               // wartosc pod przekatna w kolumnie o indeksie w(!)
               double wartosc = m(ww, w);
               if (wartosc != 0) // gdy nie zero
               {
                  for (k = w; k < Cols; k++)
                  {
                     m.data[ww][k] -= (wartosc * m.data[w][k]);
                     //m(ww, k) -= (wartosc * m(w, k));
                  }
               } 
            } 
         }
         
         // Mamy macierz trójkątną. Teraz wystarczy wymnożyć wartości na przekątnej.
         // {
         //    std::stringstream ss;
         //    ss << m;
         //    debug(ss.str());
         // }
         
         for (w = 0; w < Rows; w++)
         {
            wyznacznik *= m.data[w][w];
         }
            
         result_status = 0; // OK
         return wyznacznik;
      }
      
      /** Method extracts matrix values as a std::vector of std::vectors. 
         * The original matrix is not modified
         * @return a std::vector of std::vectors of values
         */
      
      std::vector<std::vector<T>> to2DimVector() const
      {
         return data;
      }
      
      
      /** The method returns a Frobenius norm of a matrix. 
       \f[ \| \mathbf{A} \|_F = \sum_{i, j} a_{ij}^2  \f]
       Frobenius norm of a matrix is a sum of squares of all its elements.
       */
      T Frobenius_norm () const 
      {
         T suma {};
         
         for (auto & w : data)
            for (auto & e : w)
            {
               auto e2 = e * e;
               suma = suma + e2;
            }
            
         return suma;
      }
      
      
//   
      
//    public: 
//       std::pair<Matrix, Matrix> Householder ()
//       {
//           std::pair<Matrix, Matrix> wynik;
//           auto PA (*this);
//           auto Arows = getRows();
//           Matrix jednostkowa (Arows, Arows, 1.0);
//           auto P (jednostkowa); // macierz jednostkowa
//             
//            for (int i = 0; i < Arows; i++)
//             {
//                 // wyluskuje i-ta kolumne:   
//                 auto kol = PA.getCol(i);
//                 // i ja normalizuje:
//                 auto norm (kol);
//                 norm.normalise_by_columns_to_unit_sum();
//                 
//                 // wyznaczam wartosc D:
//                 T D2 {};
//                 for (std::size_t k = i; k < Arows; k++)
//                     D2 += pow(norm(k, 0), 2);
//                 
//                 auto D = sqrt (D2);
//                 if (norm(i, 0) > 0)
//                     D *= -1;
//                 
//                 // mam juz D :-)
//                 
//                 // wyznaczam wektor kolumnowy V
//                 auto V(norm);
//                 for (int w = 0; w < i; w++)
//                     V(w, 0) = 0.0;
//                 V(i, 0) = std::sqrt( (1 - (norm(i, 0) / D) ) / 2.0);
//                 double p = - D * V(i, 0);
//                 for (int w = i + 1; w < Arows; w++)
//                     V(w, 0) = norm(w, 0) / (2 * p);
//                 
//                 // mam wektor V :-)
//                 
//                 // wyznaczam macierz Householdera
//                 Matrix jednostkowa (Arows, Arows, 1.0);
//                 auto Pi = jednostkowa - (V * !V) * 2;
//                 
//                 //auto Pi = roznica(jednostkowa(N), skaluj(2, iloczyn (V, transponuj(V))));
//                 P = Pi * P;
//                 PA = Pi * PA;
// //                 P  = iloczyn (Pi, P);
// //                 PA = iloczyn (Pi, PA);
//          
// //          for (auto & wiersz : P)
// //             debug(wiersz);
//          }
//       
//          wynik.first = !P;
//          wynik.second = PA;
//          return wynik;
//       }
      
      
   public:
   /** Gauss elimination method for solving system of linear equations: A * X = Y
    @param Y a column vector Y
    @return a column vector X */
   Matrix Gauss (const Matrix & Y)
   {
      const double EPSILON = 0.001;
      Matrix M(*this);
      size_t rows = getRows();
      size_t cols = getCols() + 1;
      
      for (size_t w = 0; w < rows; w++)
         M.data[w].push_back(Y.data[w][0]);      
      
      for (size_t w = 0; w < rows; w++)
      {
         // dziele wszystkie wartosci w wierszu przez wartosc na przekatnej:
         auto Mww = M.data[w][w];
         
         // tutaj musze sprawdzic, czy nie ma zera na przekatnej
         // sprawdzam, czy na przekatnej jest zero 
         if (fabs(M.data[w][w]) < EPSILON)
         {
             
            bool naprawione = false;
            // szukam wiersza niezerowego:
            for (size_t i = w + 1; i < rows and !naprawione; i++)
            {
               if (M.data[i][w] != 0)
               {
                  // dodaje ten wiersz:
                  for (size_t k = 0; k < cols; k++)
                     M.data[w][k] += M.data[i][k];
                  naprawione = true; // koniec szukania
                  //debug(M);
               }
            }
            //debug(naprawione);
            if (!naprawione) // nie udalo sie znalezc wiersza, przypisuje wartosc 1
            {
               M.data[w][w] = 1.0;
               for (size_t k = w + 1; k < cols - 1; k++)
                  M.data[w][k] = 0.0;
               M.data[w][cols - 1] = 1.0;
               //debug(M);
            }
         }
         
         Mww = M.data[w][w];
         for (size_t k = 0; k < cols; k++)
            M.data[w][k] /= Mww;
         
         // odejmuje ten wiersz od lezacych ponizej:
         for (size_t ww = w + 1; ww < rows; ww++)
         {
            double skala = - M.data[ww][w] / M.data[w][w];
            for (size_t k = 0; k < cols; k++)
               M.data[ww][k] += skala * M.data[w][k];
         }
         
      }

      //debug(M);
      // mamy macierz trojkatna rozszerzona
      for (int w = rows - 1; w >= 0; w--)
      {
         //debug(w);
         for (int ww = w - 1; ww >= 0; ww--)
         {
            //debug(ww);
            double skala = - M.data[ww][w] / M.data[w][w];
            for (size_t k = ww + 1; k < cols; k++)
               M.data[ww][k] += skala * M.data[w][k];
         }
      }
      
      //debug(M);
      Matrix X(rows, 1);
      for (size_t r = 0; r < rows; r++)
         X.data[r][0] = M.data[r][cols - 1];
      
      return X;
      
   }

      
//    public:
//        std::pair<Matrix, std::vector<double>> eigen (const int iterations)
//         {
//             auto N = getRows();
//             
//             std::vector<double> eigenvalues(N);
//             
//             Matrix A (*this);
//             for (int i = 0; i < iterations; i++)
//             {
//                 auto qr = A.Householder();
//                 A = qr.second * qr.first;
//             }
//             
//             //debug(A);
//             
//             for (size_t i = 0; i < N; i++)
//                 eigenvalues[i] = A(i, i);
//             
//             // jeszcze trzeba znalezc wektory wlasne
//             
//             std::vector<double> Y(N, 0.0);
//             
//             std::vector<std::vector<double>> eigenvectors;
//             
//             for (double lambda : eigenvalues)
//             {
//                 //debug(lambda);
//                 // tworze macierz:
//                 Matrix Alambda (*this);
//                 int licznik = 0;
//                 for (auto & wiersz : Alambda.data)
//                 {
//                     wiersz[licznik] -= lambda;
//                     licznik++;
//                 }
//                 // mam macierz, teraz wyszukuje wektory:
//                 //debug(Alambda);
//                 auto wektor = Alambda.Gauss(Y);
//                 eigenvectors.push_back(wektor);
//             }
//             std::pair<Matrix, std::vector<double>> eigens;
//             eigens.first = eigenvectors;
//             eigens.second = eigenvalues;
// 
//             return eigens;
//         } 
      
   
      /** Method for printing a matrix. */
      template<class U> 
      friend std::ostream & operator<< (std::ostream & ss, const Matrix<U> & m);
      
   };



//////////////////////////////
   template<class T>
   std::ostream & operator<< (std::ostream & ss, const  Matrix<T> & m)
   {
      int w, k;
      for (w = 0; w < m.Rows; w++)
      {
         for (k = 0; k < m.Cols; k++)
         {
            T wartosc = m.data[w][k];
            ss << wartosc << " ";
         }
         ss << std::endl;
      }   
      return ss;
   }

}

#endif
