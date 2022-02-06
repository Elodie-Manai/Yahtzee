// ----- TODO -----
// ================
//
// Pour permettre de lancer les dés manquants :
// ajouter choices en attribut dans throwDices()
// trier les index à 0 de choices, pour ne relancer le random quand pour ces index là
// ne montrer que les nouveaux dés lancés, avec leur vrai index + 1, 
// pour permettre de remplis les index à 0 dans choices
//
// ================

// #include <iostream>
#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#define LAPS 3
#define DICE_NUMBER 5

int throwDices(unsigned, unsigned *, unsigned *);
int chooseDices(unsigned, unsigned *, unsigned *);
int showDices(unsigned *, unsigned *, unsigned, bool);
// int hasBeenChosen(unsigned, unsigned *, unsigned);

int main()
{
    std::srand(time(0));

    printf("Welcome to YAHZEE!!!\n");
    printf("----------------------------------\n");

    unsigned dices[DICE_NUMBER];
    unsigned choices[DICE_NUMBER];
    unsigned dicesKept = 0;

    memset(dices, 0, DICE_NUMBER);
    memset(&choices, 0, sizeof(choices));

    // will run for at least 1 turn and at most 3 turns
    for (unsigned i = 0; i < LAPS && dicesKept < DICE_NUMBER; i++)
    {
        printf("--- Turn %d ---\n", i + 1);
        // Throw the dices
        throwDices(DICE_NUMBER, dices, choices);

        // Show the dices that were thrown
        showDices(dices, choices, DICE_NUMBER, false);
        printf("Choose your dices wisely!\n");

        // Add the chosen dices in choices
        dicesKept += chooseDices(DICE_NUMBER - dicesKept, choices, dices);

        // Show the dices kept
        showDices(choices, choices, DICE_NUMBER, true);
    }
    return 0;
}

int throwDices(unsigned diceNumber, unsigned *dices, unsigned *choices)
{
    unsigned i = 0;
    for (i; i < diceNumber && choices[i] == 0; i++)
    {
        // printf("---------------------------\n");
        // printf("choices[i] = %d && i = %d\n", choices[i], i);
        dices[i] = (unsigned)(rand() % 6) + 1;
    }
    return 0;
}

int chooseDices(unsigned diceSize, unsigned *choices, unsigned *dices)
{
    char choice;
    unsigned indexChosen = 0;
    int i;

    for (i = 0; i < diceSize && choice != 'c'; i++)
    {
        printf("Vous pouvez encore garder jusqu'à %d dé(s), c pour quitter :", diceSize - i);
        memset(&choice, 0, sizeof(choice));
        std::scanf(" %c", &choice);
        indexChosen = ((int)choice - '0') - 1;
        if (choice == 'c')
            return i;
        
        if (indexChosen >= 0 && indexChosen < diceSize)
        {
            choices[indexChosen] = dices[indexChosen];
            printf("Vous avez gardé le dé numéro %d de valeur %d\n", indexChosen + 1, choices[indexChosen]);
        }
        else
            i--;
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

// int hasBeenChosen(unsigned diceNumberIndex, unsigned *input, unsigned choicesLength)
// {
//     printf("diceNumberIndex %d, choicesLength %d\n", diceNumberIndex, choicesLength);
//     for (unsigned i = 0; i < choicesLength; i++)
//     {
//         if (i == input[diceNumberIndex])
//             return 1;
//     }
//     return 0;
// }