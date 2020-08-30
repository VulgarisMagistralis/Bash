#include<math.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
int get_val(int, char*);
void print_vec(int*, int);
int main(int argc, char **args){
	int i = 0, size = atoi(args[1]);
	int *ids; char *prevs;
	ids = malloc(size * sizeof(int));
	prevs = malloc(size * sizeof(char));
	for(i = 0; i < size; i++){
		if(fork()){
			prevs[i] = 'p';
			ids[i] = get_val(i, prevs);

		}else{
			prevs[i] = 'c';
			ids[i] = get_val(i, prevs);
		}

	}


//	printf("%d", i);
        return 0;
}
int get_val(int curr, char *prevs){
	int c = 0, p = 0, i, val = 0;
	if(prevs[0] == 'p'){
		val = pow(2, curr);
		while(prevs[i] == 'c')

	}else{



	}

	return val;
}
void print_vec(int *v,int max){
        int j,k = 2^max;
        printf("\t Process tree:");
        for(j = 0; j < k; j++) printf("%d ",v[j]);
        printf("\n");
}

