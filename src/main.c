#include <ctype.h>

#include "args.h"

#define URANDOM "/dev/urandom"

int generate(Args *args) {
    int c = 0, status = 0;
    long end = 0;
    char *buf = NULL;
    FILE *fp = NULL;

    buf = calloc(args->size + 1, sizeof(char));
    if (buf == NULL) {
        perror("calloc");
        goto cleanup;
    }

    fp = fopen(URANDOM, "r");
    if (fp == NULL) {
        perror("fopen");
        goto cleanup;
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

cleanup:
    // Free resources
    free(buf);

    if (fp != NULL && fclose(fp) != 0) {
        perror("flose");
    } else {
        status = 0;
    }

    return status;
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

    return generate(&args);
}
