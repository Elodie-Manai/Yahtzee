#ifndef SCORE_GRID_H
#define SCORE_GRID_H

struct grid {
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

class ScoreGrid {

    public:
        ScoreGrid() {}
        void getGrid(struct grid *grid) {
            grid = &this->grid; 
        };
        // void setPoints(unsigned indexGrid, unsigned dices[5]) {
        //     this->grid[indexGrid] = getPoints(indexGrid, dices);
        // }

    private:
        struct grid grid;
        int getPoints(unsigned indexGrid, unsigned *dices[5], unsigned sizeOfDices) {
            unsigned pts = 0;
            switch (indexGrid)
            {
                //Top grid :
                case 1:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 1) pts += 1;
                    break;
                case 2:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 2) pts += 2;
                    break;
                case 3:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 3) pts += 3;
                    break;
                case 4:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 4) pts += 4;
                    break;
                case 5:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 5) pts += 5;
                    break;
                case 6:
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 6) pts += 6;
                    break;
                
                // Bottom grid :
                case 7: // Brelan
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 1) pts += 1;
                    for (unsigned i = 0; i < sizeOfDices; i++)
                    {
                        /* code */
                    }
                    
                    break;
                case 8: // Carre
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 2) pts += 2;
                    break;
                case 9: // Petite suite
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 3) pts += 3;
                    break;
                case 10: // Grande Suite
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 4) pts += 4;
                    break;
                case 11: // Full
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 5) pts += 5;
                    break;
                case 12: // Yahtzee
                    for(unsigned i = 0; i < sizeOfDices; i++) if(*dices[i] == 6) pts += 6;
                    break;
                case 13: // Chance
                    for(unsigned i = 0; i < sizeOfDices; i++) pts += *dices[i];
                    break;
                
                default:
                    break;
            }

            return pts;
        }
};

#endif