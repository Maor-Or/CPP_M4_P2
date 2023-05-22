
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

    // SmartTeam::~SmartTeam()
    // {
    // }

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
        if (!(getLeader()->isAlive()))
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
        for (unsigned long i = 0; i < getCurrCowboysSize(); i++)
        {
            victim = findNewVictim(enemyTeam);
            // incase the entire enemy team is dead,
            // a nullptr will be returned, and the attack is over:
            if (victim == nullptr)
            {
                return;
            }

            // if the cowboy is dead, can't attack:
            // if (_cowboysArray[i]->isAlive() == 0)
            // {
            //     continue;
            // }
             if (getCowboyArray().at(i)->isAlive() == 0)
            {
                continue;
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
                camp(getCowboyArray().at(i), enemyTeam);
                continue;

            /*
            if there are no cowboys on the attacking team and there are cowboys on the attacked team,
            then the ninjas should try getting the cowboys using RUSH strategy
            */
            case 1:
                rush(getCowboyArray().at(i), enemyTeam);
                continue;

            /*
            if none of the above happens, cowboys should kill the other cowboys
            while the ninjas go to their closest prays, using BRAWL strategy
            */
            case 2:
                brawl(getCowboyArray().at(i), enemyTeam);
                continue;

            default:
                continue;
            }
        }

        // go through all the ninjas secondly, by order of addition:
        for (unsigned long i = 0; i < getCurrNinjasSize(); i++)
        {
            victim = findNewVictim(enemyTeam);
            // incase the entire enemy team is dead,
            // a nullptr will be returned, and the attack is over:
            if (victim == nullptr)
            {
                return;
            }

            // if the ninja is dead, can't attack:
            if (getNinjasArray().at(i)->isAlive() == 0)
            {
                continue;
            }

            // checking the enemy team's location and status:
            int strategy = analizeEnemyTeam(enemyTeam);

            switch (strategy)
            {
            case 0:
                camp(getNinjasArray().at(i), enemyTeam);
                continue;

            case 1:
                rush(getNinjasArray().at(i), enemyTeam);
                continue;

            case 2:
                brawl(getNinjasArray().at(i), enemyTeam);
                continue;

            default:
                continue;
            }
        }
    }

    // my added functions:
    int SmartTeam::analizeEnemyTeam(Team *enemyTeam)
    {
        bool attackingTeamCowboys = false;

        // checking if the attacking team has living cowboys:
        for (unsigned long i = 0; i < getCurrCowboysSize(); ++i)
        {
            if (getTeamArray().at(i)->isAlive())
            {
                // attacking team has cowboys:
                if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(getTeamArray().at(i)))
                {
                    attackingTeamCowboys = true;
                    break;
                }
            }
        }

        int enemyTeamSize = enemyTeam->getCurrTeamSize();

        // checking for cowboys on the defending team:
        for (unsigned long i = 0; i < enemyTeamSize; ++i)
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
    void SmartTeam::rush(Character *attacker, Team *enemyTeam)
    {
        attacker->print(); cout << " is rushing" << endl;

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
    void SmartTeam::camp(Character *attacker, Team *enemyTeam)
    {
        cout << attacker->print() << " is camping" << endl;

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
        if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(attacker))
        {
            Cowboy *target = findFurthestCowboy(attacker, enemyTeam);
            if (target != nullptr)
            {
                attacker->attackTarget(target);
            }
            else
            {
                Ninja *Ninja_target = findClosestNinja(attacker, enemyTeam);
                if (Ninja_target == nullptr)
                {
                    return;
                }
                else
                {
                    attacker->attackTarget(Ninja_target);
                }
            }
        }
    }

    /*
    if none of the above happens, cowboys should kill the weakest cowboys and then the weakest ninjas
    while the ninjas go to their closest prays, using BRAWL strategy
    */
    void SmartTeam::brawl(Character *attacker, Team *enemyTeam)
    {
        cout << attacker->print() << " is brawling" << endl;

        // cowboys should shoot the cowboys and then the closest enemy ninjas:
        if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(attacker))
        {
            Cowboy *target = findWeakestCowboy(attacker, enemyTeam);
            if (target != nullptr)
            {
                attacker->attackTarget(target);
            }
            else
            {
                Character *other_target = findLowestHPEnemy(attacker, enemyTeam);
                if (other_target == nullptr)
                {
                    return;
                }
                else
                {
                    attacker->attackTarget(other_target);
                }
            }
        }

        // ninjas should go for the closest enemys:
        if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(attacker))
        {
            Character *target = findClosestEnemy(attacker, enemyTeam);
            if (target == nullptr)
            {
                return;
            }
            else
            {
                attacker->attackTarget(target);
            }
        }
    }

    Ninja *SmartTeam::scanForNinjaThreat(Character *attacker, Team *enemyTeam)
    {
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();
        Character *currEnemy = nullptr;

        // looking for close ninjas:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
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

    Ninja *SmartTeam::findClosestNinja(Character *attacker, Team *enemyTeam)
    {
        double minDistance = numeric_limits<double>::max();
        Character *currEnemy = nullptr, *minDistEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for closest cowboy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(currEnemy))
                {
                    if (attacker->distance(currEnemy) < minDistance)
                    {
                        minDistance = attacker->distance(currEnemy);
                        minDistEnemy = currEnemy;
                    }
                }
            }
        }
        return minDistEnemy != nullptr ? dynamic_cast<Ninja *>(minDistEnemy) : nullptr;
    }

    Cowboy *SmartTeam::findFurthestCowboy(Character *attacker, Team *enemyTeam)
    {

        double maxDistance = 0;
        Character *currEnemy = nullptr, *maxDistEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for furtherst cowboy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Cowboy *ninjaPtr = dynamic_cast<Cowboy *>(currEnemy))
                {
                    if (attacker->distance(currEnemy) > maxDistance)
                    {
                        maxDistance = attacker->distance(currEnemy);
                        maxDistEnemy = currEnemy;
                    }
                }
            }
        }
        return maxDistEnemy != nullptr ? dynamic_cast<Cowboy *>(maxDistEnemy) : nullptr;
    }

    Cowboy *SmartTeam::closestCowboy(Character *attacker, Team *enemyTeam)
    {

        double minDistance = numeric_limits<double>::max();
        Character *currEnemy = nullptr, *minDistEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for closest cowboy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(currEnemy))
                {
                    if (attacker->distance(currEnemy) < minDistance)
                    {
                        minDistance = attacker->distance(currEnemy);
                        minDistEnemy = currEnemy;
                    }
                }
            }
        }

        return minDistEnemy != nullptr ? dynamic_cast<Cowboy *>(minDistEnemy) : nullptr;
    }

    Character *SmartTeam::findLowestHPEnemy(Character *attacker, Team *enemyTeam)
    {

        int lowestHP = numeric_limits<int>::max();
        Character *currEnemy = nullptr, *minHPEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for lowest hp enemy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (currEnemy->getHP() < lowestHP)
                {
                    lowestHP = currEnemy->getHP();
                    minHPEnemy = currEnemy;
                }
            }
        }
        return minHPEnemy != nullptr ? (minHPEnemy) : nullptr;
    }

    Cowboy *SmartTeam::findWeakestCowboy(Character *attacker, Team *enemyTeam)
    {

        int lowestHP = numeric_limits<int>::max();
        Character *currEnemy = nullptr, *minHPEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for lowest hp cowboy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(currEnemy))
                {
                    if (currEnemy->getHP() < lowestHP)
                    {
                        lowestHP = currEnemy->getHP();
                        minHPEnemy = currEnemy;
                    }
                }
            }
        }
        return minHPEnemy != nullptr ? dynamic_cast<Cowboy *>(minHPEnemy) : nullptr;
    }

    Character *SmartTeam::findClosestEnemy(Character *attacker, Team *enemyTeam)
    {

        double minDistance = numeric_limits<double>::max();
        Character *currEnemy = nullptr, *minDistEnemy = nullptr;
        int currEnemyTeamSize = enemyTeam->getCurrTeamSize();

        // looking for closest enemy:
        for (unsigned long i = 0; i < currEnemyTeamSize; ++i)
        {
            currEnemy = enemyTeam->getCharacterAt(i);
            if (currEnemy->isAlive())
            {
                if (attacker->distance(currEnemy) < minDistance)
                {
                    minDistance = attacker->distance(currEnemy);
                    minDistEnemy = currEnemy;
                }
            }
        }
        return minDistEnemy != nullptr ? (minDistEnemy) : nullptr;
    }

} // namespace ariel
