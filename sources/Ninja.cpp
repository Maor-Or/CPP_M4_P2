#include "Ninja.hpp"

#include <string>
#include <iostream>

using namespace std;

namespace ariel
{

    // Ctors & Dtors:
    Ninja::Ninja(std::string name, Point characterLoction)
        : Character(name, characterLoction), _speed(0)
    {
    }


    // functions to implement:
    void Ninja::move(const Character *enemy)
    {
        setLocation(Point::moveTowards(getLocation(), enemy->getLocation(), _speed));
    }

    void Ninja::slash(Character *enemy) const
    {
        // can't slash a dead enemy (why not?). can't slash self. can't slash if dead
        if (!(enemy->isAlive()) || enemy == this || !(isAlive()))
        {
            throw std::runtime_error("can't shoot a dead enemy | dead cowboy can't shoot | can't shoot self");
        }

        double distance = getLocation().distance(enemy->getLocation());

        if (isAlive() && distance < 1)
        {
            enemy->hit(40);
        }
    }

    string Ninja::print() const
    {
        if (isAlive())
        {
            cout << "N " << getName() << " " << getHP() << " (" << getLocation().getX() << "," << getLocation().getY() << ")" << endl;
            return "N " + getName() + " " + to_string(getHP()) + " (" + to_string(getLocation().getX()) + "," + to_string(getLocation().getY()) + ") \n";
        }

        // else hitPoints = 0:
        cout << "N (" << getName() << ") "
             << "(" << getLocation().getX() << "," << getLocation().getY() << ")" << endl;
        return "N (" + getName() + ") " + "(" + to_string(getLocation().getX()) + "," + to_string(getLocation().getY()) + ")\n";
    }

    // my added functions:
    void Ninja::attackTarget(Character *enemy)
    {
        if (distance(enemy) < 1)
        {
            slash(enemy);
        }
        else
        {
            move(enemy);
        }
    }

    //getters & setters:
    int Ninja::getSpeed() const
    {
        return _speed;
    }

    void Ninja::setSpeed(int newSpeed)
    {
        _speed = newSpeed;
    }

} // namespace ariel
