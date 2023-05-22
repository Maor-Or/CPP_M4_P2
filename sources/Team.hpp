#pragma once

#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

#include <array>

namespace ariel
{
    static constexpr int MAX_TEAM_SIZE = 10;

    class Team
    {
    private:
        std::array<Character *, MAX_TEAM_SIZE> teamArray;
        std::array<Character *, MAX_TEAM_SIZE> ninjasArray;
        std::array<Character *, MAX_TEAM_SIZE> cowboysArray;
        Character *_leader;
        unsigned long _currTeamSize, _currCowboysSize, _currNinjasSize;

    public:
        // Ctors & Dtors:
        Team(Character *leader);
        virtual ~Team();

        // for tidy:
        //  Delete copy operations
        Team(const Team &) = delete;
        Team &operator=(const Team &) = delete;
        // Delete move operations
        Team(Team &&) = delete;
        Team &operator=(Team &&) = delete;

        // functions to implement:
        void add(Character *newTeamMember);
        virtual void attack(Team *enemyTeam);
        int stillAlive() const;
        void print() const;

        // my added functions:
        void updateLeader();
        Character *findNewVictim(Team *enemyTeam);

        // getters & setters:
        int getCurrTeamSize() const;
        Character *getCharacterAt(unsigned long index);
        Character *getLeader();
        unsigned long getCurrTeamSize();
        unsigned long getCurrCowboysSize();
        unsigned long getCurrNinjasSize();
        std::array<Character *, MAX_TEAM_SIZE> &getTeamArray();
        std::array<Character *, MAX_TEAM_SIZE> &getNinjasArray();
        std::array<Character *, MAX_TEAM_SIZE> &getCowboyArray();
    };

};