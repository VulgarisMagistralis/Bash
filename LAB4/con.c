#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
void print(int*,int);
int main(int argc, char **args){
	int *v, i, size = atoi(args[1]);
	int stat, cpid, pid;
	v = malloc(size*sizeof(int));
	for(i = 0; i < size; i++){
		pid = fork();
		if(pid<0){perror("cant fork");exit(0);}
		else if(!pid){
			sleep(size-i);
			stat = size-i;
			cpid = getpid();
			fprintf(stdout,"\n %d from %d\nEnter element %d:",getpid(),getppid(),i+1);
			fscanf(stdin,"%d",&v[i]);
			fprintf(stdout,"\n exiting with %d, read:%d",size-i,v[i]);
			exit(size-i);
		}else if(getpid() > 0)
			 fprintf(stdout,"\n\n Child pid: %d with exit status: %d,stat: %d\n\n",
			      waitpid(cpid,&stat,0),WEXITSTATUS(stat),stat);
	}
	printf("\n");
	fprintf(stdout,"\n\n%d %d %d \n\n",v[0],v[1],v[2]);
	print(v, size);
	return 0;
}
void print(int *v, int size){
	int i,status;
	fprintf(stdout,"array , codes:\n");
	for(i = 0; i < size; i++){
		fprintf(stdout,"%d: %d , %d \n",i,v[i],WEXITSTATUS(i));
	}
}
