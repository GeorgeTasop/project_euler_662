CC=gcc
CFLAGS=-I. -fopenmp
OBJ = prob662.o

prob: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm -f *.o
	rm -f prob
