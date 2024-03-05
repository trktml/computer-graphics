struct Point2D
{
    double x;
    double y;

    Point2D() : x(0), y(0) {}
    Point2D(double x_val, double y_val) : x(x_val), y(y_val) {}
};

struct Color
{
    double red;
    double green;
    double blue;

    Color() : red(0), green(0), blue(0) {}
    Color(double r, double g, double b) : red(r), green(g), blue(b) {}
};

struct Line2D
{
    Point2D p1;
    Point2D p2;
    Color color;

    Line2D() : p1(), p2(), color() {}
    Line2D(Point2D point1, Point2D point2, Color lineColor) : p1(point1), p2(point2), color(lineColor) {}
};
