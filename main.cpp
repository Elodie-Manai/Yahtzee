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

int main()
{
    Gameplay gameplay;
    Player *players[gameplay.maxPlayer];


    char name[40 + 1];
    gameplay.getUserPseudo((char *)"Votre petit nom ?", name);
    Player test = Player(name);

    std::srand(time(0));
    
    printf("Welcome to YAHZEE !\n");

    printf("----------------------------------\n");

    gameplay.makeTurn(&test);

    gameplay.stockScore(&test);
}
