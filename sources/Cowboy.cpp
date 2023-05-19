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
        if (isAlive()&&hasboolets())
        {
            enemy->hit(10);
            _bulletAmount -= 1;
        }
        
    }
    bool Cowboy::hasboolets() const {return _bulletAmount > 0;}
    void Cowboy::reload() {_bulletAmount = BULLETAMOUNT;}
    string Cowboy::print() const
    {
        if (isAlive())
        {
            cout <<"C ("<< _name <<") "<< _hitPoints << " (" << _location.getX() << "," << _location.getY() << ")"<<endl ;
            return "C (" + _name + ") " +  to_string(_hitPoints) + " (" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ") \n";
        }

        //else hitPoints = 0:
        cout <<"C ("<< _name <<") "<< "(" << _location.getX() << "," << _location.getY() << ")"<<endl ;
        return "C (" + _name + ") " + "(" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ")\n" ;
    }

    //my added functions:
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
