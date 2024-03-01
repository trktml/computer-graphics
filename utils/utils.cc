#include "utils.h"

// Bu fonksiyon, verilen dizini oluşturur.
bool createDirectory(const std::string &path)
{
#ifdef _WIN32
    if (_mkdir(path.c_str()) != 0)
    {
        // std::cerr << "Error creating directory: " << path << std::endl;
        return false;
    }
#else
    if (mkdir(path.c_str(), 0777) != 0)
    {
        // std::cerr << "Error creating directory: " << path << std::endl;
        return false;
    }
#endif
    return true;
}