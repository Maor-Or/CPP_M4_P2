#pragma once

#include "Team.hpp"

namespace ariel
{
    class Team2 : public Team
    {
    private:
    public:
        // Ctors & Dtors:
        Team2(Character *leader);

        // functions to implement:
        void attack(Team *enemyTeam) override;
    };

} // namespace ariel
