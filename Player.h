#ifndef PLAYER_H
#define PLAYER_H

#include "ScoreGrid.h"

class Player {

    public:
        Player(char *name) { this->name = name; this->score = 0; }
        char *getName() { return this->name; }
        unsigned getScore() { return this->score; }
        void setScore(unsigned score) { this->score = score; }
        void setName(char *name) { this->name = name; }

    private:
        char *name;
        unsigned score;
        grid grille;
        ScoreGrid scoreGrid;
};

#endif

