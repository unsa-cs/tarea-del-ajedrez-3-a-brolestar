all: main.o chess.o gc.o
	g++ main.o chess.o gc.o $(HW).c -lglut -lGL -lGLU -w -o $(HW)
main.o: main.c chess.h
	g++ -c main.c -ggdb3
chess.o: chess.c chess.h figures.h
	g++ -c chess.c -ggdb3
gc.o: gc.c gc.h
	g++ -c gc.c -ggdb3
clean:
	rm *o prob*[^c]
