OBJS = draw.o output.o matrix.o main.o
OUTPUT = picture.ppm

all: $(OBJS)
	gcc -o lines $(OBJS)
	./lines

main.o: main.c include/draw.h include/output.h include/matrix.h
	gcc $(DBG) -c main.c include/draw.h include/output.h include/matrix.h

draw.o: draw.c include/draw.h include/output.h include/dimen.h
	gcc $(DBG) -c draw.c include/draw.h include/output.h include/dimen.h

output.o: output.c include/output.h include/draw.h
	gcc $(DBG) -c output.c include/output.h include/draw.h

matrix.o: matrix.c include/matrix.h
	gcc $(DBG) -c matrix.c include/matrix.h

clean:
	rm -rf *.o $(OUTPUT)

