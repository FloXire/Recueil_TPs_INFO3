#include <stdio.h>
#include "affichage.h"
#include "comparaison.h"

// affiche le tableau
void printTab(int *tab, int tailleTab)
{
    for (int i=0; i<tailleTab; i++)
    {
        printf("%16d\n", tab[i]);
    }
}

// retourne 1 si le tableau est trié, 0 sinon
int verifTabTrie(int *tab, int tailleTab, int (*fctComp)(int, int))
{
    for (int i=0; i<(tailleTab-1); i++)
    {
        if (fctComp(tab[i+1], tab[i])) return 0;
    }
    return 1;
}

void printTrie(int *tab, int tailleTab, int (*fctComp)(int, int))
{
    if (verifTabTrie(tab, tailleTab, fctComp) != 1)
    {
        printf("Tableau non trié\n\n");
    }
    else printf("Tableau trié\n\n");
}

int (*menu(void))(int, int)
{
    int (*listeFonction[2])(int, int) = {triCroissant, triDecroissant};
    int typeFct;

    printf("Quelle fonction de comparaison voulez vous utiliser ?\n");
    printf("Entrez 1 pour un tri croissant\n");
    printf("Entrez 2 pour un tri décroissant\n");
    printf("Votre choix : ");
    scanf("%d", &typeFct);

    return listeFonction[typeFct-1];
}
