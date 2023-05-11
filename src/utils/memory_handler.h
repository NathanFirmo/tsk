#ifndef MEMORY_HANDLER
#define MEMORY_HANDLER
#include <string.h>

void bail(const char *msg);

void *bail_alloc(size_t size);

char *bail_strdup(const char *s);
#endif
