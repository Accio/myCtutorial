#include <stdio.h>
#include <malloc.h>

#define myput(x) printf(#x "=%d\n", x)

int* allocate(int N) {
  int* ip=(int *)malloc(N*sizeof(int));
  if(ip==NULL)
    puts("bad memory allocation");// die
  return(ip);
}

int main(int argc, char** argv) {
  int i=0;

  int ia[5]; // a static array 
  int *ip;
  for(i=0;i<5;i++) {
    ia[i]=i+1;
  }
  for(i=0;i<5;i++) {
    myput(ia[i]);
  }
  ip=ia;
  for(i=0;i<5;i++) {
    myput(*ip++);
  }

  int* myip=allocate(6);
  for(i=0;i<6;++i) {
    myip[i]=i*2+1;
  }
 
  /* following commands will cause memory error since myip has changed */
  //for(i=0;i<6;++i)
  //  myput(*myip++);
  //free(myip);

  /* in contrast the following lines are fine since myip has not changed*/
  for(i=0;i<6;++i)
    myput(myip[i]);
  free(myip);
  return 0;
}
