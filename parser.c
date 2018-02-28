#include"include/parser.h"

void parse_instructions(char *filename, struct Matrix *t,
			struct Matrix *e, Frame f) {
	FILE *file = fopen(filename, "r");
	if (!file) return;
	
	char line[256];
	
	while (fgets(line, sizeof(line), file) != 0) {
		if (!strncmp(line, "line", strlen(line))) {
			
		}
		else if (!strncmp(line, "ident", strlen(line))) {
			ident(t);
		}
		else if (!strncmp(line, "scale", strlen(line))) {
			
		}
		else if (!strncmp(line, "translate", strlen(line))) {
			
		}
		else if (!strncmp(line, "rotate", strlen(line))) {
			
		}
		else if (!strncmp(line, "apply", strlen(line))) {
			matrix_mult(t, e);
		}
		else if (!strncmp(line, "display", strlen(line))) {
			display(f);
		}
		else if (!strncmp(line, "save", strlen(line))) {
			write_to_file(f);
			save_png(f);
		}
		else if (!strncmp(line, "quit", strlen(line))) {
			break;
		}
	}
	
	fclose(file);
	file = 0;
}

