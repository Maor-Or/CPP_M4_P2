#include "YoungNinja.hpp"

namespace ariel
{

    // Ctors & Dtors:
    YoungNinja::YoungNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        _hitPoints = 100;
        _speed = 14;
    }

    YoungNinja::~YoungNinja()
    {
    }

} // namespace ariel