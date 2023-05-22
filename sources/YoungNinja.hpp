#pragma once

#include "Ninja.hpp"
#include <string>

namespace ariel
{
    static constexpr int YOUNG_NINJA_HP = 100;
    static constexpr int YOUNG_NINJA_SPEED = 14;

    class YoungNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        YoungNinja(std::string name, Point characterLoction);
    };

} // namespace ariel
