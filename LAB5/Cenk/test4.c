#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdbool.h>
#include<signal.h>
#include<sys/wait.h>
#define SIZE 100
//params
int flag = 0;
bool permit = true;
int limit;
pid_t cid;
//params
void handler(int);
int main(int argc, char **args){
	if(argc != 2) return 1;
	srand(time(0));
	limit = rand() % 10 + 10;
	int stat; srand(time(NULL));
	signal(SIGUSR1, handler);
	if(fork()){
		char line[SIZE];
		FILE *fp = fopen(args[1],"r");
		printf("Limit: %d\n",limit);
                while(1){
			while(fgets(line,SIZE,fp) != NULL){
				sleep(1);
				if(permit)fprintf(stdout, "%s\n", line);
			}
			fseek(fp,0,SEEK_SET);
		}
		fclose(fp);
		exit(22);
		wait(&stat);
	}else{
		cid = getpid();
		while(1){
			sleep((rand()%10)+1);
			kill(getppid(),SIGUSR1);
		}

		exit(0);
	}
	return 0;
}
void handler(int signal){
	flag++;
	if(signal == SIGUSR1 && (getpid()!=cid)){
		printf("Received signal with count:%d\n", flag);
		if((flag >= limit) && (flag < (limit + 5))) printf("Ignored\n");
		else if(flag >= (limit + 5)){ printf("Killing parent\n");kill(cid, SIGUSR1); exit(0);}
		else if((flag % 2) == 1){permit = false;printf("jumped\n");}
		else if((flag % 2) == 0){permit = true;printf("Continue printing\n");}
	}else if(signal == SIGUSR1){printf("Killing child\n"); exit(0);}
	return;
}
