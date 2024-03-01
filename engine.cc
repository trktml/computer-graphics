#include "utils.h"

img::EasyImage generate_image(const ini::Configuration &configuration)
{
        // get the file name from the configuration

        // [General]
        // type = "2DLSystem"
        // size = 1000
        // backgroundcolor = (0.0, 0.0, 0.0)
        int size = configuration["General"]["size"].as_int_or_die();

        ini::DoubleTuple backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();

        // [2DLSystem]
        // inputfile = "Koch.L2D"
        // color = (0.5, 1, 0)

        // get input file from configuration
        std::string lsystem_input_file_name = configuration["2DLSystem"]["inputfile"];
        lsystem_input_file_name = "./inputfiles/" + lsystem_input_file_name;

        // get color from configuration and convert it to a vector of doubles
        ini::DoubleTuple color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();

        // read the LSytem2D file and forward it to l2d
        std::ifstream lsystem_file(lsystem_input_file_name);
        if (lsystem_file.peek() == std::istream::traits_type::eof())
        {
                std::cout << "Ini file appears empty. Does '" << lsystem_input_file_name << "' exist?" << std::endl;
        }

        LParser::LSystem2D l2d;

        lsystem_file >> l2d;
        lsystem_file.close();

        img::EasyImage image(size, size, img::Color(backgroundcolor.at(0), backgroundcolor.at(1), backgroundcolor.at(2)));

        // l2d.get_alphabet() is a set of strings
        // print values
        const std::set<char> alphabet = l2d.get_alphabet();
        std::cout << "Alphabet: " << std::endl;
        for (char s : alphabet)
        {
                std::cout << s << std::endl;
        }

        for (size_t i = 0; i < 200; i++)
                image.draw_line(i, 0, size - 1, size - i - 1, img::Color(255, 0, 0));
        for (size_t i = 0; i < 200; i++)
                image.draw_line(0, i, size - i - 1, size - 1, img::Color(0, 255, 0));
        return image;
}

int main(int argc, char const *argv[])
{
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv + 1, argv + argc);
                if (args.empty())
                {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName))
                        {
                                args.push_back(filelistName);
                        }
                }
                for (std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                if (fin.peek() == std::istream::traits_type::eof())
                                {
                                        std::cout << "Ini file appears empty. Does '" << fileName << "' exist?" << std::endl;
                                        continue;
                                }
                                fin >> conf;
                                fin.close();
                        }
                        catch (ini::ParseException &ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        // log
                        std::cout << "Generated image of size " << image.get_height() << " x " << image.get_width() << std::endl;
                        if (image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if (pos == std::string::npos)
                                {
                                        // filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0, pos) + ".bmp";
                                }
                                std::string::size_type slash = fileName.rfind('/');
                                if (slash != std::string::npos)
                                {
                                        fileName = "./outputs/" + fileName.substr(slash + 1);
                                }

                                size_t folder_pos = fileName.find_last_of('/');
                                if (folder_pos != std::string::npos)
                                {
                                        // We get the folder path.
                                        std::string directory = fileName.substr(0, folder_pos);

                                        // We create the folder (if it has not been created before).
                                        createDirectory(directory);
                                }

                                try
                                {
                                        std::ofstream f_out(fileName.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;
                                        f_out.close();
                                }
                                catch (std::exception &ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch (const std::bad_alloc &exception)
        {
                // When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
                // Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
                //(Unless of course you are already consuming the maximum allowed amount of memory)
                // If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
                // mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}
