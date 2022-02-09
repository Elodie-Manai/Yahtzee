#ifndef PLAYER_H
#define PLAYER_H

#include "ScoreGrid.h"

class Player {

    public:
        Player(char *name) { this->name = name; }
        char *getName() { return this->name; }
        void setScore(unsigned choice, unsigned *dices) { this->scoreGrid.setPoints(choice, dices); }
        void showScore() {  
                grid grille;
                this->scoreGrid.getGrid(&grille);

                printf("Points pour les un : %d", grille.one);
        }
        void setName(char *name) { this->name = name; }

    private:
        char *name;
        ScoreGrid scoreGrid;
};

#endif

