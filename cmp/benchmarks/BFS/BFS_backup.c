#define global
#include "stdio.h"
#include "barrier.h"
#define NPROC 2
volatile int CountLock = 0;

#define NOLINK 999999
#define NODENUM 8

volatile int test_graph[NODENUM][NODENUM] = {{0,1,2,NOLINK,4,5,1,7},{1,0,NOLINK,3,4,5,6,7},
				{3,3,0,5,6,11,NOLINK,13},{1,1,2,0,12,13,NOLINK,15},
				{1,2,3,NOLINK,0,10,NOLINK,15},{1,1,6,NOLINK,NOLINK,0,14,15},
				{1,1,4,NOLINK,6,7,0,NOLINK},{NOLINK,1,6,9,NOLINK,11,8,0}};

volatile int test_visited[NODENUM] = {0};


void BFS(int node,int begin,int end,int c[NODENUM][NODENUM])
{
	int queue[NODENUM] = {0};
	int queueNum = 0;
	int queueBegin = 0;
	int queueEnd = 0;
	int temp,i;

	queue[queueEnd] = node;
	queueNum++;
	queueEnd++;
	while(queueNum>0){
		temp = queue[queueBegin];
		queueBegin++;
		queueNum--;
		if(test_visited[temp]==0){
			test_visited[temp] = 1;
			printf("visit %d\n",temp);
			for(i = begin;i<=end;i++){
				if(test_visited[i]==0&&c[temp][i]!=NOLINK){
					queue[queueEnd] = i;
					queueNum++;
					queueEnd++;
				}
			}
		}
	}
}


void Traversal(int begin, int end , int c[NODENUM][NODENUM])
{
	int i = begin;
	for(i;i<=end;i++){
		BFS(i,begin,end,c);
	}
};

int main()
{
	unsigned ProcessId = 0;
	int my_id = 0;
	barrier_init(NPROC);
	for(ProcessId = 1;ProcessId < NPROC; ProcessId++){
		my_id = MTA_fork();
		printf("loop %d after fork %d\n",ProcessId,my_id);
		my_id = MTA_getthreadID();
		printf("loop %d after MTA_getthreadID %d\n",ProcessId,my_id);
		if(my_id != 0)		break;
	}

	MTA_Bar_Stats(1);
	barrier(MTA_getthreadID() , NPROC);
	MTA_Bar_Stats(0);
	
	MTA_Stats(1);
	{
		MTA_Lock_Stats(1);
		MTA_Lock_Acquire(&CountLock);
		MTA_Lock_Stats(0);

		my_id = MTA_getthreadID();
		Traversal(my_id*4,(my_id+1)*4-1,test_graph);

		MTA_Lock_Stats(1);
		MTA_Lock_Release(&CountLock);
		MTA_Lock_Stats(0);
	}

	MTA_Bar_Stats(1);
	barrier(MTA_getthreadID() , NPROC);
	MTA_Bar_Stats(0);
	MTA_Stats(0);
	 while(MTA_wait() == -1);

}

	
	
