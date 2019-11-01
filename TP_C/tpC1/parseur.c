#include "anale.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void initPile() {

}


int isChevron(char c) {

    if (c == '<') return 1;
    else if (c == '>') return 2;
    else return 0;

}


int main(int argc, char const *argv[]) {

    enum Etats
    {
        attenteBalise,
        lectureBalise
    };

    enum Etats etat;
    etat = attenteBalise;

    FILE *fp; // pointeur fichier
    char c;
    char *pile[255];

    /*for (int i = 0; i < 255; i++) {
        pile[i] = (char *) malloc(sizeof(char)*10);
    }*/

    int pointeurPile = 0;
    char tempBalise[11];

    if ((fp=fopen(argv[1], "rt")))
    {
        for (c=fgetc(fp); !feof(fp); c=fgetc(fp)) // le 2ème fgetc est executé à la fin de la boucle
        {

            switch (etat)
            {
                case attenteBalise: // on attend un chevron ouvrant
                    if (isChevron(c) == 1)
                    {
                        etat = lectureBalise;
                    }
                    break;

                case lectureBalise:
                    if (isChevron(c) == 2)
                    {
                        strcat(tempBalise, "\0");
                        pile[pointeurPile] = tempBalise;
                        printf("%s\n", pile[pointeurPile]);
                        pointeurPile ++;
                        etat = attenteBalise;
                        tempBalise[0] = '\0';
                    }
                    else
                    {
                        strcat(tempBalise, &c);
                    }
                break;
            }

        }
        fclose(fp);
    }
    else printf("Erreur d'ouverture du fichier\n");

    return 0;
}
