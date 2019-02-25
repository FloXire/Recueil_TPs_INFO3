#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#define UDP_port_s 8000

// Main
int main() {

    // Socket serveur
    int sock_S;
    // Message transmis
    char msg[10];
    // Structures des sockets
    struct sockaddr_in sa_S, sa_C;
    // Taille sac ?
    unsigned int size_sa_C;

    // Définition socket
    sock_S = socket(PF_INET, SOCK_DGRAM, 0);
    // Erreur définition socket
    perror("socket");

    // Mise à zéro des bits correspondants à la structure sockaddr
    bzero((char*) &sa_S, sizeof(struct sockaddr));

   // Définition valeurs sa_S
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_S.sin_port = htons(UDP_port_s);

    bind(sock_S, (struct sockaddr *) &sa_S, sizeof(struct sockaddr));

    size_sa_C = sizeof(struct sockaddr);

    while(1) {
	// Récupération du message
	recvfrom(sock_S, msg, 10 * sizeof(char), 0, (struct sockaddr *) &sa_C, &size_sa_C);
	// Affichage du résultat
	printf("%s\n", msg);
	// Envoi réponse
	sendto(sock_S, "ntm", 10 * sizeof(char), 0, (struct sockaddr *) &sa_C, size_sa_C);
    }

    // Fermeture socket
    close(sock_S);
    // Fermeture
    // exit(EXIT_SUCCESS);

    return 0;
}
