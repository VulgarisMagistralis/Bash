#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
void *routine(void *x){
	long int ret;
	sleep((long int)x);
	fprintf(stdout,"Process ID: %d\nThread ID: %ld\n",getpid(),pthread_self());
	fprintf(stdout, "Enter return value: "); fscanf(stdin, "%ld", &ret);
	pthread_exit((void*) ret);
}
int main(int argc, char **args){
	void *ret;
	long int x = atoi(args[1]);
	pthread_t thd;
	if(pthread_create(&thd, NULL, routine, (void*)x)) return 1;
	if(pthread_join(thd, &ret)) return 1;
	fprintf(stdout, "Thread[%ld] sent %ld\n", thd,(long int) ret);
	return 0;
}
