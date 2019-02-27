#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_MAX 5000
#define IN 0
#define OUT 1


int main ()
{
	int  i,pid_fils,tube[2];

	if (pipe(tube)==-1)
	{
		perror("Erreur lors de la cr�ation du tube : ");
		exit(1);
	}
	if ((pid_fils=fork())==-1)
	{
		perror("Erreur dans la cr�ation du processus fils : ");
		exit(2);
	}

	if (pid_fils>0)
	{
		close(tube[IN]);
		// Emission

		write(tube[OUT],system("ls -al"),20000);
		printf("Emission de ls -al\n");
		sleep(2);

		wait(NULL);
	}
	else
	{
        char *chaine;
		close(tube[OUT]);
		// Reception
		read(tube[IN],chaine,TAILLE_MAX);
		printf("Je recois : \"%s\"\n",chaine);
	}
	return(0);
}
