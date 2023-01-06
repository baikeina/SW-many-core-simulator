#include <stdio.h>

int main()
{
  int *local_ptr = (int *)0x7fff7f88;

  while (1)
  {
    if (*(local_ptr+16) == 100)
    { 
      printf("finished\n");
      break;
    }
  }
  return 0;
}
