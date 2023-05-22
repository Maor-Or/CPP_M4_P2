#pragma once

#include "Team.hpp"

namespace ariel
{
    static constexpr int CAMP = 0;
    static constexpr int RUSH = 1;
    static constexpr int BRAWL = 2;


    class SmartTeam : public Team
    {
    private:
        Character **_enemyTeamArray;

    public:
        // Ctors & Dtors:
        SmartTeam(Character *leader);

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
