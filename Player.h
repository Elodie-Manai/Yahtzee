#ifndef PLAYER_H
#define PLAYER_H

#include "ScoreGrid.h"

class Player {

    public:
        Player() {}

        char *getName() { return this->name; }

        void setScore(unsigned choice, unsigned *dices) { this->scoreGrid.setPoints(choice, dices); }

        void showScore(unsigned gridLength) {  
            int gridArray[13];
            memset(gridArray, 0, 13 * sizeof(int));
            this->scoreGrid.getGrid(gridArray, this->scoreGrid.combinationsNames);

            for (unsigned i = 0; i < gridLength; i++)
            {
                printf("%s : %d\n", this->scoreGrid.combinationsNames[i], gridArray[i]);
            }
            
            
        }
        void setName(char *name) { strcpy(this->name, name); }
        

    private:
        char name[40+1];
        ScoreGrid scoreGrid;
};

#endif

