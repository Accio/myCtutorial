/* example of fork + wait */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DEFAULT_CODE 0

int main(int argc, char **argv) {
  int child_id;
  int code;
  pid_t w;
  int status;

  if(argc==1) 
    code = DEFAULT_CODE;
  else
    code = atoi(argv[1]);

  printf("Here I am in the forkee program! Code=%d\n", code);
  
  child_id=fork();
  if(child_id) {
    printf("I am the parent. Bye now!\n");
    w=wait(&status);
    if(w==-1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    
    if (WIFEXITED(status)) {
      printf("exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      printf("stopped by signal %d\n", WSTOPSIG(status));
    }

  } else {
    printf("Child PID is %d\n", getpid());
    if(argc == 1) {
      printf("Try to kill me from another terminal...\n");
      pause();
    }

    _exit(code);
  }
  return 0;
}
