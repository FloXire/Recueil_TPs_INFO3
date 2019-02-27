#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H

typedef struct Link_s
{
    struct Link_s *previousLink;
    int data;
    struct Link_s *followingLink;
} Link;

typedef struct LinkedList_s
{
    int nbLinks;
    Link *first;
    Link *last;
} LinkedList;

LinkedList *initList(void);
int displayList(LinkedList *list);
int displayReverseList(LinkedList *list);
void insertEnd(LinkedList *list, int data);
void insertStart(LinkedList *list, int data);
int insertInd(LinkedList *list, int data, int ind);
int deleteEnd(LinkedList *list);
int deleteStart(LinkedList *list);
int deleteInd(LinkedList *list, int ind);
int deleteList(LinkedList *list);

#endif
