#include "YoungNinja.hpp"

namespace ariel
{

    // Ctors & Dtors:
    YoungNinja::YoungNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        setHP(YOUNG_NINJA_HP);
        setSpeed(YOUNG_NINJA_SPEED);
    }

} // namespace ariel