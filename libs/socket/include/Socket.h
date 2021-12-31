#ifndef SOCKET_H
#define SOCKET_H

#include "Monitor.hpp"

#define PORT 6066

extern Monitor mon;


void client_func(int argc, char *argv[]);
void server_func();
void error(char const *msg);

#endif