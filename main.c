/*
Pixel coordinates from:
http://au.mathworks.com/matlabcentral/mlc-downloads/downloads/submissions/40334/versions/2/screenshot.png
*/

#include"include/draw.h"
#include"include/output.h"
#include"include/matrix.h"

//how big to make the "pixels"
#define PIXEL_WIDTH	10

//offset from lower left corner
#define OFFSET		19

//(x, y) is the top left of the pixel
void fill_pixel(Frame f, struct Pixel *p, int x, int y) {
	int a, b;
	for (a = x+1; a < x+PIXEL_WIDTH; a++) {
	for (b = y-1; b > y-PIXEL_WIDTH; b--) {
		plot_point(f, a, b, p);
	}
	}
}

//pushes the pixel border into the frame, and fills in the pixel
//note: the borders arent drawn immediately
void place_pixel(struct Matrix *m, Frame f, struct Pixel *p, int x, int y) {
	push_edge(m, x, y, 0, x+PIXEL_WIDTH, y, 0);
	push_edge(m, x, y, 0, x, y-PIXEL_WIDTH, 0);
	push_edge(m, x, y-PIXEL_WIDTH, 0, x+PIXEL_WIDTH, y-PIXEL_WIDTH, 0);
	push_edge(m, x+PIXEL_WIDTH, y, 0, x+PIXEL_WIDTH, y-PIXEL_WIDTH, 0);

	fill_pixel(f, p, x, y);
}

//len is int, coords is int[]
void batch_place(struct Matrix *m, Frame f, struct Pixel *p, int *coords, int *len) {
	int x;
	for (x = 1; x < *len; x+=2) {
		place_pixel(m, f, p,
				(coords[x-1]+OFFSET)*PIXEL_WIDTH,
				(coords[x]+OFFSET)*PIXEL_WIDTH);
	}
}

void add_coord(int *coords, int *len, int x, int y) {
	coords[*len] = x;
	coords[(*len)+1] = y;
	(*len)+=2;
}

int main() {
	struct Matrix *a = new_matrix(1, 5);
	struct Matrix *b = new_matrix(3, 1);
	struct Matrix *i = new_matrix(3, 3);
	ident(i);

	printf("empty matrix\n");
	print_matrix(b);
	printf("identity matrix\n");
	print_matrix(i);
	printf("pushing points\n");
	push_point(b, 1, 2, 3);
	print_matrix(b);
	push_point(b, 4, 5, 6);
	print_matrix(b);
	
	printf("pushing edge\n");
	push_edge(b, 10, 11, 12, 21, 22, 23);
	print_matrix(b);

	printf("back:%d cols:%d\n", b->back, b->cols);
	push_point(b, 4, 5, 6);
	printf("back:%d cols:%d\n", b->back, b->cols);
	print_matrix(b);
	
	a->m[0][0] = 2.0f;
	a->m[0][1] = 3.0f;
	a->m[0][2] = 4.0f;
	a->back = 3;

	printf("matrix mult with [2, 3, 4]\n");
	matrix_mult(a, b);
	print_matrix(b);

	free_matrix(a);
	free_matrix(b);
	free_matrix(i);
	a = b = i = 0;

	printf("drawing mario!\n");
	//setup
	a = new_matrix(3, 1);
	
	Frame f;
	memset(f, 255, sizeof(Frame));
	struct Pixel p;
	int coords[2048];
	int len = 0;

	FILE *file = fopen("mario", "r");
	char line[64];
	int num_colors, num_coords, x, y;
	int red, green, blue;
	int n,m;

	//the good stuff
	/* File Format
	 *
	 * <# of colors>
	 * For each color:
	 * 	<r, g, b> value
	 * 	<# of coordinate pairs>
	 * 	For each coord pair:
	 * 		<x, y>
	 *
	 * Ex:
	 * 2
	 * 255,255,255
	 * 3
	 * 0,0
	 * 1,1
	 * 2,2
	 * 0,0,0
	 * 1
	 * 70,45
	 * */
	//num colors
	fgets(line, sizeof(line), file);
	sscanf(line, "%d\n", &num_colors);
	
	for (n = 0; n < num_colors; n++) {
		//color
		fgets(line, sizeof(line), file);
		sscanf(line, "%d,%d,%d\n", &red, &green, &blue);
		pixel_color(&p, red, green, blue);

		//number of coords
		fgets(line, sizeof(line), file);
		sscanf(line, "%d\n", &num_coords);
		
		for (m = 0; m < num_coords; m++) {
			fgets(line, sizeof(line), file);
			sscanf(line, "%d,%d\n", &x, &y);
			
			add_coord(coords, &len, x, y);
		}
		
		batch_place(a, f, &p, coords, &len);
		memset(coords, 0, sizeof(coords));
		len = 0;
	}
	
	pixel_color(&p, 0, 0, 0);
	draw_lines(f, a, &p);

	write_to_file(f);
	save_png(f);
	display(f);

	free_matrix(a);
	pclose(file);

	file = 0;
	a = 0;
	
	return 0;
}

