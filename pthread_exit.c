#include <pthread.h>
#include <stdio.h>

void *PrintThreadId (void *threadid) {
	long tid = (long) threadid;
	printf ("tid: %ld\n", tid);
}

int main (int argc, char *argv[]) {
	pthread_t threads[5];
	for (long t = 0; t < 5; t++) {
		if (t > 1) {
			pthread_exit (NULL);
		}
		printf ("t: %ld\n", t);
		pthread_create (&threads[t], NULL, PrintThreadId, (void *) t);
	}
}
