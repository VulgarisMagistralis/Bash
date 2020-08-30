#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>
void fork_sing(int, int);
void start_fork(int, int);
int main(int argc, char **args){
	if(argc != 2) return 1;
	start_fork(atoi(args[1]),1);
	return 0;
}
void start_fork(int tot_level,int cur_level){
	if(cur_level > tot_level) return;
	fork_sing(cur_level, tot_level);
	if(cur_level%2 == 0) fork_sing(cur_level, tot_level);
}
void fork_sing(int l,int t){
	if(fork())exit(0);
	if(l==t)fprintf(stdout,"%d: %d from %d\n",l,getpid(),getppid());
       	start_fork(t,l+1);
}
