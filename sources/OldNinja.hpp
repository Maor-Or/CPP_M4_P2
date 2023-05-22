#pragma once

#include "Ninja.hpp"



namespace ariel
{

    static constexpr int OLD_NINJA_HP = 150;
    static constexpr int OLD_NINJA_SPEED = 8;

    class OldNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        OldNinja(std::string name, Point characterLoction);
    };

} // namespace ariel
