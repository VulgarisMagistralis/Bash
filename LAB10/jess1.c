#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "semaphore.h"
#include <sys/wait.h>
sem_t *sem,*sem1;
int main(){
	sem = malloc(sizeof(sem_t));
	sem1 = malloc(sizeof(sem_t));
	sem_init(sem,0,1);
	sem_init(sem1,0,0);
	if(!fork()){
	//fork() returns integer
		while(1){ 
		sem_wait(sem);
	    	printf("Child: titties \n");
		sem_post(sem1);
		exit(0);		
		}
	}else{
		while(1){
		sem_wait(sem1);
    		printf("Parent: yes \n");
		sem_post(sem);
		exit(0);
		}
	}
    	return 0;
}
