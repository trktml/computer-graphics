#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#endif

#include "l_parser.h"
#include "ini_configuration.h"

LParser::LSystem2D read_lsystem_from_file(const ini::Configuration &configuration);

bool fix_file_path(std::string &filePath);

bool createDirectory(const std::string &path);