/*
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define MAX_LINE_LENGTH 2


#define BUILT_INS 4


#define TRUE 1
#define FALSE 0


#define EXIT_command "exit"

#define EXIT_SUCCESS 0


char error_message[30] = "An error has occurred\n";


// Function Prototypes

// parse_command();

void check_line_length(char *line);

int check_built_in(char *command);

void whoosh_exit();

int main(int argc, char *argv[])
{
	// while (1) {
	// 	printf("whoosh> ");
	// 	parse_command();
	// }

	check_line_length(argv[1]);


	

	whoosh_exit();

	return EXIT_SUCCESS;
}

// 
// void parse_command()
// {
// 	// use fgets
// 	// make sure line isn't too long though



// }

void check_line_length(char *line)
{
	if (strlen(line) > MAX_LINE_LENGTH) {
		// print error and exit
	}
}

// check if built in
int check_built_in(char *command)
{
	char *built_ins[] = {
		"exit",
		"cd",
		"pwd",
		"path"
	};

	for (int i = 0; i < BUILT_INS; i++) {
		if (strcmp(command, built_ins[i]) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

// ??? for the IMPLEMENTED functions, should
// wait, execv, etc. be used?
// Probably not...

void whoosh_exit()
{
	// write(STDERR_FILENO, error_message, strlen(error_message));
	// execv... call the system exit() method
	exit(0);
}

void whoosh_cd()
{

}

// also have to implement
// pwd and path... the rest, just check
// if the command is a built-in command

// ^ jk... if it's... exit, cd, pwd, or path...
// then don't create a new process. Just use the built in.
// Else, create a new process to run the command/program


