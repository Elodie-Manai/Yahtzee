// TODO
// 1 : Faire une fonction qui fonctionne VRAIMENT pour l'input de l'utilisateur - OK
// 2 : Faire la fonction de calcul des points (easy) - OK
// 3 : Faire un array de players avec peut-être un menu pour choisir son pseudo - EN COURS
// 4 : Afficher la fin
// 5 : Je vais ouvrir une mini API pour pouvoir sauvegarder les scores pour la présentation :p
// 6 : il faut qu'on rajout le déblocage des 35 points quand on arrive à 63 points avec 1,2,3,4,5,6 - OK
// 7 : faire un fonction selectCombination()

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
    Player *players[gameplay.maxPlayer];

    char name[40 + 1];
    gameplay.getUserPseudo((char *)"Votre petit nom ?", name);
    Player player = Player(name);

    std::srand(time(0));

    printf("Welcome to YAHZEE !\n");

    printf("----------------------------------\n");

    makeTurn(&player);

    stockScore(&player);
}

int stockScore(Player *player)
{
    player->showScore(gameplay.gridLength);
    unsigned indexChosen = gameplay.getUserChoice((char *)"Quelle est la combinaison choisie ?", 'c') + 1;

    player->setScore(indexChosen, gameplay.dices);
    return 0;
}

int makeTurn(Player *player)
{
    unsigned choices[gameplay.diceNumber];
    unsigned dicesKept = 0;

    memset(gameplay.dices, 0, gameplay.diceNumber);
    memset(&choices, 0, sizeof(choices));
    printf("--- It's your turn %s ---\n", player->getName());

    // will run for at least 1 turn and at most 3 turns
    for (unsigned i = 0; i < gameplay.laps && dicesKept < gameplay.diceNumber; i++)
    {
        printf("--- Turn %d ---\n", i + 1);
        memset(gameplay.dices, 0, gameplay.diceNumber);
        // Throw the dices
        gameplay.throwDices(gameplay.diceNumber, gameplay.dices, choices);

        // Show the dices that were thrown
        gameplay.showDices(gameplay.dices, choices, gameplay.diceNumber, false);
        printf("Choose your dices wisely!\n");

        // Add the chosen dices in choices
        dicesKept += gameplay.chooseDices(gameplay.diceNumber - dicesKept, choices, gameplay.dices);

        // Show the dices kept
        gameplay.showDices(choices, choices, gameplay.diceNumber, true);
    }

    return 0;
}