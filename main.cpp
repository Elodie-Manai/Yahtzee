// TODO
// 0 : Afficher la fin (les scores et qui gagne !) - ok
// 1 : Petite Suite ne marche pas, tester les autres combinaisons (Full et 1,2,3,4,5 marchent) - ok
// 2 : Il est actuellement possible de sélectionner plusieurs fois la meme combinaison - ok
// 3 : Verifier que le +35 pts bonus est bien attribué au joueur

/*
    Top : Ok 
    Brelan : Ok
    Carre : Ok
    Petite suite : NOK
    Grande suite : Ok
    Full : Ok
    Yahtzee : Ok
    Chance : Ok
*/

#include <stdio.h> // standard I/O, to inputs and outputs (like printf)
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include "Player.h"
#include "Gameplay.h"

// #define CHEAT

int stockScore(Player *player);
int makeLap(Player *player);

Gameplay gameplay;

int main()
{
    std::srand(time(0)); // Pas besoin de l'initialiser à chaque boucle, gourmand en ressources...
    printf("///////////////////////////////////\n");
    printf("------- Welcome to YAHZEE ! -------\n");
    printf("///////////////////////////////////\n");

    int playersNumber = gameplay.getUserChoice((char *)"How many are you?\t", 'c') + 1;
    if (playersNumber > 0)
    {
        Player players[playersNumber <= gameplay.MAX_PLAYER ? playersNumber : gameplay.MAX_PLAYER];
        printf("Number of players: %d\n", playersNumber);
        char name[40 + 1];

        for (int i = 0; i < playersNumber; i++)
        {
            memset(name, '\0', 41);
            gameplay.getUserPseudo((char *)"What's your little name?\t", name);

            players[i].setName(name);

            printf("Hello %s\n", name);
            printf("----------------------------------\n");
        }

        for (unsigned turns = 0; turns < gameplay.TURNS; turns++)
        {
            printf("--- Turn n°%d ---\n", turns + 1);

            for (int i = 0; i < playersNumber; i++)
            {
                makeLap(&players[i]);
                stockScore(&players[i]);
            }
        }

        printf("///////////////////////////////////\n");
        printf("------------- SCORES -------------\n");
        printf("///////////////////////////////////\n");

        int scores[playersNumber];
        for (int i = 0; i < playersNumber; i++)
        {
            scores[i] = players[i].returnScore();
            printf("- %s: %d\n", players[i].getName(), scores[i]);
        }

        printf("----------------------------------\n");

        printf("///////////////////////////////////\n");
        printf("------- AND THE WINNER IS.. -------\n");
        printf("///////////////////////////////////\n\n\n");

        // Sort scores :
        int bestScore = 0;
        int winner = 0;

        for(int i = 0; i < playersNumber; i++) {
            if(bestScore < scores[i]){
                bestScore = scores[i];
                winner = i;
            }   
        }

        printf("%s !! With %d points !", players[winner].getName(), bestScore);


    }
}

int stockScore(Player *player)
{
    unsigned scoreSet = 1;

    while (scoreSet == 1)
    {
        player->showScore(gameplay.GRID_LENGTH);
        unsigned indexChosen = gameplay.getUserChoice((char *)"Which conbination do you choose?", 'c');

        scoreSet = player->setScore(indexChosen, gameplay.choices);
        if (scoreSet == 1) printf("You can choose a combination only once!\nPlease select another one :)\n");
    }
    return 0;
}

int makeLap(Player *player)
{
    unsigned dicesKept = 0;
    memset(gameplay.dices, 0, gameplay.DICE_NUMBER * sizeof(int));
    memset(gameplay.choices, 0, gameplay.DICE_NUMBER * sizeof(int));
    printf("----------------------------------\n");
    printf("--- Player: %s ---\n", player->getName());
    printf("----------------------------------\n");

    // will run for at least 1 turn and at most 3 turns
    for (unsigned i = 0; i < gameplay.LAPS && dicesKept < gameplay.DICE_NUMBER; i++)
    {
        printf("--- Lap n°%d ---\n", i + 1);
        memset(gameplay.dices, 0, gameplay.DICE_NUMBER);
        // Throw the dices
        gameplay.throwDices(gameplay.DICE_NUMBER, gameplay.dices, gameplay.choices);
        #ifdef CHEAT
                for (unsigned i = 0; i < 5; i++)
                    gameplay.dices[i] = i + 1;
                    // gameplay.dices[3] = 6;
                    // gameplay.dices[4] = 6;
        #endif

        // Show the dices that were thrown
        gameplay.showDices(gameplay.dices, gameplay.choices, gameplay.DICE_NUMBER, false);
        printf("Choose your dices wisely!\n");

        // Add the chosen dices in choices
        dicesKept += gameplay.chooseDices(gameplay.DICE_NUMBER - dicesKept, gameplay.dices, gameplay.choices);

        // Show the dices kept
        gameplay.showDices(gameplay.dices, gameplay.choices, gameplay.DICE_NUMBER, true);
    }

    return 0;
}
