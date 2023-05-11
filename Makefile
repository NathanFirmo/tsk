build:
	@mkdir -p bin
	gcc src/main.c src/parser/event_consumer.c src/parser/tsk_struct_handler.c src/utils/get_boolean.c src/utils/memory_handler.c src/logging/event_printer.c src/logging/logger.c -lyaml -o bin/tsk
