OBJS = draw.o output.o matrix.o parser.o main.o
OUTPUT = picture.ppm
EXEC = exec

all: $(OBJS)
	gcc -o $(EXEC) $(OBJS)
	./$(EXEC)

main.o: main.c include/draw.h include/output.h include/matrix.h
	gcc $(DBG) -c main.c include/draw.h include/output.h include/matrix.h

draw.o: draw.c include/draw.h include/output.h include/dimen.h
	gcc $(DBG) -c draw.c include/draw.h include/output.h include/dimen.h

output.o: output.c include/output.h include/draw.h
	gcc $(DBG) -c output.c include/output.h include/draw.h

matrix.o: matrix.c include/matrix.h
	gcc $(DBG) -c matrix.c include/matrix.h

parser.o: parser.c include/parser.h
	gcc $(DBG) -c parser.c include/parser.h

clean:
	rm -rf *.o $(OUTPUT)

