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