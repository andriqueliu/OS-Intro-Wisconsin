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

char **store_lines(char *file_name, int *i)
{
        FILE *fp = NULL;
        fp = fopen(file_name, "r");
        if (fp == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(1);
        }

        char **lines = malloc(sizeof(char *));
        if (lines == NULL) {

        }

        size_t number_of_lines = sizeof(char *);

        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, fp)) {
                printf("this is the line we just got: %s", line);

                // check line length
                

                // copy this line into the collection
                lines[*i] = malloc(MAX_LINE_LENGTH * sizeof(char));
                strncpy(lines[*i], line, MAX_LINE_LENGTH); // ???

                printf("testing... %s\n", lines[*i]);

                number_of_lines += sizeof(char *);

                char **temp = realloc(lines, number_of_lines);
                if (temp == NULL) {

                }
                lines = temp;

                (*i)++;
        }

        fclose(fp);

        return lines;
}

// char **store_lines(char *file_name, int *number_of_lines)
// {
//         // printf("Testing number of lines: %d\n", *number_of_lines);

//         FILE *fp = NULL;
//         fp = fopen(file_name, "r");
//         if (fp == NULL) {
//                 fprintf(stderr, "Error opening file\n");
//                 exit(1);
//         }

//         // dynamically allocate one more index in the word sentence link array
//         // for every line found
        
//         char **lines = malloc(sizeof(char *));
//         if (lines == NULL) {
//                 fprintf(stderr, "Memory error encountered\n");
//                 exit(1);
//         }
//         printf("THERE'S A MALLOC\n");


//         return NULL;

//         int line_i = 0;
//         // size_t curr_size = 1;
//         // !!! You don't need to create that struct...
//         // just use an array of each line...
//         // when it comes time to compare, just deref. down to the appropriate word in the line

//         // example... so strnlen 
//         char line[MAX_LINE_LENGTH];
//         while (fgets(line, MAX_LINE_LENGTH, fp)) {


//                 printf("The current line says... %s", line);
//                 printf("The length of the current line is... %zd\n", strnlen(line, MAX_LINE_LENGTH));
                
//                 // int line_length = check_line_length(line);
//                 check_line_length(line);


//         }
//         // the end of the array should be null termed

//         // lines[line_i] = '\0';
//         printf("I just not nulled\n");

//         printf("Gonna close\n");
//         fclose(fp);
//         printf("Closed\n");

//         return lines;
// }

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

