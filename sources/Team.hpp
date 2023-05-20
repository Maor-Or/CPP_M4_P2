#pragma once

#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

#define MAX_TEAM_SIZE 10

namespace ariel
{
    class Team
    {
    protected:
        Character *_teamArray[MAX_TEAM_SIZE];
        Character *_cowboysArray[MAX_TEAM_SIZE];
        Character *_ninjasArray[MAX_TEAM_SIZE];
        Character *_leader;
        int _currTeamSize, _currCowboysSize, _currNinjasSize;

        // my added private functions:
        void updateLeader();
        Character *findNewVictim(Team *enemyTeam);

    public:
        // Ctors & Dtors:
        Team(Character *leader);
        ~Team();

        // functions to implement:
        void add(Character *newTeamMember);
        virtual void attack(Team *enemyTeam);
        int stillAlive() const;
        void print() const;
        int getCurrTeamSize() const;
        Character *getCharacterAt(int index);
    };

};