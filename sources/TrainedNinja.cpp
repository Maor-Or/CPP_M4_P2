#include "TrainedNinja.hpp"

namespace ariel
{
    // Ctors & Dtors:
    TrainedNinja::TrainedNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        setHP(TRAINED_NINJA_HP);
        setSpeed(TRAINED_NINJA_SPEED);
    }

} // namespace ariel
