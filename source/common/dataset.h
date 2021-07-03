/** @file */

#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include "datum.h"
#include "../common/extensional-fuzzy-number-gaussian.h"

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
      
      /** Constructor that creates a dataset from a matrix of numbers.
       @date 2019-02-28
       */
      dataset (const std::vector<std::vector<double>> & matrix_of_numbers);
      
      /** Constructor that creates a dataset from a matrix of fuzzy extensional gaussian numbers.
       @date 2019-02-28
       */
      dataset (const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & matrix_of_numbers);
      
      dataset & operator = (const dataset & ds);
      dataset & operator = (dataset && ds);
      
      /** The method adds data items from the right operand.
       * The left operand is modified. 
       * The right operand is not modified.
       @throw ksi::exception If the numbers of attributes in both datasets do not match. */
      dataset & operator += (const dataset & ds);
      
      /** The method adds a datum to the dataset by copying (allocates memory). */
      void addDatum (const ksi::datum & d);
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

      /** @return a fuzzy number in row and column
       *  @param row row number 
       *  @param col column number 
       *  @exception ksi::exception if invalid row or col
       *  @date 2019-01-21
       */
      ext_fuzzy_number_gaussian getFuzzyNumber (std::size_t row, std::size_t col) const ;
      
      
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
      
      /** @return a matrix of data 
       * @param dummy dummy parameter, used only to distinguish methods, exactly the same as getMatrix()
       * @exception ksi::exception if some data do not exists */
      std::vector<std::vector<double>> getMatrix (double dummy) const ;

      /** @return a matrix of data 
       * @exception ksi::exception if some data do not exists
       * @date 2019-01-21
       */
      std::vector<std::vector<ext_fuzzy_number_gaussian>> getMatrixOfFuzzyNumbers () const ;
      
      /** @return a matrix of data 
       * @param dummy dummy parameter, used only to distinguish methods
       * @exception ksi::exception if some data do not exists
       * @date 2019-01-22
       */
      std::vector<std::vector<ext_fuzzy_number_gaussian>> getMatrix(ext_fuzzy_number_gaussian) const ;
      
            
      /** A method get r-th datum from the dataset. The method does not copy the datum!
       * @return a pointer to the datum or nullptr if r is illegal 
       * @param  r index of datum 
       * @date 2018-01-04
       */
      const datum * getDatum (std::size_t r) const ;
      
      /** A method get r-th datum from the dataset. The method does not copy the datum!
       * @return a pointer to the datum or nullptr if r is illegal 
       * @param  r index of datum 
       * @date 2018-01-04
       */
      datum * getDatumNonConst (std::size_t r) const;

      /** The method splits horizontally the dataset into two datasets.
       * The first dataset has number_of_items.
       * The second dataset has the other data.
       * The original dataset is not modified.
       * @param number_of_items number of items in the first dataset to return
       * @return a pair of datasets  
       * @date 2019-07-19
       */
      std::pair<dataset, dataset> splitDataSetHorizontally (std::size_t number_of_items) const ;
      
      
      /** The method splits vertically the dataset into two datasets.
       * The first dataset has attributes 0 .. last_index.
       * The second dataset has attributes last_index + 1, .. number_of_attributes - 1. The original dataset is not modified.
       * If start_index > end_index, an empty dataset is returned
       * @param last_index index of the last attribute in the first dataset to return
       * @return a pair of datasets  
       */
      std::pair<dataset, dataset> splitDataSetVertically (std::size_t last_index) const ;
      
      
      /** The method cuts of the last attribute of all data.
       @return a pair of datasets: first -- data set with all attributes but last, second -- data set with only the last attribute
       @date 2019-07-18
       */
      std::pair<dataset, dataset> cufOffLastAttribute () const ;
      
      
      /** @return The method return a subdataset composed of copies of data with indices in range [start_index, end_index].
       * If end_index is larger than maximal index in the data set, it is reset to the maximal possible index in the dataset.
       * @date 2019-02-27
       */
      dataset subdataset (const std::size_t start_index, const std::size_t end_index) const;
      
      /** return maximal numerical label of data items */
      std::size_t getMaximalNumericalLabel () const;
      
      /** simply sets maximal numerical label of data items  */
      void setMaximalNumericalLabel (std::size_t id);
      
      /** The method reset id's of data items from 0 to max - 1. **/
      void resetIDs ();
      
      /** The method removes untypical data.
       @param minimal_typicality minimal acceptable typicality of data 
       @date 2020-01-04
       */
      void remove_untypical_data (const double minimal_typicality);

      /** The method removes untypical data.
       @param typical_data a vector of bools: true stands for a typical datum, false -- for untypical
       @throw ksi::exception if the lenght of the typical_data vector does not match the size of the dataset
       @date 2020-01-04
       */
      void remove_untypical_data (const std::vector<bool> & typical_data);
      
       /** @return a vector with true for typical datum or false for untypical
       @param minimal_typicality minimal acceptable typicality of data 
       @date 2020-01-04
       */
      std::vector<bool> get_if_data_typical (const double minimal_typicality);
      
      
      friend std::ostream & operator << (std::ostream & s, const dataset & d);
   };
}


#endif
