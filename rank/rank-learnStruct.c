#include <stdlib.h>
#include <stdio.h>

#include "stat_rank.h"

// from createDRank with createDRankStruct, it seems clear that DRank can be seen as a synonym of DRankStruct*
DRankStruct createDRankStruct(double value, int index) {
  DRankStruct *it=(DRankStruct*)malloc(sizeof(DRankStruct));
  it->index=index;
  it->value=value;
  it->rank=-1.0;
  return(*it);
}

void destroyDRankStruct(DRankStruct *it) {
  free(it);
}

// note how to write functions for Struct and StructPtr!
// compare this function with compareDRank(const void* a, const void* b)
int compareDRankStruct (const void* a, const void* b)
{
  // equivalent
  // return ((*(DRankStruct*)a).value-(*(DRankStruct*)b).value);
  return (((DRankStruct*)a)->value-((DRankStruct*)b)->value);
}


// apparently rankDRank can be faster than rankDRankStruct because it moves only pointers, but not the whole data structures
void rankDRankStruct(DRankStruct* items, int len) {
  int i=0;
  qsort(items, len, sizeof(DRankStruct), compareDRankStruct);
  for(i=0;i<len;++i)
    (items[i].index)++;
  
}

void rankDRank(DRank* items, int len) {
  int i=0;
  qsort(items, len, sizeof(DRank), compareDRank);
  for(i=0;i<len;++i)
    (items[i]->index)++;
}

extern int Ndim; 
extern double* values; 

void useDRankStruct() {
  int i;
  puts("---------- Using DRankStruct ----------");
  DRankStruct *ilist=(DRankStruct*)malloc(Ndim*sizeof(DRankStruct));

  puts("Before sorting");
  for(i=0;i<Ndim;++i) {
    ilist[i]=createDRankStruct(values[i], i);
    printf("ilist[%d]=%.2f, index=%d, rank=%.1f\n", 
	   i, ilist[i].value, ilist[i].index, ilist[i].rank);
  }
  rankDRankStruct(ilist, Ndim);
  puts("After sorting");
  for(i=0;i<Ndim;++i) {
    printf("ilist[%d]=%.2f, order=%d, rank=%.1f\n", 
	   i, ilist[i].value, ilist[i].index, ilist[i].rank);
  }
}
