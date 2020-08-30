#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/wait.h>
#include<sys/types.h>
FILE *fp;
bool flag = true;
int file_pipe[2];
int print_pipe[2];
void *to_up();
void *prints();
void *reads(){
	close(file_pipe[0]);
	close(print_pipe[0]);
	close(print_pipe[1]);
	char c = fgetc(fp);
	FILE *stream;
	stream = fdopen(file_pipe[1],"w");
	printf("DEAD?\n");
	if(c == EOF) flag = false;
	else fprintf(stream,"%c", c);
	close(file_pipe[1]);
	pthread_exit(NULL);
}
void *to_up(){
	close(file_pipe[1]);
	close(print_pipe[0]);
	char c, d;
	FILE *in_stream, *out_stream;
	in_stream = fdopen(file_pipe[0],"r");
	out_stream = fdopen(print_pipe[1],"w");
	c = fgetc(in_stream);
	d = toupper(c);
	printf("DEAD??\n");
	fprintf(out_stream,"%c",d);
	close(print_pipe[1]);
	close(file_pipe[0]);
	pthread_exit(NULL);
}
void *prints(){
	close(file_pipe[1]);
	close(file_pipe[0]);
	close(print_pipe[1]);
	char c;
	FILE *stream;
	stream = fdopen(print_pipe[0],"r");
	c = fgetc(stream);
	fprintf(stdout,"%c",c);
	close(print_pipe[0]);
	pthread_exit(NULL);
}
int main(int argc, char **args){
	if(argc != 2) return 1;
	pthread_t reader, maner, printer;
	if(pipe(file_pipe)){printf("pipe fail\n");exit(1);}
	if(pipe(print_pipe)){printf("Pipe fail\n");exit(1);}
	fp = fopen(args[1],"r");
	//if(fp == NULL) return 1;
	while(flag){
		pthread_create(&reader, NULL, reads, NULL);
		pthread_create(&maner, NULL, to_up, NULL);
		pthread_create(&printer, NULL, prints, NULL);
		pthread_join(reader, NULL); pthread_join(maner, NULL); pthread_join(printer, NULL);
	}
	printf("\n");
	return 1;
}
