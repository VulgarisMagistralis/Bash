#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/types.h>
typedef struct ID_vector vector;
typedef struct ID_vector{
	int id;
	struct ID_vector *next;
}ID_vector;
void wrapper(int);
void vector_print(ID_vector*);
void fork_doub(int,int,struct ID_vector*);
void fork_sing(int,int,struct ID_vector*);
void start_fork(int,int,struct ID_vector*);
int main(int argc, char **args){
	if(argc != 2) return 1;
	wrapper(atoi(args[1]));
	return 0;
}
void wrapper(int t){
	//struct ID_vector *IDs = malloc(sizeof(struct ID_vector));
	start_fork(t, 1, IDs);
	//vector_print(IDs);
}
void start_fork(int tot_level,int cur_level,struct ID_vector *ids){
	if(cur_level > tot_level) return;
	else if(cur_level == 1)//create root
	else if(cur_level % 2 == 1) fork_sing(cur_level+1, tot_level,ids);
	else fork_doub(cur_level+1, tot_level,ids);
}
void fork_sing(int l, int t,struct ID_vector *ids){
	if(fork()) exit(0);
	ids->next = malloc(sizeof(struct ID_vector));
	ids->id = getpid();
        start_fork(t, l, ids->next);
}
void fork_doub(int l, int t, struct ID_vector *ids){//possibly wrong
	if(fork())exit(0);
	ids->next = malloc(sizeof(struct ID_vector));
        ids->id = getpid();
        start_fork(t, l, ids->next);
}
void vector_print(struct ID_vector* ids){
	while(ids->next != NULL){
		fprintf(stdout,"%d ",ids->id);
		ids = ids->next;
	}
	fprintf(stdout, "\n");
}


