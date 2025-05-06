#ifndef CLIENT_UI_H
#define CLIENT_UI_H

#include <stdio.h>

/*
 * Function: display_ls
 * --------------------
 * Prints the server's directory listing to the console.
 *
 * Parameters:
 *   - data: A string received from the server, containing filenames/folders.
 *
 * Purpose:
 *   Called when the server sends the result of an "ls" or "list" command.
 */
void display_ls(const char *data);

/*
 * Function: show_progress
 * -----------------------
 * Displays a dynamic progress message while downloading a file.
 *
 * Parameters:
 *   - received: Number of bytes received so far.
 *   - total: Total number of bytes expected for the file.
 *
 * Purpose:
 *   Used to inform the user of download progress in real time.
 *   Can be reused anywhere download progress needs to be shown.
 */
void show_progress(long received, long total);

/*
 * Function: download_file
 * -----------------------
 * Handles file download from the server over a socket.
 *
 * Parameters:
 *   - sockfd: The socket file descriptor to receive data from.
 *   - filename: The local filename to save the downloaded content.
 *   - offset: Number of bytes already downloaded (used to resume).
 *
 * Purpose:
 *   Downloads a file from the server, resuming if needed, and displays progress.
 *   Receives the total size from the server first, then writes chunks to file.
 *   Relies on show_progress to update the user.
 *
 * Notes:
 *   - Creates or appends to file as needed.
 *   - Closes the file automatically after the transfer.
 *   - Prints success message after completion.
 */
void download_file(int sockfd, const char *filename, long offset);

/*
 * Function: handle_quit
 * ---------------------
 * Displays a goodbye message to the user when quitting the client.
 *
 * Purpose:
 *   Can be called when the QUIT command is issued to provide user feedback.
 */
void handle_quit();

#endif // CLIENT_UI_H
