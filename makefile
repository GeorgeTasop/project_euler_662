CC=gcc
CFLAGS=-I. -lm -fopenmp
OBJ = prob662.o

prob662: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm -f *.o
	rm -f prob662
