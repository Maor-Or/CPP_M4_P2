#pragma once

#include "Team.hpp"

namespace ariel
{
    class Team2 : public Team
    {
    private:
    public:
        Team2(Character *leader);
        ~Team2();


        void attack(Team *enemyTeam);
    };

} // namespace ariel
