#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

void arg_validator(int argc, char *argv[])
{
        num_args_validator(argc);
        word_selection_validator(argc, argv);
}

void num_args_validator(int argc) {
        if (argc > 3) {
                exit(1);
        }
}

void word_selection_validator(int argc, char *argv[]) {
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

int main(int argc, char *argv[])
{
        printf("There are %d arguments\n", argc);
        printf("First argument: %s\n", argv[0]);
        printf("Second argument: %s\n", argv[1]);


        arg_validator(argc, argv);

        printf("Test number: %ld\n", strtol("10", NULL, 10));
        char *end;
        printf("Test number: %ld\n", strtol("ff", &end, 10));
        printf("Crap letter: %s\n", end);

        // // this is UB!
        // char *plox;
        // *plox = 'h';
        // *(plox + 1) = 'e';
        // printf("%s\n", plox);

        // FILE *file_ptr = 



        return EXIT_SUCCESS;
}


