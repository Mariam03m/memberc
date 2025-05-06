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
#include "client_ui.h"


int main() {
    int sockfd = connect_to_server("127.0.0.1", 8080);
    if (sockfd < 0) return 1;

    char cmd[256], buffer[1024];
    while (1) {
        printf("> ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "quit") == 0) break;

        send_command(sockfd, cmd);
        receive_response(sockfd, buffer, sizeof(buffer));

        if (strncmp(cmd, "ls", 2) == 0) {
            display_ls(buffer);
        } else if (strncmp(cmd, "get", 3) == 0) {
            char *filename = strchr(cmd, ' ');
            if (filename) download_file(sockfd, filename + 1, 0);
        } else {
            printf("%s\n", buffer);
        }
    }

    close(sockfd);
    return 0;
}
