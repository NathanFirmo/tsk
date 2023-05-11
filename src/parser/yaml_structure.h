#include "state.h"

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
