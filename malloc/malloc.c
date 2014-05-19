#include <stdio.h>
#include <malloc.h>

#define myput(x) printf(#x "=%d\n", x)

int* allocate(int N) {
  int* ip=(int *)malloc(N*sizeof(int));
  if(ip==NULL)
    // die
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
 
  for(i=0;i<6;++i)
    myput(*myip++);

  free(myip);
  return 0;
}
