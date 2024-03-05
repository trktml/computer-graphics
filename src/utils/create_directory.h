#ifdef _WIN32
#include <direct.h>
#endif
#include <string>
#include <iostream>
#include <sys/stat.h>

bool createDirectory(const std::string &path);