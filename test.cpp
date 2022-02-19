#include <stdio.h> // standard I/O, pour pouvoir gérer l'entrée sortie (genre les printf)
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>

#define LAPS 3
#define DICE_NUMBER 5
#define MAX_PLAYER 10

int printArray(unsigned *, int, bool);
int sortArray(unsigned *, int);
int checkForIdenticals(unsigned *, int, int);

int main()
{
    unsigned dices[DICE_NUMBER];
    dices[0] = 3;
    dices[1] = 2;
    dices[2] = 6;
    dices[3] = 6;
    dices[4] = 6;

    // printArray(dices, DICE_NUMBER, false);

    int n = sizeof(dices) / sizeof(dices[0]);

    // printf("this is n %d\n", n);

    // sortArray(dices, DICE_NUMBER);

    int isYahtzee = checkForIdenticals(dices, DICE_NUMBER, 5);
    int isBrelan = checkForIdenticals(dices, DICE_NUMBER, 3);
    int isCarre = checkForIdenticals(dices, DICE_NUMBER, 4);

    isYahtzee ? printf("A Yahtzee!\n") : printf("Sorry nothing to see here!\n");

    isBrelan ? printf("A Brelan!\n") : printf("Sorry nothing to see here!\n");

    isCarre ? printf("A Carré!\n") : printf("Sorry nothing to see here!\n");

    // printf("You've got %d point\n", pts);

    printArray(dices, DICE_NUMBER, true);

    // for (unsigned i = 0; i < DICE_NUMBER; i++)
    // {
    //     if (dices[i + 1] && dices[i] == dices[i + 1] || dices[i] + 1 != dices[i+1])
    //     {
    //         printf("this is not a Grande Suite!\n");
    //         return 1;
    //     }
    // }
    // printf("this is a Grande Suite!\n");
    return 0;
}

int checkForIdenticals(unsigned *array, int sizeArray, int numberOfIdenticalRequired)
{
    for (unsigned i = 0; i < sizeArray; i++)
    {
        unsigned countOfIdentical = 0;
        unsigned pts = 0;

        for (unsigned j = 0; j < sizeArray; j++) if (array[i] == array[j])countOfIdentical += 1;
        
        if (countOfIdentical >= numberOfIdenticalRequired) return 1;
    }
    return 0;
}

int sortArray(unsigned *array, int sizeArray)
{
    for (unsigned j = 0; j < sizeArray; j++)
    {
        for (unsigned i = 0; i < sizeArray; i++)
        {
            if (array[i + 1] && array[i] > array[i + 1])
            {
                // printf("before sort: \narray[%d] = %d && array[%d] = %d\n", i, array[i], i + 1, array[i + 1]);
                int temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
                // printf("after sort: \narray[%d] = %d && array[%d] = %d\n", i, array[i], i + 1, array[i + 1]);
                i -= 1;
            }
        }
    }

    return 0;
}

int printArray(unsigned *array, int sizeArray, bool isArraySorted)
{
    printf("--------------------------------\n");
    // if (!isArraySorted)
    //   printf("Array before sort:\n");
    if (isArraySorted)
        printf("Your dices:\n");

    for (unsigned i = 0; i < sizeArray; i++)
        printf("%d\n", array[i]);

    printf("--------------------------------\n");
    return 0;
}