/*
 * Do parent and child have two separate heaps?
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 1024
#define NUMCHILD 2

int main(int argc, char *argv[]){
  pid_t pid;
  char *common;
  
  /*Try to see if common can be shared */
  common = (char *) malloc (sizeof (char));
  *common = 'M';
  
  fprintf(stdout, "Caller  : mypid=%d\t *(common):%c\t common:%ld\n",
    getpid(), *common, (long int) common);
  fflush (stdout);

  pid=fork();
  if (pid == 0) {
    fprintf(stdout, "Child 1 : mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    *common = 'C';
    fprintf(stdout, "Child 2 : mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    exit (0);
  } else {
    
    sleep(2); // C on *(common) ?? NO
    fprintf(stdout, "Parent 1: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    *common = 'P';
    fprintf(stdout, "Parent 2: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
  }

  return 0;
}
