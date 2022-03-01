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
            char **combinationsNames;
            this->scoreGrid.getGrid(gridArray, combinationsNames);

            for (unsigned i = 0; i < gridLength; i++)
            {
                printf("%s : %d\n", combinationsNames[i], gridArray[i]);
            }
            
            
        }
        void setName(char *name) { strcpy(this->name, name); }
        

    private:
        char name[40+1];
        ScoreGrid scoreGrid;
};

#endif

