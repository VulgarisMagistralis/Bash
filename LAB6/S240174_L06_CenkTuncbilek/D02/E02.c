#include<stdio.h>
#include<ctype.h>
#include<limits.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<dirent.h>
#include<sys/wait.h>
#define MAX 1000
//global variables
int p_write = 0;
int p_read = 0;
int ans = 0;
int pipe_open;
int req_pipe[2];
int data_pipe[2];
int answer_pipe[2];
//prototypes
void handler(int);
void sort_file(char*);
int count_lines(char*);
int main(int argc, char **argv){
	if(argc != 3) return 1;
	//local variables
	int result[2], ret_res[2], i, request = 0;
 	char *file_name, *file_name1, **files;
 	int file_count = 0,tot_lines = 0;
	int number_of_procs = atoi(argv[1]), j = 0;
	char command[PATH_MAX], cwd[PATH_MAX];
	pid_t pid = 0;
 	getcwd(cwd, sizeof(cwd));
	if(pipe(req_pipe) < 0) return 1;
	if(pipe(data_pipe) < 0) return 1;
	if(pipe(answer_pipe) < 0) return 1;
	pipe_open = 1;
	//allocation for variables
	file_name = malloc(PATH_MAX * sizeof(char));
	file_name1 = malloc(PATH_MAX * sizeof(char));
	files = malloc(MAX * sizeof(char*));
	for(i = 0; i < number_of_procs; i++) files[i] = (char*)malloc(PATH_MAX * sizeof(char));
	//system() call setup
	snprintf(command,sizeof(command),"cd && cd %s && ls > %s/list.txt",argv[2],cwd);
	system(command);
	printf("list.txt created\n");
// 	FILE *fp = fopen("list.txt", "r");
//        char *path_name = malloc(PATH_MAX*sizeof(char));
	signal(SIGPIPE, handler);
	for(i =	0; i < number_of_procs; i++){
		if(!fork()){
			close(req_pipe[0]);
			close(data_pipe[1]);
			close(answer_pipe[0]);
			printf("Child [%d] started\n", getpid());
			pid = getpid(); request = 1;
			if(pipe_open) write(req_pipe[1], &request, 1);
			else{fprintf(stderr,"Pipe is closed\n"); return i;}
 			while(!p_write); printf("check1\n");
			read(data_pipe[0], file_name1, MAX);
			printf("reading from %s\n", file_name1);
			sort_file(file_name1);
 			result[1] = count_lines(file_name);
			result[0] = getpid(); 	//reading lines! wc -l
			write(answer_pipe[1], result, sizeof(result));
			p_read = 1;
			close(req_pipe[1]);
			close(data_pipe[0]);
			close(answer_pipe[1]);
			exit(0);
		}else{
			close(req_pipe[1]);
			close(data_pipe[0]);
			close(answer_pipe[1]);
			FILE *fp = fopen("list.txt", "r");
		        char *path_name = malloc(PATH_MAX*sizeof(char));
				read(req_pipe[0], &request, 1);
				fscanf(fp, "%s",file_name);
				if(i == 1) fscanf(fp, "%s",file_name);
				printf("read file from list: %s\n",file_name);
				snprintf(path_name, MAX, "%s/%s", argv[2], file_name);
				printf("writing %s into pipe\n", path_name);
				files[file_count++] = path_name;///////
				write(data_pipe[1], path_name, MAX);
				p_write = 1;
				while(!p_read);
				read(answer_pipe[0], ret_res, sizeof(ret_res)+1);
				tot_lines = tot_lines + ret_res[1];
//				printf("%d -%d\n",ret_res[0],ret_res[1]);
//				if(fp == NULL) kill(pid, SIGPIPE);
				wait(NULL);
			fclose(fp);/*
			char *f = malloc(MAX*sizeof(char));
			for(j = 0; j < number_of_procs; j++)
	 			snprintf(f, MAX," %s.txt",files[j]);
			printf("%s\n",f);
			snprintf(command, PATH_MAX, "sort -m %s > all_sorted.txt", f);
			system(command);*/
			close(req_pipe[0]);
			close(data_pipe[1]);
 			close(answer_pipe[0]);
		}
	}
}
void handler(int signal){
	if(!getpid()){
		 if(signal == SIGPIPE){
			printf("Pipe closed\n");
			pipe_open = 0;
		}
	}
}
void sort_file(char *file_path){
	char comm[PATH_MAX], cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	snprintf(comm,sizeof(comm),"cd && sort -n -o %s %s",file_path,file_path);
	printf("file sorted by %d\n",getpid());
	system(comm);
}
int count_lines(char *file){
	int n = 0; char c;
	FILE *fp = fopen(file,"r");
	do{
		c = getc(fp);
		if(c == '\n') n++;
	}while(c != EOF);
	fclose(fp);
	return n;
}
