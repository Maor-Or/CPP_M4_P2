#include "Ninja.hpp"

#include <string>
#include <iostream>

using namespace std;

namespace ariel
{

    // constructors:
    Ninja::Ninja(std::string name, Point characterLoction)
        : Character(name, characterLoction), _speed(0)
    {
    }

    Ninja::~Ninja()
    {
    }

    // functions to implement:
    void Ninja::move(const Character *enemy)
    {//TODO: fix this, copy func on point isnt working 
        double newx = Point::moveTowards(_location, enemy->getLocation(), _speed).getX();
        double newy = Point::moveTowards(_location, enemy->getLocation(), _speed).getY();
       cout<< to_string(newx) <<to_string(newy)<<endl;
       _location.setX(newx);
       _location.setY(newy);
    }

    void Ninja::slash(Character *enemy) const
    {
        //can't slash a dead enemy (why not?). can't slash if dead. can't slash self
        if (!(enemy->isAlive())||enemy == this||!(isAlive()))
        {
            throw std::runtime_error("can't shoot a dead enemy | dead cowboy can't shoot | can't shoot self");
        }

        double distance = _location.distance(enemy->getLocation());

        if (isAlive() && distance < 1)
        {
            enemy->hit(40);
        }
    }

    string Ninja::print() const
    {
        if (isAlive())
        {
            cout << "N (" << _name << ") " << _hitPoints << " (" << _location.getX() << "," << _location.getY() << ")" << endl;
            return "N (" + _name + ") " + to_string(_hitPoints) + " (" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ") \n";
        }

        // else hitPoints = 0:
        cout << "N (" << _name << ") "
             << "(" << _location.getX() << "," << _location.getY() << ")" << endl;
        return "N (" + _name + ") " + "(" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ")\n";
    }

    // my added functions:
    void Ninja::attackTarget(Character *enemy)
    {
        // printf("in ninja attack:\n");
        if (distance(enemy)<1)
        {
            slash(enemy);
        }
        else
        {
            move(enemy);
        }
    }

} // namespace ariel
