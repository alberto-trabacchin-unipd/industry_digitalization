#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>


void error(char const *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("Error opening socket.\n");
    
    server = gethostbyname(argv[1]);

    if (server == NULL)
        fprintf(stderr, "Error, no such host");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Connection failed\n");

    while (true) {
        bzero(buffer, 255);
        printf("\nInserire l'id della scatola da cercare: ");
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) error("Error on writing\n");

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);

        if (n < 0) error("Error on reading\n");

        if (strncmp("stop", buffer, 4) == 0) {
            printf("\nServer: ricevuto ordine di chiusura...\n");
            printf("Client: chiusa connessione tcp/ip\n\n");
            break;
        }
        else {
            printf("Server: %s", buffer);
        }
    }
    close(sockfd);
}