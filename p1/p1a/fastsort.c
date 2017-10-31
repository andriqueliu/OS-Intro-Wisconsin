#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 50

#define EXIT_SUCCESS 0

// You need a struct? This struct contains a word, which will "hook" to its containing
// sentence?
// idea... so the qsort takes a sorting function...
// this function will take the struct ptr, BUT will then
// deref. and compare the appropriate STRINGs!!!



// Function prototypes

void arg_validator(int argc, char *argv[]);
void num_args_validator(int argc);
void word_selection_validator(int argc, char *argv[]);


char **store_lines(char *file_name, int *number_of_lines);

void check_line_length(char *line);



void free_lines(char **lines, int number_of_lines);


int main(int argc, char *argv[])
{
        printf("There are %d arguments\n", argc);
        printf("First argument: %s\n", argv[0]);
        printf("Second argument: %s\n", argv[1]);


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

        int number_of_lines = 1;

        char *file_name = argv[1];

        char **lines = store_lines(file_name, &number_of_lines);
        
        // test and print everything out

        printf("Here are some returned lines!\n");
        int i = 0;
        while (i < number_of_lines - 1) {
                printf("%s", lines[i]);
                i++;
        }

        // from that function, return the array of structs... malloc inside? or allocate from outside


        // get each individual line of that file...

        // get the selected word of each line

        // link each selected word with containing line

        // compare the structs... deref. and get the appropriate data (word)

        // then, iterate across all of the structs and print out the sentence


        // free_lines(lines, number_of_lines);

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
                exit(1);
        }
}

void word_selection_validator(int argc, char *argv[])
{
        if (argc == 3) {
                char *word_selection = argv[2];
                if (word_selection[0] != '-') {
                        exit(1);
                }
                
                char *end;
                long word_selection_value;
                word_selection_value = strtol((word_selection + 1), &end, 10);

                printf("%ld\n", word_selection_value);
                printf("%s\n", end);


        }
}

char **store_lines(char *file_name, int *number_of_lines)
{
        // printf("Testing number of lines: %d\n", *number_of_lines);

        FILE *fp = NULL;
        fp = fopen(file_name, "r");
        if (fp == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(1);
        }

        // dynamically allocate one more index in the word sentence link array
        // for every line found

        char **lines = malloc(sizeof(char *));
        if (lines == NULL) {
                fprintf(stderr, "Memory error encountered\n");
                exit(1);
        }

        int line_i = 0;
        // size_t curr_size = 1;
        // !!! You don't need to create that struct...
        // just use an array of each line...
        // when it comes time to compare, just deref. down to the appropriate word in the line

        // example... so strnlen 
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, fp)) {


                printf("The current line says... %s", line);
                printf("The length of the current line is... %zd\n", strnlen(line, MAX_LINE_LENGTH));
                
                // int line_length = check_line_length(line);
                check_line_length(line);

                // note: if line is just whitespace, use an empty string!

                // allocate space for the line!
                // malloc space for the max line, then copy everything from the line into it!
                // get the appropriate word
                // *(lines + i) = malloc(MAX_LINE_LENGTH + 1); // maybe + 1?
                // strncpy(*(lines + i), line, MAX_LINE_LENGTH + 1);
                lines[line_i] = malloc(MAX_LINE_LENGTH * sizeof(char)); // maybe + 1?

                lines[line_i] = "hello\0";
                printf("yo !!%s\n", lines[line_i]);


                // strncpy(lines[line_i], line, MAX_LINE_LENGTH);
                char *temp_line = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strncpy(temp_line, line, MAX_LINE_LENGTH);
                strncpy(lines[line_i], temp_line, MAX_LINE_LENGTH);

                printf("Just making sure the line was copied: %s\n", lines[line_i]);



                // realloc
                line_i++;
                *number_of_lines += 1;

                printf("Testing... %d\n", *number_of_lines);
                char **temp_lines = realloc(lines, *number_of_lines);
                if (temp_lines != NULL) {
                        lines = temp_lines;
                } else {
                        fprintf(stderr, "Memory error encountered\n");
                        exit(1);
                }
                printf("I just realloc\n");

        }
        // the end of the array should be null termed

        // lines[line_i] = '\0';
        printf("I just not nulled\n");

        printf("Gonna close\n");
        fclose(fp);
        printf("Closed\n");

        return lines;
}

void check_line_length(char *line)
{
        int line_length = strnlen(line, MAX_LINE_LENGTH);

        if (
                (line_length == (MAX_LINE_LENGTH - 1)) &&
                (line[MAX_LINE_LENGTH - 2] != '\n')) {

                fprintf(stderr, "Input line length exceeded limit\n");
                exit(1);
        }
}



// iterate through the array, freeing each element as you go
// finally, free the char array
void free_lines(char **lines, int number_of_lines)
{
        int i = 0;

        while (i < number_of_lines - 1) {
                free(lines[i]);
                i++;
        }

        free(lines);
}

