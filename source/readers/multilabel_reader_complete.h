
#ifndef MULTILABEL_READER_COMPLETE_H
#define MULTILABEL_READER_COMPLETE_H

#include <memory>

#include "../readers/reader-complete.h"

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
   class multilabel_reader_complete : public reader_complete
   {
   protected:
       const char SEPARATOR { '|' };
       
       /** The method extract values and creates a new datum with them.
        @param attributes numerical attributes (before |)
        @param labels     extra value (after |)
        @date 2022-05-18
        @author Krzysztof Siminski
        */
       virtual datum extract_values(const std::string & attributes, const std::string & labels);
    public:
      multilabel_reader_complete ();
      multilabel_reader_complete (const multilabel_reader_complete & wzor);
      multilabel_reader_complete (multilabel_reader_complete && wzor);
      multilabel_reader_complete & operator= (const multilabel_reader_complete & wzor);
      multilabel_reader_complete & operator= (multilabel_reader_complete && wzor);
      virtual ~multilabel_reader_complete ();
      
      virtual dataset read(const std::string& filename);
      
      /** The prototype design pattern. */
      virtual std::shared_ptr<reader> clone() const; 
      
      
   };
}


#endif
