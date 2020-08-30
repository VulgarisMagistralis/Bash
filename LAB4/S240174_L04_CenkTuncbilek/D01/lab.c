#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<time.h>
/* wait() returns the pid of child
*/
int main(int argc, char **args){
	int stat,r,n1; pid_t cpid;
	srand(time(NULL));
	if(fork()){
		fprintf(stdout,"Parent: PID=%d; ParentPID=%d\n",getpid(), getppid());
		sleep((n1 = (rand() % 11)));
		fprintf(stdout,"Slept %d seconds\n", n1);
		cpid = wait((int*)0);
		fprintf(stdout, "n1: %d Parent Wait: ChildPID=%d \n ",n1, cpid);
   	        fprintf(stdout, "WIFEXITED=%d WEXITSTATUS=%d \n",WIFEXITED(0),WEXITSTATUS(cpid));
	  	printf("Parent completed\n");
	  //	exit(0);
	}else{
		r = rand() % 256;
		fprintf(stdout,"Child : PID=%d; ParentPPID=%d\n",getpid(),getppid());
    		sleep((rand() % 11));
    		fprintf(stdout, "Child completed, reuturn value: %d, parent : %d\n",r,getppid());
		exit(r);
	}
	return 0;
}
