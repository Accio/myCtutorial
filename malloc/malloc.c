#include <stdio.h>
#include <stdlib.h>

#define myput(x) printf(#x "=%d\n", x)

int* allocate(int N) {
  int* ip=(int *)malloc(N*sizeof(int));
  if(ip==NULL) {
     perror("bad memory allocation in allocate");
     exit(EXIT_FAILURE);
  }
  return(ip);
}

int main(int argc, char** argv) {
  int i=0;
  int Nstat=5;
  int Ndym=6;

  int ia[Nstat]; // a static array 
  int *ip;
  for(i=0;i<Nstat;i++) {
    ia[i]=i+1;
  }
  for(i=0;i<Nstat;i++) {
    myput(ia[i]);
  }
  ip=ia;
  for(i=0;i<Nstat;i++) {
    myput(*ip++);
  }

  int* myip=allocate(Ndym);
  for(i=0;i<Ndym;++i) {
    myip[i]=i*2+1;
  }
 
  /* following commands will cause memory error since myip has changed */
  //for(i=0;i<Ndym;++i)
  //  myput(*myip++);
  //free(myip);

  /* in contrast the following lines are fine since myip has not changed*/
  for(i=0;i<Ndym;++i)
    myput(myip[i]);
  free(myip);
  return 0;
}
