#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#define SIZE 720
long int level;
typedef struct{
        long int curr;
        pthread_t id;
	char ancestors[SIZE];
}node;
void *routine(void *self){
        node *leaf = self;
        if(leaf->curr >= level){
                fprintf(stdout,"Thread tree: %s %ld\n",leaf->ancestors, pthread_self());
                pthread_exit(NULL);
        }
	char current[100], ancestors[SIZE];
 	sprintf(current,"%ld ",pthread_self());
	strcpy(ancestors, leaf->ancestors); strcat(ancestors, current);
        node child1; child1.curr = leaf->curr + 1; strcpy(child1.ancestors,ancestors);
        node child2; child2.curr = leaf->curr + 1; strcpy(child2.ancestors,ancestors);
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
