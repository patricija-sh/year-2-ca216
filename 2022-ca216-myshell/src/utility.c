#include "myshell.h"

void sighandler(int signum)  // To catch any Ctrl + C action.
{
	printf("\n You've decided to end the process, received a signal %d.\n", signum);
	exit(0);
}

// This piece of code is taken from lab 04/05 in part 5 - Fork and Exec.
void syserr(char *msg)  // Any execs the child process did that didn't execute right will set off this function.
{
	fprintf(stderr,"%s: %s\n", strerror(errno), msg);
  	abort();
}


void tokeniser(char *buffer, char **args, int *token_num, int input_flag)
{
	char *token;
	token = strtok(buffer, SEPARATORS); // Split the command into separate tokens.
	int i = 0;
	
	if(input_flag)  // If the input redirection flag has been set then keep the command of args[0]
	{               // and add onto args whatever the contents of the file are.
		i = 1;
	}

	for(; token != NULL ; i += 1)
	{
		args[i] = token;      
		token = strtok(NULL, SEPARATORS);
	}

	args[i] = NULL;  // Set last value to NULL for execvp.
	*token_num = i;  // The total count of arguments written in the shell prompt.
}


void check_bg(int *bg_flag, int *argc, char **args)  // Check if command should be run in the background.
{
	if(!strcmp(args[*argc - 1], "&"))
		{
			printf("I will run this command in the background.\n");
			args[*argc - 1] = NULL;  // where the & is
			*bg_flag = 1;  // set flag so process runs in background
			*argc -= 1;
		}
}

void check_batchfile(int argc, char **argv)
{
	if(argc > 1)  // If a batchfile was provided.
	{
		FILE *f_batch = freopen(argv[1], "r", stdin);
		if(f_batch != NULL)
		{
			printf("Successful opening of file.\n");
		}
		else
		{
			printf("Failed to open file - either misspelled or doesn't exist.\n");
			exit(0);
		}
	}
}


void check_i_o(int token_num, char **args)  // Check for <, >, >> and replace appropriate STDIN/STDOUT streams to file provided.
{
	for(int i = 1; i < token_num; i += 1)  // Cycle through args to find redirection signs.
	{
		if(!strcmp(args[i], ">"))  // Output redirection.
		{
			FILE *f_out = freopen(args[i + 1], "w", stdout);
			check_file(f_out);  // Make sure nothing wrong happened with the file.
			args[i] = NULL;     // So commands can only access up to but not including the redirection sign.
			break;              // Exit out of for loop.
		}
		else if(!strcmp(args[i], "<"))  // Input redirection.
		{
			char buf[1024];
			char *tmp[token_num];
			int input_sign = i;  // We can assume the position of output redirection if we know where input redirection is.
			
			FILE *f_in = freopen(args[i + 1], "r", stdin);  // i + 1 is the input file.
			check_file(f_in);

			if(fgets(buf, BUFFER_SIZE, stdin)) // Check is there anything in the file.
			{
				for(int i = 0; i < token_num; i += 1)
				{
					tmp[i] = args[i]; // args is going to be overwritten with the contents of the file, so tmp will hold what args had.
				}

				tokeniser(buf, args, &token_num, 1);  // Last parameter is the input flag, which is set to 1 so args[0] command isn't overwritten.
			}

			if(tmp[input_sign + 2] && !strcmp(tmp[input_sign + 2], ">"))  // Is there output redirection provided too.
			{
				FILE *f_out = freopen(tmp[input_sign + 3], "w", stdout);
				check_file(f_out);
			}
			else if(tmp[input_sign + 2] && !strcmp(tmp[input_sign + 2], ">>"))
			{
				FILE *f_append = freopen(tmp[input_sign + 3], "a", stdout);
				check_file(f_append);
			}

			break;
		}
		else if(!strcmp(args[i], ">>"))  // Append contents to end of file provided.
		{
			FILE * f_append = freopen(args[i + 1], "a", stdout);  
			check_file(f_append);
			args[i] = NULL;
			break;
		}
	}
}

void check_file(FILE *f)  // Make sure nothing wrong happens with the file when doing i/o redirection.
{
	if(f != NULL)
	{
		printf("Successful opening of file.\n");
	}
	else
	{
		printf("Failed.\n");
		abort();
	}
}
