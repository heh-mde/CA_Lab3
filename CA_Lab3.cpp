#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>

static int help_num = 0;
static int version_num = 0;
static int list_num = 0;
static int parameter_num = 0;

static std::string parameter;
static std::string list;

int main(int argc, char* argv[]) {

    const char* short_options = "hvp::l:";

    const struct option long_options[] = {
            {"help",          no_argument,       0,  'h'},
            {"version",       no_argument,       0,  'v'},
            {"parameter_num", optional_argument, 0,  'p'},
            {"list",          required_argument, 0,  'l'},
            {0,               0,                 0,   0}
    };
    int opt;
    int opt_index = -1;

    while ((opt = getopt_long(argc, argv, short_options, long_options, &opt_index)) != -1) {
        switch (opt) {
        case 'h': {
            if (help_num) {
                puts("Too many help flags");
		exit(1);
            }
            help_num++;
            break;
        }
        case 'v': {
            if (version_num) {
                puts("Too many help flags");
		exit(1);
            }
            version_num++;
            break;
        }
        case 'p': {
            if (help_num) {
                puts("Too many help flags");
		exit(1);
            }
            parameter_num++;
            if (optarg) {
                parameter = optarg;
            }
            else {
                parameter = "None";
            }
            break;
        }
        case 'l': {
            if (help_num) {
                puts("Too many help flags");
		exit(1);
            }
            list_num++;
            list = optarg;
            break;
        }
        case '?':
            exit(1);
        default: {
            abort();
        }
        }
        opt_index = -1;
    }

    if (help_num) {
        printf("-h --help Show list of commands message\n"
            "-v --version Show version of program\n"
            "-p --parameter Parameter with optional value\n"
            "-l --list List with required values\n");
    }

    if (version_num) {
       	puts("Version: 1.0.0");
    }

    if (parameter_num) {
        if (parameter != "None") {
            printf("Value of parameter: ");
            std::cout << parameter << "\n";
        }
        else {
            puts("Parameter set to default.");
        }
    }

    if (list_num) {
        printf("List of values: [ ");
        int counter;
        while ((counter = list.find(',')) != std::string::npos) {
            printf("%i, ", (int)std::stod(list.substr(0, counter)));
            list.erase(0, counter + 1);
        }
        std::cout << list << " ]\n";
    }

    return 0;
};
