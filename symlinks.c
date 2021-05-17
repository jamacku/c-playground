#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#include <getopt.h>

int main(int argc, char *argv[]) {
    char *root_path;
    int option;
    int digit_optind = 0;

    // Example of use: ./symlinks --root "/home/dummy" foo.original bar.symlink

    /**
     * Parse arguments
     * https://linux.die.net/man/3/getopt_long 
    */
    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            { "root", required_argument, 0, 'r' },
            { "help", no_argument,       0, 'h' }
        };

        option = getopt_long(argc, argv, "hr:", long_options, &option_index);
            if (option == -1)
                break;

        switch (option) {
            case 'h':
                printf("Usage: %s [-r|--root <path>] <file> <symlink>\n", argv[0]);
                break;

            case 'r':
                root_path = optarg;
                printf("Optional alternative root path is: \"%s\"\n", root_path);
                break;

            default:
                printf("E: getopt returned character code \"0%o\"\n", option);
        }
    }

    if (optind < argc) {
            printf("non-option ARGV-elements: ");
            while (optind < argc)
                printf("%s ", argv[optind++]);
            printf("\n");
        }

    exit(EXIT_SUCCESS);


    // TODO: Deal with --root value

    // TODO: Symlink stuff

}