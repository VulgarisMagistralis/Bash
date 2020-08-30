#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>
/*
	Works but numbers are not in
	requested order due to nature
	of implemented recursion
*/
int i = 0;
char lock = 0;
char tas(char*);
void print_vec(int*, int);
void fork_sing(int, int, int*);
void start_fork(int, int, int*);
int main(int argc, char **args){
	if(argc != 2) return 1;
	int *vec;
        vec = malloc(atoi(args[1]));
	start_fork(atoi(args[1]), 1, vec);
	return 0;
}
void start_fork(int tot_level,int cur_level,int *vec){
	if(cur_level > tot_level){
		vec[cur_level-1] = ++i;
 		print_vec(vec, tot_level);
		return;
	}
	while(tas(&lock));	//CS
	++i;
	vec[cur_level-1] = i;
	lock = 0;	//CS
	fork_sing(cur_level, tot_level, vec);
	fork_sing(cur_level, tot_level, vec);
}
void fork_sing(int l,int t,int *vec){
	if(fork()) exit(0);
       	start_fork(t, l + 1, vec);
}
void print_vec(int *vec, int t){
	int j;
	for(j = 0;j <= t;j++)printf("%d -", vec[j]);
	printf("\n");
}
char tas(char *lock) {
	char val;
	val = *lock;
	*lock = 1;
	return val;
}
