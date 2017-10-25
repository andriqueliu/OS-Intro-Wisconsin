#include <stdio.h>

#define EXIT_SUCCESS 0

void arg_validator(int argc, char *argv[])
{
        int more_than_two_args = (argc > 2);
        int invalid_optional_arg = (
		argc == 2 &&
		argv[0][0] == '-');
        if (argc > 3) {
        	exit(1);
        }
        if (argc == 3) {
        	char dash_check = argv[2][0];
        	if (dash_check != '-') {
        		exit(1);
        	}
        	char *
        }
}

int main(int argc, char *argv[])
{
	printf("There are %d arguments\n", argc);
	printf("First argument: %s\n", argv[0]);
	printf("Second argument: %s\n", argv[1]);

	if (!arg_validator(argc, argv)) {
		printf("BAD\n");
		return 1;
	}

        return EXIT_SUCCESS;
}


