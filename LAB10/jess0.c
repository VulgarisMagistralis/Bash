#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    fork();
    printf("Show me the new line before the pid child dies \n");
    return 0;
}
