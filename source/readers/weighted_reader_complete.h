
#ifndef WEIGHTED_READER_COMPLETE_H
#define WEIGHTED_READER_COMPLETE_H

#include <memory>

#include "../readers/multilabel_reader_complete.h"

namespace ksi
{
    /** The class reads complete data from a file. Each datum is tagged with a sequence of labels. 
     Numerical attributes are separated from symbolical labels with a bar '|'. Eg:
     1.2 5.6 7.8 | A B
     There are three atributes: 1.2 and 5.6 and 7.8.
     There are two labels: A and B.
     
     @author Krzysztof Siminski
     @date 2022-05-15
     */
   class weighted_reader_complete : public multilabel_reader_complete
   {
   protected:
       
       
       /** The method extract values and creates a new datum with them.
        @param attributes numerical attributes (before |)
        @param weight     weight as a string (after |)
        @date 2022-05-18
        @author Krzysztof Siminski
        */
       virtual datum extract_values(const std::string & attributes, const std::string & labels);
    public:
      weighted_reader_complete ();
      weighted_reader_complete (const weighted_reader_complete & wzor);
      weighted_reader_complete (weighted_reader_complete && wzor);
      weighted_reader_complete & operator= (const weighted_reader_complete & wzor);
      weighted_reader_complete & operator= (weighted_reader_complete && wzor);
      virtual ~weighted_reader_complete ();
      
       
      
      /** The prototype design pattern. */
      virtual std::shared_ptr<reader> clone() const; 
      
      
   };
}


#endif
