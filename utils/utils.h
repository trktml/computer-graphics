#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>

#include "easy_image.h"
#include "ini_configuration.h"
#include "l_parser.h"

bool createDirectory(const std::string &path);