/*
 *  Verify the size of a pipe
 *  Run in background
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define SIZE  512*1024		// 512 Kbytes

int fd[2];

int
main (int argc, char ** argv){
  int i, n, nR, nW;
  char c = '1';

  // no buffering
  setbuf (stdout, 0);

  // Create pipe
  pipe(fd);

  n = 0;
  if (fork()) {
    fprintf (stdout, "\nParent PID=%d\n", getpid());
//    sleep (1);
    for (i=0; i<SIZE; i++) {
       nW = write (fd[1], &c, 1);
       n = n + nW;
       fprintf (stdout, "W %d\r", n);
    }
  } else {
    fprintf (stdout, "Child  PID=%d\n", getpid());
    sleep (10);
    for (i=0; i<SIZE; i++) {
      nR = read (fd[0], &c, 1);
      n = n + nR;
      fprintf (stdout, "\t\t\t\tR %d\r", n);
    }
  }

   return (0);
}
