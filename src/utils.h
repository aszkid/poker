#pragma once
#include <stdio.h>

#define _log(fd, color, ...)                                                   \
    do {                                                                       \
        fprintf(fd, "%s[%s:%d] ", color, __FILE__, __LINE__);                  \
        fprintf(stdout, __VA_ARGS__);                                          \
        fprintf(fd, "\x1B[0m\n");                                              \
    } while (0)

#define log_info(...) _log(stdout, "\x1B[1;34m", __VA_ARGS__)
#define log_error(...) _log(stdout, "\x1B[1;31m", __VA_ARGS__)
#define log_debug(...) _log(stdout, "\x1B[1;30m", __VA_ARGS__)
