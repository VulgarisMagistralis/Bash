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
int p_read = 0;
int ans = 0;
int pipe_open;
int req_pipe[2];
int data_pipe[2];
int answer_pipe[2];
//prototypes
void handler(int);
int sort_file(char*);
//char *send_file_name(FILE*,char*);
int count_lines(char*);
int main(int argc, char **argv){
	if(argc != 3) return 1;
	//local variables
	int result[2], ret_res[2], i, request = 0;
 	char *file_name, **files; int ans[1];
 	int file_count = 0,tot_lines = 0;
	int number_of_procs = atoi(argv[1]), j = 0;
	char command[PATH_MAX], cwd[PATH_MAX];
	pid_t pid = 0;
 	getcwd(cwd, sizeof(cwd));
	if(pipe(req_pipe) < 0) return 1;
	if(pipe(data_pipe) < 0) return 1;
	if(pipe(answer_pipe) < 0) return 1;
	pipe_open = 1;
	printf("1111111\n");
	//allocation for variables
	file_name = malloc(PATH_MAX * sizeof(char));
	files = malloc(MAX * sizeof(char*));
	for(i = 0; i < number_of_procs; i++) files[i] = (char*)malloc(PATH_MAX * sizeof(char));
	 printf("222222\n");
	//system() call setup
	snprintf(command,sizeof(command),"cd && cd %s && ls > %s/list.txt",argv[2],cwd);
	system(command);
	printf("list.txt created\n");
	signal(SIGPIPE, handler);
	printf("33333\n");
	for(i =	0; i < number_of_procs; i++){
		if(!fork()){
			close(req_pipe[0]);
			close(data_pipe[1]);
			close(answer_pipe[0]);
			printf("Child [%d] started\n", getpid());
			pid = getpid(); request = 1;
			if(pipe_open) write(req_pipe[1], &request, 1);
			else{fprintf(stderr,"Pipe is closed\n"); return i;}
			while(!p_read);
 			read(data_pipe[0], file_name, sizeof(file_name));
			printf("%s\n",file_name);
			if(sort_file(file_name)) result[1] = count_lines(file_name);
			result[0] = getpid(); 	//reading lines! wc -l
			printf("Child writing to answer_pipe\n");ans = 1;
			write(answer_pipe[1], result, sizeof(result));
			close(req_pipe[1]);
			close(data_pipe[0]);
			close(answer_pipe[1]);
			exit(0);
		}else{
			close(req_pipe[1]);
			close(data_pipe[0]);
			close(answer_pipe[1]);
			FILE *fp = fopen("list.txt", "r");
			while(1){
				while(!request){
					read(req_pipe[0], &request, 1);
					printf("44444\n");
				}
				fscanf(fp, "%s",file_name);
				snprintf(file_name, MAX, "%s/%s", argv[2], file_name);
				if(file_name == NULL){fprintf(stderr,"FAILED\n");return 1;}
				printf("writing file name into pipe\n");
				files[j++] = file_name;
				write(data_pipe[1], file_name, sizeof(file_name));
				p_read = 1;
				while(!ans);
				read(answer_pipe[0], ret_res, sizeof(ret_res));
				file_count++;
				tot_lines = tot_lines + ret_res[1];
				kill(pid, SIGPIPE);
			}
			fclose(fp);
			for(j=0;j<number_of_procs;j++) snprintf(command,PATH_MAX," %s",files[j]);
			snprintf(command, PATH_MAX, "sort -n %s all_sorted.txt", command);
			system(command);
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
int sort_file(char *file_path){
	char comm[PATH_MAX], cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	snprintf(comm,sizeof(comm),"sort –n –o %s %s",file_path,file_path);
	printf("file sorted by %d\n",getpid());
	system(comm);
	return 1;
}/*
char *send_file_name(FILE *fp,char *dir){
	char *path=malloc(MAX*sizeof(char*)), *file_name = malloc(PATH_MAX * sizeof(char));
	printf("Looking for file name\n");
	fscanf(fp,"%s",file_name);
	snprintf(path,MAX,"%s/%s",dir,file_name);
	return path;
}*///wc
int count_lines(char *file){
	int n = 0; char c;
	FILE *fp = fopen(file,"r");
	while((c = fgetc(fp)) != '\0') if(c == '\n') n++;
	fclose(fp);
	return n;
}
