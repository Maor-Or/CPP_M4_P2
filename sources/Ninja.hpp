#pragma once

#include "Character.hpp"
#include <string>

namespace ariel
{
    class Ninja : public Character
    {
    private:
        
        int _speed;

    public:

        // Ctors & Dtors:
        Ninja(std::string name, Point characterLoction);
    
        //functions to implement:
        void move(const Character *enemy);
        void slash(Character *enemy) const;
        std::string print() const override;
        
        //my added functions:
        void attackTarget(Character*enemy) override;
        
        //getters & setters:
        int getSpeed() const;
        void setSpeed(int newSpeed);

    };
    
} // namespace ariel
