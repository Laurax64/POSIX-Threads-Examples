#include <pthread.h>
#include <stdio.h>

// Mutex for synchronizing print output
pthread_mutex_t print_mutex;

void *PrintThreadId (void *threadid)
{
  long tid = (long) threadid;
  printf ("tid: %ld\n", tid);
  pthread_mutex_unlock (&print_mutex);
}

int main (int argc, char *argv[])
{
  // Initialize the mutex, to ensure that the mutex is in a valid, known state before using it.
  pthread_mutex_init (&print_mutex, NULL);
  pthread_t threads[5];
  for (long t = 0; t < 5; t++)
	{
	  pthread_mutex_lock (&print_mutex);
	  printf ("t: %ld\n", t);
	  pthread_create (&threads[t], NULL, PrintThreadId, (void *) t);
	}
}
