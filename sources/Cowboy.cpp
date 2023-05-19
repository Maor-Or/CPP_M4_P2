#include "Cowboy.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    // constructors:
    Cowboy::Cowboy(std::string name, Point characterLoction)
        : Character(name, characterLoction), _bulletAmount(BULLETAMOUNT)
    {
        _hitPoints = COWBOY_HP;
    }

    Cowboy::~Cowboy()
    {
    }

    // functions to implement:
    void Cowboy::shoot(Character *enemy)
    {
        // can't shoot a dead enemy (why not?). can't shoot if dead. can't shoot self
        if (!(enemy->isAlive())||!(isAlive())||this ==enemy)
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
        _bulletAmount = BULLETAMOUNT;
    }
    string Cowboy::print() const
    {
        if (isAlive())
        {
            cout << "C (" << _name << ") " << _hitPoints << " (" << _location.getX() << "," << _location.getY() << ")" << endl;
            return "C (" + _name + ") " + to_string(_hitPoints) + " (" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ") \n";
        }

        // else hitPoints = 0:
        cout << "C (" << _name << ") "
             << "(" << _location.getX() << "," << _location.getY() << ")" << endl;
        return "C (" + _name + ") " + "(" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ")\n";
    }

    // my added functions:
    void Cowboy::attackTarget(Character *enemy)
    {
        // printf("in cowboy attack:\n");

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
