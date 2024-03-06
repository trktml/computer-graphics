#include "utils.h"

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

bool fix_file_path(std::string &filePath)
{
    // Is the file path empty?
    if (filePath.empty())
    {
        throw "File path is empty!";
        return false;
    }

    std::filesystem::path path(filePath);

    // Fix the file path
    filePath = std::filesystem::canonical(path).string();

    return true;
}

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

void printLSystemInfo(const LParser::LSystem2D &l2d)
{
    const std::string initiator = l2d.get_initiator();
    std::cout << "İnitiator: " << std::endl;
    std::cout << initiator << std::endl;

    const std::set<char> &alphabet = l2d.get_alphabet();
    std::cout << "Alphabet: " << std::endl;
    for (const auto &s : alphabet)
    {
        std::cout << s << std::endl;
    }
}

std::string get_lsystem_string_after_iterations(LParser::LSystem2D &l2d)
{
    std::string lsystem_string;
    for (size_t i = 0; i < l2d.get_nr_iterations(); i++)
    {
        std::string current_lsystem_string = lsystem_string;
        lsystem_string = "";
        for (char c : current_lsystem_string)
        {
            switch (c)
            {
            case '+':
                lsystem_string += "+";
                break;
            case '-':
                lsystem_string += "-";
                break;
            case '[':
                lsystem_string += "[";
                break;
            case ']':
                lsystem_string += "]";
                break;
            case '(':
                lsystem_string += "(";
                break;
            case ')':
                lsystem_string += ")";
                break;
            default:
                lsystem_string += l2d.get_replacement(c);
                break;
            }
        }
    }
    return lsystem_string;
}