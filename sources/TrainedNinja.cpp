#include "TrainedNinja.hpp"

namespace ariel
{
    // Ctors & Dtors:
    TrainedNinja::TrainedNinja(std::string name, Point characterLoction)
        : Ninja(name, characterLoction)
    {
        _hitPoints = 120;
        _speed = 12;
    }

    TrainedNinja::~TrainedNinja()
    {
    }
} // namespace ariel
