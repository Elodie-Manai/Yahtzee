#ifndef PLAYER_H
#define PLAYER_H

#include "ScoreGrid.h"

class Player {

    public:
        Player() {}

        char *getName() { return this->name; }

        void setScore(unsigned choice, unsigned *dices) { this->scoreGrid.setPoints(choice, dices); }

        int showScore(unsigned gridLength) {  
            printf("player.showScore() l.16");
            int gridArray[13];
            memset(gridArray, 0, 13 * sizeof(int));

            char *combinationsNames;
            this->scoreGrid.getGrid(gridArray, combinationsNames);

            for (unsigned i = 0; i < gridLength; i++)
            {
                // printf("%s : %d\n", combinationsNames[i], gridArray[i]);
                printf("%s\n", combinationsNames[i]);
            }
            return 0;
            
        }
        void setName(char *name) { strcpy(this->name, name); }
        

    private:
        char name[40+1];
        ScoreGrid scoreGrid;
};

#endif

