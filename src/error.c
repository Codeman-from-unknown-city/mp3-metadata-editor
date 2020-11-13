//
// Created by suprog on 11.11.2020.
//

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void error(int code, char *err_msg_format, ...) {
    if (err_msg_format) {
        va_list args;
        va_start(args, err_msg_format);
        vfprintf(stderr, err_msg_format, args);
        putchar('\n');
        va_end(args);
    }
    exit(code);
}

void usage_err(const char *program_name) {
  error(1, "usage: %s --filepath=(path to your mp3) [COMMAND]", program_name);
}