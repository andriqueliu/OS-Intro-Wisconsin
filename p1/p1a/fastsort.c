/*
 * fastsort.c
 * 
 * Sorts lines of a specified file. The nth word of each line is selected
 * by the user for lexicographical comparison.
 * 
 * Note: lines that only contain spaces and that end in newlines will
 * yield a word only composed of null bytes for comparison.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max length of a line
// If all indices up to the last index are not occupied by null terminators,
// then the second-to-last index must be occupied by a newline.
#define MAX_LINE_LENGTH 128
// Max length of a word
// A word must leave two indices available for a newline followed by a
// null terminator
#define MAX_WORD_LENGTH MAX_LINE_LENGTH - 2

#define BASE_TEN 10

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Determine nth word of each line to use for comparison (1-indexed)
int nth_word;

// Function prototypes
void arg_validator(int argc, char *argv[]);
void num_args_validator(int argc);
void word_selection_validator(int argc, char *argv[]);
char **store_lines(char *file_name, int *i);
void check_line_length(char *line);
int compare_lines(const void *line_a, const void *line_b);
char *extract_nth_word(const void *line);
void print_lines(char **lines, int line_i);
void free_lines(char **lines, int line_i);

int main(int argc, char *argv[])
{
        // Indicate which line of the file is being inspected
        int line_i = 0;

        arg_validator(argc, argv);
        // char **lines = store_lines(argv[1], &line_i);
        

        // todo: get correct nth word

        // test...
        // nth_word = 3; // 3rd word
        
        // printf("Before sorting:\n");
        // print_lines(lines, line_i);
        // qsort(lines, line_i, sizeof(char *), compare_lines);
        // printf("After sorting:\n");
        // print_lines(lines, line_i);

        // free_lines(lines, line_i);

        return EXIT_SUCCESS;
}

// Validate program arguments
void arg_validator(int argc, char *argv[])
{
        num_args_validator(argc);
        word_selection_validator(argc, argv);
}

// Validate the number of arguments given to the program
void num_args_validator(int argc)
{
        if (argc > 3) {
                fprintf(stderr, "No more than 3 arguments allowed\n");
                exit(EXIT_FAILURE);
        }
}

// Validate and set the word selection argument
void word_selection_validator(int argc, char *argv[])
{
        if (argc == 3) {
                char *word_selection = argv[2];
                if (word_selection[0] != '-') {
                        fprintf(stderr, "Word selection value missing a dash\n");
                        exit(EXIT_FAILURE);
                }
                
                char *end = NULL; // Points to the start of the first non-valid char
                                  // (not a number) in word_selection.
                                  // This char pointer is modified in strtol
                long word_selection_value;

                // Start at one index later to skip the '-'
                word_selection_value = strtol((word_selection + 1), &end, BASE_TEN);

                if ((end == '\0') && (word_selection + 1) != '\0') {
                        printf("Word selection value: %ld\n", word_selection_value);
                        nth_word = word_selection_value;
                } else {
                        fprintf(stderr, "Word selection value contains invalid chars\n");
                        printf("end: %s\n", end);
                        printf("%ld\n", word_selection_value);
                        exit(EXIT_FAILURE);
                }
        }
}

// Store file lines in a char array
char **store_lines(char *file_name, int *i)
{
        FILE *fp = NULL;
        fp = fopen(file_name, "r");
        if (fp == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
        }

        char **lines = malloc(sizeof(char *));
        if (lines == NULL) {
                fprintf(stderr, "Memory error encountered\n");
                exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];
        size_t number_of_lines = sizeof(char *);

        while (fgets(line, MAX_LINE_LENGTH, fp)) {
                check_line_length(line);

                lines[*i] = malloc(MAX_LINE_LENGTH * sizeof(char));
                strncpy(lines[*i], line, MAX_LINE_LENGTH);

                number_of_lines += sizeof(char *);
                char **temp = realloc(lines, number_of_lines);
                if (temp == NULL) {
                        fprintf(stderr, "Memory error encountered while reallocating\n");
                        exit(EXIT_FAILURE);
                }
                lines = temp;

                (*i)++;
        }

        fclose(fp);

        return lines;
}

// Verifies the length of the line
void check_line_length(char *line)
{
        int line_length = strnlen(line, MAX_LINE_LENGTH);

        // printf("line length: %d\n", line_length);

        if (
                (line_length == (MAX_LINE_LENGTH - 1)) &&
                (line[MAX_LINE_LENGTH - 2] != '\n')) {

                fprintf(stderr, "Input line length exceeded limit\n");
                exit(EXIT_FAILURE);
        }
}

// Compares two lines
int compare_lines(const void *a, const void *b)
{
        char *line_a = *(char **) a;
        char *line_b = *(char **) b;

        char *word_a = extract_nth_word(line_a);
        char *word_b = extract_nth_word(line_b);

        int result = strcmp(word_a, word_b);
        
        free(word_a);
        free(word_b);
        
        return result;
}

// Extract the nth word from a line
char *extract_nth_word(const void *line)
{
        // Make a copy of the line
        char temp[MAX_LINE_LENGTH];
        strncpy(temp, line, MAX_LINE_LENGTH);

        // Zero-initialize char array in the event no valid tokens
        // are found
        char *temp_word = calloc(MAX_WORD_LENGTH, sizeof(char));
        if (temp_word == NULL) {
                fprintf(stderr, "Memory error encountered\n");
                exit(EXIT_FAILURE);
        }

        int i = -1;
        char *token = strtok(temp, " \n");

        while (token != NULL) {
                i++;

                strncpy(temp_word, token, MAX_WORD_LENGTH);
                if (i == (nth_word - 1)) {
                        return temp_word;
                }

                token = strtok(NULL, " \n");
        }

        return temp_word;
}


// Print out stored lines
void print_lines(char **lines, int line_i)
{
        int i = 0;
        while (i < line_i) {
                printf("line: %s", lines[i]);
                i++;
        }
}

// Frees memory allocated to hold lines
void free_lines(char **lines, int line_i)
{
        int i = 0;
        while (i < line_i) {
                free(lines[i]);
                i++;
        }
        free(lines);
}
