#include "event_printer.h"
#include "../parser/state.h"
#include <stdio.h>
#include <yaml.h>
#include "logger.h"

void print_event(int state, int eventType) {
    switch (state) {
    case STATE_START:
        log_debug("state: STATE_START");
        break;
    case STATE_STREAM:
        log_debug("state: STATE_STREAM");
        break;
    case STATE_DOCUMENT:
        log_debug("state: STATE_DOCUMENT");
        break;
    case STATE_SECTION:
        log_debug("state: STATE_SECTION");
        break;
    case STATE_TASK_LIST:
        log_debug("state: STATE_TASK_LIST");
        break;
    case STATE_TASK_ITEM:
        log_debug("state: STATE_TASK_ITEM");
        break;
    case STATE_TASK_ITEM_KEY:
        log_debug("state: STATE_TASK_ITEM_KEY");
        break;
    case STATE_STEP_LIST:
        log_debug("state: STATE_STEP_LIST");
        break;
    case STATE_STEP_ITEM:
        log_debug("state: STATE_STEP_ITEM");
        break;
    case STATE_STEP_ITEM_KEY:
        log_debug("state: STATE_STEP_ITEM_KEY");
        break;
    case STATE_STEP_NAME:
        log_debug("state: STATE_STEP_NAME");
        break;
    case STATE_COMMAND_LIST:
        log_debug("state: STATE_COMMAND_LIST");
        break;
    case STATE_COMMAND_ITEM:
        log_debug("state: STATE_COMMAND_ITEM");
        break;
    case STATE_STOP:
        log_debug("state: STATE_STOP");
        break;
    }

    switch (eventType) {
    case YAML_NO_EVENT:
        log_debug("event: YAML_NO_EVENT\n");
        break;
    case YAML_STREAM_START_EVENT:
        log_debug("event: YAML_STREAM_START_EVENT\n");
        break;
    case YAML_STREAM_END_EVENT:
        log_debug("event: YAML_STREAM_END_EVENT\n");
        break;
    case YAML_DOCUMENT_START_EVENT:
        log_debug("event: YAML_DOCUMENT_START_EVENT\n");
        break;
    case YAML_DOCUMENT_END_EVENT:
        log_debug("event: YAML_DOCUMENT_END_EVENT\n");
        break;
    case YAML_ALIAS_EVENT:
        log_debug("event: YAML_ALIAS_EVENT\n");
        break;
    case YAML_SCALAR_EVENT:
        log_debug("event: YAML_SCALAR_EVENT\n");
        break;
    case YAML_SEQUENCE_START_EVENT:
        log_debug("event: YAML_SEQUENCE_START_EVENT\n");
        break;
    case YAML_SEQUENCE_END_EVENT:
        log_debug("event: YAML_SEQUENCE_END_EVENT\n");
        break;
    case YAML_MAPPING_START_EVENT:
        log_debug("event: YAML_MAPPING_START_EVENT\n");
        break;
    case YAML_MAPPING_END_EVENT:
        log_debug("event: YAML_MAPPING_END_EVENT\n");
        break;
    }
}
