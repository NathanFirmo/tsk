#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_handler.h"

/* Helper to bail on error. */
void bail(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/* Helper to allocate memory or bail. */
void *bail_alloc(size_t size) {
    void *p = calloc(1, size);
    if (!p) {
        bail("out of memory");
    }
    return p;
}

/* Helper to copy a string or bail. */
char *bail_strdup(const char *s) {
    char *c = strdup(s ? s : "");
    if (!c) {
        bail("out of memory");
    }
    return c;
}
