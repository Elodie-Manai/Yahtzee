#ifndef SCORE_GRID_H
#define SCORE_GRID_H

// struct grid
// {
//     unsigned one;
//     unsigned two;
//     unsigned three;
//     unsigned four;
//     unsigned five;
//     unsigned six;

//     unsigned brelan;
//     unsigned carre;
//     unsigned petiteSuite;
//     unsigned grandeSuite;
//     unsigned full;
//     unsigned yahtzee;
//     unsigned chance;
// };

class ScoreGrid
{

    public:
        ScoreGrid() {}
        void getGrid(int *grille, char **combinations)
        {
            grille = this->gridArray;
            combinations = this->combinationsNames;
        };
        void setPoints(unsigned indexGrid, unsigned dices[5]) {
            this->setGrid(this->gridArray, indexGrid, getPoints(indexGrid + 1, dices, 5));
        };

    private:
        int gridArray[13];
        char *combinationsNames[13] = {"one", "two", "three", "four", "five", "six", "Brelan", "Carre", "Petite suite", "Grande suite", "Full", "Yahtzee", "Chance"}; 
        
        int setGrid(int *gridArray, int index, unsigned pts) {
            if (index - 1 < 0 || index - 1 > sizeof(gridArray)) return -1;
            gridArray[index - 1] = pts;
            return 0;
        }
        unsigned getPoints(unsigned indexGrid, unsigned *dices, unsigned sizeOfDices)
        {
            unsigned pts = 0;
            bool isValid = false;
            // printf("call me baby ! %d", indexGrid);
            
            for(unsigned i = 0; i < sizeOfDices; i++) printf("dice %d : %d\n", i, dices[i]);

            switch (indexGrid)
            {
<<<<<<< HEAD
            // Top grid :
            case 1:
            {
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 1)
                        pts += 1;
            }
            break;
            case 2:
            {
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 2)
                        pts += 2;
            }
            break;
            case 3:
            {
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 3)
                        pts += 3;
            }
            break;
            case 4:
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 4)
                        pts += 4;
                break;
            case 5:
            {
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 5)
                        pts += 5;
            }
            break;
            case 6:
            {
                for (unsigned i = 0; i < sizeOfDices; i++)
                    if (dices[i] == 6)
                        pts += 6;
            }
            break;

            // Bottom grid :
            case 7: // Brelan
            {
                for (unsigned i = 1; i < 7; i++)
                {
                    unsigned compt = 0;
                    for (unsigned j = 0; j < sizeOfDices - 3; j++)
                    {
                        if (dices[j] == i)
                            compt++;
                    }
                    if (compt >= 3)
                    {
                        isValid = true;
                        break;
                    }
                }
                if (isValid)
                    for (unsigned i = 0; i < sizeOfDices; i++)
                        pts += dices[i];
            }

            break;
            case 8: // Carre
            {
                for (unsigned i = 1; i < 7; i++)
                {
                    unsigned compt = 0;
                    for (unsigned j = 0; j < sizeOfDices - 3; j++)
                    {
                        if (dices[j] == i)
                            compt++;
                    }
                    if (compt >= 4)
                    {
                        isValid = true;
                        break;
                    }
                }
                if (isValid)
                    for (unsigned i = 0; i < sizeOfDices; i++)
                        pts += dices[i];
            }
            break;
            case 9: // Petite suite
            {
                unsigned cmpt = 0;
                for (unsigned i = 1; i < 7 && cmpt < 3; i++) // Valeur du dés
                {
                    isValid = false;
                    for(unsigned j = 0; j < sizeOfDices; j++) {
                        if(dices[j] == i) {
                            isValid = true;
                            cmpt++;
                        }
                    }
                    if(!isValid && i > 1) break;
                    else if (isValid && cmpt > 3) {
                        pts = 30;
                        break;
                    }
                }

            }
            break;
            case 10: // Grande Suite
            {
                this->sortArray(dices, sizeOfDices);
                for (unsigned i = 0; i < sizeOfDices; i++)
                {
                    if (dices[i + 1] && dices[i] == dices[i + 1] || dices[i] + 1 != dices[i+1])
                        break;
                }
                pts += 40;
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
                unsigned lastDice = dices[0];
                for (unsigned i = 1; i < sizeOfDices; i++)
                {
                    if (dices[i] != lastDice){
                        break;
                        isValid = false;
                    }
                }
                if (isValid)
                    pts = 50;
            }
            break;
            case 13: // Chance
            {
                for (unsigned i = 0; i < sizeOfDices; i++) pts += dices[i];
            }
            break;

            default:
                pts = 0;
                break;
            }
            printf("points : %d\n", pts);
=======
                int valueOfDice = 0;
                // Top grid :
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                {
                    for (unsigned i = 0; i < sizeOfDices; i++) if (dices[i] == indexGrid) pts += indexGrid;
                }
                break;

                // Bottom grid :
                case 7: // Brelan
                {
                    if(this->checkForIdenticals(dices, 5, 3)) for (unsigned i = 0; i < 5; i++) pts += dices[i];
                }
                break;
                case 8: // Carre
                {
                    if(this->checkForIdenticals(dices, 5, 4)) for (unsigned i = 0; i < 5; i++) pts += dices[i];
                }
                break;
                case 9: // Petite suite
                {
                    unsigned cmpt = 0;
                    for (unsigned i = 1; i < 7 && cmpt < 3; i++) // Valeur du dés
                    {
                        isValid = false;
                        for(unsigned j = 0; j < sizeOfDices; j++) {
                            if(dices[j] == i) {
                                isValid = true;
                                cmpt++;
                            }
                        }
                        if(!isValid && i > 1) break;
                        else if (isValid && cmpt > 3) {
                            pts = 30;
                            break;
                        }
                    }

                }
                break;
                case 10: // Grande Suite
                {
                    this->sortArray(dices, sizeOfDices);
                    for (unsigned i = 0; i < sizeOfDices; i++)
                    {
                        if (dices[i + 1] && dices[i] == dices[i + 1] || dices[i] + 1 != dices[i+1])
                            break;
                    }
                    pts += 40;
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
                    if(this->checkForIdenticals(dices, 5, 5)) pts = 50;
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
>>>>>>> c0b8d87392eae6de9a9ee281b4a19630bc0e0e2a
            return pts;
        }

        int sortArray(unsigned *array, int sizeArray) // Very pretty ! :D
        {
            if(sizeArray > sizeof(array)) return -1; // Protection a ajouter partout normalement..
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
<<<<<<< HEAD

=======
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
>>>>>>> c0b8d87392eae6de9a9ee281b4a19630bc0e0e2a
            return 0;
        }
};

#endif