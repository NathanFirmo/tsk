#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "get_boolean.h"

/*
 * Convert a yaml boolean string to a boolean value (true|false).
 */
int get_boolean(const char *string, bool *value) {
    char *t[] = {"y",    "Y",    "yes", "Yes", "YES", "true",
                 "True", "TRUE", "on",  "On",  "ON",  NULL};
    char *f[] = {"n",     "N",     "no",  "No",  "NO",  "false",
                 "False", "FALSE", "off", "Off", "OFF", NULL};
    char **p;

    for (p = t; *p; p++) {
        if (strcmp(string, *p) == 0) {
            *value = true;
            return 0;
        }
    }
    for (p = f; *p; p++) {
        if (strcmp(string, *p) == 0) {
            *value = false;
            return 0;
        }
    }
    return EINVAL;
}
