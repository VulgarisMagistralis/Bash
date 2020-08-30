#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include"semaphore.h"
#include"pthread.h"
sem_t *sem;
int c = 1;
void run(){fprintf(stdout,"%d is increasing: %d\n",getpid(), ++c);}
int main(int argc, char **args) {
	int i,size = atoi(args[1]);
	sem = (sem_t*)malloc(sizeof(sem_t));
	sem_init(sem, 0, 1);
	int ids[100];
	for(i = 0; i < size; i++){
		fork();
		if(ids[c] == 0) ids[c] = getpid();
	}
	sleep(10);
	for(i = 0; i < 10; i++) if(ids[i] > 0) printf("%d\n",ids[i]);
/*
	sem_wait(sem);
	run();
	sem_post(sem);
*/
	return 0;
}
