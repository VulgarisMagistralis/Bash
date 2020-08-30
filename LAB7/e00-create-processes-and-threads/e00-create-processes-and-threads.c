// time ./e00-create-processes-and-threads 300   creates 100 threads and
// displays the CPU time 
//
// time ./e00-create-processes-and-threads -300  creates 100 processes and
// displays the CPU time 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *t (){
  pthread_t tid;
  
  pthread_exit (NULL);
}

int main (int argc, char *argv[]){
  pthread_t tid;
  int i, pid, n, rc;

  n = atoi(argv[1]);
  if (n > 0) {
    fprintf (stdout, "Creating %d threads\n", n);
    for (i=0; i< n; i++){
      rc = pthread_create (&tid, NULL, t, NULL);
      if (rc) {
        fprintf (stderr, "ERROR: Pthread_create() return_code:  %d thread %d\n", rc, n);
        exit(-1);
      }
    }
  }
  else {
    n = -atoi(argv[1]);
    fprintf (stdout, "Creating %d processes\n", n);
    for (i=0; i< n; i++){
      pid = fork();
      if (pid==-1) {
        fprintf (stderr, "ERROR: fork() return_code:  %d process n. %d\n", pid, n);
        exit(-1);
      }
      else
        if (pid ==0)
          break;
    }
  }
}
