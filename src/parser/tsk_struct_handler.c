#include <stdlib.h>
#include "yaml_structure.h"
#include "../utils/memory_handler.h"
#include "tsk_struct_handler.h"

void add_task(struct task **tasks, char *name, struct step *steps) {
    // printf("Adding task %s\n", name);
    /* Create task object. */
    struct task *t = bail_alloc(sizeof(*t));
    t->name = bail_strdup(name);
    t->steps = steps;

    /* Append to list. */
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
    // printf("Adding step %s\n", name);
    /* Create step object. */
    struct step *s = bail_alloc(sizeof(*s));
    s->name = bail_strdup(name);
    s->commands = commands;

    /* Append to list. */
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
    // printf("Adding command %s\n", exec);
    /* Create command object. */
    struct command *c = bail_alloc(sizeof(*c));
    c->exec = bail_strdup(exec);

    /* Append to list. */
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

