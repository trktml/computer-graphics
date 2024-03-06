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
#include <list>

#ifdef _WIN32
#include <direct.h>
#endif

#include "l_parser.h"
#include "ini_configuration.h"

LParser::LSystem2D read_lsystem_from_file(const ini::Configuration &configuration);

bool fix_file_path(std::string &filePath);

bool createDirectory(const std::string &path);

void printLSystemInfo(const LParser::LSystem2D &l2d);

std::string get_lsystem_string_after_iterations(LParser::LSystem2D &l2d);