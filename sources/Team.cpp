#include "Team.hpp"
#include <limits>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    // Ctors&Dtors:
    Team::Team(Character *leader)
        : _leader(leader), _currTeamSize(0), _currNinjasSize(0), _currCowboysSize(0)
    {
        add(leader);
    }

    Team::~Team()
    {
        // freeing the teamates from the heap allocation:
        for (unsigned long i = 0; i < _currTeamSize; i++)
        {
            delete teamArray.at(i);
        }
    }

    // functions to implement:
    void Team::add(Character *newTeamMember)
    {
        if (_currTeamSize >= MAX_TEAM_SIZE || newTeamMember->getIsInTeam() == true)
        {
            throw std::runtime_error("team is already full! | new member is already in a team!");
        }

        // adding the new team member:
        teamArray.at(_currTeamSize++) = newTeamMember;
        newTeamMember->setIsInTeam();

        // if the new teamate is a cowboy then add it to the cowboys array:
        if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(newTeamMember))
        {
            cowboysArray.at(_currCowboysSize++) = newTeamMember;
        }

        // if the new teamate is a ninja then add it to the ninjas array:
        else if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(newTeamMember))
        {
            ninjasArray.at(_currNinjasSize++) = newTeamMember;
        }
    }

    void Team::attack(Team *enemyTeam)
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

        // first, all the cowboys attack:
        for (unsigned long i = 0; i < _currCowboysSize; ++i)
        {
            // if the victim is already dead, find new victim:
            if (!(victim->isAlive()))
            {
                victim = findNewVictim(enemyTeam);
                // incase the entire enemy team is dead,
                // a nullptr will be returned, and the attack is over:
                if (victim == nullptr)
                {
                    return;
                }
            }

            if (cowboysArray.at(i)->isAlive())
            {
                cowboysArray.at(i)->attackTarget(victim);
            }
        }

        // after that, all the ninjas attack:
        for (unsigned long i = 0; i < _currNinjasSize; ++i)
        {
            // if the victim is already dead, find new victim:
            if (!(victim->isAlive()))
            {
                victim = findNewVictim(enemyTeam);
                // incase the entire enemy team is dead,
                // a nullptr will be returned, and the attack is over:
                if (victim == nullptr)
                {
                    return;
                }
            }
            
            if (ninjasArray.at(i)->isAlive())
            {
                ninjasArray.at(i)->attackTarget(victim);
            }
        }
    }

    int Team::stillAlive() const
    {
        int count = 0;
        for (unsigned long i = 0; i < _currTeamSize; ++i)
        {
            
            if (teamArray.at(i)->isAlive())
            {
                count++;
            }
        }
        return count;
    }
    void Team::print() const
    {
        // first, all the cowboys print:
        for (unsigned long i = 0; i < _currCowboysSize; ++i)
        {
            cowboysArray.at(i)->print();
        }

        // after that, all the ninjas print:
        for (unsigned long i = 0; i < _currNinjasSize; ++i)
        {
            ninjasArray.at(i)->print();
        }
    }

    // my added functions:

    int Team::getCurrTeamSize() const { return _currTeamSize; }
    Character *Team::getCharacterAt(unsigned long index)
    {
        if (index >= 0 && index < _currTeamSize)
        {
            return teamArray.at(index);
        }
        return nullptr;
    }

    Character *Team::getLeader()
    {
        return _leader;
    }

    unsigned long Team::getCurrTeamSize()
    {
        return _currTeamSize;
    }

    unsigned long Team::getCurrCowboysSize()
    {
        return _currCowboysSize;
    }

    unsigned long Team::getCurrNinjasSize()
    {
        return _currNinjasSize;
    }

    std::array<Character *, MAX_TEAM_SIZE> &Team::getTeamArray()
    {
        return teamArray;
    }

    std::array<Character *, MAX_TEAM_SIZE> &Team::getNinjasArray()
    {
        return ninjasArray;
    }

    std::array<Character *, MAX_TEAM_SIZE> &Team::getCowboyArray()
    {
        return cowboysArray;
    }

    Character *Team::findNewVictim(Team *enemyTeam)
    {
        // the entire enemy team might be already all dead:
        if (enemyTeam->stillAlive() == 0)
        {
            return nullptr;
        }

        // else - find the closest alive to the attacking team's leader:
        double minDistance = numeric_limits<double>::max();
        Character *currCharacter = nullptr, *minDistEnemy = nullptr;

        // goes through all enemys to find the right victim:
        for (unsigned long i = 0; i < enemyTeam->_currTeamSize; i++)
        {
            // currCharacter = enemyTeam->_teamArray[i];
            currCharacter = enemyTeam->teamArray.at(i);

            // checking if the enemy is alive:
            if (currCharacter->isAlive())
            {
                // checking if a new minDistance found:
                if (currCharacter->distance(_leader) < minDistance)
                {
                    minDistance = currCharacter->distance(_leader);
                    minDistEnemy = currCharacter;
                }
            }
        }
        return minDistEnemy;
    }

    void Team::updateLeader()
    {
        double minDistance = numeric_limits<double>::max();
        Character *currCharacter = nullptr, *minDistCharacter = nullptr;

        // goes through all teamates to find the right leader:
        for (unsigned long i = 0; i < _currTeamSize; i++)
        {
            // currCharacter = _teamArray[i];
            currCharacter = teamArray.at(i);

            // checking if the teamate is alive (and not the leader, because the leader is already dead)
            if (currCharacter->isAlive()) //&&currCharacter!=_leader)
            {
                // checking if a new minDistance found:
                if (currCharacter->distance(_leader) < minDistance)
                {
                    minDistance = currCharacter->distance(_leader);
                    minDistCharacter = currCharacter;
                }
            }
        }
        if (minDistCharacter != nullptr)
        {
            _leader = minDistCharacter;
        }
    }
};