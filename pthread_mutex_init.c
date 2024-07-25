#include <pthread.h>
#include <stdio.h>

// Mutex for synchronizing print output
pthread_mutex_t print_mutex;

void *PrintThreadId (void *threadid)
{
  long tid = (long) threadid;
  printf ("tid: %ld\n", tid);
  // Unlock the mutex after printing both t and tid with the same value
  pthread_mutex_unlock (&print_mutex);
}

int main (int argc, char *argv[])
{
  // Initialize the mutex
  pthread_mutex_init (&print_mutex, NULL);
  pthread_t threads[5];
  for (long t = 0; t < 5; t++)
	{
	  // Lock the mutex before printing
	  pthread_mutex_lock (&print_mutex);
	  printf ("t: %ld\n", t);
	  pthread_create (&threads[t], NULL, PrintThreadId, (void *) t);

	}
}
