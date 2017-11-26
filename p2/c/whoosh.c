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

char **parse_input(void);
void print_args(char **args);
void free_args(char **args);

void check_line_length(char *line);

int check_built_in(char *command);

void whoosh_exit();

int main(int argc, char *argv[])
{
	// while (1) {
	// 	printf("whoosh> ");

	// 	parse_input();
	// }


	char **args = parse_input();

	print_args(args);
	free_args(args);



	// whoosh_exit();

	return EXIT_SUCCESS;
}

// has to result in a command, plus the list of its arguments...
char **parse_input(void)
{
	// get the line from stdin
	char line[MAX_LINE_LENGTH + 2];
	fgets(line, MAX_LINE_LENGTH + 2, stdin);
	check_line_length(line);





	// get the list of arguments, command included
	char **args = malloc(MAX_LINE_LENGTH * sizeof(char *));

	// Make a copy of the line
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
		// now, store that temp_word
		args[i] = temp_word;


		token = strtok(NULL, " \n");

		// printf("%s\n", temp_word);
	}

	// Null-terminate the list of arguments
	args[i + 1] = '\0';

	return args;
}

void print_args(char **args)
{
	int i = 0;
	while (args[i] != '\0') {
		printf("String: %s\n", args[i]);
		i++;
	}
}

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

// // Extract the nth word from a line
// char *extract_nth_word(const void *line)
// {
// 	// Make a copy of the line
// 	char temp[MAX_LINE_LENGTH];
// 	strncpy(temp, line, MAX_LINE_LENGTH);

// 	// Zero-initialize char array in the event no valid tokens
// 	// are found
// 	char *temp_word = calloc(MAX_WORD_LENGTH, sizeof(char));
// 	if (temp_word == NULL) {
// 		fprintf(stderr, "Memory error encountered\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	int i = -1;
// 	char *token = strtok(temp, " \n");

// 	while (token != NULL) {
// 		i++;

// 		strncpy(temp_word, token, MAX_WORD_LENGTH);
// 		if (i == (nth_word - 1)) {
// 			return temp_word;
// 		}

// 		token = strtok(NULL, " \n");
// 	}

// 	return temp_word;
// }


void check_line_length(char *line)
{
	if (strnlen(line, MAX_LINE_LENGTH + 2) > MAX_LINE_LENGTH) {
		// print error and exit
		printf("oh no temporary error message\n");
	}
}

// maybe modify this? just pass the cmd and args directly,
// no need to return and act?
// Check if command is built-in
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

void whoosh_pwd()
{

}

// 
void whoosh_path()
{

}

// also have to implement
// pwd and path... the rest, just check
// if the command is a built-in command

// ^ jk... if it's... exit, cd, pwd, or path...
// then don't create a new process. Just use the built in.
// Else, create a new process to run the command/program


