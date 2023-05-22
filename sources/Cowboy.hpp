#pragma once

#include "Character.hpp"
#include <string>


namespace ariel
{
    constexpr int COWBOY_HP = 110;
    constexpr int BULLETAMOUNT = 6;
    
    class Cowboy : public Character
    {
    private:
        int _bulletAmount;

    public:
        // Ctors & Dtors:
        Cowboy(std::string name, Point characterLoction);

        // functions to implement:
        void shoot(Character *enemy);
        bool hasboolets() const;
        void reload();
        std::string print()const override;

        // my added functions:
        void attackTarget(Character *enemy) override;
    };
} // namespace ariel
