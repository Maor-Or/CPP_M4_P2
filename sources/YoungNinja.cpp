#include "YoungNinja.hpp"

namespace ariel
{

    // Ctors & Dtors:
    YoungNinja::YoungNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        setHP(100);
        setSpeed(14);
    }

    // YoungNinja::~YoungNinja()
    // {
    // }

} // namespace ariel