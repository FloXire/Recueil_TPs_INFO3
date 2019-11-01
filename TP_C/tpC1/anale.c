#include "anale.h"
#include <stdio.h>
#include <string.h>



int isChevron(char c) {

    if (c == '<') return 1;
    else if (c == '>') return 2;
    else return 0;

}


void lectFic(char const *nomFic)
{
    FILE *fp; // pointeur fichier
    char c;
    char balise[10];
    int lect = 0;

    if ((fp=fopen(nomFic, "rt")))
    {

        for (c=fgetc(fp); !feof(fp); c=fgetc(fp)) // le 2ème fgetc est executé à la fin de la boucle
        {

            if (lect == 1)
            {
                if((isChevron(c) != 2) || (c != ' '))
                {
                    strcat(balise, &c);
                }
                else
                {
                    lect = 0;
                    printf("%s\n", balise);
                    balise = "";
                }
            }


            else if (isChevron(c) == 1)
            {
                lect = 1;
            }

        }
        fclose(fp);
    }
    else printf("Erreur d'ouverture du fichier\n");
}


int main(int argc, char const *argv[]) {
    /* code */

    lectFic(argv[1]);

    return 0;
}
