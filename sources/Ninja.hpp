#pragma once

#include "Character.hpp"
#include <string>

namespace ariel
{
    class Ninja : public Character
    {
    protected:
        
        int _speed;

    public:

        // Ctors & Dtors:
        Ninja(std::string name, Point characterLoction);
        ~Ninja();
    
        //functions to implement:
        void move(const Character *enemy);
        void slash(Character *enemy) const;
        std::string print() const;
        
        //my added functions:
        void attackTarget(Character*enemy);

    };
    
} // namespace ariel
