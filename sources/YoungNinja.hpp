#pragma once

#include "Ninja.hpp"
#include <string>

namespace ariel
{
    class YoungNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        YoungNinja(std::string name, Point characterLoction);
        //~YoungNinja();
    };

} // namespace ariel
