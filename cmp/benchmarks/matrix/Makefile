OBJS = matrix.o  func.o
CC = alpha-unknown-linux-gnu-gcc 

BFS: $(OBJS)
	$(CC)  -O3 -g3 -w -static $(OBJS) -o matrix -lm

func.o: func.s
	$(CC) -O3 -g3 -w -static  -c func.s
matrix.o: matrix.c 
	$(CC) -O3 -g3 -w -static  -c matrix.c

clean:
	rm -f *.o matrix

