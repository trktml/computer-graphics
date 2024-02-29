#include "debug_tools.h"

#ifdef NDEBUG
#define DEBUG_MODE false
#else
#define DEBUG_MODE true
#endif

namespace debug_tools
{
    std::tuple<int, const char **> GET_DEBUG_ARGUMENTS(int argc, const char *argv[])
    {

#if DEBUG_MODE
        int const default_argc = 2;
        char const *default_args[] = {argv[0], "./ini/debug.ini"};
        if (argc == 1) // no arguments were passed
        {
            // do things for no arguments

            // usually those variables are set here for a generic flow onwards
            argc = default_argc;
            argv = default_args;
        }

        char buffer[FILENAME_MAX];
        if (getcwd(buffer, FILENAME_MAX) != nullptr)
        {
            std::cout << "Current directory: " << buffer << std::endl;
        }
        else
        {
            std::cerr << "Error getting current directory" << std::endl;
        }
#endif

        return std::make_tuple(argc, argv);
    }
}