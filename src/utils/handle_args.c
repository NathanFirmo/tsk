#include "handle_args.h"
#include "../logging/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int handle_args(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            log_version();
            return 1;
        }

        if (strcmp(argv[i], "--init") == 0) {
            FILE *fp;

            fp = fopen("tsk.yaml", "w");
            if (fp == NULL) {
                log_error("Failed to create the sample file.");
                return 1;
            }

            fprintf(fp, "# This is a sample file. See more info in https://github.com/NathanFirmo/tsk\n\n");
            fclose(fp);

            fp = fopen("tsk.yaml", "a");
            if (fp == NULL) {
                log_error("Failed to create the sample file.");
                return 1;
            }

            fprintf(fp, "task:\n");
            fprintf(fp, "  main:\n");
            fprintf(fp, "    step:\n");
            fprintf(fp, "      - name: Echo\n");
            fprintf(fp, "        run:\n");
            fprintf(fp, "          - echo \"Hello world\"\n");
            fprintf(fp, "\n");
            fprintf(fp, "      - name: List files\n");
            fprintf(fp, "        run:\n");
            fprintf(fp, "          - ls\n");

            fclose(fp);

            printf("Sample \"tsk.yaml\" file created successfully. Run tsk in your shell to see commands execution.\n");
            return 1;
        }
    }
    return 0;
}
