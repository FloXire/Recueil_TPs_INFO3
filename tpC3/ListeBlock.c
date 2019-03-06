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
    DataBlock value;
    Block *previousBlock;
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

    listBlock->nbCells = 0;
    listBlock->first = NULL;
    listBlock->last = NULL;

    return listBlock;
}


Block* CreateBlock()
{
    Block *newBlock;
    newBlock = (Block*) malloc(sizeof(newBlock));
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
    if (listBlock->first != NULL)
    {
        Block currentBlock = listBlock->first;
    }
    else // La liste de bloc est vide, on créé un premier bloc
    {

    }

    while (currentBlock != NULL)
    {
        SCell *newCell = getEmptyCellInBLock(currentBlock);
        if (newCell != NULL)
        {
            return newCell;
        }
    }

    // Ici, on n'a pas trouvé de places disponibles -> on créé un nouveau bloc à la fin



}
