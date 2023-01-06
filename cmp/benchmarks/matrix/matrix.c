#include "stdio.h"
#include "barrier.h"
#define NPROC 4
volatile int CountLock = 0; // global lock var
volatile int count = 0;		// thread exec count
volatile int write = 0;

void work1(int a[20], int *result_ptr, int *ptr, int f[16])
{
	MTA_Lock_Stats(1);
	MTA_Lock_Acquire(&CountLock);
	MTA_Lock_Stats(0);

	int i, j;
	int finish = 100;
	int temp[4]; 		// store the temp data of calculate result
	// MTA_DMA_READ read data from main core
	count++;

	if (write == 0)
	{
		MTA_DMA_WRITE(&f[0], ptr, 16);
		write = 1;
		printf("write to main core\n");
	}

	printf("send read request before\n");
	MTA_DMA_READ(&a[16], ptr, 4);
	printf("send read request after\n");

	printf("core-0 deal success\n");

	// // calculate
	// for (i = 0; i < 4; i++)
	// {
	// 	for (j = 0; j < 4; j++)
	// 	{
	// 		temp[i] += a[j + i * 4] * a[16 + j];
	// 	}
	// }

	// printf("the first column calculate result is:\n");
	// for (i = 0; i < 4; i++)
	// {
	// 	printf("%d   ", temp[i]);
	// }
	// printf("\n");

	// MTA_DMA_WRITE(&temp[0], result_ptr, 4);

	if (count == 4)
	{
		MTA_DMA_WRITE(&finish, ptr + 16, 1);
	}

	MTA_Lock_Stats(1);
	MTA_Lock_Release(&CountLock);
	MTA_Lock_Stats(0);
}

void work2(int a[20], int b[20], int *result_ptr, int *ptr, int f[16])
{
	MTA_Lock_Stats(1);
	MTA_Lock_Acquire(&CountLock);
	MTA_Lock_Stats(0);

	int i, j, temp[4];
	int finish = 100;

	// get data from salve core
	MTA_RMA_READ(&b[0], &a[0], 16, 0);
	count++;

	if (write == 0)
	{
		MTA_DMA_WRITE(&f[0], ptr, 16);
		write = 1;
		printf("write to main core\n");
	}

	printf("send read request before\n");
	MTA_DMA_READ(&b[16], ptr + 4, 4);
	printf("send read request after\n");

	// printf("core-1 deal success\n");

	// // calculate
	// for (i = 0; i < 4; i++)
	// {
	// 	for (j = 0; j < 4; j++)
	// 	{
	// 		temp[i] += b[j + i * 4] * b[16 + j];
	// 	}
	// }

	// printf("the second column calculate result is:  ");
	// for (i = 0; i < 4; i++)
	// {
	// 	printf("%d   ", temp[i]);
	// }
	// printf("\n");

	// MTA_DMA_WRITE(&temp[0], result_ptr + 4, 4);

	if (count == 4)
	{
		MTA_DMA_WRITE(&finish, ptr + 16, 1);
	}

	MTA_Lock_Stats(1);
	MTA_Lock_Release(&CountLock);
	MTA_Lock_Stats(0);
}

void work3(int a[20], int b[20], int *result_ptr, int *ptr, int f[16])
{

	MTA_Lock_Stats(1);
	MTA_Lock_Acquire(&CountLock);
	MTA_Lock_Stats(0);

	int i, j, temp[4];
	int finish = 100;

	MTA_RMA_READ(&b[0], &a[0], 16, 0);
	count++;

	if (write == 0)
	{
		MTA_DMA_WRITE(&f[0], ptr, 16);
		write = 1;
		printf("write to main core\n");
	}

	printf("send read request before\n");
	MTA_DMA_READ(&b[16], ptr + 8, 4);
	printf("send read request after\n");

	// printf("core-2 deal success\n");

	// // calculate
	// for (i = 0; i < 4; i++)
	// {
	// 	for (j = 0; j < 4; j++)
	// 	{
	// 		temp[i] += b[j + i * 4] * b[16 + j];
	// 	}
	// }

	// printf("the third column calculate result is:  ");
	// for (i = 0; i < 4; i++)
	// {
	// 	printf("%d   ", temp[i]);
	// }
	// printf("\n");

	// MTA_DMA_WRITE(&temp[0], result_ptr + 8, 4);

	if (count == 4)
	{
		MTA_DMA_WRITE(&finish, ptr + 16, 1);
	}

	MTA_Lock_Stats(1);
	MTA_Lock_Release(&CountLock);
	MTA_Lock_Stats(0);
}

void work4(int a[20], int b[20], int *result_ptr, int *ptr, int f[16])
{

	MTA_Lock_Stats(1);
	MTA_Lock_Acquire(&CountLock);
	MTA_Lock_Stats(0);

	int i, j, temp[4];
	int finish = 100;

	MTA_RMA_READ(&b[0], &a[0], 16, 0);
	count++;

	if (write == 0)
	{
		MTA_DMA_WRITE(&f[0], ptr, 16);
		write = 1;
		printf("write to main core\n");
	}

	printf("send read request before\n");
	MTA_DMA_READ(&b[16], ptr + 12, 4);
	printf("send read request after\n");

	// printf("core-3 deal success\n");

	// // calculate
	// for (i = 0; i < 4; i++)
	// {
	// 	for (j = 0; j < 4; j++)
	// 	{
	// 		temp[i] += b[j + i * 4] * b[16 + j];
	// 	}
	// }

	// printf("the forth column calculate result is:  ");
	// for (i = 0; i < 4; i++)
	// {
	// 	printf("%d   ", temp[i]);
	// }
	// printf("\n");

	// MTA_DMA_WRITE(&temp[0], result_ptr + 12, 4);

	if (count == 4)
	{
		MTA_DMA_WRITE(&finish, ptr + 16, 1);
	}

	MTA_Lock_Stats(1);
	MTA_Lock_Release(&CountLock);
	MTA_Lock_Stats(0);
}

int main()
{
	unsigned ProcessId = 0;
	int my_id = 0;
	int a[20] = {1, 2, 3, 4, 2, 5, 3, 6, 2, 4, 1, 3, 4, 5, 3, 6}; // the is the origin data
	int b[20], c[20], d[20], e[20];

	int f[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};	//this is the main core data.

	int *main_ptr = (int *)0x7fff7f88; // main core matrix origin address.
	int *result = (int *)0x7fff7f30;

	int i, j, k;

	barrier_init(NPROC);
	/*fork threadid  fast forward mode*/
	for (ProcessId = 1; ProcessId < NPROC; ProcessId++)
	{
		my_id = MTA_fork();
		printf("loop %d after fork %d\n", ProcessId, my_id);
		my_id = MTA_getthreadID();
		printf("loop %d after MTA_getthreadID %d\n", ProcessId, my_id);
		if (my_id != 0)
			break;
	}

	MTA_Bar_Stats(1); // used together with the function barrier
	barrier(MTA_getthreadID(), NPROC);
	MTA_Bar_Stats(0); // used together with the function barrier

	MTA_Stats(1); // signifying the start of real execution (indicate the first barrier is reached, we can start the normal node)
	{
		my_id = MTA_getthreadID();

		if (my_id == 0)
		{
			work1(a, result, main_ptr, f);
		}
		else if (my_id == 1)
		{
			work2(a, b, result, main_ptr, f);
		}
		else if (my_id == 2)
		{
			work3(a, c, result, main_ptr, f);
		}
		else if (my_id == 3)
		{
			work4(a, d, result, main_ptr, f);
		}
	}

	MTA_Bar_Stats(1); // used together with the function barrier
	barrier(MTA_getthreadID(), NPROC);
	MTA_Bar_Stats(0); // used together with the function barrier

	MTA_Stats(0); // signifying the end of real execution

	while (MTA_wait() == -1)
		;
}
