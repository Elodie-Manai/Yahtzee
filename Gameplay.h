#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Player.h"


class Gameplay {

    public:
        Gameplay() {}
        int laps = 3;
        int diceNumber = 5;
        int maxPlayer = 10;
        int gridLength = 13;
        unsigned dices[5];

        int stockScore(Player *player) {
            player->showScore(this->gridLength);
            unsigned indexChosen = this->getUserChoice("Quelle est la combinaison choisie ?", 'c') + 1;
            
            player->setScore(0, this->dices);
            return 0;
        }

        int makeTurn(Player *player)
        {
            unsigned choices[this->diceNumber];
            unsigned dicesKept = 0;

            memset(this->dices, 0, this->diceNumber);
            memset(&choices, 0, sizeof(choices));
            printf("--- It's your turn %s ---\n", player->getName());

            // will run for at least 1 turn and at most 3 turns
            for (unsigned i = 0; i < this->laps && dicesKept < this->diceNumber; i++)
            {
                printf("--- Turn %d ---\n", i + 1);
                memset(this->dices, 0, this->diceNumber);
                // Throw the dices
                this->throwDices(this->diceNumber, this->dices, choices);

                // Show the dices that were thrown
                this->showDices(this->dices, choices, this->diceNumber, false);
                printf("Choose your dices wisely!\n");

                // Add the chosen dices in choices
                dicesKept += this->chooseDices(this->diceNumber - dicesKept, choices, this->dices);

                // Show the dices kept
                this->showDices(choices, choices, this->diceNumber, true);
            }
            
            // player->setScore(0, choices);
            // player->showScore();
            
            return 0;
        }

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

                if (indexChosen >= 0 && indexChosen < this->diceNumber && choices[indexChosen] == 0)
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
            char buff[sizeof(output)];
            memset(&buff, 0, sizeof(buff));

            printf("%s", ask);
            std::scanf(" %s", &buff[0]);

            sprintf(output, "%s", buff);
            return 0;
        }
            

    private:

        
        
};

#endif

