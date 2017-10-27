#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10

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


char **store_lines(char *file_name);

void check_line_length(char *line);



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

        char **lines = store_lines(argv[1]);
        
        // from that function, return the array of structs... malloc inside? or allocate from outside


        // get each individual line of that file...

        // get the selected word of each line

        // link each selected word with containing line

        // compare the structs... deref. and get the appropriate data (word)

        // then, iterate across all of the structs and print out the sentence


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

char **store_lines(char *file_name)
{
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
                // some exit stuff
                fprintf(stderr, "Memory error encountered\n");
        }

        int i = 0;
        // !!! You don't need to create that struct...
        // just use an array of each line...
        // when it comes time to compare, just deref. down to the appropriate word in the line

        // example... so strnlen 
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH + 1, fp)) {

                printf("%s", line);
                printf("The length of the current line is... %zd\n", strnlen(line, MAX_LINE_LENGTH));
                
                check_line_length(line);

                // note: if line is just whitespace, use an empty string!

                // allocate space for the line!
                // malloc space for the max line, then copy everything from the line into it!
                // get the appropriate word
                *(lines + i) = malloc(MAX_LINE_LENGTH + 1); // maybe + 1?
                strncpy(*(lines + i), line, MAX_LINE_LENGTH + 1);

                // realloc
                i++;
        }
        // the end of the array should be null termed

        fclose(fp);

        return lines;
}

void check_line_length(char *line)
{
        if (
                (strnlen(line, MAX_LINE_LENGTH) == MAX_LINE_LENGTH) &&
                (line[MAX_LINE_LENGTH - 1] != '\n')) {

                fprintf(stderr, "Input line length exceeded limit\n");
                exit(1);
        }
}






