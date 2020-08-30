#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<sys/wait.h>
#define SIZE 100
pid_t cid;
int pipeline[2];
void handler(int);
int write_pipe(char*);
int main(int argc, char **argv){
	char line[SIZE];int stat;

	setbuf(stdout,NULL);
	signal(SIGUSR1, handler);
	if(pipe(pipeline) == 0){
		if(fork()){
			close(pipeline[0]);
			while(1){
				printf("\nEnter string<write \"end\" to terminate>:");
				fscanf(stdin, "%s", line);
				if(write_pipe(line)){printf("Terminating parent\n");exit(0);}
			}
			close(pipeline[1]);
			wait(&stat);
			exit(0);
		}else{
			cid = getpid();
			close(pipeline[1]);
			while(1){
				read(pipeline[0],line,SIZE);
				printf("\nEntered string :%s",line);
			}
		}
	}
	return 0;
}
int write_pipe(char *line){
	int i;
	for(i = 0; line[i] != '\0'; i++) line[i] = toupper(line[i]);
	if(!strcmp(line, "END")){kill(cid, SIGUSR1); return 1;}
	write(pipeline[1],line,sizeof(line));
	return 0;
}
void handler(int signal){
	if(signal != SIGUSR1) return;
	printf("\nProcess[ %d ] will be terminated!\n",getpid());
	exit(0);
}
