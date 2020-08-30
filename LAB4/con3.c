#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main(void){
	int status, j, i, *v,*s;
	v = malloc(4 * sizeof(int));
	s= malloc(4 * sizeof(int));
	pid_t childID, endID;
	for(j = 0; j < 5; j++){
		if((childID = fork()) == -1){perror("fork error");exit(1);}
		else if(childID == 0){printf("Child process started at j = %d\n",j);sleep(j);exit(j);}
		endID = waitpid(childID, &status,0);
		v[j] = endID;s[j] = status;
	}
	if(getpid() > 0){
		for(i=0;i<5;i++){

//  			endID = waitpid(childID, &status,0);
//	      		if(endID == -1){perror("waitpid error");exit(1);}
//			else if(endID == 0){printf("Parent waiting for child \n");sleep(1);}
//			else{// if(endID == v[i]){
              			if(WIFEXITED(s[i]))printf("Child ended normally ::%d\n", WEXITSTATUS(s[i]));
              			else if(WIFSIGNALED(status))printf("Child ended because of an uncaught signal\n");
              			else if(WIFSTOPPED(status)) printf("Child process has stopped\n");
//				exit(0);
//			}
		}

	}
}
