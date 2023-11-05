#include <ctype.h>

#include "args.h"

#define URANDOM "/dev/urandom"

void generate(Args *args) {
    int c;
    long end = 0;
    char *buf = calloc(args->size + 1, sizeof(char));
    FILE *fp = fopen(URANDOM, "r");

    if (buf == NULL) {
        perror("calloc");
        exit(1);
    }

    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    while (end < args->size) {
        c = fgetc(fp);

        // Discard non-printable
        if (c < '!' || c > '~') continue;

        // Discard unwanted chars
        if (args->punct == false && ispunct(c)) continue;
        if (args->digit == false && isdigit(c)) continue;
        if (args->upper == false && isupper(c)) continue;
        if (args->lower == false && islower(c)) continue;

        // Otherwise, store in buffer
        buf[end++] = c;
    }

    // Print the generated string
    puts(buf);

    // Free resources
    free(buf);

    if (fclose(fp) != 0) {
        perror("flose");
    }
}

int main(int argc, char *argv[]) {
    Args args = {
        .size   = 16,
        .upper  = true,
        .lower  = true,
        .punct  = true,
        .digit  = true,
    };

    // Ignore malformed args
    if (argc < 1) return 1;

    Args_parse(&args, argc, argv);
    generate(&args);
}
