#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
int i = 0;
char lock = 0;
void print_vec(int*, int);
void cycle(int*, int, int);
char tas(char*);
int main(int argc, char **args){
        if(argc != 2) return 1;
        int *ids;
	ids = malloc(atoi(args[1]) * sizeof(int));
	ids[i] = 1;
	cycle(ids, atoi(args[1]), 1);
        return 0;
}
char tas(char *lock){
	char val;
	val = *lock;
	*lock = 1;
	return val;
}
void cycle(int *v,int max,int curr){
	v[i] = v[i-1] + 1;
	if(max <= curr){/*print_vec(v,max);*/return;}
	fork();
	while(tas(&lock));
	i++;
	printf("%d %d\n",i,getpid());
	lock = 0;
	cycle(v, max, curr + 1);
}
void print_vec(int *v,int max){
	int j;
	printf("\t Process tree:");
	for(j = 0; j < max; j++) printf("%d ",v[j]);
	printf("\n");
}




