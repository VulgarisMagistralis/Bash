#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NO 240174
int set_random(int*,int);
int create_file(int*,int);
void test_print(int*,int);
int main(int argc, char **args){
	if(argc != 2) return 1;
	int *r1,*r2; //setup parameters
	if(set_random(r1,atoi(args[1]))) return 1;
	if(set_random(r2,atoi(args[1]))) return 1;
	test_print(r1,atoi(args[1]));
/*
	if(create_file(r1,1)) return 1;
	if(create_file(r2,2)) return 1;
	//sort
	if(!fork()){
	//sort both, write
	;
	}else{
	//merge both

	}*/
	return 0;
}
int create_file(int *r,int l){
	FILE *fp; int i = 0;
	if(l == 1) fp = fopen("F1.txt","w");
	if(l == 2) fp = fopen("F2.txt","w");
	if(fp == NULL){fprintf(stderr,"file failure");return 1;}
	while(r[i] != NULL){
//		fprintf(fp,"%d\n",r[i++]);
		    printf("%d \n",r[i++]);
	}
	    printf("FGHGFHFG\n");
	fprintf(fp,'\0');
	fclose(fp);
	return 0;
}
int set_random(int *r,int size){
	int i = 0;
	r = malloc(size * sizeof(int));
	if(r == NULL){fprintf(stderr,"allocation fault");return 1;}
//	srand(NO);
        while(i < size) r[i++] = rand()%100;
	return 0;
}
void test_print(int *v,int size){
	int i = 0;
	while(i<size) printf("%d: %d\n",i,v[i],i++);

}
