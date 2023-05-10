#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <yaml.h>

/* Our example parser states. */
enum state {
    STATE_START,    /* start state */
    STATE_STREAM,   /* start/end stream */
    STATE_DOCUMENT, /* start/end document */
    STATE_SECTION,  /* top level */

    STATE_TLIST,   /* fruit list */
    STATE_TVALUES, /* fruit key-value pairs */
    STATE_TKEY,    /* fruit key */
    STATE_TNAME,   /* fruit name value */

    STATE_SLIST,   /* steps list */
    STATE_SVALUES, /* step key-value pairs */
    STATE_SKEY,    /* step key */
    STATE_SNAME,   /* strp name */

    STATE_SCOMMAND,        /* step command */
    STATE_SCOMMAND_VALUES, /* step command values */

    STATE_STOP /* end state */
};

/* yaml_* functions return 1 on success and 0 on failure. */
enum status { SUCCESS = 1, FAILURE = 0 };

struct command {
    struct command *next;
    char *exec;
};

struct step {
    struct step *next;
    char *name;
    struct command *commands;
};

struct task {
    struct task *next;
    char *name;
    struct step *steps;
};

/* Our application parser state data. */
struct parser_state {
    enum state state;      /* The current parse state */
    struct task t;         /* Task data elements. */
    struct step s;         /* Step data elements. */
    struct command c;      /* Command data elements. */
    struct task *tlist;    /* List of 'task' objects. */
    struct step *slist;    /* List of 'step' objects. */
    struct command *clist; /* List of 'command' objects. */
};

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

void print_event(int state, int eventType) {
    switch (state) {
    case STATE_START:
        printf("state: STATE_START |");
        break;
    case STATE_STREAM:
        printf("state: STATE_STREAM |");
        break;
    case STATE_DOCUMENT:
        printf("state: STATE_DOCUMENT |");
        break;
    case STATE_SECTION:
        printf("state: STATE_SECTION |");
        break;
    case STATE_TLIST:
        printf("state: STATE_TLIST |");
        break;
    case STATE_TVALUES:
        printf("state: STATE_TVALUES |");
        break;
    case STATE_TKEY:
        printf("state: STATE_TKEY |");
        break;
    case STATE_TNAME:
        printf("state: STATE_TNAME |");
        break;
    case STATE_SLIST:
        printf("state: STATE_SLIST |");
        break;
    case STATE_SVALUES:
        printf("state: STATE_SVALUES |");
        break;
    case STATE_SKEY:
        printf("state: STATE_SKEY |");
        break;
    case STATE_SNAME:
        printf("state: STATE_SNAME |");
        break;
    case STATE_SCOMMAND:
        printf("state: STATE_SCOMMAND |");
        break;
    case STATE_SCOMMAND_VALUES:
        printf("state: STATE_SCOMMAND_VALUES |");
        break;
    case STATE_STOP:
        printf("state: STATE_STOP |");
        break;
    }

    switch (eventType) {
    case YAML_NO_EVENT:
        printf(" event: YAML_NO_EVENT\n");
        break;
    case YAML_STREAM_START_EVENT:
        printf(" event: YAML_STREAM_START_EVENT\n");
        break;
    case YAML_STREAM_END_EVENT:
        printf(" event: YAML_STREAM_END_EVENT\n");
        break;
    case YAML_DOCUMENT_START_EVENT:
        printf(" event: YAML_DOCUMENT_START_EVENT\n");
        break;
    case YAML_DOCUMENT_END_EVENT:
        printf(" event: YAML_DOCUMENT_END_EVENT\n");
        break;
    case YAML_ALIAS_EVENT:
        printf(" event: YAML_ALIAS_EVENT\n");
        break;
    case YAML_SCALAR_EVENT:
        printf(" event: YAML_SCALAR_EVENT\n");
        break;
    case YAML_SEQUENCE_START_EVENT:
        printf(" event: YAML_SEQUENCE_START_EVENT\n");
        break;
    case YAML_SEQUENCE_END_EVENT:
        printf(" event: YAML_SEQUENCE_END_EVENT\n");
        break;
    case YAML_MAPPING_START_EVENT:
        printf(" event: YAML_MAPPING_START_EVENT\n");
        break;
    case YAML_MAPPING_END_EVENT:
        printf(" event: YAML_MAPPING_END_EVENT\n");
        break;
    }
}

/*
 * Consume yaml events generated by the libyaml parser to
 * import our data into raw c data structures. Error processing
 * is keep to a mimimum since this is just an example.
 */
int consume_event(struct parser_state *s, yaml_event_t *event) {
    char *value;
    int debug = 0;

    // print_event(s->state, event->type);
    switch (s->state) {
    case STATE_START:
        switch (event->type) {
        case YAML_STREAM_START_EVENT:
            s->state = STATE_STREAM;
            break;
        default:
            fprintf(stderr, "[STATE_START] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_STREAM:
        switch (event->type) {
        case YAML_DOCUMENT_START_EVENT:
            s->state = STATE_DOCUMENT;
            break;
        case YAML_STREAM_END_EVENT:
            s->state = STATE_STOP; /* All done. */
            break;
        default:
            fprintf(stderr, "[STATE_STREAM] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_DOCUMENT:
        switch (event->type) {
        case YAML_MAPPING_START_EVENT:
            s->state = STATE_SECTION;
            break;
        case YAML_DOCUMENT_END_EVENT:
            s->state = STATE_STREAM;
            break;
        default:
            fprintf(stderr,
                    "[STATE_DOCUMENT] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SECTION:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            value = (char *)event->data.scalar.value;
            if (strcmp(value, "task") == 0) {
                s->state = STATE_TLIST;
            } else {
                fprintf(stderr, "[STATE_SECTION] Unexpected scalar: %s\n",
                        value);
                return FAILURE;
            }
            break;
        case YAML_DOCUMENT_END_EVENT:
            s->state = STATE_STREAM;
            break;
        case YAML_SEQUENCE_END_EVENT:
            s->state = STATE_STOP;
            break;
        default:
            fprintf(stderr,
                    "[STATE_SECTION] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_TLIST:
        switch (event->type) {
        case YAML_SEQUENCE_START_EVENT:
            s->state = STATE_TVALUES;
            break;
        case YAML_MAPPING_END_EVENT:
            s->state = STATE_SECTION;
            break;
        default:
            fprintf(stderr, "[STATE_TLIST] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_TVALUES:
        switch (event->type) {
        case YAML_MAPPING_START_EVENT:
            s->state = STATE_TKEY;
            break;
        case YAML_SEQUENCE_END_EVENT:
            s->state = STATE_TLIST;
            break;
        default:
            fprintf(stderr,
                    "[STATE_TVALUES] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_TKEY:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            value = (char *)event->data.scalar.value;
            if (strcmp(value, "name") == 0) {
                s->state = STATE_TNAME;
            } else if (strcmp(value, "step") == 0) {
                s->state = STATE_SLIST;
            } else {
                fprintf(stderr, "[STATE_TKEY] Unexpected key: %s\n", value);
                return FAILURE;
            }
            break;
        case YAML_MAPPING_END_EVENT:
            add_task(&s->tlist, s->t.name, s->slist);
            free(s->t.name);
            memset(&s->t, 0, sizeof(s->t));
            s->slist = NULL;
            s->state = STATE_TVALUES;
            break;
        default:
            fprintf(stderr, "[STATE_TKEY] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_TNAME:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            if (s->t.name) {
                fprintf(stderr,
                        "[STATE_TNAME] Warning: duplicate 'name' key.\n");
                free(s->t.name);
            }
            s->t.name = bail_strdup((char *)event->data.scalar.value);
            s->state = STATE_TKEY;
            break;
        default:
            fprintf(stderr, "[STATE_TNAME] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SLIST:
        switch (event->type) {
        case YAML_SEQUENCE_START_EVENT:
            s->state = STATE_SVALUES;
            break;
        default:
            fprintf(stderr, "[STATE_SLIST] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SVALUES:
        switch (event->type) {
        case YAML_MAPPING_START_EVENT:
            s->state = STATE_SKEY;
            break;
        case YAML_SEQUENCE_END_EVENT:
            s->state = STATE_TKEY;
            break;
        default:
            fprintf(stderr,
                    "[STATE_SVALUES] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SKEY:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            value = (char *)event->data.scalar.value;
            if (strcmp(value, "name") == 0) {
                s->state = STATE_SNAME;
            } else if (strcmp(value, "run") == 0) {
                s->state = STATE_SCOMMAND;
            } else {
                fprintf(stderr, "[STATE_SKEY] Unexpected key: %s\n", value);
                return FAILURE;
            }
            break;
        case YAML_MAPPING_END_EVENT:
            add_step(&s->slist, s->s.name, s->clist);
            free(s->s.name);
            memset(&s->s, 0, sizeof(s->s));
            s->clist = NULL;
            s->state = STATE_SVALUES;
            break;
        default:
            fprintf(stderr, "[STATE_SKEY] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SNAME:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            if (s->s.name) {
                fprintf(stderr,
                        "[STATE_SNAME] Warning: duplicate 'name' key.\n");
                free(s->s.name);
            }
            s->s.name = bail_strdup((char *)event->data.scalar.value);
            s->state = STATE_SKEY;
            break;
        default:
            fprintf(stderr, "[STATE_SNAME] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SCOMMAND:
        switch (event->type) {
        case YAML_SEQUENCE_START_EVENT:
            s->state = STATE_SCOMMAND_VALUES;
            break;
        case YAML_SEQUENCE_END_EVENT:
            s->state = STATE_SKEY;
            break;
        default:
            fprintf(stderr,
                    "[STATE_SCOMMAND] Unexpected event %d in state %d.\n",
                    event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_SCOMMAND_VALUES:
        switch (event->type) {
        case YAML_SCALAR_EVENT:
            if (s->c.exec) {
                fprintf(stderr,
                        "[STATE_SNAME] Warning: duplicate 'name' key.\n");
                free(s->c.exec);
            }
            s->c.exec = bail_strdup((char *)event->data.scalar.value);
            add_command(&s->clist, s->c.exec);
            free(s->c.exec);
            memset(&s->c, 0, sizeof(s->c));
            s->state = STATE_SCOMMAND_VALUES;
            break;
        case YAML_SEQUENCE_END_EVENT:
            s->state = STATE_SKEY;
            break;
        default:
            fprintf(
                stderr,
                "[STATE_SCOMMAND_VALUES] Unexpected event %d in state %d.\n",
                event->type, s->state);
            return FAILURE;
        }
        break;

    case STATE_STOP:
        break;
    }

    return SUCCESS;
}

int main(int argc, char **argv) {
    // for (int i = 0; i < argc; i++) {
    // }
    int code;
    enum status status;
    struct parser_state state;
    yaml_parser_t parser;

    yaml_event_t event;
    yaml_event_type_t event_type;

    yaml_node_t *node;
    int i = 1;

    FILE *file;
    file = fopen("tsk.yaml", "rb");
    assert(file);

    memset(&state, 0, sizeof(state));

    state.state = STATE_START;

    assert(yaml_parser_initialize(&parser));
    yaml_parser_set_input_file(&parser, file);

    do {
        yaml_event_t event;
        status = yaml_parser_parse(&parser, &event);

        if (status == FAILURE) {
            fprintf(stderr, "yaml_parser_parse error\n");
            return 1;
        }

        status = consume_event(&state, &event);
        if (status == FAILURE) {
            fprintf(stderr, "consume_event error\n");
            return 1;
        }

    } while (state.state != STATE_STOP);

    /* Output parsed data. */
    for (struct task *t = state.tlist; t; t = t->next) {
        printf("\033[32mtask:\033[0m %s\n", t->name);
        for (struct step *s = t->steps; s; s = s->next) {
            printf("\033[32mstep:\033[0m %s\n", s->name);
            FILE *fp;

            fp = fopen("script.sh", "w");
            if (fp == NULL) {
                printf("Failed to create file.");
                return 1;
            }
            fprintf(fp, "# /bin/sh\n");
            fclose(fp);

            for (struct command *c = s->commands; c; c = c->next) {
                printf("\033[32mrun:\033[0m %s\n", c->exec);
                FILE *fp;

                fp = fopen("script.sh", "a");
                if (fp == NULL) {
                    printf("Failed to create file.");
                    return 1;
                }

                fprintf(fp, "%s", c->exec);
                fprintf(fp, "\n");
                fclose(fp);
            }

            pid_t pid = fork();
            if (pid == 0) {
                char *arguments[] = {"sh", "script.sh", NULL};
                execv("/bin/sh", arguments);
                perror("execv");
                exit(1);
            } else if (pid > 0) {
                wait(NULL);
            }
        }
    }

    return 0;
}
