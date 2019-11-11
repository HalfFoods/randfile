all: random.o
	gcc -o program random.o

random.o: random.c random.h
	gcc -c random.c

run:
	./program

clean:
	rm *.o
	rm program
