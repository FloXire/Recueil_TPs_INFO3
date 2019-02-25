#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define TCP_port_s 8000

// Main
int main() {

    // Socket serveur
    int sock_S;
    // Message transmis
    char msg[128];
    // Structures des sockets
    struct sockaddr_in sa_S, sa_C;
    // Taille sac ?
    unsigned int size_sa_C;

    // Définition socket
    int new_Sock_S;
    sock_S = socket(PF_INET, SOCK_STREAM, 0);
    // Erreur définition socket
    perror("socket");

    // Mise à zéro des bits correspondants à la structure sockaddr
    bzero((char*) &sa_S, sizeof(struct sockaddr));

    // Définition valeurs sa_S : ip et num port serveur
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_S.sin_port = htons(TCP_port_s);

    // attachement sock_S -> sa_S
    bind(sock_S, (struct sockaddr *) &sa_S, sizeof(struct sockaddr));

    size_sa_C = sizeof(struct sockaddr);

    // definition longueur liste d'attente
    listen(sock_S, 2);
    perror("listen");

    while(1) {

        // acceptation connexion
        new_Sock_S = accept(sock_S, (struct sockaddr *) &sa_C, &size_sa_C);
        perror("accept");


        /* fork ici */

        int fils_pid = fork();

        if (fils_pid < 0) // Erreur fork
        {
            perror("fork : ");
        }
        else if (fils_pid == 0) // c'est le fils
        {
            close(sock_S);
            perror("close");

            // lecture
            read(new_Sock_S, msg, 128*sizeof(char));
            perror("read");

            // fin service
            close(new_Sock_S);
            perror("close");

            // traitement
            printf("tampon : %s\n", msg);

            // fin ps fils
            exit(EXIT_SUCCESS);
        }
        else // c'est le père
        {
            close(new_Sock_S);
            perror("close");
        }

        /* // lecture de ce qu'à envoyé le client
        read(new_Sock_S, msg, 128*sizeof(char));
        perror("read");

        // ecriture (permet de recevoir du client)
        // write(new_Sock_S, "ntm", 10*sizeof(char));

        // Affichage du résultat
    	printf("tampon : %s\n", msg);

        // fin service
        close(new_Sock_S);
        perror("close"); */

    }

    // Fermeture socket
    close(sock_S);
    perror("close");
    // Fermeture
    exit(EXIT_SUCCESS);

    return 0;
}
