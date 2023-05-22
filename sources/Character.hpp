#pragma once
#include "Point.hpp"
#include <string>
namespace ariel
{
    class Character
    {
    private:
        Point _location;
        int _hitPoints;
        std::string _name;
        bool _isInTeam;

    public:
        // Ctors & Dtors:
        Character(std::string name, Point characterLoction);
        virtual ~Character();

        //for tidy:
        //  Delete copy operations
        Character(const Character &) = delete;
        Character &operator=(const Character &) = delete;
       
        // Delete move constructor
        Character(Character &&) = delete;

        // Delete move assignment operator
        Character &operator=(Character &&) = delete;


        // functions to implement:
        bool isAlive() const;
        double distance(Character *p_other) const;
        void hit(int dmg);
        virtual std::string print() const;

        // my added functions:
        virtual void attackTarget(Character *enemy) = 0;

        // getters & setters:
        Point getLocation() const;
        void setLocation(Point newLocation);
        int getHP() const;
        void setHP(int newhp);
        std::string getName() const;
        bool getIsInTeam() const;
        void setIsInTeam();
    };
} // namespace ariel
