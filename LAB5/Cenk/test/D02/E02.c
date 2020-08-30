#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include <sys/wait.h>
#define NO 240174
int write_file(int*,int);
int *set_random(int);
int convert(char*,char*);
int *merge_sort(char*,char*,int);
int create_file(int*, char*,int);
int main(int argc, char **args){
	if(argc != 2) return 1;
	int size = atoi(args[1]);
	char *command_vec1[] = {"/usr/bin/sort","-n","-o","F1.txt","F1.txt",NULL};
	char *command_vec2[] = {"/usr/bin/sort","-n","-o","F2.txt","F2.txt",NULL};
	if(create_file(set_random(size), "F1.txt", size)) return 1;
	if(create_file(set_random(size), "F2.txt", size)) return 1;
	if(!fork()){
		fprintf(stdout, "Child running\n");
		execv(command_vec1[0], command_vec1);
		execv(command_vec2[0], command_vec2);
		if(convert("F1.txt", "F1.bin")) return 1;
		if(convert("F2.txt", "F2.bin")) return 1;
		int *sorted = merge_sort("F1.bin", "F2.bin", size);
		if(write_file(sorted,size*2)){fprintf(stderr,"write failed\n");return 1;}
	}
	return 0;
}
int *merge_sort(char *file1, char *file2, int size){
	int i = 0, j = 0, k = 0, a, b, *sorted = malloc(2 * size * sizeof(int));
	if(sorted == NULL){ fprintf(stderr,"allocation error"); return (int*)1;}
	FILE *f1 = fopen(file1, "rb"), *f2 = fopen(file2, "rb");
	if(f1 == NULL || f2 == NULL){fprintf(stderr,"file error");return (int*)1;}
  	fread(&a, sizeof(int), 1, f1);
	fread(&b, sizeof(int), 1, f2);
        while(i < size && j < size){
                if(a<b){sorted[k++] = a;fread(&a, sizeof(int),1,f1);i++;}
                else{sorted[k++] = b; fread(&b, sizeof(int), 1, f2);j++;}
        }
        while(i < size){sorted[k++] = a; fread(&sorted[k++], sizeof(int), 1, f1); i++;}
        while(j < size){sorted[k++] = b; fread(&sorted[k++], sizeof(int), 1, f2); j++;}
	char command[100];
	snprintf(command,100,"rm -f %s",file1);
	system(command);
	snprintf(command,100,"rm -f %s",file2);
	system(command);
	return sorted;
}
int convert(char *o_path,char *n_path){
	FILE *fi = fopen(o_path,"r");
	FILE *fo = fopen(n_path,"wb");
	if(fi == NULL || fo == NULL){fprintf(stderr,"Convert error");return 1;}
	int i = 0;
	while(fscanf(fi,"%d",&i) != EOF) fwrite(&i,sizeof(int), 1, fo);
	fclose(fi);
	fclose(fo);
	return 0;
}
int create_file(int *r,char *path,int size){
	int i = 0;
	FILE *fp = fopen(path,"w");
	if(fp == NULL || r == NULL){fprintf(stderr,"file failure");return 1;}
	while(i < size) fprintf(fp, "%d\n", r[i++]);
	fclose(fp);
	return 0;
}
int *set_random(int size){
	sleep(1);
	int i = 0; srand(time(0));
	int *r = malloc(size * sizeof(int));
	if(r == NULL){fprintf(stderr,"allocation fault");return r;}
        while(i < size) r[i++] = (int)(rand() % 1000000);
	return r;
}
int write_file(int *r,int size){
	int i; FILE *fp = fopen("F12.sorted","w");
	if(fp == NULL){fprintf(stderr,"failed writing");return 1;}
	for(i = 0; i < size; i++) fprintf(fp, "%d\n", r[i]);
	return 0;
}
