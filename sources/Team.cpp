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
        // cout << "in Team's dtor"<<endl;
        for (int i = 0; i < _currTeamSize; i++)
        {
            delete _teamArray[i];
        }
    }

    // functions to implement:
    void Team::add(Character *newTeamMember)
    {
        if (_currTeamSize >= MAX_TEAM_SIZE)
        {
            throw std::runtime_error("team is already full!");
        }
        if (newTeamMember->getIsInTeam() == true)
        {
            throw std::runtime_error("new member is already in a team!");
        }

        _teamArray[_currTeamSize++] = newTeamMember;
        newTeamMember->setIsInTeam();

        // if the new teamate is a cowboy then add it to the cowboys array:
        if (Cowboy *cowboyPtr = dynamic_cast<Cowboy *>(newTeamMember))
        {
            _cowboysArray[_currCowboysSize++] = newTeamMember;
        }

        // if the new teamate is a ninja then add it to the ninjas array:
        else if (Ninja *ninjaPtr = dynamic_cast<Ninja *>(newTeamMember))
        {
            _ninjasArray[_currNinjasSize++] = newTeamMember;
        }
    }
    void Team::attack(Team *enemyTeam)
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
            // printf("attacking team is all dead\n");
            return;
        }

        // if the leader is dead then first pick a new leader:
        if (!(_leader->isAlive()))
        {
            // printf("attacking team's leader is dead, finding new leader...\n");
            updateLeader();
        }

        // find the enemy team's victim (closest to the attacking team's leader):
        Character *victim = findNewVictim(enemyTeam);
        // std::cout << "new victim found: "<< victim->getName()<<std::endl;
        // printf("new victim found: %s\n", victim->getName());

        // incase the entire enemy team is dead, a nullptr will be returned, and the attack is over:
        if (victim == nullptr)
        {
            // printf("attacked team is all dead\n");
            return;
        }

        // first, all the cowboys attack:
        for (int i = 0; i < _currCowboysSize; i++)
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
            if (_cowboysArray[i]->isAlive())
            {
                _cowboysArray[i]->attackTarget(victim);
            }
        }

        // after that, all the ninjas attack:
        for (int i = 0; i < _currNinjasSize; i++)
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
            if (_ninjasArray[i]->isAlive())
            {
                _ninjasArray[i]->attackTarget(victim);
            }
        }
    }
    int Team::stillAlive() const
    {
        int count = 0;
        for (int i = 0; i < _currTeamSize; ++i)
        {
            if (_teamArray[i]->isAlive())
            {
                ++count;
            }
        }
        return count;
    }
    void Team::print() const
    {
        // first, all the cowboys print:
        for (int i = 0; i < _currCowboysSize; i++)
        {
            _cowboysArray[i]->print();
        }

        // after that, all the ninjas print:
        for (int i = 0; i < _currNinjasSize; i++)
        {
            _ninjasArray[i]->print();
        }
    }

    // my added functions:
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
        for (int i = 0; i < enemyTeam->_currTeamSize; i++)
        {
            currCharacter = enemyTeam->_teamArray[i];

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
        for (int i = 0; i < _currTeamSize; i++)
        {
            currCharacter = _teamArray[i];

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
            // cout << "the new leader is: " << _leader->getName()<<
            // to_string(_leader->getLocation().getX())<<" , "<<
            // to_string(_leader->getLocation().getX()) <<endl ;
        }
    }
};