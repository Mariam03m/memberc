#include "net_client.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int connect_to_server(const char *ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed");
        close(sockfd);
        return -1;
    }

    printf("Connected to server.\n");
    return sockfd;
}



int send_command(int sockfd, const char *cmd)
{
    if (cmd == NULL) return -1;


    if (strcasecmp(cmd, "EXIT") == 0) {
        printf("Exiting client...\n");
        close(sockfd);
        return -1;
    }


    ssize_t bytes_sent = send(sockfd, cmd, strlen(cmd), 0);
    if (bytes_sent < 0) {
        perror("send failed");
        return -1;
    }

    return 0;
}



 int receive_response(int sockfd, char *buffer, int BUFFER_SIZE) {
    if (buffer == NULL || BUFFER_SIZE <= 1) return -1;

    ssize_t bytes_recv = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_recv < 0) {
        perror("recv failed");
        return -1;
    } else if (bytes_recv == 0) {
        printf("Server closed the connection.\n");
        return -1;
    }

    buffer[bytes_recv] = '\0';
    printf("Server: %s\n", buffer);

    return 0;

}


