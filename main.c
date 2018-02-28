#include"include/draw.h"
#include"include/output.h"
#include"include/matrix.h"
#include"include/parser.h"

int main() {
	struct Matrix edges, trans;
	Frame f;
	parse_instructions("script", &trans, &edges, f);
	
	return 0;
}

