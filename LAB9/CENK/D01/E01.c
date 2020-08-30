#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/wait.h>
FILE *fp;
bool flag = true;
int file_pipe[2];
int print_pipe[2];
void *to_up();
void *prints();
void *reads(){
	char c = fgetc(fp);
	if(c == EOF) flag = false;
	write(file_pipe[1], &c, 1);
	pthread_exit(NULL);
}
void *to_up(){
	char c;
	if(!flag) pthread_exit(NULL);
	read(file_pipe[0], &c, 1);
	c = toupper(c);
	write(print_pipe[1], &c, 1);
	pthread_exit(NULL);
}
void *prints(){
	char c;
	if(!flag) pthread_exit(NULL);
	read(print_pipe[0], &c, 1);
	printf("%c",c);
	pthread_exit(NULL);
}
int main(int argc, char **args){
	if(argc != 2) return 1;
	pthread_t reader, maner, printer;
	pipe(file_pipe);
	pipe(print_pipe);
	fp = fopen(args[1],"r");
	if(fp == NULL) return 1;
	while(flag){
		pthread_create(&reader, NULL, reads, NULL);
		pthread_create(&maner, NULL, to_up, NULL);
		pthread_create(&printer, NULL, prints, NULL);
		pthread_join(reader, NULL);
		pthread_join(maner, NULL);
                pthread_join(printer, NULL);
	}
	printf("\n");
	return 1;
}
