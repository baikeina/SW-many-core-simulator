OBJS = BFS.o  func.o
CC = alpha-unknown-linux-gnu-gcc 

BFS: $(OBJS)
	$(CC)  -O3 -g3 -w -static $(OBJS) -o BFS -lm

func.o: func.s
	$(CC) -O3 -g3 -w -static  -c func.s
BFS.o: BFS.c 
	$(CC) -O3 -g3 -w -static  -c BFS.c

clean:
	rm -f *.o BFS 

