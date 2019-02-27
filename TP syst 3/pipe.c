#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 50
#define IN 0
#define OUT 1

int main ()
{
	char chaine[TAILLE_MAX];
	int  i,pid_fils,tube[2];

	if (pipe(tube)==-1)
	{
		perror("Erreur lors de la création du tube : "); 
		exit(1);
	}
	if ((pid_fils=fork())==-1)
	{ 
		perror("Erreur dans la création du processus fils : ");
		exit(2);
	}

	if (pid_fils>0)
	{
		close(tube[IN]);
		// Emission
		for (i=0;i<10;i++)
		{
			sprintf(chaine,"chaine de caracteres %i",i);
			write(tube[OUT],chaine,TAILLE_MAX);
			printf("Emission de : \"%s\"\n",chaine);
			sleep(2);
		}
		wait(NULL);
	}
	else
	{
		close(tube[OUT]);
		// Reception
		for (i=0;i<10;i++)
		{
			read(tube[IN],chaine,TAILLE_MAX);
			printf("Je recois : \"%s\"\n",chaine);
		}
	}
	return(0);
}
