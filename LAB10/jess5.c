#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "semaphore.h"
#include <sys/wait.h>
int main(){
        fork();
        fork();
        printf("Hello, I have process number: %d => %d\n",getpid(),getppid());
        return 0;
}


