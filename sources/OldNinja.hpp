#pragma once

#include "Ninja.hpp"

namespace ariel
{
    class OldNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        OldNinja(std::string name, Point characterLoction);
        ~OldNinja();
    };

} // namespace ariel
