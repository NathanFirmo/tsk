#include "event_printer.h"
#include "../parser/state.h"
#include <stdio.h>
#include <yaml.h>

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
