#include "logger.h"
#include <stdio.h>

/* Task logging */
void log_error(const char *msg) { printf("\033[31mError:\033[0m %s\n", msg); }
void log_debug(const char *msg) { printf("\033[35mDebug:\033[0m %s\n", msg); }
void log_warn(const char *msg) { printf("\033[33mWarn:\033[0m %s\n", msg); }

/* Task logging */
void log_task(const char *msg) { printf("\033[32mtask:\033[0m %s\n", msg); }
void log_step(const char *msg) { printf("\033[32mstep:\033[0m %s\n", msg); }
void log_command(const char *msg) { printf("\033[32mrun:\033[0m %s\n", msg); }
