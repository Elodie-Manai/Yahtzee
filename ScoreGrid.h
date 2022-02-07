#ifndef SCORE_GRID_H
#define SCORE_GRID_H

struct grid
{
    unsigned one;
    unsigned two;
    unsigned three;
    unsigned four;
    unsigned five;
    unsigned six;

    unsigned brelan;
    unsigned carre;
    unsigned petiteSuite;
    unsigned grandeSuite;
    unsigned full;
    unsigned yahtzee;
    unsigned chance;
};

class ScoreGrid
{

public:
    ScoreGrid() {}
    void getGrid(struct grid *grid)
    {
        grid = &this->grid;
    };
    // void setPoints(unsigned indexGrid, unsigned dices[5]) {
    //     this->grid[indexGrid] = getPoints(indexGrid, dices);
    // }

private:
    struct grid grid;
    int getPoints(unsigned indexGrid, unsigned *dices, unsigned sizeOfDices)
    {
        unsigned pts = 0;
        bool isValid = false;
        switch (indexGrid)
        {
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
            if((dices[i] == dices[i + 1] && dices[i + 1] == dices[i + 2]) && (dices[i + 3] == dices[i + 4]) || 
                (dices[i + 2] == dices[i + 3] && dices[i + 4] == dices[i + 2]) && (dices[i] == dices[i + 1])) pts = 25;
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

        return pts;
    }

    int sortArray(unsigned *array, int sizeArray)
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
};

#endif