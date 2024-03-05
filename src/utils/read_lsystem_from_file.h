#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cmath>
#include <tuple>

#include "l_parser.h"
#include "ini_configuration.h"

LParser::LSystem2D read_lsystem_from_file(const ini::Configuration &configuration);