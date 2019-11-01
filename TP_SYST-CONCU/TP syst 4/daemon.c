#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "daemon.h"

void signal_handler()
{
    FILE* fichier = NULL;

    fichier = fopen("/tmp/daemon.txt", "w");

    if (fichier != NULL)
    {
        fprintf(fichier, "Coucou, je suis bien en vie\n");
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
}

void signal_handler2()
{
    kill(getpid(), SIGTERM);
}

void daemon2()
{
    pid_t pid, sid;
    pid = fork();

    struct sigaction act, act2;

    // Cas d'échec du fork
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Cas où on est dans le processus père
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Ici, on est dans le processus fils

    // On met le masque à 0 pour donner un accès complet aux fichiers créés par le démon
    umask(0); // rwx-rwx-rwx

    printf("%d\n", pid);

    // On change le SID du ps fils pour le détacher et le garder en vie en cas d'arrêt du processus créateur
    sid = setsid();
    printf("%d\n", sid);

    printf("%d\n", getpid());

    // Cas d'erreur
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Changement de répertoire courant car la racine est le seul répertoire dont l'existence est garantie
    // Cas d'erreur
    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Fermeture des descripteurs de fichiers par défaut (stdin, stdout, stderr)
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    act.sa_handler = signal_handler;
    act2.sa_handler = signal_handler2;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act2, NULL);

    while(1); 
}
