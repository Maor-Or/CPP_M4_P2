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
        //~SmartTeam();

        // functions to implement:
        void attack(Team *enemyTeam) override;
        
        //my added functions:
        int analizeEnemyTeam(Team *enemyTeam);

        Character *findLowestHPEnemy(Character *attacker, Team *enemyTeam);
        Character *findClosestEnemy(Character *attacker, Team *enemyTeam);

        Ninja *scanForNinjaThreat(Character *attacker, Team *enemyTeam);
        Ninja *findClosestNinja(Character *attacker, Team *enemyTeam);
        
        Cowboy *closestCowboy(Character *attacker, Team *enemyTeam);
        Cowboy *findFurthestCowboy(Character *attacker, Team *enemyTeam);
        Cowboy *findWeakestCowboy(Character *attacker, Team *enemyTeam);

        void rush(Character *attacker, Team *enemyTeam);  
        void camp(Character *attacker, Team *enemyTeam);
        void brawl(Character *attacker, Team *enemyTeam);
    };

} // namespace ariel
