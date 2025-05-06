#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include"net_client.h"
#define PORT 8080
#define BUFFER_SIZE 1024
#include "net_client.h"
int sockfd;
struct sockaddr_in serv_addr;
char buffer[BUFFER_SIZE ];
fd_set readfds;
int main()
{



        while(1)
        {
            int sock = connect_to_server("105.196.107.28", 8080);
            if (sock < 0)
            {
                printf("error");
                return -1;
            }
            printf("hello");

            int soc_fd=receive_response( sock, buffer, BUFFER_SIZE);
        }


    return 0;
}
