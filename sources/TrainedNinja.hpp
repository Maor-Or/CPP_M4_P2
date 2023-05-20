#pragma once

#include "Ninja.hpp"

namespace ariel
{
    class TrainedNinja : public Ninja
    {
    private:
    public:
        // Ctors & Dtors:
        TrainedNinja(std::string name, Point characterLoction);
        ~TrainedNinja();
    };

} // namespace ariel
