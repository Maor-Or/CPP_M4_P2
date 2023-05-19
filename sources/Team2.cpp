
#include "Team2.hpp"
#include<iostream>

using namespace std;

namespace ariel
{

    Team2::Team2(Character *leader) : Team(leader)
    {
    }

    Team2::~Team2()
    {
        // printf("in team2 dtor\n");
    }

    void Team2::attack(Team *enemyTeam)
    {

        if (enemyTeam == nullptr)
        {
            throw std::invalid_argument("victim can't be nullptr");
        }

        // if the attacking team is all dead, then the attack is over
        if (stillAlive()) // > 0
        {
            return;
        }

        // if the leader is dead then first pick a new leader:
        if (!(_leader->isAlive()))
        {
            updateLeader();
        }

        // find the enemy team's victim (closest to the attacking team's leader):
        Character *victim = findNewVictim(enemyTeam);

        // incase the entire enemy team is dead, a nullptr will be returned, and the attack is over:
        if (victim == nullptr)
        {
            return;
        }

        // go through all the team, by order of addition:
        for (int i = 0; i < _currTeamSize; i++)
        {
            // if the victim is already dead, find new victim:
            if (!(victim->isAlive()))
            {
                victim = findNewVictim(enemyTeam);
                // incase the entire enemy team is dead, a nullptr will be returned, and the attack is over:
                if (victim == nullptr)
                {
                    return;
                }
            }
            if (_teamArray[i]->isAlive())
            {
                _teamArray[i]->attackTarget(victim);
            }
        }
    }

} // namespace ariel
