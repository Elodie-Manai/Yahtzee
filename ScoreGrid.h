#ifndef SCORE_GRID_H
#define SCORE_GRID_H

#include "Gameplay.h"

class ScoreGrid
{

    public:
        ScoreGrid() {memset(this->gridArray, 0, 13 * sizeof(unsigned));}
        
        char *combinationsNames[13] = {(char *)"one", (char *)"two", (char *)"three", (char *)"four",
                                       (char *)"five", (char *)"six", (char *)"Brelan", (char *)"Carre", 
                                       (char *)"Petite suite", (char *)"Grande suite", (char *)"Full", 
                                       (char *)"Yahtzee", (char *)"Chance"};
        
        void getGrid(int *grille, char **combinations)
        {
            memcpy(grille, this->gridArray, sizeof(this->gridArray));
            combinations = this->combinationsNames;
        };
        void setPoints(unsigned indexGrid, unsigned dices[5]) {
            this->setGrid(this->gridArray, indexGrid, getPoints(indexGrid + 1, dices, 5));
        };
        int calculateScore() {
            unsigned i = 0;
            unsigned score = 0;

            for (; i < 6; i++) score += this->gridArray[i];
            
            if (score > 62) score += 35;

            for (; i < 13; i++) score += this->gridArray[i];

            return score;
        };

    private:
        Gameplay gameplay;
        int gridArray[13]; 
        
        int setGrid(int *gridArray, int index, unsigned pts) {
            gridArray[index] = pts;
            return 0;
        }
        unsigned getPoints(unsigned indexGrid, unsigned *dices, unsigned sizeOfDices)
        {
            unsigned pts = 0;
            bool isValid = false;

            switch (indexGrid)
            {
                // Top grid :
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    for (unsigned i = 0; i < sizeOfDices; i++) if (dices[i] == indexGrid) pts += indexGrid;
                break;

                // Bottom grid :
                case 7: // Brelan
                {
                    if(this->checkForIdenticals(dices, gameplay.DICE_NUMBER, 3)) for (unsigned i = 0; i < gameplay.DICE_NUMBER; i++) pts += dices[i];
                }
                break;
                case 8: // Carre
                {
                    if(this->checkForIdenticals(dices, gameplay.DICE_NUMBER, 4)) for (unsigned i = 0; i < gameplay.DICE_NUMBER; i++) pts += dices[i];
                }
                break;
                case 9: // Petite suite
                {
                    this->sortArray(dices, sizeOfDices);
                    if(dices[0] == dices[1] - 1 && dices[1] == dices[2] - 1 && dices[2] == dices[3] - 1) pts = 30;
                    else pts = 0;

                }
                break;
                case 10: // Grande Suite => What da ?
                {
                    this->sortArray(dices, sizeOfDices);
                    if(dices[0] == dices[1] - 1 && dices[1] == dices[2] - 1 && dices[2] == dices[3] - 1 && dices[3] == dices[4] - 1) pts = 40;
                    else pts = 0;
                }
                break;
                case 11: // Full
                {
                    this->sortArray(dices, sizeOfDices);
                    if((dices[0] == dices[1] && dices[1] == dices[2]) && (dices[3] == dices[4]) || 
                        (dices[2] == dices[3] && dices[3] == dices[4]) && (dices[0] == dices[1])) pts = 25;
                }
                break;
                case 12: // Yahtzee
                {
                    if(this->checkForIdenticals(dices, gameplay.DICE_NUMBER, 5)) pts = 50;
                }
                break;
                case 13: // Chance
                {
                    for (unsigned i = 0; i < sizeOfDices; i++) pts += dices[i];
                }
                break;

                default:
                    pts = -1;
                    break;
            }

            printf("Points gagnés : %d\n", pts); // Debug
            return pts;
        }

        int sortArray(unsigned *array, int sizeArray) // Very pretty ! :D
        {
            for (unsigned j = 0; j < sizeArray; j++)
            {
                for (unsigned i = 0; i < sizeArray; i++)
                {
                    if (array[i + 1] && array[i] > array[i + 1])
                    {
                        int temp = array[i + 1];
                        array[i + 1] = array[i];
                        array[i] = temp;
                        i -= 1;
                    }
                }
            }
            return 0;
        }

        int checkForIdenticals(unsigned *array, int sizeArray, int numberOfIdenticalRequired)
        {
            if(sizeArray > sizeof(array)) return -1;
            for (unsigned i = 0; i < sizeArray; i++)
            {
                unsigned countOfIdentical = 0;

                for (unsigned j = 0; j < sizeArray; j++) if (array[i] == array[j]) countOfIdentical += 1;
                
                if (countOfIdentical >= numberOfIdenticalRequired) return 1;
            }
            return 0;
        }
};

#endif