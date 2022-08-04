#include "myshell.h"

/* 
Name: myshell.c

Parameters: batchfile.txt (optional)

Description: A simple shell with 9 internal commands, the last of which executes external commands via execv. Depending on the command given
the shell may fork and the child process will exec the given commands, or the parent process will. See readme.md for more information.

Author: Patricija Shalkauskaite

Credit: The foundation of this simple shell used code from lab 04/05 but has been modified and built upon to suit this assignment.

Date: 04-03-2022
*/


int main(int argc, char **argv)
{	/*** Start of main function. ***/

	// Defining variables.
	char buffer[BUFFER_SIZE];	    // This is the buffer that will temporarily hold our input.
	char *args[ARGS_SIZE];          // Array of the input from command line.
	char *prompt = ">> ";           // Shell prompt.
	int background = 0;             // A flag to check if command entered is to be run in background.
	char shell[256];
	
	getcwd(shell, 256);          // Set the SHELL environment to be directory of myshell executable.
	strcat(shell, "/myshell");
	setenv("SHELL", shell, 1);
	setenv("PARENT", shell, 1);  // Create PARENT environment with path of myshell.

	check_batchfile(argc, argv);  // Check if a batchfile was provided.


	/*** Read in input until the 'quit' command is entered or EOF has been reached of redirected input. ***/
	while(!feof(stdin)) // It's ! because feof function returns true in case end of file is reached, otherwise false.
	{
		signal(SIGINT, sighandler);  // To capture any Ctrl + C actions that kill the command.

		if(argc == 1)  // If a batchfile hasn't been provided, output the shell prompt.
		{
			char cwd[1024];  // Current working directory.
        	getcwd(cwd, 1024);

			printf("%s %s", cwd, prompt);
		}

		/*** Read a line. ***/
		if(fgets(buffer, BUFFER_SIZE, stdin)) // Returns NULL when end of input reached.
		{	
			int token_num = 0;  // The total count of arguments written in the shell prompt.
			tokeniser(buffer, args, &token_num, 0);  // Split up the arguments given. (The 0 means no input redirection flag has been set off.)

			if (args[0]) // Check if any input was given before proceeding.
			{
				check_bg(&background, &token_num, args); // Check if command must be run in the background: if & was given.

				/*** Internal commands the child process isn't allowed to run. ***/
				if (!strcmp(args[0],"clr"))  // Clear command.
				{
					clr();
					continue;  // Otherwise won't progress to next iteration and prompt wont show.
				}
				else if(!strcmp(args[0], "cd"))  // Can't cd using fork() because environment only changes in child and dies with the child.
				{
					cd(args);
					continue;
				}
				else if(!strcmp(args[0], "pause"))  // Unless the ENTER key is pressed, the shell is paused.
				{
					pause_cmd();
					continue;
				}
				else if(!strcmp(args[0],"quit"))   // Can't quit out of program in child.
				{
					break;  // Break out of shell prompt and finish program.
				}

				/*** The child will carry out most of the commands, except for clr, cd, pause and quit. ***/
				pid_t pid = fork();
				if (pid < 0)  // Error occured.
				{
					fprintf(stderr, "Fork failed.\n");
					return 1;
				}
				else if (pid == 0)  // Child process.
				{
					check_i_o(token_num, args);  // Check for i/o redirection operators: >, < or >>.
					childish_cmd(args); // Check for internal/external command the child can do.
				}
				else  // Parent process.
				{
					if(background)  // Parent will not wait for child and move onto the next command.
					{
						background = 0;  // Set it back.
						continue;
					}
					else
					{
						waitpid(pid, 0, 0);  // Parent will wait for the child to complete.
						continue;
					}
				}
			}
		}
	}

	return(0);
}	/*** End of main function. ***/


/*** Expanded functions ***/

void childish_cmd(char **args)  // Commands child process may carry out, function checks if a command matches input given.
{
	if (!strcmp(args[0], "dir"))  // ls- al appropriate directory.
	{
		dir(args);
	}
	else if (!strcmp(args[0], "environ"))  // Output all environment variables.
	{
		environ_cmd();
	}
	else if(!strcmp(args[0], "echo"))  // Echo arguments given.
	{
		echo(args);
	}
	else if(!strcmp(args[0], "help"))  // Open the manual page.
	{
		help();
	}
	else  // External command.
	{
		external_cmd(args);
	}
}


void cd(char **args)  // Change directory to directory provided.
{
	char directory[256];
	if(args[1] && strcmp(args[1], "."))  // If a path is provided and it isn't "."
	{
		if(chdir(args[1]) != -1)  // Check the directory exists (chdir returns -1 on failure).
		{
			setenv("PWD", getcwd(directory, 100), 1);  // Set the PWD enivronment to display the correct current working directory.
		}
		else  // Invalid directory provided.
		{
			printf("Directory does not exist!\n");
		}
	}
	else  // Remain in current directory.
	{
		printf("Didn't move: %s\n", getcwd(directory, 256));
	}
}


void clr()
{
	system("clear");  // Wipe contents in prompt.
}


void dir(char **args)
{
	char dir_specified[100];
	if(args[1])  // If a path was provided.
	{
		strcpy(dir_specified, args[1]);
		execlp("ls", "ls", "-al", dir_specified, NULL);  // List the provided directory's contents.
		syserr("execl");
	}
	else
	{
		execlp("ls", "ls", "-al", NULL);  // List cwd contents.
		syserr("execl");
	}
}


void environ_cmd()
{
	execlp("env", "env", NULL);  // Output all the environment variables.
	syserr("execl");
}


void echo(char ** args)  // Repeat whatever is passed after 'echo'.
{
	if(args[1])
	{
		execvp("echo", args);
		syserr("execv");
	}
	else
	{
		printf("'echo' command entered with no arguments!\n");
		exit(0);
	}
}


void external_cmd(char ** args)
{
	execvp(args[0], args);
	printf("Invalid command!\n");  // If exec comes back into main program, it failed.
	exit(0);
}


void pause_cmd()
{
	printf("Press Enter to continue...\n");
	char char_check;
	while(1)  // Infinite loop that breaks if ENTER KEY is entered.
	{
		char_check = fgetc(stdin);
		
		/* Hexadecimal code for SPACE KEY IS 0x0A
		(ASCII Code is 10 but if you enter just the number 10 it thinks it's ENTER KEY) */
		if(char_check == 0x0A)
		{
			break;
		}
		char_check = getchar();
	}
}

void help()  // Open the manual page.
{
	execlp("more", "more", "-d", "../manual/readme.md", NULL);  // -d says to press 'q' to quit, or 'h' for instructions.
	syserr("execl");										 // ../manual/readme.md assumes user is in the bin directory to open file.
}