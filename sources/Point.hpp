#pragma once

namespace ariel
{
    class Point
    {
    private:
        double _xLoc, _yLoc;

    public:
        // Ctors & Dtors:
        Point(double xloc, double yloc);
        Point(const Point &other);
        ~Point();

        // Move Constructor
        Point(Point &&other) noexcept;

        // Move Assignment Operator
        Point &operator=(Point &&other) noexcept;

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
