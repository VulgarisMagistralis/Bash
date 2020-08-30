#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
void vector_print(int*, int);
void fork_sing(int, int,int*);
void start_fork(int,int,int*);
int main(int argc, char **args){
	if(argc != 2) return 1;
	start_fork(atoi(args[1]), 1, malloc(atoi(args[1]) * sizeof(int)));
	return 0;
}
void start_fork(int tot_level, int cur_level, int *v){
	if(cur_level > tot_level){vector_print(v, tot_level); return;}
	if(cur_level == 1)fork_sing(cur_level, tot_level,v);
	else if(cur_level % 2 == 0) fork_sing(cur_level, tot_level, v);
	else if(cur_level % 2 == 1){
		fork_sing(cur_level, tot_level, v);
		fork_sing(cur_level, tot_level, v);
	}
}
void fork_sing(int l, int t,int *v){
	if(fork())exit(0);
	v[l-1] = getpid();
        start_fork(t, l+1, v);
}
void vector_print(int *v,int t){
	int i;  printf("\n");
	for(i = 0; i <t; i++) printf("%d ",v[i]);
	printf("\n");
}
