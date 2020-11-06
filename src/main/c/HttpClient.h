#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sock;
char buffer[256];
struct sockaddr_in server;

#endif
