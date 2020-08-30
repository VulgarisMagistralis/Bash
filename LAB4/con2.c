#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
void print(int*, int);
void proc_routine(int*, int, int);
int main(int argc, char **args){
        int *v,i = 0, size = atoi(args[1]);
        v = malloc(size*sizeof(int));
	proc_routine(v,0,size);
	while(WIFEXITED(i) && i<=size){
		i++:
	}

//        print(v, size);
        return 0;
}
void proc_routine(int *vec,int level,int size){
	if(size<=level) return;
	int stat, cpid;
	if(!fork()){
		sleep(level);
		fprintf(stdout,"\n %d from %d\nEnter element %d:",getpid(),getppid(),level+1);
		fscanf(stdin,"%d",&vec[level]);
		stat = level;cpid = getpid();
		exit(size-level);
	//else fprintf(stdout,"\n waitpid=> %d", waitpid(cpid,&stat,0));
		proc_routine(vec,level+1,size);
	}
}
void print(int *v, int size){
        int i;
        fprintf(stdout,"array , codes:\n");
        for(i = 0; i < size; i++){
                fprintf(stdout,"%d: %d , %d \n",i,v[i],WEXITSTATUS(i));
        }
}




