
#include "headers.h"

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

img::EasyImage generate_image(const ini::Configuration &configuration)
{
        LParser::LSystem2D l2d = read_lsystem_from_file(configuration);

        int size = configuration["General"]["size"].as_int_or_die();

        ini::DoubleTuple backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();

        ini::DoubleTuple color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();

        img::EasyImage image(size, size, img::Color(backgroundcolor.at(0), backgroundcolor.at(1), backgroundcolor.at(2)));

        printLSystemInfo(l2d);

        std::string lsystem_string = l2d.get_initiator();
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
        std::cout << "lsystem_string: " << lsystem_string << " ";

        double startingAngle = l2d.get_starting_angle();

        const int fixed_step = 15;
        double angle = startingAngle;

        Point2D point(600, 10);
        Line2D line;
        for (const char c : lsystem_string)
        {
                switch (c)
                {
                case '+':
                        angle += l2d.get_angle();
                        break;
                case '-':
                        angle -= l2d.get_angle();
                        break;
                case '[':
                        break;
                case ']':
                        break;
                default:
                        double x = point.x + std::cos((int(angle) % 360) * M_PI / 180) * fixed_step;
                        double y = point.y + std::sin((int(angle) % 360) * M_PI / 180) * fixed_step;
                        Point2D newPoint(x, y);
                        line.p1 = point;
                        line.p2 = newPoint;

                        std::cout << "p1.x: " << line.p1.x << ", p1.y: " << line.p1.y << ", p2.x: " << line.p2.x << ", p2.y: " << line.p2.y << std::endl;
                        image.draw_line(abs(line.p1.x), abs(line.p1.y), abs(line.p2.x), abs(line.p2.y), img::Color(color.at(0), color.at(1), color.at(2)));
                        point = newPoint;
                        break;
                }
        }

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

                                try
                                {
                                        size_t folder_pos = fileName.find_last_of('/');
                                        if (folder_pos != std::string::npos)
                                        {
                                                // We get the folder path.
                                                std::string directory = fileName.substr(0, folder_pos);

                                                // We create the folder (if it has not been created before).
                                                createDirectory(directory);
                                        }

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
