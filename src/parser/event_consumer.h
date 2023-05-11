#ifndef EVENT_CONSUMER
#define EVENT_CONSUMER

#include <yaml.h>
#include <stdbool.h>
#include "yaml_structure.h"
#include "tsk_struct_handler.h"
#include "../utils/get_boolean.h"
#include "../utils/memory_handler.h"

int consume_event(struct parser_state *s, yaml_event_t *event);

#endif
