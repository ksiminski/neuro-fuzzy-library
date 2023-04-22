/** @file */ 

#ifndef GRFCM_H
#define GRFCM_H

 
#include <vector> 
#include <string>
#include "../auxiliary/definitions.h"
#include "../partitions/partitioner.h"
#include "../partitions/partition.h"
#include "../partitions/fcm-T.h"
#include "../partitions/fcm.h"
#include "../common/dataset.h"
#include "../common/extensional-fuzzy-number-gaussian.h"


namespace ksi
{
   /** The class implements Granular Fuzzy C-means clustering algorithm. */
   class grfcm : virtual public fcm_T<ext_fuzzy_number_gaussian>
   {
   protected:
       /** maximal number of data items in one part of data */
       int _max_number_of_dataitems_in_a_part;
       /** input file name to read data from */
       std::string _input_file_name;

       
   public: 
       /** @param MAXIMAL_NUMBER_OF_DATAITEMS_IN_A_PART maximal number of data items read in one part 
           @param INPUT_FILE_NAME input file name 
           @param EPSILON epsilon value for comparison of membership matrix values in two consecutive iterations, the lower the value, the more iterations are needed*/
       grfcm (const int MAXIMAL_NUMBER_OF_DATAITEMS_IN_A_PART, const std::string & INPUT_FILE_NAME, const double EPSILON);
       grfcm (const grfcm & wzor); 
       grfcm (grfcm && wzor); 
      
       grfcm & operator = (const grfcm & wzor); 
       grfcm & operator = (grfcm && wzor); 
       virtual ~grfcm ();  
      
       virtual partitioner * clone () const;
      
       /** @param ds it is just a dummy parameter, it is not used */
       virtual ksi::partition doPartition(const ksi::dataset & ds);
      
       /** @return an abbreviation of a method */
       virtual std::string getAbbreviation () const;
   };

}

#endif

