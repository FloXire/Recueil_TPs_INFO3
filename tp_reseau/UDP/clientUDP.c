#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


#define UDP_port_s 8000
#define IP_addr_S "127.0.0.1"

int main ()
{
    int sock_C;

    // Message transmis
    char message[10];
    // Taille sac
    unsigned int taille_sa_S;
    struct sockaddr_in sa_S;

    // création socket client
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);
    perror("socket");

    // IP et num port server
    bzero((char*) &sa_S, sizeof(sa_S));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = inet_addr( IP_addr_S );
    sa_S.sin_port = htons( UDP_port_s );

    //emission vers le serveur à partir du client
    taille_sa_S = sizeof( struct sockaddr );
    sendto(sock_C, "salut", 10*sizeof(char), 0, (struct sockaddr*) &sa_S, taille_sa_S);

    // reception du serveur et affichage
    recvfrom(sock_C, message, 10*sizeof(char), 0, (struct sockaddr*) &sa_S, &taille_sa_S);

    printf("%s\n", message);

    close(sock_C);
    exit(EXIT_SUCCESS);
}
