#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/wait.h>
int i = 0;
int curr = 1;
int max = 0;
void print_vec(int*, int);
void *routine(){
	if(curr > max){printf(">>>%d at level: %d\n",++i,curr); pthread_exit(NULL);}
        pthread_t id1, id2;
 //       printf(">>>%d at level: %d\n",++i,curr);
        pthread_create(&id1,NULL,routine,NULL);
	printf(">>>%d at level: %d\n",++i,curr);
	pthread_create(&id2,NULL,routine,NULL);
	printf(">>>%d at level: %d\n",++i,curr);
	curr++;
	pthread_join(id1,NULL);x
	pthread_join(id2,NULL);
	return NULL;
}
int main(int argc, char **args){
        if(argc != 2) return 1;
	pthread_t id;
	max = atoi(args[1]);
	pthread_create(&id,NULL,routine,NULL);
	pthread_join(id,NULL);
        return 0;
}
void print_vec(int *v,int max){
        int i;
        printf("\nProcess tree:");
        for(i=0;i<max;i++) printf("%d ",v[i]);
}


