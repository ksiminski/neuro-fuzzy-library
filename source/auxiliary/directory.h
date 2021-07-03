

#ifndef DIRECTORY_H 
#define DIRECTORY_H

#include <filesystem>
#include <string>

namespace ksi 
{
    class directory 
    {
    public:
        /** The function creates directories for the file, eg. for file "a/b/c/file" a hierarchy of directories "a/b/c" is created.
         @param file_path a path of a file to create a directory for
         @return true, if directory exists or has been successfully created, false -- otherwise
         */
        static bool create_directory_for_file (const std::string & file_path); 
    };
}


#endif
