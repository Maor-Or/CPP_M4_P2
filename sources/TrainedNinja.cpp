#include "TrainedNinja.hpp"

namespace ariel
{
    // Ctors & Dtors:
    TrainedNinja::TrainedNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        setHP(120);
        setSpeed(12);
    }

    // TrainedNinja::~TrainedNinja()
    // {
    // }
} // namespace ariel
