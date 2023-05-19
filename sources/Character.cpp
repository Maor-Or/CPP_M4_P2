#include "Character.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    // Ctors & Dtors:
    Character::Character(string name, Point characterLoction)
        : _name(name), _location(characterLoction), _hitPoints(0)
    {
    }

    Character::~Character()
    {
    }

    // functions to implement:
    bool Character::isAlive() const { return _hitPoints > 0; }
    double Character::distance(Character *p_other) const
    {
        return this->getLocation().distance(p_other->getLocation());
    }
    void Character::hit(int dmg)
    {
        _hitPoints -= dmg;
        if (_hitPoints < 0)
        {
            _hitPoints = 0;
        }
    }
    string Character::getName() const { return _name; }
    Point Character::getLocation() const { return _location; }
    string Character::print() const
    {
        if (isAlive())
        {
            cout << "(" << _name << ") " << _hitPoints << " (" << _location.getX() << "," << _location.getY() << ")" << endl;
            return "(" + _name + ") " + to_string(_hitPoints) + " (" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ") \n";
        }

        // else hitPoints = 0:
        cout << "(" << _name << ") "
             << "(" << _location.getX() << "," << _location.getY() << ")" << endl;
        return "(" + _name + ") " + "(" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ")\n";
    }

    // my added functions:
    void Character::attackTarget(Character *enemy) {printf("Character attack is called...");}

}; // namespace ariel