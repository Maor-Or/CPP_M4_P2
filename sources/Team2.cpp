
#include "Team2.hpp"
#include <iostream>

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
        // if the attacked team is already dead then throw an error:
        if (enemyTeam->stillAlive() == 0)
        {
            throw std::runtime_error("attacked team is already dead");
            return;
        }

        // if the attacking team is all dead, then the attack is over
        if (stillAlive() == 0)
        {
            printf("attacking team is all dead\n");
            return;
        }
        // if the leader is dead then first pick a new leader:
        if (!(_leader->isAlive()))
        {
            printf("attacking team's leader is dead, finding new leader...\n");
            updateLeader();
            printf("new leader: ");
            _leader->print();
        }

        // find the enemy team's victim (closest to the attacking team's leader):
        Character *victim = findNewVictim(enemyTeam);
        std::cout << "new victim found: " << victim->getName() << std::endl;
        printf("new victim found: ");
        victim->print();

        // incase the entire enemy team is dead, a nullptr will be returned, and the attack is over:
        if (victim == nullptr)
        {
            printf("attacked team is all dead\n");
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
