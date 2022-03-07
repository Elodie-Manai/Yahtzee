// TODO
// 0 : Faire une fonction qui fonctionne VRAIMENT pour l'input de l'utilisateur - OK
// 1 : Faire la fonction de calcul des points (easy) - OK
// 2 : Faire un array de players avec peut-être un menu pour choisir son pseudo - OK
// 3 : Afficher la fin (les scores et qui gagne !)
// 4 : Je vais ouvrir une mini API pour pouvoir sauvegarder les scores pour la présentation :p - OK
// 5 : il faut qu'on rajout le déblocage des 35 points quand on arrive à 63 points avec 1,2,3,4,5,6 - OK
// 6 : faire une fonction selectCombination() - OK
// 7 : compter les tours et verifier que l'indice de l'array choisi à la fin du tour pour les combinaisons
//     est vide (pas possible de faire deux fois la mmeme combinaison) - OK
// 8 : Petite Suite ne marche pas, tester les autres combinaisons (Full et 1,2,3,4,5 marchent) - EN COURS
// 9 : Si on choisi une combinaison et que l'on ne marque pas de points on peut à nouveau la sélectionner.
//     il faudrait trouver une solution pour ne pas la rechoisir. Je propose de setter le tableau avec des -1
//     au lieu de 0, de cette façon si c'est -1 il est possible de selectionner si c'est 0 on ne peut pas

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

#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
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

        for (int i = 0; i < playersNumber; i++)
        {
            int score = players[i].returnScore();
            printf("- %s: %d\n", players[i].getName(), score);
        }

        printf("----------------------------------\n");
    }
}

int stockScore(Player *player)
{
    player->showScore(gameplay.GRID_LENGTH);
    unsigned indexChosen = gameplay.getUserChoice((char *)"Which conbination do you choose?", 'c');

    player->setScore(indexChosen, gameplay.choices);
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
