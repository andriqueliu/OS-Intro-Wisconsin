#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 128

#define EXIT_SUCCESS 0

// You need a struct? This struct contains a word, which will "hook" to its containing
// sentence?
// idea... so the qsort takes a sorting function...
// this function will take the struct ptr, BUT will then
// deref. and compare the appropriate STRINGs!!!

struct word_sentence_link {
        char *word;
        char *sentence;
};

// Function prototypes

void arg_validator(int argc, char *argv[]);
void num_args_validator(int argc);
void word_selection_validator(int argc, char *argv[]);






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

struct word_sentence_link *create_word_sentence_links(
        char *file_name) {

        FILE *fp = NULL;
        fp = fopen(file_name, "r");
        if (fp == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(1);
        }

        // dynamically allocate one more index in the word sentence link array
        // for every line found

        struct word_sentence_link *links = malloc(sizeof(struct word_sentence_link));
        if (links == NULL) {
                // some exit stuff
        }

        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, fp)) {
                // check if the input line is too long... if it is, return an error

                printf("%s", line);

                // note: if line is just whitespace, use an empty string!

                // get the appropriate word
                // 

                // link that word and this line together

                // using that struct... add everything to a struct array!

        }

        fclose(fp);

        return 
}






