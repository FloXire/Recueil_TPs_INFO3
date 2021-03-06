#include "quicksort.h"
#include "comparaison.h"

void switche(int *tab, int ind1, int ind2)
{
    int temp = tab[ind1];
    tab[ind1] = tab[ind2];
    tab[ind2] = temp;
}

int quickSort(int *tab, int ind1, int ind2, int (*fctComp)(int, int))
{
    int nbElmts = ind2-ind1+1; // Nombre d'éléments dans la partie du tableau que l'on traite
    // Si on a un ou deux éléments dans cette partie du tableau on arrête la récursion
    if (nbElmts <= 2)
    {
        if ((nbElmts == 2) && fctComp(tab[ind2], tab[ind1])) switche(tab, ind1, ind2);
        // Terminaison de la récursion
        return 0;
    }

    int i = ind1+1;
    int j = ind2;
    int pivot = tab[ind1];

    while (i<j)
    {
        /* On incrémente i de 1 si l'élément à l'indice i est
        plus petit que le pivot. De la même façon on décrémente j
        si l'élément à l'indice j est plus grand que le pivot */
        if (fctComp(tab[i],pivot) || fctComp(pivot, tab[j]))
        {
            if (fctComp(tab[i], pivot)) i++;
            if (fctComp(pivot, tab[j])) j--;
        }
        /* Sinon, on switch les deux valeurs, on se retrouve
         avec la plus petite des deux valeurs dans la première
         partie du tableau et la plus grande dans la deuxième */
        else
        {
            switche(tab, i, j);
            i++;
            j--;
        }
    } // à partir d'ici i == j
    if (fctComp(pivot,tab[j]))
    {
        switche(tab, ind1, j);
    }

    // Appel récursif sur la partie gauche du tableau
    quickSort(tab, ind1, j-1, fctComp);

    // Appel récursif sur la partie droite du tableau
    quickSort(tab, i, ind2, fctComp);

    return 0;
}

/*
int quickSort(int *tab, int ind1, int ind2, int (*fctComp)(int, int))
{
    (*fctComp)(ind1, ind2);

    return 0;
}
*/
