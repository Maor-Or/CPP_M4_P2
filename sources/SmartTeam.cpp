
#include "SmartTeam.hpp"
#include <iostream>
#include <limits>

using namespace std;

namespace ariel
{
    // Ctors & Dtors:
    SmartTeam::SmartTeam(Character *leader) : Team(leader)
    {
    }

    SmartTeam::~SmartTeam()
    {
    }

    // functions to implement:
    void SmartTeam::attack(Team *enemyTeam)
    {

        // can't attack a nullptr team:
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

        // go through all the cowboys first, by order of addition:
        for (int i = 0; i < _currCowboysSize; i++)
        {
            victim = findNewVictim(enemyTeam);
            // incase the entire enemy team is dead,
            // a nullptr will be returned, and the attack is over:
            if (victim == nullptr)
            {
                return;
            }

            // if the cowboy is dead, can't attack:
            if (_cowboysArray[i]->isAlive() == 0)
            {
                break;
            }

            // checking the enemy team's location and status:
            int strategy = analizeEnemyTeam(enemyTeam);

            switch (strategy)
            {
            /*
            if there are cowboys on the attacking team and no cowboys on the attacked team,
            and the cowboys can be protected, then use CAMP strategy
            */
            case 0:
                CAMP(_cowboysArray[i], enemyTeam);
                break;

            /*
            if there are no cowboys on the attacking team and there are cowboys on the attacked team,
            then the ninjas should try getting the cowboys using RUSH strategy
            */
            case 1:
                RUSH(_cowboysArray[i], enemyTeam);
                break;

            /*
            if none of the above happens, cowboys should kill the other cowboys
            while the ninjas go to their closest prays, using BRAWL strategy
            */
            case 2:
                BRAWL(_cowboysArray[i], enemyTeam);
                break;

            default:
                break;
            }
        }

        // go through all the ninjas secondly, by order of addition:
        for (int i = 0; i < _currNinjasSize; i++)
        {
            victim = findNewVictim(enemyTeam);
            // incase the entire enemy team is dead,
            // a nullptr will be returned, and the attack is over:
            if (victim == nullptr)
            {
                return;
            }

            // if the ninja is dead, can't attack:
            if (_ninjasArray[i]->isAlive() == 0)
            {
                break;
            }

            // checking the enemy team's location and status:
            int strategy = analizeEnemyTeam(enemyTeam);

            switch (strategy)
            {
            case 0:
                CAMP(_ninjasArray[i], enemyTeam);
                break;

            case 1:
                RUSH(_ninjasArray[i], enemyTeam);
                break;

            case 2:
                BRAWL(_ninjasArray[i], enemyTeam);
                break;

            default:
                break;
            }
        }
    }

    // my added functions:
    int SmartTeam::analizeEnemyTeam(Team *enemyTeam)
    {
        bool attackingTeamCowboys = false;

        // checking if the attacking team has living cowboys:
        for (int i = 0; i < _currCowboysSize; ++i)
        {
            if (_teamArray[i]->isAlive())
            {
                // attacking team has cowboys:
                if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(_teamArray[i]))
                {
                    attackingTeamCowboys = true;
                    break;
                }
            }
        }

        int enemyTeamSize = enemyTeam->getCurrTeamSize();

        // checking for cowboys on the defending team:
        for (int i = 0; i < enemyTeamSize; ++i)
        {
            if (enemyTeam->getCharacterAt(i)->isAlive())
            {
                // if found an enemy cowboy:
                if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(enemyTeam->getCharacterAt(i)))
                {
                    // 2 - both teams have cowboys, BRAWL. 1 - only enemy team has cowboys, RUSH
                    return attackingTeamCowboys ? 2 : 1;
                }
            }
        }
        // 0 - only attacking team has cowboys, CAMP. 1 - no team has cowboys, RUSH
        return attackingTeamCowboys ? 0 : 1;
    }

    /*
    if there are no cowboys on the attacking team and there are cowboys on the attacked team,
    then the ninjas should try getting the cowboys using RUSH strategy
    */
    void SmartTeam::RUSH(Character *attacker, Team *enemyTeam)
    {
        Ninja *threat = scanForNinjaThreat(attacker, enemyTeam);
        if (threat != nullptr)
        {
            attacker->attackTarget(threat);
        }
        else
        {
            attacker->attackTarget(closestCowboy(attacker, enemyTeam));
        }
    }

    /*
    if there are cowboys on the attacking team and no cowboys on the attacked team,
    and the cowboys can be protected, then use CAMP strategy
    */
    void SmartTeam::CAMP(Character *attacker, Team *enemyTeam)
    {
        // ninjas should go for their cowboys and protect them:
        if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(attacker))
        {
            Ninja *threat = scanForNinjaThreat(attacker, enemyTeam);
            if (threat != nullptr)
            {
                attacker->attackTarget(threat);
            }
            else
            {
                dynamic_cast<Ninja *>(attacker)->move(closestCowboy(attacker, this));
            }
        }

        // cowboys should shoot the cowboys and then the closest enemy ninjas:
        if (Cowboy *ninjaPtr = dynamic_cast<Cowboy *>(attacker))
        {
            
        }
    }

    /*
    if none of the above happens, cowboys should kill the other cowboys
    while the ninjas go to their closest prays, using BRAWL strategy
    */
    void SmartTeam::BRAWL(Character *attacker, Team *enemyTeam)
    {
    }

    Ninja *SmartTeam::scanForNinjaThreat(Character *attacker, Team *enemyTeam)
    {
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();
        Character *currEnemy = nullptr;

        // looking for close ninjas:
        for (int i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(currEnemy))
                {
                    if (attacker->distance(currEnemy) < 1)
                    {
                        return dynamic_cast<Ninja *>(currEnemy);
                    }
                }
            }
        }
        return nullptr;
    }

    Cowboy *SmartTeam::closestCowboy(Character *attacker, Team *enemyTeam)
    {
        double minDistance = numeric_limits<double>::max();
        Character *currEnemy = nullptr, *minDistEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for closest cowboy:
        for (int i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Cowboy *ninjaPtr = dynamic_cast<Cowboy *>(currEnemy))
                {
                    if (attacker->distance(currEnemy) < minDistance)
                    {
                        minDistance = attacker->distance(currEnemy);
                        minDistEnemy = currEnemy;
                    }
                }
            }
        }
        return currEnemy != nullptr ? dynamic_cast<Cowboy *>(currEnemy) : nullptr;
    }

} // namespace ariel
