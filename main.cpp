#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <cstring>
#define LAPS 3
#define DICE_NUMBER 5

int throwDices(unsigned, unsigned *);
int chooseDices(unsigned, unsigned *, unsigned *);

int main()
{
    unsigned dices[DICE_NUMBER];
    unsigned choices[DICE_NUMBER];
    unsigned dicesKept = 0;

    for (unsigned i = 0; i < LAPS && dicesKept < DICE_NUMBER; i++)
    {
            printf("turn %d\n", i + 1);
            throwDices(DICE_NUMBER - dicesKept, dices);
            // choose dices to keep
            dicesKept += chooseDices(DICE_NUMBER - dicesKept, choices, dices);
            memset(dices, 0, DICE_NUMBER);
    }

    return 0;
}

int throwDices(unsigned diceNumber, unsigned *input)
{
    for (unsigned i = 0; i < diceNumber; i++)
    {
        input[i] = (unsigned)(rand() % 6) + 1;
        printf("%d\n", input[i]);
    }
    return 0;
}

int chooseDices(unsigned diceNumber, unsigned *input, unsigned *dices)
{
    char choice;
    int i;
    for (i = 0; i < diceNumber && choice != 'c'; i++)
    {
        scanf(&choice);
        if (choice != 'c')
        {
            choice = (unsigned)choice - 1;
            if (choice >= 0 && choice <= diceNumber)
            {
                input[choice] = dices[choice];
            }
            else
            {
                i--;
            }
        }
    }
    return i;
}

int showDices() {}