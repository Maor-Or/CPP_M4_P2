#pragma once
#include "Point.hpp"
#include <string>
namespace ariel
{
    class Character
    {
    protected:

        Point _location;
        int _hitPoints;
        std::string _name;
        bool _isInTeam;

    public:
       
           // Ctors & Dtors:
        Character(std::string name, Point characterLoction);
       virtual ~Character();

        // functions to implement:
        bool isAlive() const;
        double distance(Character *p_other) const;
        void hit(int dmg);
        std::string getName() const;
        Point getLocation() const;
        virtual std::string print() const;

        // my added functions:
        virtual void attackTarget(Character *enemy) = 0;
        void setIsInTeam();
        bool getIsInTeam() const;
    };
} // namespace ariel
