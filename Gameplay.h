#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Player.h"


class Gameplay {

    public:
        Gameplay() {}
        const unsigned LAPS = 3;
        const unsigned DICE_NUMBER = 5;
        const unsigned MAX_PLAYER = 10;
        const unsigned GRID_LENGTH = 13;
        const unsigned TURNS = 13;
        unsigned dices[5];
        unsigned choices[5];

        int throwDices(unsigned diceNumber, unsigned *dices, unsigned *choices)
        {
            
            for (unsigned i = 0; i < diceNumber; i++)
            {
                if(choices[i] == 0) dices[i] = (unsigned)(rand() % 6) + 1;
            }
            return 0;
        }

        int chooseDices(unsigned diceSize, unsigned *dices, unsigned *choices)
        {
            unsigned indexChosen = 0;
            int i;

            for (i = 0; i < diceSize; i++)
            {
                char dicesLeft[63 + 1];
                sprintf(dicesLeft, "You still can choose %d dice(s), select 'c' to quit:", diceSize - i);

                indexChosen = this->getUserChoice(dicesLeft, 'c');
                
                if(indexChosen == -1) return i;

                if (indexChosen >= 0 && indexChosen < this->DICE_NUMBER && choices[indexChosen] == 0)
                {
                    choices[indexChosen] = dices[indexChosen];
                    printf("You chose dice n°%d of value: %d\n", indexChosen + 1, choices[indexChosen]);
                }
                else i--;
            }
            return i;
        }

        int showDices(unsigned *dices, unsigned *choices, unsigned diceNumber, bool isChosenDices)
        {
            const char* presentationText;
            if (isChosenDices) {
                presentationText = "The dices you chose are:";
            } else {
                presentationText = "The dices you thrown are:";
            }

            printf("----------------------------------\n");
            printf("%s\n", presentationText);


            for (unsigned i = 0; i < diceNumber; i++)
            {
                if (isChosenDices && choices[i] != 0) printf("Dice [%d]: %d\n", i + 1, choices[i]);
                if (!isChosenDices && choices[i] == 0) printf("Dice [%d]: %d\n", i + 1, dices[i]);
            }
            printf("----------------------------------\n");

            return 0;
        }

        int getUserChoice(char *ask, char escape) {
            char choice[2];
            memset(&choice, 0, sizeof(choice));

            printf("%s", ask);
            std::scanf(" %s", &choice[0]);

            if(choice[0] == escape) return -1;

            return atoi(choice) - 1; // It's adding +1 for a myterious reason, so we need to substract one...
        }

        int getUserPseudo(char *ask, char *output) {      
            printf(" %s", ask);
            std::scanf(" %s", output);

            return 0;
        }
            
};

#endif

