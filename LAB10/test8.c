#include<pthread.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
long int count = 0;
sem_t *sem;
long int level;
int curr = 0;
typedef struct thread_list tl;
typedef struct tl{ int id; tl *next;} thread_list;
thread_list *head;
void init_tree(int);
thread_list *print_vec();
static void *routine(void*);
int main(int argc, char **args){
        level = atoi(args[1]);
	sem = malloc(sizeof(sem_t));
	head = malloc(sizeof(thread_list));
	sem_init(sem, 0, 1);
	init_tree(level);
	sem_destroy(sem);
        return 0;
}
static void *routine(void *self){
	if(count >= pow(2, level + 1) - 1){print_vec(head); pthread_exit((void*)count);}
        if(count >= pow(2, level)) head->next = print_vec(head);
        void *i;
        pthread_t child1, child2;
        thread_list *t, *temp;
	t = malloc(sizeof(thread_list));
        sem_wait(sem);
        t->id = ++count;
	temp = head;
	printf("cc\n");
	while(temp->next != NULL) temp = temp->next;
	temp->next = t;
        sem_post(sem);
printf("xx\n");
        pthread_create(&child1, NULL, routine, NULL);
        pthread_create(&child2, NULL, routine, NULL);
        pthread_join(child1, &i);
        pthread_join(child2, &i);
        return NULL;
}
void init_tree(int n){
	int i;
	pthread_t *ids;
	ids = malloc(n * sizeof(pthread_t));
	for(i = 0; i < n; i++) pthread_create(&ids[i], NULL, routine, NULL);
	for(i = 0; i < n; i++) pthread_join(ids[i], NULL);
}

thread_list *print_vec(thread_list *h){
	thread_list *temp;
	temp = malloc(sizeof(thread_list));
	printf("Process tree: ");
	while(h != NULL){
		printf("%d ",h->id);
		h = h->next;
	}
	printf("\n");
	return temp;
}
