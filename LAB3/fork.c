#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <sys/types.h>
#include <unistd.h>
void start_fork();
int main(int argc, char **args){
	start_fork();
	return 0;
}
void start_fork(){
	int i = 44;
//	fprintf(stdout,"Starting here: ID:%d, ParentID: %d\n",getpid(),getppid());
	if(fork() != 0) exit(0); //parent goes in gets killed do it for odd levels ,
	fprintf(stdout,"Count:%d\n",i);
        fprintf(stdout,"Then here: ID:%d, ParentID: %d\n",getpid(),getppid());
}

