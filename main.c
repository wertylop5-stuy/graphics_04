#include"include/draw.h"
#include"include/output.h"
#include"include/matrix.h"
#include"include/parser.h"

int main() {
	struct Matrix *edges = new_matrix(4, 1);
	struct Matrix *trans = new_matrix(4, 4);
	Frame f;
	memset(f, 0, sizeof(f));
	parse_instructions("script", trans, edges, f);
	
	return 0;
}

