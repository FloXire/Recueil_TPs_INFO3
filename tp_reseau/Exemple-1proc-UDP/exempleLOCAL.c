/*
 * exemple.c
 * Exemple d'utilisation des primitives UDP
 *
 */

#include <assert.h>  /* pour insertion messages d'erreur */
#include <stdio.h>   /* pour entree-sorties */
#include <string.h>  /* pour chaine de char */

#include "primitives.h" /* fichier d'entete */

int main (int argc, char **argv)
/* argc : nbre d'arguments
   argv : vecteur d'arguments */
{
    int priseEmission, priseReception;
    char buffer [100]; /* tableau */

    assert (argc == 2); /* erreur si pas 2 arguments */

    priseEmission = creePriseEmission ("127.0.0.1", 1920);
	/* emission vers le port 1920 de la boucle locale */

    priseReception = creePriseReception (1920);
	/* reception sur le port 1920 */

    envoie (priseEmission, argv[1], strlen (argv[1]));
	/* usage : exemple.exe hello
	   emission de "hello" */

    memset (buffer, '\0', 100*sizeof (char));
	/* RAZ buffer */

    recoit (priseReception, buffer, 100*sizeof (char)-1);
	/* reception (ordre bloquant) dans le buffer de "hello" */

    puts (buffer);
	/* ecriture sur sortie standard */
    
    return 0;
}

