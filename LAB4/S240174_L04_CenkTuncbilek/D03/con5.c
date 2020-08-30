#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int *v;
void child_routine(int,int,int*);
void parent_routine(int*,int*,int,int);
int main(int argc,char **args){
	pid_t childID;
        int status, j, *s;
	int number = atoi(args[1]);
        v = malloc(number*sizeof(int));
        s = malloc(number*sizeof(int));
        for(j = 0; j < number; j++){
                if((childID = fork()) == -1){perror("fork error");exit(1);}
                else if(childID == 0){child_routine(j,number,v);exit(j);}
                waitpid(childID, &status,0);
                s[j] = status;
        }
        if(getpid() > 0)
                for(j = 0; j < number; j++)
                         if(WIFEXITED(s[j])) parent_routine(v, s, number, j);
	                 else if(WIFSIGNALED(s[j]))printf("Child ended because of an uncaught signal\n");
                         else if(WIFSTOPPED(s[j])) printf("Child process has stopped\n");
}
void parent_routine(int *v, int*s, int n, int j){
	printf("Child ended normally with code: %d\n", WEXITSTATUS(s[j]));
	printf("It recieved : %d\n",v[j]);
}
void child_routine(int j,int n,int *v){
	printf("Child process started : %d\n",j);
	sleep(n-j);
	printf("Child slept %d seconds, enter a number: ",n-j);
	fscanf(stdin,"%d",&v[j]);
}
