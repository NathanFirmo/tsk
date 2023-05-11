#ifndef LOGGER
#define LOGGER

/* Program logging */
void log_error(const char *msg);
void log_debug(const char *msg);
void log_warn(const char *msg);

/* Task logging */
void log_task(const char *msg);
void log_step(const char *msg);
void log_command(const char *msg);

#endif
