#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
void vector_print(int*, int);
void fork_sing(int,int,int*,int);
void start_fork(int,int,int*,int);
int main(int argc, char **args){
	if(argc != 2) return 1;
	int vector[10], ID_count = 0;
//	vector = malloc(atoi((args[1])+1) * sizeof(int));
	vector[ID_count] = ++ID_count;
	start_fork(atoi(args[1]), 1, vector, ID_count);
	return 0;
}
void start_fork(int tot_level, int cur_level, int *v,int ID_count){
	if(cur_level > tot_level){vector_print(v, tot_level); return;}
	fork_sing(cur_level, tot_level, v, ID_count + 1);
}
void fork_sing(int l, int t,int *v,int ID_count){
	fork();
	v[ID_count] = ID_count++;
        start_fork(t, l+1, v,ID_count);
}
void vector_print(int *v,int t){
	int i;  printf("\nProcess tree: ");
	for(i = 1; i <= t; i++) printf("%d ",v[i]);
	printf("\n");
}
