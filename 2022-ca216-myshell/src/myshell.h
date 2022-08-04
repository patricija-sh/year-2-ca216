// Libraries.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <errno.h>

// Definitions.
#define BUFFER_SIZE 1024   // Maximum size of the buffer (temporary storage unit to hold what we get from command line).
#define ARGS_SIZE 64       // Maximum number of arguments parsed.
#define SEPARATORS " \t\n"  // For strtok() function.

// Global variables.
extern char **environ;
extern int errno;

// Function prototypes.

// Shell commands.
void childish_cmd(char **args);  // Comamnds the child process may execute.
void clr();  // Clears content off screen.
void cd(char **args);  // Change directory.
void dir(char **argv);  // List contents of given (or current) directory.
void echo(char ** args);  // Output what comes after echo.
void pause_cmd();  // Pause shell operations until ENTER kEY is pressed.
void environ_cmd();  // Output environment variables.
void external_cmd(char ** args); // Execute external commands via execvp.
void help();  // Show the readme.md file.

// More general functions.
void syserr(char *msg);  // Handle errors if commands fail.
void sighandler(int signum);  // Catch Ctrl + C actions.
void check_bg(int *bg_flag, int *argc, char **args);  // Check if command is to be run in background
void check_i_o(int token_num, char **args);  // Parse command to see if redirection is required.
void check_file(FILE *f);  // Check if a file exists.
void check_batchfile(int argc, char **argv);  // Check if a batchfile was provided.
void tokeniser(char *buffer, char **args, int *token_num, int input_flag);  // Split the input given into an array.