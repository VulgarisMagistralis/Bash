#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
long int level;
typedef struct{
        long int curr;
        pthread_t id;
}node;
void *routine(void *self){
        node *leaf = self;
        if(leaf->curr >= level){
                fprintf(stdout,"Thread ID: %ld at level %ld\n",leaf->id,leaf->curr);
                pthread_exit(NULL);
        }
	node child1; child1.curr = leaf->curr+1;
	node child2; child2.curr = leaf->curr+1;
        pthread_create(&(child1.id), NULL, routine, (void*)&child1);
        pthread_create(&(child2.id), NULL, routine, (void*)&child2);
        pthread_join(child1.id, NULL);
        pthread_join(child2.id, NULL);
        return NULL;
}
int main(int argc, char **args){
        level = atoi(args[1]);
        node root;
        root.id = pthread_self(); root.curr = 0;
        pthread_create(&(root.id), NULL, routine, (void*)&root);
	pthread_join(root.id, NULL);
        return 0;
}
