#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

void print_debug(const char *format, ...) {
    va_list args;
#if 0
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}
