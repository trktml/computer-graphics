#include <tuple>
#include <iostream>
#include <string>
#include <unistd.h>

namespace debug_tools
{
    std::tuple<int, const char **> GET_DEBUG_ARGUMENTS(int argc, const char *argv[]);
}