/*
 * 
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>



#define MAX_LINE_LENGTH 2


#define EXIT_CMD "exit"

#define EXIT_SUCCESS 0


char error_message[30] = "An error has occurred\n";


// Function Prototypes

// parse_cmd();

void check_line_length(char *line);


void whoosh_exit();

int main(int argc, char *argv[])
{
	// while (1) {
	// 	printf("whoosh> ");
	// 	parse_cmd();
	// }

	check_line_length(argv[1]);

	return EXIT_SUCCESS;
}

// 
// void parse_cmd()
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


// func to print error message and exit
void whoosh_exit()
{
	write(STDERR_FILENO, error_message, strlen(error_message));
	// execv... call the system exit() method
}


