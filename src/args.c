#include "args.h"

void show_usage(char *program) {
    printf(
        "%s, %s\n"
        "\nUsage:\n"
        "  %s [options]\n"
        "\nOptions:\n"
        "  -h --help           Display this help menu\n"
        "  -s --size <number>  How long the generated string should be (16)\n"
        "\n"
        "  -D --digit          Enable digits (default)\n"
        "  -L --lower          Enable lower case (default)\n"
        "  -P --punct          Enable punctuation (default)\n"
        "  -U --upper          Enable upper case (default)\n"
        "\n"
        "  -d --no-digit       Disable digits\n"
        "  -l --no-lower       Disable lower case\n"
        "  -p --no-punct       Disable punctuation\n"
        "  -u --no-upper       Disable upper case\n",
        program, VERSION, program
    );
    exit(1);
}

long parse_long(char *str) {
    long size = 0;
    char *endptr = NULL;

    errno = 0;
    size = strtol(str, &endptr, 10);

    if (errno != 0
        || str == endptr
        || *endptr != '\0'
    ) {
        return -1;
    }

    return size;
}

void Args_parse(Args *args, int argc, char *argv[]) {
    char *arg;

    // Start at 1 to skip program
    for (int i = 1; i < argc; i++) {
        arg = argv[i];

        // -h/--help
        if (!strcmp(arg, "-h")
            || !strcmp(arg, "--help")
        ) {
            show_usage(argv[0]);

        // -s/--size
        } else if (!strcmp(arg, "-s")
            || !strcmp(arg, "--size")
        ) {
            if (i >= argc - 1) {
                fprintf(stderr, "--size requires <number>\n");
                show_usage(argv[0]);
            }

            args->size = parse_long(argv[++i]);

            if (args->size < 0) {
                fprintf(stderr, "Invalid size: %s\n", argv[i]);
                show_usage(argv[0]);
            }

        // -D/--digit
        } else if (!strcmp(arg, "-D")
            || !strcmp(arg, "--digit")
        ) {
            args->digit = true;

        // -L/--lower
        } else if (!strcmp(arg, "-L")
            || !strcmp(arg, "--lower")
        ) {
            args->lower = true;

        // -P/--punct
        } else if (!strcmp(arg, "-P")
            || !strcmp(arg, "--punct")
        ) {
            args->punct = true;

        // -U/--upper
        } else if (!strcmp(arg, "-U")
            || !strcmp(arg, "--upper")
        ) {
            args->upper = true;

        // -d/--no-digit
        } else if (!strcmp(arg, "-d")
            || !strcmp(arg, "--no-digit")
        ) {
            args->digit = false;

        // -l/--no-lower
        } else if (!strcmp(arg, "-l")
            || !strcmp(arg, "--no-lower")
        ) {
            args->lower = false;

        // -p/--no-punct
        } else if (!strcmp(arg, "-p")
            || !strcmp(arg, "--no-punct")
        ) {
            args->punct = false;

        // -u/--no-upper
        } else if (!strcmp(arg, "-u")
            || !strcmp(arg, "--no-upper")
        ) {
            args->upper = false;

        // Any other arg
        } else {
            fprintf(stderr,
                "Invalid argument: %s\n", arg
            );
            show_usage(argv[0]);
        }
    }

    // Validate arguments
    if (args->digit == false
        && args->lower == false
        && args->punct == false
        && args->upper == false
    ) {
        fprintf(stderr,
            "At least one type of character must be enabled\n"
        );
        show_usage(argv[0]);
    }
}

