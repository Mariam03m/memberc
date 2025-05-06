
#include "client_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h> // for ntohl if needed

void display_ls(const char *data) {
    printf("Server Directory Listing:\n%s\n", data);
}

void show_progress(long received, long total) {
    int percent = (int)((received * 100) / total);
    printf("\rDownloading: %ld/%ld bytes (%d%%)", received, total, percent);
    fflush(stdout);
}

void download_file(int sockfd, const char *filename, long offset) {
    char buffer[4096];
    long received = offset;
    long total = 0;
    ssize_t bytes;

    // Receive total file size from server (assumes both server/client are same architecture)
    if (read(sockfd, &total, sizeof(total)) != sizeof(total)) {
        perror("Failed to read file size");
        return;
    }

    // Optional: Convert from network byte order if server sends with htonl/htonll
    // total = ntohl(total); // if server uses htonl

    int fd = open(filename, offset > 0 ? O_WRONLY | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    while ((bytes = read(sockfd, buffer, sizeof(buffer))) > 0) {
        ssize_t written = write(fd, buffer, bytes);
        if (written < 0) {
            perror("Error writing to file");
            break;
        }
        received += written;
        show_progress(received, total);
        if (received >= total) break;
    }

    if (bytes < 0) {
        perror("Error reading from socket");
    } else if (received < total) {
        fprintf(stderr, "\nDownload incomplete. Expected %ld bytes, received %ld bytes.\n", total, received);
    } else {
        printf("\nDownload complete.\n");
    }

    close(fd);
}

void handle_quit() {
    printf("\nDisconnecting from server. Goodbye!\n");
}
