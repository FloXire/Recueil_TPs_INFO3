/* include */

#include <stdlib.h>
#include <stdio.h>
#include "Liste.h"

/* Define */

#define SIZE_BLOCK 10

/* Prototypes */

SCell** CreateBlock();
SCell* getPtrCell();
SCell* delPtrCell();

/* Structures */

struct SCell
{
    Data value;
    SCell *previousCell;
    SCell *followingCell;
};

struct SList
{
    SCell *first;
    SCell *last;
    int nbCells;
    SList *block;
};

/* Code */

SCell** CreateBlock()
{
    SCell** blocRetour;
    blocRetour = (SCell**) malloc(sizeof(SCell)*SIZE_BLOCK);
    for (int i=0; i<SIZE_BLOCK; i++)
    {
        blocRetour[i] = NULL;
    }

    return blocRetour;
}

// On veut allouer une adresse à une cellule
SCell* getPtrCell(SList *list)
{
    int i = 0;

    while (list->block[i] = NULL && i<SIZE_BLOCK)
    {
        /* code */
    }
    if (list->)
}

SCell* delPtrCell()
{

}
