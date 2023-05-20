#pragma once

#include "Team.hpp"

namespace ariel
{
    class SmartTeam : public Team
    {
    private:
        Character **_enemyTeamArray;

    public:
        // Ctors & Dtors:
        SmartTeam(Character *leader);
        ~SmartTeam();

        // functions to implement:
        Ninja *scanForNinjaThreat(Character *attacker, Team *enemyTeam);
        Cowboy *closestCowboy( Character *attacker, Team *enemyTeam); 

        void attack(Team *enemyTeam);
        int analizeEnemyTeam(Team *enemyTeam);
        void RUSH(Character *attacker,Team *enemyTeam);
        void CAMP(Character *attacker,Team *enemyTeam);
        void BRAWL(Character *attacker,Team *enemyTeam);
    };

} // namespace ariel
