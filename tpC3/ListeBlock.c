/* include */

#include <stdlib.h>
#include <stdio.h>
#include "Liste.h"
#include "ListeBlock.h"

/* Prototypes */

SCell** CreateBlock();
SCell* getPtrCell();
SCell* delPtrCell();

/* Structures */

struct Block
{
    DataBlock dataBlock;
    //Block *previousBlock;
    Block *followingBlock;
};

struct SListBlock
{
    Block *first;
    Block *last;
    int nbCells;
};

/* Code */

SListBlock* CreateListBlock()
{
    SListBlock *listBlock = (SListBlock*) malloc(sizeof(listBlock));

    if (listBlock == NULL)
    {
        exit(EXIT_FAILURE);
    }

    listBlock->nbBlocks = 0;
    listBlock->first = NULL;
    listBlock->last = NULL;

    return listBlock;
}

Block* createBlock()
{
    Block *newBlock;
    newBlock = (Block*) malloc(sizeof(newBlock));

    if (newBlock == NULL) exit(EXIT_FAILURE);

    //newBlock->previousBlock = NULL;
    newBlock->followingBlock = NULL;

    // Initialisation de toutes les structures à NULL
    for (int i=0; i<SIZE_BLOCK; i++)
    {
        newBlock->dataBlock[i] = NULL;
    }

    return newBlock;
}

SCell* getEmptyCellInBLock(Block *block)
{
    int i=0;
    while (i<SIZE_BLOCK)
    {
        if (block[i] == NULL) return &block[i];
    }

    return NULL;
}

SCell* getPtrNewCell(SCellList *listBlock)
{
    Block currentBlock = listBlock->first;

    while (currentBlock != NULL)
    {
        SCell *newCell = getEmptyCellInBLock(currentBlock);
        if (newCell != NULL)
        {
            return newCell;
        }

        currentBlock = currentBlock->followingBlock;
    }

    Block *newBlock = createBlock();

    // Si la liste est vide
    if (listBlock->first == NULL)
    {
        listBlock->first = newBlock;
    }
    else
    {
        //newBlock->previousBlock = listBlock->last;
        list->last->followingBlock = newBlock;
    }

    listBlock->last = newBlock;
    listBlock->nbBlocks++;

    // On retourne l'adresse de la première cellule du nouveau bloc
    return &(newBlock->dataBlock[0]);
}

/* A faire :  */

// Fonction de suppression d'une cellule (+ potentiellement libération d'un bloc)
// Faire la jonction entre ListeBlock.c et Liste.c (remplacer les malloc par des getPtrCell et les suppression par un appel à la nouvelle fonction d'une cellule)
// Comparaison de l'accélération obtenue
