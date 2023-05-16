#include <stdlib.h>
#include "yaml_structure.h"
#include "../utils/memory_handler.h"
#include "tsk_struct_handler.h"
#include "../logging/logger.h"
#include <stdio.h>

void add_task(struct task **tasks, char *name, struct step *steps) {
    char *log_level = getenv("LOG_LEVEL");
    if (log_level != NULL && strcmp(log_level, "DEBUG") == 0) {
        log_debug("Adding task:");
        log_debug(name);
        printf("\n");
    }

    struct task *t = bail_alloc(sizeof(*t));
    t->name = bail_strdup(name);
    t->steps = steps;

    if (!*tasks) {
        *tasks = t;
    } else {
        struct task *tail = *tasks;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = t;
    }
}

void add_step(struct step **steps, char *name, struct command *commands) {
    char *log_level = getenv("LOG_LEVEL");
    if (log_level != NULL && strcmp(log_level, "DEBUG") == 0) {
        log_debug("Adding step:");
        log_debug(name);
        printf("\n");
    }

    struct step *s = bail_alloc(sizeof(*s));
    s->name = bail_strdup(name);
    s->commands = commands;

    if (!*steps) {
        *steps = s;
    } else {
        struct step *tail = *steps;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = s;
    }
}

void add_command(struct command **commands, char *exec) {
    char *log_level = getenv("LOG_LEVEL");
    if (log_level != NULL && strcmp(log_level, "DEBUG") == 0) {
        log_debug("Adding command:");
        log_debug(exec);
        printf("\n");
    }

    struct command *c = bail_alloc(sizeof(*c));
    c->exec = bail_strdup(exec);

    if (!*commands) {
        *commands = c;
    } else {
        struct command *tail = *commands;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = c;
    }
}
void destroy_steps(struct step **steps) {
    for (struct step *s = *steps; s; s = *steps) {
        *steps = s->next;
        free(s->name);
        free(s->commands);
        free(s);
    }
}

void destroy_tasks(struct task **tasks) {
    for (struct task *t = *tasks; t; t = *tasks) {
        *tasks = t->next;
        free(t->name);
        destroy_steps(&t->steps);
        free(t);
    }
}

