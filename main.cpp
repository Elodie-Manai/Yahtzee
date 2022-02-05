// #include <iostream>
#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#define LAPS 3
#define DICE_NUMBER 5

int throwDices(unsigned, unsigned *);
int chooseDices(unsigned, unsigned *, unsigned *);
int showDices(unsigned *, unsigned, const char *);

int main()
{
    printf("Welcome to YAHZEE!!!\n");
    printf("----------------------------------\n");

    unsigned dices[DICE_NUMBER];
    unsigned choices[DICE_NUMBER];
    unsigned dicesKept = 0;

    memset(dices, 0, DICE_NUMBER);
    memset(&choices, 0, sizeof(choices));

    for (unsigned i = 0; i < LAPS && dicesKept < DICE_NUMBER; i++)
    {
        printf("--- Turn %d ---\n", i + 1);
        throwDices(DICE_NUMBER - dicesKept, dices);
        showDices(dices, DICE_NUMBER - dicesKept, "The dices you thrown are:");
        printf("Choose your dices wisely!\n");
        dicesKept += chooseDices(DICE_NUMBER - dicesKept, choices, dices);
        showDices(choices, dicesKept, "The dices you chose are:");
        // memset(dices, 0, DICE_NUMBER);
        // memset(&choices, 0, sizeof(choices));
    }
    return 0;
}

int throwDices(unsigned diceNumber, unsigned *input)
{
    for (unsigned i = 0; i < diceNumber; i++)
    {
        input[i] = (unsigned)(rand() % 6) + 1;
    }
    return 0;
}

int chooseDices(unsigned diceNumber, unsigned *input, unsigned *dices)
{
    char choice;
    unsigned index = 0;
    int i;
    // printf("Dice number: %d\n", diceNumber);

    for (i = 0; i < diceNumber && choice != 'c'; i++)
    {
        //choice = '\0';
        printf("Vous pouvez encore garder jusqu'à %d dé(s), c pour quitter :", diceNumber - i);
        memset(&choice, 0, sizeof(choice));
        std::scanf(" %c", &choice);
        // fgets("%c", 1, stdin);
        // cin >> (choice);
        // stdin > choice
        // memset(stdin, 0, sizeof(stdin));
        index = ((int) choice - '0') - 1;
        if (choice == 'c') return i;

        if (index >= 0 && index < diceNumber) {
            input[index] = dices[index];
            printf("Vous avez gardé le dé numéro %d de valeur %d\n", index + 1, input[index]);
        }
        else i--;
    }
    return i;
}

int showDices(unsigned *dices, unsigned count, const char *presentationText) {
    printf("----------------------------------\n");
    printf("%s\n", presentationText);
    for (unsigned i = 0; i < count; i++)
    {
        printf("Dice %d: %d\n", i+1, dices[i]);
    }
    printf("----------------------------------\n");

    return 0;
}