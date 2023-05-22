#pragma once

#include "Ninja.hpp"

namespace ariel
{
    static constexpr int TRAINED_NINJA_HP = 120;
    static constexpr int TRAINED_NINJA_SPEED = 12;

    class TrainedNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        TrainedNinja(std::string name, Point characterLoction);
    };

} // namespace ariel
