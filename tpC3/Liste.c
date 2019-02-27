#include <stdlib.h>
#include <stdio.h>
#include "Liste.h"

struct SCell
{
    Data value;
    struct SCell *previousCell;
    struct Scell *followingCell;
};

struct SList
{
    struct SCell *first;
    struct SCell *last;
    int nbCells;
};

SList* CreateList()
{
    SList *list = malloc(sizeof(list));

    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    list->nbCells = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void DeleteList(SList *list)
{

    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }
    else if (list->nbCells == 0)
    {
        printf("Liste vide\n");
    }
    else
    {
        SCell *currentCell;
        SCell *nextCell;

        nextCell = list->last;

        while (nextCell->previousCell != NULL)
        {
            currentCell = nextCell;
            nextCell = nextCell->previousCell;
            free(currentCell);
        }
    }

    free(list);

    printf("Liste supprimée\n");
}

SCell* AddElementBegin(SList *list,Data elem)
{
    SCell *newCell;

    newCell = malloc(sizeof(newCell));

    if (list == NULL || newCell == NULL)
    {
        exit(EXIT_FAILURE);
    }

    newCell->value = elem;
    newCell->previousCell = NULL;

    // Si la liste est vide :
    if (list->first == NULL)
    {
        newCell->followingCell = NULL;
        list->last = newCell;
    }
    else
    {
        newCell->followingCell = list->first;
        list->first->previousCell = newCell;
    }

    list->first = newCell;
    list->nbCells++;

    return newCell;
}

SCell* AddElementEnd(SList *list,Data elem)
{
    SCell *newCell;

    newCell = malloc(sizeof(newCell));

    if (list == NULL || newCell == NULL)
    {
        exit(EXIT_FAILURE);
    }

    newCell->value = elem;
    newCell->followingCell = NULL;

    // Si la liste est vide :
    if (list->last == NULL)
    {
        newCell->previousCell = NULL;
        list->first = newCell;
    }
    else
    {
        newCell->previousCell = list->last;
        list->last->followingCell = newCell;
    }

    list->last = newCell;
    list->nbCells++;

    return newCell;
}










YA UN TRUC A CHECK ICI

SCell* AddElementAfter(SList *list,SCell *cell,Data elem)
{
    SCell *newCell;

    newCell = malloc(sizeof(newCell));

    if (list == NULL || newCell == NULL)
    {
        exit(EXIT_FAILURE);
    }

    newCell->value = elem;

    // Si la liste est vide :
    if (list->first == NULL)
    {
        printf("Cette liste ne contient aucune cellule\n");
        // Par convention on retourne le pointeur de la cellule passée en paramètre
        return cell;
    }
    else
    {
        if (cell != list->last)
        {
            newCell->followingCell = cell->followingCell;
        }
        else
        {
            cell->followingCell->previousCell = cell->previousCell;
            cell->prev cell->followingCell;
            newCell->previousCell = cell;
            cell->followingCell->previousCell = newCell;
            cell->followingCell = newCell;
        }
        // Sinon on est dans le cas où on ajoute une cellule à la fin
        else
        {
            AddElementEnd(list, elem);
        }
    }

    list->nbCells++;

    return newCell;
}

void DeleteCell(SList *list,SCell *cell)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Si la liste est vide :
    if (list->nbCells == 0)
    {
        printf("Cette liste ne contient aucune cellule, impossible de supprimer la votre\n");
    }
    else if (list->nbCells == 1)
    {
        list->first = NULL;
        list->last = NULL;
        free(cell);
    }
    // Si la liste comporte au moins 2 cellules
    else
    {
        // Si la cellule a supprimer est la première ou la dernière
        // Si on rentre dans ce if, la cellule ne peut pas être la première ET la dernière
        if ((cell->followingCell == NULL) || (cell->previousCell == NULL))
        {
            // Si la cellule a supprimer est la dernière
            if (cell->followingCell == NULL)
            {
                cell->previousCell->followingCell = NULL;
                list->last = cell->previousCell;
            }
            // Sinon c'est la première
            else
            {
                cell->followingCell->previousCell = NULL;
                list->first = cell->followingCell;
            }
        }
        // Si la cellule est comprise entre deux autres cellules
        else
        {
            cell->followingCell->previousCell = cell->previousCell;
            cell->previousCell->followingCell = cell->followingCell;
        }

        list->nbLinks--;
        free(cell);
    }
}

SCell* GetFirstElement(SList *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    return list->first;
}

SCell* GetLastElement(SList *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    return list->last;
}

SCell* GetPrevElement(SCell *cell)
{
    return cell->previousCell;
}


SCell* GetNextElement(SCell *cell)
{
    return cell->previousCell;
}


Data GetData(SCell *cell)
{
    return cell->value;
}
