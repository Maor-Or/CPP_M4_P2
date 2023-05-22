#include "OldNinja.hpp"

namespace ariel
{
    // Ctors & Dtors:
    OldNinja::OldNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        setHP(OLD_NINJA_HP);
        setSpeed(OLD_NINJA_SPEED);
    }

    // OldNinja::~OldNinja()
    // {
    // }
} // namespace ariel
