#include <iostream>
#include "Point.hpp"
#include <math.h>
#include <string>
using namespace std;

namespace ariel
{

    // Ctors & Dtors:
    Point::Point(double xloc, double yloc) : _xLoc(xloc), _yLoc(yloc)
    {
    }
    Point::Point(const Point &other) : _xLoc(other.getX()), _yLoc(other.getY())
    {
    }

    Point::~Point()
    {
    }

    // Move Constructor
    Point::Point(Point &&other) noexcept
        : _xLoc(other._xLoc), _yLoc(other._yLoc)
    {
        // Move any necessary resources from 'other' to 'this'
    }

    // Move Assignment Operator
    Point &Point::operator=(Point &&other) noexcept
    {
        if (this != &other)
        {
            // Move any necessary resources from 'other' to 'this'
            _xLoc = other._xLoc;
            _yLoc = other._yLoc;
        }
        return *this;
    }

    // functions to implement:
    double Point::distance(Point other) const
    {
        return sqrt(pow((_xLoc - other.getX()), 2) + pow((_yLoc - other.getY()), 2));
    }
    void Point::print() { std::cout << "(" << _xLoc << "," << _yLoc << ")\n"; }
    Point Point::moveTowards(Point origin, Point destination, double distance)
    {
        // negative distance is invalid:
        if (distance < 0)
        {
            throw std::invalid_argument("Invalid argument: value must be non-negative");
        }

        double currDistance = origin.distance(destination);

        if (distance == 0 || currDistance == 0)
        {
            return origin;
        }

        if (currDistance <= distance)
        {
            return destination;
        }

        double ratio = distance / currDistance;

        double new_xLoc_location =
            origin.getX() + (destination.getX() - origin.getX()) * ratio;

        double new_yLoc_location =
            origin.getY() + (destination.getY() - origin.getY()) * ratio;

        // Point p_res(new_xLoc_location, new_yLoc_location);
        // return p_res;
        return {new_xLoc_location, new_yLoc_location};
    }

    // my added functions:
    double Point::getX() const { return _xLoc; }
    double Point::getY() const { return _yLoc; }
    Point &Point::operator=(const Point &other)
    {
        _xLoc = other._xLoc;
        _yLoc = other._yLoc;
        return *this;
    }
    void Point::setX(double newx) { _xLoc = newx; }
    void Point::setY(double newy) { _yLoc = newy; }

};
