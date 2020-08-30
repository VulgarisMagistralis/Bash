#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "semaphore.h"
#include <sys/wait.h>

int main(){
    	if(fork()){
		printf("%d from %d\n",getpid(),getppid());
	}else{
 		printf("%d from %d\n",getpid(),getppid());
	}
 	if(fork()){
		printf("%d from %d\n",getpid(),getppid());
	}else{
		printf("%d from %d\n",getpid(),getppid());
	}

    	return 0;
}
