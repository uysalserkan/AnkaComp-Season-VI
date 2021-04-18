#include <stdio.h>
#include <pthread.h>

int main()
{
      pid_t  n; // return value of fork; it is process ID
	/* fork another process */
	n = fork();
	if (n < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if (n == 0) { /* child process */
		execlp("/bin/ls", "ls", NULL);
	}
	else { /* parent process */
		/* parent will wait for the child 
             to complete */
		wait (NULL);
		printf ("Child Complete");
		exit(0);
	}
}

