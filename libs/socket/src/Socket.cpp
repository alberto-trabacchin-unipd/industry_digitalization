#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <sstream>
#include <iostream>
#include <string>

#include "Socket.h"
#include "Monitor.hpp"


void client_func(int argc, char *argv[]) {
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
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) error("Error on writing\n");

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);

        if (n < 0) error("Error on reading\n");

        printf("Server: %s", buffer);

        if (strncmp("Bye", buffer, 3) == 0)
            break;
    }
    close(sockfd);
}

void server_func() {

    int sockfd, newsockfd, portno;
    char buffer[256];
    std::stringstream str_value;
    size_t box_id;

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket.\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = PORT;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Binding failed\n");
    
    listen(sockfd, 1);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("Error on accept\n");
    
    while (true) {
        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        std::string response;
        
        if (n < 0) error("Error on reading\n");

        if (strncmp("stop", buffer, 4) == 0) {
            n = write(newsockfd, buffer, strlen(buffer));
            if (n < 0) error("Error on writing\n");
            close(newsockfd);
            close(sockfd);
            return;
        }
        else {
            str_value << buffer;
            str_value >> box_id;
            response = mon.find_box(box_id);
            bzero(buffer, 255);
            strcpy(buffer, response.c_str());
            n = write(newsockfd, buffer, strlen(buffer));

            if (n < 0) error("Error on writing\n");
        }
    }
} 

void error(char const *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void prova() {
    printf("CIao");
}