/*
 *	Problème des Lecteurs rédacteurs
 *	bibliothèque pthread
 *	Solution avec semaphores mutex uniquement
 *	
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "macros-thread.h"
#include "tprintf.h"


/* Notions Globales */

#define NBTHREADS 6

int nbLecteurs = 0;

/* -- A COMPLETER -- */
/* declarer les semaphores mutex */



/* Fonction principales des threads "redacteur" */
void * redacteur(void * arg) {
	char * nom = *(char **)arg;

	tprintf("debut thread redacteur %s\n", nom);

	/* -- A COMPLETER -- */
	/* gerer la synchronisation lecteurs/redacteurs */

		tprintf("%s ecrit...\n", nom);
		sleep(5+rand()%6);
		tprintf("%s : nbLecteurs=%i\n", nom, nbLecteurs);
		tprintf("%s a fini d ecrire...\n", nom);

	/* -- A COMPLETER -- */
	/* gerer la synchronisation lecteurs/redacteurs */

	tprintf("fin thread redacteur %s\n", nom);
	pthread_exit(0);
}

/* Fonction principales des threads "lecteur" */
void * lecteur(void * arg) {
	char * nom = *(char **)arg;

	tprintf("debut thread lecteur %s\n", nom);

	/* -- A COMPLETER -- */
	/* gerer la synchronisation lecteurs/redacteurs */

		tprintf("%s lit...\n", nom);
		sleep(1+rand()%3);
		tprintf("%s a fini de lire...\n", nom);

	/* -- A COMPLETER -- */
	/* gerer la synchronisation lecteurs/redacteurs */

	tprintf("fin thread lecteur %s\n", nom);
	pthread_exit(0);
}

/* Fonction principales de demarrage et de creation des threads  */
int main ()
{
	pthread_t threads[NBTHREADS];
	char * nomsThreads[NBTHREADS]={"r1", "w1","r2", "r3", "w2", "r4"};
	void * (* thread_main) (void *);
	int i, errcode;

	/* -- A COMPLETER -- */
	/* initialiser les semaphores mutex */

	/* Creation des threads lecteurs et redacteurs */
	for ( i=0; i<NBTHREADS; i++ ){
		if ( nomsThreads[i][0]=='w' ) {
			thread_main = redacteur;
		} else if ( nomsThreads[i][0]=='r' ) {
			thread_main = lecteur;
		}
		errcode=pthread_create (&threads[i], NULL, thread_main, &nomsThreads[i]);
		if ( errcode != 0 ) {
			fprintf(stderr, "Erreur de creation du thread %s\n", nomsThreads[i]);
		}
	}

	/* Attente de terminaison de tous les threads */
	for (i=0; i<NBTHREADS; i++) {
		errcode=pthread_join (threads[i], NULL);
		if (errcode) { 
			fprintf(stderr, "erreur pthread_join pour le thread %s\n", nomsThreads[i]);
			exit(EXIT_FAILURE);
		}
	}

	/* -- A COMPLETER -- */
	/* Detruire les semaphores mutex */


	exit(EXIT_SUCCESS);
}

