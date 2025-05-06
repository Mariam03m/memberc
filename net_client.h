#ifndef NET_CLIENT_H
#define NET_CLIENT_H

#include <stdio.h>

int connect_to_server(const char *ip, int port);
int send_command(int sockfd, const char *cmd);
int receive_response(int sockfd, char *buffer, int size);
void disconnect(int sockfd);

#endif // NET_CLIENT_H

