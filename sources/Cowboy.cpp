#include "Cowboy.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    // Ctors & Dtors:
    Cowboy::Cowboy(std::string name, Point characterLoction)
        : Character(name, characterLoction), _bulletAmount(BULLETAMOUNT)
    {
        setHP(COWBOY_HP);
    }

    // Cowboy::~Cowboy()
    // {
    // }

    // functions to implement:
    void Cowboy::shoot(Character *enemy)
    {
        // can't shoot a dead enemy (why not?). can't shoot if dead. can't shoot self
        if (!(enemy->isAlive()) || !(isAlive()) || this == enemy)
        {
            throw std::runtime_error("can't shoot a dead enemy | dead cowboy can't shoot | can't shoot self");
        }

        if (hasboolets())
        {
            enemy->hit(10);
            _bulletAmount -= 1;
        }
    }
    bool Cowboy::hasboolets() const { return _bulletAmount > 0; }

    void Cowboy::reload()
    {
        // can't reload if dead
        if (!(isAlive()))
        {
            throw std::runtime_error("dead cowboy can't reload");
        }

        // else reload:
        _bulletAmount = BULLETAMOUNT;
    }
    string Cowboy::print() const
    {
        if (isAlive())
        {
            cout << "C " << getName() << " " << getHP() << " (" << getLocation().getX() << "," << getLocation().getY() << ")" << endl;
            return "C " + getName() + " " + to_string(getHP()) + " (" + to_string(getLocation().getX()) + "," + to_string(getLocation().getY()) + ") \n";
        }

        // else hitPoints = 0:
        cout << "C (" << getName() << ") "
             << "(" << getLocation().getX() << "," << getLocation().getY() << ")" << endl;
        return "C (" + getName() + ") " + "(" + to_string(getLocation().getX()) + "," + to_string(getLocation().getY()) + ")\n";
    }

    // my added functions:
    void Cowboy::attackTarget(Character *enemy)
    {
        if (!(hasboolets()))
        {
            reload();
        }
        else
        {
            shoot(enemy);
        }
    }

} // namespace ariel
