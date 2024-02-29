#include "easy_image.h"
#include "ini_configuration.h"
#include "debug_tools.h"
#include "my_utils.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

img::EasyImage generate_image(const ini::Configuration &configuration)
{
        int width = configuration["ImageProperties"]["width"].as_int_or_die();
        int height = configuration["ImageProperties"]["height"].as_int_or_die();

        img::EasyImage image(width, height);
        for (unsigned int i = 0; i < width; i++)
        {
                for (unsigned int j = 0; j < height; j++)
                {
                        image(i, j) = img::Color(i % 256, j % 256, (i + j) % 256);
                }
        }

        return image;
}

int main(int argc, char const *argv[])
{
        // for vscode debugging purposes, it gives "debug.ini" as first argument
        int debug_argc;
        const char **debug_argv;
        std::tie(debug_argc, debug_argv) = debug_tools::GET_DEBUG_ARGUMENTS(argc, argv);
        argc = debug_argc;
        argv = debug_argv;

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
                                        // Klasör yolunu alıyoruz.
                                        std::string directory = fileName.substr(0, folder_pos);

                                        // Klasörü oluşturuyoruz (eğer daha önce oluşturulmadıysa).
                                        if (!createDirectory(directory))
                                        {
                                                return 1; // Klasör oluşturma başarısız olduğunda programı sonlandırıyoruz.
                                        }
                                }

                                try
                                {
                                        std::ofstream f_out(fileName.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;
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
