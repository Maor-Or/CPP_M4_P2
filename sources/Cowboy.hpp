#pragma once

#include "Character.hpp"
#include <string>

#define BULLETAMOUNT 6
#define COWBOY_HP 110

namespace ariel
{
    class Cowboy : public Character
    {
    private:
        int _bulletAmount;

    public:
        // Ctors & Dtors:
        Cowboy(std::string name, Point characterLoction);
        ~Cowboy();

        // functions to implement:
        void shoot(Character *enemy);
        bool hasboolets() const;
        void reload();
        std::string print() const;

        // my added functions:
        void attackTarget(Character *enemy);
    };
} // namespace ariel
