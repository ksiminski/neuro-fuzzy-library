/** @file */

#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include "datum.h"

namespace ksi
{
   /** Class representing a data set.
    @date   2017-12-29
    @author Krzysztof Siminski 
    */
   class dataset 
   {
   protected:
      /** maximal numerical label of data items  */ 
      std::size_t _maximalNumberLabel = 0; 
       
      std::vector<datum *> data;
      //const char MISSING_VALUE_SYMBOL = '?';
   public:
      virtual ~dataset();
      
      dataset ();
      dataset (const dataset & ds);
      dataset (dataset && ds);
      dataset & operator = (const dataset & ds);
      dataset & operator = (dataset && ds);
      
      /** The method adds a datum to the dataset by copying (allocates memory). */
      void addDatum (const ksi::datum d);
      /** The method adds a datum to the dataset without allocation of memory. */
      void addDatum (ksi::datum* p);
      
      /** @return returns number of data items in the dataset */
      std::size_t getNumberOfData() const;
      /** @return returns number of attributes in a datum */
      std::size_t getNumberOfAttributes() const;
      
      /** @return a value of a data item in row and column
       @param row row number 
       @param col column number 
       @exception ksi::exception if invalid row or col
       */
      double get (std::size_t row, std::size_t col) const ;
      
      /** Method sets a value in a row and a column
       @param row row number 
       @param col column number 
       @exception ksi::exception if invalid row or col
       */
      void set (std::size_t row, std::size_t col, double value);
      
      /** @return true -- if data in a row and a column exists, otherwise -- false
       @date 2017-12-31 
       @exception ksi::exception if invalid row or col
       */
      bool exists (std::size_t row, std::size_t col) const;
      
      /** @return a matrix of data 
        * @exception ksi::exception if some data do not exists */
      std::vector<std::vector<double>> getMatrix () const ;
      
      /** A method get r-th datum from the dataset. The method does not copy the datum!
       * @return a pointer to the datum or nullptr if r is illegal 
       * @param  r index of datum 
       * @date 2018-01-04
       */
      datum * getDatum (std::size_t r) const ;
      
      /** The method splits vertically the dataset into two datasets.
       * The first dataset has attributes 0 .. last_index.
       * The second dataset has attributes last_index + 1, .. number_of_attributes - 1. The original dataset is not modified.
       * @param last_index index of the last attribute in the first dataset to return
       * @return a pair of datasets  
       */
      std::pair<dataset, dataset> splitDataSetVertically (std::size_t last_index) const ;
      
      /** return maximal numerical label of data items */
      std::size_t getMaximalNumericalLabel () const;
      
      /** simply sets maximal numerical label of data items  */
      void setMaximalNumericalLabel (std::size_t id);
      
      /** The method reset id's of data items from 0 to max - 1. **/
      void resetIDs ();
      
      friend std::ostream & ksi::operator << (std::ostream & s, const dataset & d);
   };
}


#endif
