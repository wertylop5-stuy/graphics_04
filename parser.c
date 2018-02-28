#include"include/parser.h"

void parse_instructions(char *filename, struct Matrix *t,
			struct Matrix *e, Frame f) {
	FILE *file = fopen(filename, "r");
	char line[256];
	
	while (fgets(line, sizeof(line), file) != EOF) {
		if (!strncmp(line, "line")) {
		}
		else if (!strncmp(line, "ident")) {
		}
		else if (!strncmp(line, "scale")) {
		}
		else if (!strncmp(line, "translate")) {
		}
		else if (!strncmp(line, "rotate")) {
		}
		else if (!strncmp(line, "apply")) {
		}
		else if (!strncmp(line, "display")) {
		}
		else if (!strncmp(line, "save")) {
		}
		else if (!strncmp(line, "quit")) {
		}
	}
	
	fclose(file);
	file = 0;
}

