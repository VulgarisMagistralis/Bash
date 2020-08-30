#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<sys/wait.h>
#include<semaphore.h>
int i=0;
void print_vec(int*, int);
void start_fork(int);
int main(int argc, char **args){
        if(argc != 2) return 1;
	setbuf(stdout, 0);
        start_fork(atoi(args[1]));
        return 0;
}
void start_fork(int max){
	pid_t pid;
	int j, *vec;
	sem_t *sem_p, *sem_c;
	int max2 = pow(2, max);
	sem_p = malloc(sizeof(sem_t));
	sem_c = malloc(sizeof(sem_t));
	vec = malloc((max + 1) * sizeof(int));
	sem_init(sem_p, 0, max2);
	sem_init(sem_c, 1, max2);
	for(j = 0; j < 2; ++j){
		if(!fork()){
			sem_wait(sem_c);
			printf("%d ",++i);
			sem_post(sem_p);
			sleep(10);
		}else{
			sem_wait(sem_p);
			printf("%d\n",++i);
			sem_wait(sem_c);
		}

	}
	printf("%d\n",++i);
	vec[max] = i;
//	print_vec(vec, max);
}
void print_vec(int *vec, int t){
        int j;
        for(j = 0; j <= t; j++) printf("%d -", vec[j]);
        printf("\n");
}
