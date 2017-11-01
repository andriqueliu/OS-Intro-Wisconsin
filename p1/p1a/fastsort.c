#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max length of a line
// If all indices up to the last index are not occupied by null terminators,
// then the second-to-last index must be occupied by a newline.
#define MAX_LINE_LENGTH 128

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// You need a struct? This struct contains a word, which will "hook" to its containing
// sentence?
// idea... so the qsort takes a sorting function...
// this function will take the struct ptr, BUT will then
// deref. and compare the appropriate STRINGs!!!



// Function prototypes

void arg_validator(int argc, char *argv[]);
void num_args_validator(int argc);
void word_selection_validator(int argc, char *argv[]);


char **store_lines(char *file_name, int *i);

void check_line_length(char *line);

void print_lines(char **lines, int line_i);

void free_lines(char **lines, int line_i);


int main(int argc, char *argv[])
{
        arg_validator(argc, argv);

        // this is also ub... with strtol... you have a char pointer.
        // strtol just modifies that char pointer to point at an already existing
        // string!
        // printf("Test number: %ld\n", strtol("10", NULL, 10));
        // char *end;
        // printf("Test number: %ld\n", strtol("ff", &end, 10));
        // printf("Crap letter: %s\n", end);

        // // this is UB!
        // char *plox;
        // *plox = 'h';
        // *(plox + 1) = 'e';
        // printf("%s\n", plox);

        int line_i = 0;

        char *file_name = argv[1];

        char **lines = store_lines(file_name, &line_i);
        



        


        // now that you have the lines, put them into a function...
        // use that function to sort through everything
        // still, you need a function to pick out the correct word...


        // from that function, return the array of structs... malloc inside? or allocate from outside


        // get each individual line of that file...

        // get the selected word of each line

        // link each selected word with containing line

        // compare the structs... deref. and get the appropriate data (word)

        // then, iterate across all of the structs and print out the sentence

        print_lines(lines, line_i);

        free_lines(lines, line_i);

        return EXIT_SUCCESS;
}

void arg_validator(int argc, char *argv[])
{
        num_args_validator(argc);
        word_selection_validator(argc, argv);
}

void num_args_validator(int argc)
{
        if (argc > 3) {
                exit(EXIT_FAILURE);
        }
}

void word_selection_validator(int argc, char *argv[])
{
        if (argc == 3) {
                char *word_selection = argv[2];
                if (word_selection[0] != '-') {
                        exit(EXIT_FAILURE);
                }
                
                char *end;
                long word_selection_value;
                word_selection_value = strtol((word_selection + 1), &end, 10);

                printf("%ld\n", word_selection_value);
                printf("%s\n", end);


        }
}

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

        printf("line length: %d\n", line_length);

        if (
                (line_length == (MAX_LINE_LENGTH - 1)) &&
                (line[MAX_LINE_LENGTH - 2] != '\n')) {

                fprintf(stderr, "Input line length exceeded limit\n");
                exit(EXIT_FAILURE);
        }
}

// char **sort_lines(char **lines, int line_i)
// {

// }

// // Compares two lines
// int compare_lines(const void *a, const void *b)
// {
//         // so these point to the actual char *s... now make sure to fetch
//         // the correct element from each line

//         // so... you have a line!

//         // make a copy of the lines...
//         char temp_a[MAX_LINE_LENGTH];
//         char temp_b[MAX_LINE_LENGTH];
//         strncpy(temp_a, a, MAX_LINE_LENGTH);
//         // ^ something similar...
//         // now, get the correct word...

//         // strcmp when you have the word
// }


// Print out lines
void print_lines(char **lines, int line_i)
{
        int i = 0;
        while (i < line_i) {
                printf("%s", lines[i]);
                printf("%p\n", lines[i]);
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

