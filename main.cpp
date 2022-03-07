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
// 8 : Petite Suite ne marche pas, tester les autres combinaisons (Full et 1,2,3,4,5 marchent)


// Top : 1 : Ok, 2 : 
// Petite suite : NOK
//

#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include "Player.h"
#include "Gameplay.h"

#define CHEAT

int stockScore(Player *player);
int makeLap(Player *player);

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
        
        for (int i = 0; i < playersNumber; i++)
        {
            memset(name, '\0', 41);
            gameplay.getUserPseudo((char *)"Votre petit nom ?\t", name);

            players[i].setName(name);

            printf("Hello %s\n", name);
        }

        for (unsigned turns = 0; turns < gameplay.TURNS; turns++)
        {
            printf("--- Turn %d ---\n", turns + 1);
            for (int i = 0; i < playersNumber; i++)
            {
                makeLap(&players[i]);
                stockScore(&players[i]);
            }
        }
    }
}

int stockScore(Player *player)
{
    player->showScore(gameplay.GRID_LENGTH);
    unsigned indexChosen = gameplay.getUserChoice((char *)"Quelle est la combinaison choisie ?", 'c');

    player->setScore(indexChosen, gameplay.choices);
    return 0;
}

int makeLap(Player *player)
{
    unsigned dicesKept = 0;
    memset(gameplay.dices, 0, gameplay.DICE_NUMBER * sizeof(int));
    memset(gameplay.choices, 0, gameplay.DICE_NUMBER * sizeof(int));

    printf("--- It's your turn %s ---\n", player->getName());

    // will run for at least 1 turn and at most 3 turns
    for (unsigned i = 0; i < gameplay.LAPS && dicesKept < gameplay.DICE_NUMBER; i++)
    {
        printf("--- Lap %d ---\n", i + 1);
        memset(gameplay.dices, 0, gameplay.DICE_NUMBER);
        // Throw the dices
        gameplay.throwDices(gameplay.DICE_NUMBER, gameplay.dices, gameplay.choices);
#ifdef CHEAT
        for(unsigned i = 0; i < 5; i++) gameplay.dices[i] = 2;
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