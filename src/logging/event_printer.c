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
    case STATE_TLIST:
        log_debug("state: STATE_TLIST");
        break;
    case STATE_TVALUES:
        log_debug("state: STATE_TVALUES");
        break;
    case STATE_TKEY:
        log_debug("state: STATE_TKEY");
        break;
    case STATE_TNAME:
        log_debug("state: STATE_TNAME");
        break;
    case STATE_SLIST:
        log_debug("state: STATE_SLIST");
        break;
    case STATE_SVALUES:
        log_debug("state: STATE_SVALUES");
        break;
    case STATE_SKEY:
        log_debug("state: STATE_SKEY");
        break;
    case STATE_SNAME:
        log_debug("state: STATE_SNAME");
        break;
    case STATE_SCOMMAND:
        log_debug("state: STATE_SCOMMAND");
        break;
    case STATE_SCOMMAND_VALUES:
        log_debug("state: STATE_SCOMMAND_VALUES");
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
