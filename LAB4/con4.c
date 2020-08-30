#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
void child_routine(int);
int main(){
	pid_t pids[4];
	int i;
	int n = 4;
	/* Start children. */
	for (i = 0; i < n; ++i) {
	  if ((pids[i] = fork()) < 0){perror("fork");exit(1);}
	  else if(pids[i] == 0){child_routine(i+1);exit(i+1);}
	}

/* Wait for children to exit. */
	int status;
	pid_t pid,endPID;
	while (n > 0) {
	  endPID = waitpid(pids[n-1],&status,WNOHANG|WUNTRACED);
	  if(WIFEXITED(status)) printf("Child with PID %d exited with status %d. EXIT: %d endpid:%d\n", pids[n-1], status,WEXITSTATUS(status),endPID);
	  --n;
	}
	return 0;
}
void child_routine(int i){
	printf("created %d\n",i);
	sleep(i);
}

