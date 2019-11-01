#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "affichage.h"
#include "quicksort.h"


// initialise le tableau avec des valeurs aléatoires
void remplirTab(int *tab, int tailleTab)
{
    time_t t;
    srand(time(&t));
    for (int i=0; i<tailleTab; i++)
    {
        tab[i] = rand();
    }
}

int main(int argc, char const *argv[]) {

    int tailleTab = 10;
    int tab[tailleTab];
    remplirTab(tab, tailleTab);

    int (*fctComp)(int, int);
    fctComp = menu();

    if (tailleTab < 20000) printTab(tab, tailleTab);
    printTrie(tab, tailleTab, fctComp);

    quickSort(tab, 0, tailleTab-1, fctComp);

    if (tailleTab < 20000) printTab(tab, tailleTab);
    printTrie(tab, tailleTab, fctComp);

    return 0;
}
