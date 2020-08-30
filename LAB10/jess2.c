#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    fork();
    printf("Hello, I have process number: %d => %d\n",getpid(),getppid());
    return 0;
}
