#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include <getopt.h>

#include <fcntl.h>          /* Definition of AT_* constants */    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

#define DIRECTORY_A "/symlinks/etc/init.d/A"
#define DIRECTORY_B "/symlinks/etc/init.d/B"

#define DEFAULT_ROOT_PATH "/"

int main(int argc, char *argv[]) {
    char *root_path = DEFAULT_ROOT_PATH;

    // getopt stuff
    int option;
    int digit_optind = 0;

    struct stat st = {0};

    int counter = 0;

    // dir stuff
    DIR *p_root_path;

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
                counter = 2;
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
        while (optind < argc) {
            printf("%s ", argv[optind++]);
            counter++;
        }
        printf("\n");
    }

    if (counter < 2) {
        printf("E: Missing parameters, please see --help\n");
        exit(EXIT_FAILURE);
    }

    /**
     * Deal with root_path
     */
    p_root_path = opendir ((const char*)root_path);
    if (p_root_path == NULL) {
        printf ("E %d: Cannot open root_path directory: \"%s\"\n", errno, root_path);
        exit(EXIT_FAILURE);
    }

    // TODO: Create directories

    /*if (stat(DIRECTORY_A, &st) == -1) {
        mkdirat(DIRECTORY_A, 0700);
    }

    if (stat(DIRECTORY_B, &st) == -1) {
        mkdir(DIRECTORY_B, 0700);
    }*/

    // TODO: Create file

    // TODO: Create symlink
    
    closedir (p_root_path);
    exit(EXIT_SUCCESS);
}