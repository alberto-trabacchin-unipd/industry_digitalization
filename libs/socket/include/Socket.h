#ifndef SOCKET_H
#define SOCKET_H

#include "Monitor.hpp"

#define PORT 8585

extern Monitor mon;

void server_func();
void error(char const *msg);

#endif