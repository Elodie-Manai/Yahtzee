#ifndef PLAYER_H
#define PLAYER_H

#include "ScoreGrid.h"

class Player
{

    public:
        Player() {}

        char *getName() { return this->name; }

        int setScore(unsigned choice, unsigned *dices) { return this->scoreGrid.setPoints(choice, dices); }

        void showScore(unsigned gridLength)
        {
            int gridArray[13];
            memset(gridArray, 0, 13 * sizeof(int));
            this->scoreGrid.getGrid(gridArray, this->scoreGrid.combinationsNames);

            for (unsigned i = 0; i < gridLength; i++)
            {
                printf("[%d] %s : %d\n", i + 1, this->scoreGrid.combinationsNames[i], gridArray[i] == -1 ? gridArray[i] + 1 : gridArray[i]);
            }
        }

        void setName(char *name) { strcpy(this->name, name); }

        int returnScore()
        {
            return this->scoreGrid.calculateScore();
        }

    private:
        char name[40 + 1];
        ScoreGrid scoreGrid;
};

#endif
