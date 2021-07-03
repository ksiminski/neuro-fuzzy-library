
#include <filesystem>
#include <string>

#include "./directory.h"
#include "../service/debug.h"


bool ksi::directory::create_directory_for_file(const std::string & file_path)
{
   std::filesystem::path sciezka_pliku (file_path);
   auto sciezka_katalogu = sciezka_pliku.parent_path();
   if (not std::filesystem::exists(sciezka_katalogu))
      return std::filesystem::create_directories(sciezka_katalogu);
   else 
      return true;
}

