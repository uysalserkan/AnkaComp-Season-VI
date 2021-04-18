#include <pthread.h>
#include <stdio.h>

int sum;     /* shared sum by threads – global variable */
void *runner (void *param);   /*  thread start function */

int  main(int argc, char *argv[]){
	pthread_t tid; /* id of the created thread */
	pthread_attr_t attr;  /* set of thread attributes */
	
	if (argc != 2) {
		fprintf (stderr, “usage: a.out <value>\n”); 
		return -1; 
	}
	if (atoi(argv[1]) < 0) {
		fprintf (stderr, “%d must be >= 0\n”, atoi(argv[1]); 
		return -1; 	
	}
	
	pthread_attr_init (&attr); 	
	pthread_create (&tid, &attr, runner, argv[1]); 
	pthread_join (tid, NULL); 
	printf (“sum = %d\n”, sum); 
}

void *runner (void *param)
{
	int i; 

	int upper; 

	upper = atoi(param); 
	sum = 0; 

	for (i = 1; i <= upper; ++i) 
		sum += i; 

	pthread_exit(0); 
}

