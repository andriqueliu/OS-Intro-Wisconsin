/*
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#define MAX_LINE_LENGTH 128


#define BUILT_INS 4


#define TRUE 1
#define FALSE 0


#define EXIT_command "exit"

#define EXIT_SUCCESS 0


char error_message[30] = "An error has occurred\n";



// Function Prototypes

char **get_args(void);
void print_args(char **args);
void free_args(char **args);

void check_line_length(char *line);


void parse_command(char **args);

void whoosh_exit();
void whoosh_cd();
void whoosh_pwd();
void whoosh_path();

void whoosh_error();

// !!! maybe use a global to point to the args?
// so if you have to exit, make sure to free the args
// ^TODO: make sure args are freed correctly

int main(int argc, char *argv[])
{
	while (1) {
		printf("whoosh> ");


		// get the line
		// get the args from that line
		// then, decide what program to run (built-in or otherwise)
		char **args = get_args();
		parse_command(args);
		free_args(args);
	}

	return EXIT_SUCCESS;
}



// 
char **get_args(void)
{
	// Get input from stdin
	char line[MAX_LINE_LENGTH + 2];
	fgets(line, MAX_LINE_LENGTH + 2, stdin);
	check_line_length(line);

	// Initialze string array (guaranteed to store each argument)
	char **args = malloc(MAX_LINE_LENGTH * sizeof(char *));

	// Make a copy of the line, since strtok is destructive
	char temp[MAX_LINE_LENGTH + 1];
	strncpy(temp, line, MAX_LINE_LENGTH + 1);

	int i = -1;
	char *token = strtok(temp, " \n");
	while (token != NULL) {
		i++;

		// Zero-initialize char array in the event no valid tokens
		// are found
		char *temp_word = calloc(MAX_LINE_LENGTH, sizeof(char));
		if (temp_word == NULL) {
			// fprintf(stderr, "Memory error encountered\n");
			// exit(EXIT_FAILURE);
		}

		strncpy(temp_word, token, MAX_LINE_LENGTH);
		args[i] = temp_word;

		token = strtok(NULL, " \n");
	}
	args[i + 1] = '\0'; // Null-terminate the list of arguments

	return args;
}

void print_args(char **args)
{
	int i = 0;
	while (args[i] != '\0') {
		printf("argument: %s\n", args[i]);
		i++;
	}
}

// 
void free_args(char **args)
{
	// Free each argument
	int i = 0;
	while (args[i] != '\0') {
		free(args[i]);
		i++;
	}

	// Free the array
	free(args);
}


// Ensure that line length is supported
void check_line_length(char *line)
{
	if (strnlen(line, MAX_LINE_LENGTH + 2) > MAX_LINE_LENGTH) {
		whoosh_error();
	}
}

// 
void parse_command(char **args)
{
	char *command = args[0];

	if (strcmp(command, "exit") == 0) {
		free_args(args);
		whoosh_exit();
	} else if (strcmp(command, "cd") == 0) {
		// maybe pass args into everything and if an error is found,
		// free the args
		printf("cd\n");
	} else if (strcmp(command, "pwd") == 0) {
		printf("pwd\n");
	} else if (strcmp(command, "path") == 0) {
		printf("path\n");
	} else {
		printf("Sorry dude, no command found\n");
		// use other builtin.....
	}



}

// Exit the program
void whoosh_exit()
{
	exit(0);
}

// Change directories
void whoosh_cd()
{

}

// Print working directory
void whoosh_pwd()
{

}

// 
void whoosh_path()
{

}

// Print an error message and exit the program
void whoosh_error()
{
	write(STDERR_FILENO, error_message, strlen(error_message));
	whoosh_exit();
}


