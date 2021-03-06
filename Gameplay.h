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

        int throwDices(unsigned diceNumber, unsigned *dices, unsigned *choices)
        {
            
            for (unsigned i = 0; i < diceNumber; i++)
            {
                // printf("---------------------------\n");
                // printf("choices[i] = %d && i = %d\n", choices[i], i);
                if(choices[i] == 0) dices[i] = (unsigned)(rand() % 6) + 1;
            }
            return 0;
        }

        int chooseDices(unsigned diceSize, unsigned *choices, unsigned *dices)
        {
            unsigned indexChosen = 0;
            int i;

            for (i = 0; i < diceSize; i++)
            {
                char dicesLeft[63 + 1];
                sprintf(dicesLeft, "Vous pouvez encore garder jusqu'à %d dé(s), c pour quitter :", diceSize - i);

                indexChosen = this->getUserChoice(dicesLeft, 'c');
                
                if(indexChosen == -1) return i;

                if (indexChosen >= 0 && indexChosen < this->DICE_NUMBER && choices[indexChosen] == 0)
                {
                    choices[indexChosen] = dices[indexChosen];
                    printf("Vous avez gardé le dé numéro %d de valeur %d\n", indexChosen + 1, choices[indexChosen]);
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
                if (isChosenDices && choices[i] != 0) printf("Dice %d: %d\n", i + 1, choices[i]);
                if (!isChosenDices && choices[i] == 0) printf("Dice %d: %d\n", i + 1, dices[i]);
            }
            printf("----------------------------------\n");

            return 0;
        }

        int getUserChoice(char *ask, char escape) {
            char choice;
            memset(&choice, 0, sizeof(choice));

            printf("%s", ask);
            std::scanf(" %c", &choice);

            if(choice == escape) return -1;

            return ((int)choice - '0') - 1;
        }

        int getUserPseudo(char *ask, char *output) {      
            printf(" %s", ask);
            std::scanf(" %s", output);

            return 0;
        }
            
};

#endif

