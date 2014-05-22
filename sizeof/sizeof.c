#include <stdlib.h>
#include <stdio.h>


int arrayLength(const int* ptr) {
  return(sizeof(ptr)/sizeof(ptr[0])); // wrong (it equals 2)
  //return(sizeof(ptr)/sizeof(int)); // wrong (it equals 2)
}

int main() {
  int Ndim=5;
  printf("Ndim=%d\n", Ndim);

  int stat_ptr[Ndim];
  int i=0;
  for(i=0;i<Ndim;i++)
    stat_ptr[i]=i;
  printf("stat_ptr length (func)=%d\n", arrayLength(stat_ptr)); // sizeof only applies to the original array
  printf("stat_ptr length (local, size(int))=%d\n", (int)(sizeof(stat_ptr)/sizeof(int))); 
  printf("stat_ptr length (local, size([0]))=%d\n", (int)(sizeof(stat_ptr)/sizeof(stat_ptr[0])));

  int *dyn_ptr=(int *) malloc(Ndim*sizeof(int));
  for(i=0;i<Ndim;i++)
    dyn_ptr[i]=i;
  printf("dyn_ptr length (func)=%d\n", arrayLength(dyn_ptr));// sizeof only applies to the original array (not pointer)
  printf("dyn_ptr length (local, size(int))=%d\n", (int)(sizeof(dyn_ptr)/sizeof(int)));
  printf("dyn_ptr length (local, size([0]))=%d\n", (int)(sizeof(dyn_ptr)/sizeof(dyn_ptr[0])));
  free(dyn_ptr);
  return 0;
}
