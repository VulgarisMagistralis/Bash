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
//c: 1 ready 0 not
//p: 1 accept 0 deny
//global variables
int current_process_number = 0;
int pipe_open;
int *permit_list; // store which children are requesting fifo
//int *finished_proces_list;	// store finished processes
int pipeline[2];
int data_pipe[2];
int answer_pipe[2];
//prototypes
void handler(int);
void request_pipe();
char *data_pipe(char*);
char *send_file_name();
int main(int argc, char **argv){
	if(argc != 3) return 1;
	//local variables
	int i, request = 0; char *file_name;
	int number_of_procs = atoi(args[1]);
	char command[PATH_MAX], cwd[PATH_MAX];
 	getcwd(cwd, sizeof(cwd));
	if(pipe(pipeline) < 0) return 1;
	if(pipe(data_pipe) < 0) return 1;
	if(pipe(answer_pipe) < 0) return 1;
	pipe_open = 1;
	//allocation for variables filled with 0
	file_name = malloc(PATH_MAX * sizeof(char));
	permit_list = calloc(number_of_procs * sizeof(int));
	pid_t *pids = calloc(number_of_procs * sizeof(pid_t));
//	finished_process_list = calloc(number_of_procs * sizeof(int));
	//system() call setup
	snprintf(command,sizeof(command),"cd && cd %s && ls > %s/list.txt",argv[2],cwd);
	system(command);
	for(i =	0; i < number_of_procs; i++){
		if(!fork()){
			printf("Child [%d] started\n", getpid());
			pids[i] = getpid();
			current_process_number = i;
			if(!pipe_open) return 1; //problem
			request_pipe();
			sort_file(data_pipe(argv[2]));
			;


			exit(0);
		}
	}
	while(1){
		do{read(pipeline[0], request, 1);} while(!request);
		if((file_name = send_file_name())==NULL){fprintf(stderr,"FAILED\n");return 1;}
		printf("writing file name into pipe\n");
		write(pipeline[1], file_name, sizeof(file_name));
		data_pipe();

	}

//	for()waitpid();
}

//SIGUSR1 REQUEST
//SIGUSR2 RETURN REQ.
void handler(int signal){
	if(getpid()){
		if(signal == SIGUSR1){
			int i = 0;
			printf("Child request received\n");
			while(permit_list[i] != 0 && i < sizeof(permit_list)) i++;
			permit_list[i] = current_process_number + 1;

		}

	}

}
char *data_pipe(char *dir){
	int i = 0;char *file_name[PATH_MAX];
	while(i < sizeof(permit_list)){
		if(permit_list[i] > 0 && (permit_list[i]-1) == getpid())
			read(data_pipe[0], file_name, PATH_MAX);
		else i++;
	}
	if(file_name == NULL){fprintf(stderr,"Read error\n"); return NULL;}
	permit_list[i] = 0; // removing itself from waiting queue
	snprintf(file_name, PATH_MAX, " %s/%s", dir, file_name);
	return file_name;
}
int sort_file(char *file_path){
	char comm[PATH_MAX], cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	snprintf(comm,sizeof(comm),"sort –n –o %s %s.sorted",file_path,file_path);
	system(comm);
}
char *send_file_name(){ // done
	int i = 0, line_no;
	char *file_name = malloc(PATH_MAX*sizeof(char));
	FILE *fp = fopen("list.txt","r");
	if(fp == NULL){fprintf(stderr,"read error\n"); return 1;}
	while(permit_list[i] == 0)i++;
	line_no = permit_list[i]-1;
	i = 0;
	printf("Looking for file name\n");
	while((fscanf(fp,"%s",file_name) != EOF))
		if(i == line_no) return file_name;
		else i++;
	fprintf(stderr,"File not found\n");
	return NULL;
}
void request_pipe(){//not done ?
	printf("Child sending request signal\n");
        kill(getpid(), SIGUSR1);// request_pipe here
	write(pipeline[1],1,1));
}
