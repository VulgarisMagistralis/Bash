#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
/*
	SIGALRM = 14 ?
	SIGUSR1 = 10
	SIGUSR2 = 12
*/
#define NUM 80
int sig_list[NUM];
void handler(int);
int sig_check();
void clean_list(int[]);
int main(int argc, char **args){
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	signal(SIGALRM, handler);
	int done = 0;
	while(!done){
		printf("\tWAITING SIGNALS!\n");
		sleep(5);
		done = sig_check();
	}
	printf("\tEnding program\n");
	return 0;
}
int sig_check(){
	int i = 0;
	int list[3];
//	while(i < NUM){
		if(sig_list[i] + sig_list[i+1] + sig_list[i+2] == 30 || sig_list[i] + sig_list[i+1] + sig_list[i+2] == 36){
                        fprintf(stdout, "\tTERMINATED!\n");
			list[0] = i; list[1] = i+1; list[2]=i+2;
			clean_list(list);
			i = i + 3;
                        return 1;
		}else if((sig_list[i] + sig_list[i+1]) == 22){
			fprintf(stderr, "\tERROR!\n");
			list[0] = i; list[1] = i + 1;
			clean_list(list);
			i = i + 2;
			return 0;
		}else if(sig_list[i] + sig_list[i+1] == 20 || (sig_list[i] + sig_list[i+1]) == 24){
 			fprintf(stdout, "\tSUCCESS!\n");
			list[0] = i; list[1] = i + 1;
			clean_list(list);
			i = i + 2;
			return 0;
		}else if(sig_list[i] == 14) i++;
	//}
	return 0;
}
void clean_list(int signals[]){
	int i = signals[0];
	if(signals[2] == 0){
		while(i+2 < NUM && sig_list[i] != 0){
			sig_list[i] = sig_list[i+2];
			i++;
		}
	}else while(i+3 < NUM && sig_list[i] != 0){ sig_list[i] = sig_list[i+3]; i++;}
}
void handler(int signum){
	if(signum == SIGUSR1 || signum == SIGUSR2){
		int i = 0;
		while(sig_list[i] != 0) i++;
		sig_list[i] = signum;
	}//else if(signum == SIGALRM) clean_list(-1);
}
