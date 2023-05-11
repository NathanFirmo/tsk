#include "logging/logger.h"
#include "parser/event_consumer.h"
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

int main(int argc, char **argv) {
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

    if (file == NULL) {
        log_warn("There's no \"tsk.yml\" file in current working directory.\nYou can create your own manually or run \"tsk --init\" to create a sample file.");
        return 0;
    }

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
