#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv){
	int n;
	int pipeline[2];
	char wr = 'x';
	char rd;
	if(pipe(pipeline) == 0)
		if(!fork()){
			close(pipeline[1]);
			n = read(pipeline[0],&rd,1);
			printf("Read: %ld bytes: %c\n", n, rd);
			exit(0);
		}else{
			close(pipeline[0]);
			printf("Wrote: %ld bytes: %c\n",write(pipeline[1],&wr,1),wr);
		}
	return 0;
}
