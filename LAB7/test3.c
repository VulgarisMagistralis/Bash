#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int level;
void start_tree(long int);
void *routine(void *c){
        long int curr = (long int)c;
        if(curr >= level){
               // fprintf(stdout,"Thread ID: %ld at level %ld\n",pthread_self(),leaf->curr);
                pthread_exit(NULL);
        }
        start_tree(curr+1);
        start_tree(curr+1);
        return NULL;
}
int main(int argc, char **args){
        level = atoi(args[1]);
        start_tree(0);
        return 0;
}
void start_tree(long int curr){
        pthread_t tid;
        if(pthread_create(&tid, NULL, routine, (void*)curr)) return;
         printf("at level %ld with id: %ld\n",curr, tid);
//        if(pthread_join(tid, NULL)) return;
}





