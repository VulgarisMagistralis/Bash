#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
typedef struct{
	long int level;
	long int curr;
	pthread_t *c1;
	pthread_t *c2;
	pthread_t id;
}node;
//void start_tree(long int, long int);
void *routine(void *self){
	node *leaf = self;
	if(leaf->curr >= leaf->level){
		fprintf(stdout,"Thread ID: %ld at level %ld\n",leaf->id,leaf->curr);
		pthread_exit(NULL);
	}
//	start_tree(leaf->level, leaf->curr+1);
//	start_tree(leaf->level, leaf->curr+1);
	
	if(pthread_create(&(info->id), NULL, routine, (void*)info)) return;
	if(pthread_create(&(info->id), NULL, routine, (void*)info)) return;
	pthread_join(leaf->c1, NULL);
	pthread_join(leaf->c2, NULL);
	return NULL;
}
int main(int argc, char **args){
        long int level = atoi(args[1]);
	node root;
	root.id = pthread_self();
	root.level = level;
	root.curr = 0;
	pthread_create(&(root.id), NULL, routine, (void*)root);
//	start_tree(level, 0, root); // node 0
        return 0;
}/*
void start_tree(long int level, long int curr, node parent){
	node *child;
	child = malloc(sizeof(node));
	child->level = level; child->curr = curr;
        if(pthread_create(&(info->id), NULL, routine, (void*)info)) return;

//	 printf("at level %ld with id: %ld\n",curr,info->id);
//	printf("::::::%ld\n",info->id);
//        pthread_join(info->id, NULL);
//	free(info);
}
*/
