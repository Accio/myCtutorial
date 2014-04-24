/* example of fork */
/* Origin: http://home.adelphi.edu/sbloch/class/archive/271/fall2005/examples/c/fork_examples/ex2.c */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TIME 0

int main(int argc, char **argv) {
  int child_id;
  int seconds;

  if(argc==1) 
    seconds = DEFAULT_TIME;
  else
    seconds = atoi(argv[1]);

  printf("Here I am in the forkee program! Seconds=%d\n", seconds);
  
  child_id=fork();
  if(child_id) {
    printf("I am the parent. Bye now!\n");
  } else {
    sleep(seconds);
    printf("I am the child. Bye now!\n");
  }
  return 0;
}
