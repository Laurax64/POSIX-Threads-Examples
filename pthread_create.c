#include <pthread.h>
#include <stdio.h>

void *PrintThreadId (void *threadId)
{
  long tid = (long) threadId;
  printf ("tid: %ld\n", tid);
}

int main (int argc, char *argv[])
{
  pthread_t threads[5];
  for (long t = 0; t < 5; t++)
	{
	  printf ("t: %ld\n", t);
	  pthread_create (&threads[t], NULL, PrintThreadId, (void *) t);
	}
}
