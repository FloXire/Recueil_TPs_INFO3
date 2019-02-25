#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


#define TCP_port_s 8000
#define IP_addr_S "127.0.0.1"

int main (argc, argv)
int argc;
char * argv[];
{
    int sock_C;

    // Message transmis
    char message[128];
    // Taille sac
    unsigned int size_sa_S;
    struct sockaddr_in sa_S;
    char C;

    if (argc == 1)
    {
        printf("usage : ./clientTCP.out message\n");
        exit(EXIT_SUCCESS);
    }

    // argv[1] --> message
    sprintf(message, "%s", argv[1]);

    // création socket client, pas de bind -> ephémère
    sock_C = socket(PF_INET, SOCK_STREAM, 0);
    perror("socket");

    // IP et num port server
    bzero((char*) &sa_S, sizeof(sa_S));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = inet_addr(IP_addr_S);
    sa_S.sin_port = htons(TCP_port_s);

    size_sa_S = sizeof(sa_S);

    connect(sock_C, (struct sockaddr *) &sa_S, size_sa_S);
    perror("connect");

    // lecture
    write(sock_C, message, 128*sizeof(char));
    perror("write");

    close(sock_C);
    perror("close");

    exit(EXIT_SUCCESS);
}
