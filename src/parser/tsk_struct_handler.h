#ifndef TSK_STRUCT_HANDLER
#define TSK_STRUCT_HANDLER

void add_task(struct task **tasks, char *name, struct step *steps);
void add_step(struct step **steps, char *name, struct command *commands);
void add_command(struct command **commands, char *exec);
void destroy_steps(struct step **steps);
void destroy_tasks(struct task **tasks);

#endif
