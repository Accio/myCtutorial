/* example of exec: executing another program in a forked process */

#include <stdio.h>
#include <stdlib.h>

#define FORK_TIME 0
#define FORK_BIN "fork"

int main(int argc, char **argv) {
  int child_id;
  int seconds;
  char child_argv[10];

  if(argc==1)
    seconds = FORK_TIME;
  else
    seconds = atoi(argv[1]);

  snprintf(child_argv, sizeof(child_argv), "%d", seconds);

  printf("Here I am in the execee program! Seconds =%s\n", child_argv);
  
  child_id=fork();
  if(child_id) {
    printf("I am in the execee program. Bye now\n");
  } else {
    execl(FORK_BIN, FORK_BIN ,child_argv, NULL); // note that the last parameter of execl must be NULL
  }
  return 0;
}
