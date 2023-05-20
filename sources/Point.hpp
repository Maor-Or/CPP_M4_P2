#pragma once

namespace ariel
{
    class Point
    {
    private:
        double _x, _y;

    public:
        // Ctors & Dtors:
        Point(double x, double y);
        Point(const Point &other);
        ~Point();

        // functions to implement:
        double distance(Point other) const; // sqrt((x1-x2)^2 +(y1-y2)^2)
        void print();
        static Point moveTowards(Point origin, Point destination, double distance);

        // my added functions:
        double getX() const;
        double getY() const;
        Point &operator=(const Point &other);
        void setX(double newx);
        void setY(double newy);
    };

}; // namespace ariel
