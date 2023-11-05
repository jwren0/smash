#ifndef _SMASH_ARGS_H
#define _SMASH_ARGS_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v0.0.1"
#define DEF_SIZE 16

typedef struct {
    // Number of characters to generate
    long size;

    // Which types of characters to accept
    bool upper;
    bool lower;
    bool punct;
    bool digit;
} Args;

void show_usage(char *program);
void Args_parse(Args *args, int argc, char *argv[]);

#endif // _SMASH_ARGS_H
