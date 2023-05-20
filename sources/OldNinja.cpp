#include "OldNinja.hpp"

namespace ariel
{
    // Ctors & Dtors:
    OldNinja::OldNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        _hitPoints = 150;
        _speed = 8;
    }

    OldNinja::~OldNinja()
    {
    }
} // namespace ariel
