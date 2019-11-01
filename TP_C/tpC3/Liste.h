#ifndef _LISTE_H
	#define _LISTE_H

typedef struct SCell SCell;
typedef struct SList SList;

union typeData
{
	int i;
	SCell **block;
};

typedef union typeData Data;

SList* CreateList();
void DeleteList(SList *list);

SCell* AddElementBegin(SList *list,Data elem);
SCell* AddElementEnd(SList *list,Data elem);
SCell* AddElementAfter(SList *list,SCell *cell,Data elem);
void DeleteCell(SList *list,SCell *cell);

SCell* GetFirstElement(SList *list);
SCell* GetLastElement(SList *list);
SCell* GetPrevElement(SCell *cell);
SCell* GetNextElement(SCell *cell);
Data GetData(SCell *cell);

#endif
