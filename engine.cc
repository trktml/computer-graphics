#include "headers.h"

img::EasyImage generate_image(const ini::Configuration &configuration)
{
        LParser::LSystem2D l2d = read_lsystem_from_file(configuration);

        int size = configuration["General"]["size"].as_int_or_die();

        ini::DoubleTuple backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();

        ini::DoubleTuple color = configuration["2DLSystem"]["color"].as_double_tuple_or_die();

        img::EasyImage image(size, size, img::Color(backgroundcolor.at(0), backgroundcolor.at(1), backgroundcolor.at(2)));

        printLSystemInfo(l2d);

        std::string lsystem_string = get_lsystem_string_after_iterations(l2d);

        const int fixed_step = 5;
        double angle = l2d.get_starting_angle();

        std::stack<Point2D> point_stack;

        int x_max = 0, x_min = std::numeric_limits<int>::max(), y_max = 0, y_min = std::numeric_limits<int>::max();

        Point2D point(0, 0);
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
                case '(':
                        point_stack.push(point);
                        break;
                case ')':
                        point = point_stack.top();
                        break;
                default:
                        double x = point.x + std::cos((int(angle) % 360) * M_PI / 180) * fixed_step;
                        double y = point.y + std::sin((int(angle) % 360) * M_PI / 180) * fixed_step;
                        Point2D newPoint(x, y);
                        line.p1 = point;
                        line.p2 = newPoint;

                        x_max = std::max(x_max, static_cast<int>(x));
                        x_min = std::min(x_min, static_cast<int>(x));
                        y_max = std::max(y_max, static_cast<int>(y));
                        y_min = std::min(y_min, static_cast<int>(y));

                        point = newPoint;
                        break;
                }
        }

        int image_width = x_max - x_min + 1;
        int image_height = y_max - y_min + 1;

        float scale_factor = 1.0f;
        if (image_width > 1500 || image_height > 1500)
        {
                float max_dimension = std::max(image_width, image_height);
                scale_factor = 1500.0f / max_dimension;
        }
        scale_factor *= 0.95f;

        int x_offset = -x_min;
        int y_offset = -y_min;

        point.x = 0;
        point.y = 0;

        angle = l2d.get_starting_angle();
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
                case '(':
                        point_stack.push(point);
                        break;
                case ')':
                        point = point_stack.top();
                        break;
                default:
                        double x = point.x + std::cos((int(angle) % 360) * M_PI / 180) * fixed_step;
                        double y = point.y + std::sin((int(angle) % 360) * M_PI / 180) * fixed_step;

                        Point2D newPoint(x + x_offset, y + y_offset);

                        line.p1.x = point.x + x_offset;
                        line.p1.y = point.y + y_offset;

                        line.p2 = newPoint;

                        if (l2d.draw(c))
                        {
                                int scaled_x1 = static_cast<int>((line.p1.x) * scale_factor);
                                int scaled_y1 = static_cast<int>((line.p1.y) * scale_factor);
                                int scaled_x2 = static_cast<int>((line.p2.x) * scale_factor);
                                int scaled_y2 = static_cast<int>((line.p2.y) * scale_factor);

                                image.draw_line(scaled_x1, scaled_y1, scaled_x2, scaled_y2, img::Color(color.at(0), color.at(1), color.at(2)));
                        }

                        point.x = newPoint.x;
                        point.y = newPoint.y;
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
                                fix_file_path(fileName);

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
                        catch (std::exception &ex)
                        { // Catch other standard library exceptions
                                std::cerr << "Caught exception: " << ex.what() << std::endl;
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
                                        fix_file_path(fileName);
                                        size_t folder_pos = fileName.find_last_of('/'); // TO-DO not working on windows
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