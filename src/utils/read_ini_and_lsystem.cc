#include "read_ini_and_lsystem.h"

LParser::LSystem2D read_lsystem_from_file(const ini::Configuration &configuration)
{
    // get input file from configuration
    std::string lsystem_input_file_name = configuration["2DLSystem"]["inputfile"];
    lsystem_input_file_name = "./inputfiles/" + lsystem_input_file_name;

    // read the LSytem2D file and forward it to l2d
    std::ifstream lsystem_file(lsystem_input_file_name);
    if (lsystem_file.peek() == std::istream::traits_type::eof())
    {
        std::cout << "Ini file appears empty. Does '" << lsystem_input_file_name << "' exist?" << std::endl;
    }

    // Read the entire file contents
    std::string file_content;
    std::getline(lsystem_file, file_content, '\0');

    // Replace all occurrences of "[ , ]" with "( , )" using `std::replace`
    std::replace(file_content.begin(), file_content.end(), '[', '(');
    std::replace(file_content.begin(), file_content.end(), ']', ')');

    // Create a stringstream to hold the modified file content
    std::stringstream modified_content_stream;
    modified_content_stream << file_content;

    // Pass the stringstream to LSystem2D for parsing

    LParser::LSystem2D l2d;

    modified_content_stream >> l2d;

    lsystem_file.close();

    return l2d;
}