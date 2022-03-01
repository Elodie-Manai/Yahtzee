// TODO
// 0 : Faire une fonction qui fonctionne VRAIMENT pour l'input de l'utilisateur - OK
// 1 : Faire la fonction de calcul des points (easy) - OK
// 2 : Faire un array de players avec peut-être un menu pour choisir son pseudo - EN COURS
// 3 : Afficher la fin (les scores et qui gagne !)
// 4 : Je vais ouvrir une mini API pour pouvoir sauvegarder les scores pour la présentation :p
// 5 : il faut qu'on rajout le déblocage des 35 points quand on arrive à 63 points avec 1,2,3,4,5,6 - OK
// 6 : faire un fonction selectCombination()
// 7 : compter les tours et verifier que l'indice de l'array choisi à la fin du tour pour les combinaisons
//     est vide (pas possible de faire deux fois la mmeme combinaison)

// #include <iostream>
#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include "Player.h"
#include "Gameplay.h"

int stockScore(Player *player);
int makeTurn(Player *player);

Gameplay gameplay;

int main()
{
    std::srand(time(0)); // Pas besoin de l'initialiser à chaque boucle, gourmand en ressources...
    printf("Welcome to YAHZEE !\n");

    printf("----------------------------------\n");


    int playersNumber = gameplay.getUserChoice((char *)"How many are you?\t", 'c') + 1;
    if (playersNumber > 0)
    {
        Player players[playersNumber <= gameplay.MAX_PLAYER ? playersNumber : gameplay.MAX_PLAYER];
        printf("Nombre de joueurs : %d\n", playersNumber);
        char name[40 + 1];
        
        for (int i = 0; i <= playersNumber; i++)
        {
            memset(name, '\0', 41);
            gameplay.getUserPseudo((char *)"Votre petit nom ?\t", name);

            players[i].setName(name);

            printf("Hello %s\n", name);
        }

        for (unsigned turns = 0; turns < gameplay.TURNS; turns++)
        {
            for (int i = 0; i < playersNumber; i++)
            {
                makeTurn(&players[i]);
                stockScore(&players[i]);
            }
        }
    }
}

int stockScore(Player *player)
{
    player->showScore(gameplay.GRID_LENGTH);
    unsigned indexChosen = gameplay.getUserChoice((char *)"Quelle est la combinaison choisie ?", 'c') + 1;

    player->setScore(indexChosen, gameplay.dices);
    return 0;
}

int makeTurn(Player *player)
{
    unsigned choices[gameplay.DICE_NUMBER];
    unsigned dicesKept = 0;

    memset(gameplay.dices, 0, gameplay.DICE_NUMBER);
    memset(&choices, 0, sizeof(choices));
    printf("--- It's your turn %s ---\n", player->getName());

    // will run for at least 1 turn and at most 3 turns
    for (unsigned i = 0; i < gameplay.LAPS && dicesKept < gameplay.DICE_NUMBER; i++)
    {
        printf("--- Turn %d ---\n", i + 1);
        memset(gameplay.dices, 0, gameplay.DICE_NUMBER);
        // Throw the dices
        gameplay.throwDices(gameplay.DICE_NUMBER, gameplay.dices, choices);

        // Show the dices that were thrown
        gameplay.showDices(gameplay.dices, choices, gameplay.DICE_NUMBER, false);
        printf("Choose your dices wisely!\n");

        // Add the chosen dices in choices
        dicesKept += gameplay.chooseDices(gameplay.DICE_NUMBER - dicesKept, choices, gameplay.dices);

        // Show the dices kept
        gameplay.showDices(choices, choices, gameplay.DICE_NUMBER, true);
    }

    return 0;
}