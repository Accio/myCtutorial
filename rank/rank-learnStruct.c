#include <stdlib.h>
#include <stdio.h>

#include "rank.h"

// from createItem with createItemStruct, it seems clear that Item can be seen as a synonym of ItemStruct*
ItemStruct createItemStruct(double value, int index) {
  ItemStruct *it=(ItemStruct*)malloc(sizeof(ItemStruct));
  it->index=index;
  it->value=value;
  it->order=0;
  it->rank=-1.0;
  return(*it);
}

void destroyItemStruct(ItemStruct *it) {
  free(it);
}

// note how to write functions for Struct and StructPtr!
// compare this function with compareItem(const void* a, const void* b)
int compareItemStruct (const void* a, const void* b)
{
  // equivalent
  // return ((*(ItemStruct*)a).value-(*(ItemStruct*)b).value);
  return (((ItemStruct*)a)->value-((ItemStruct*)b)->value);
}


// apparently rankItem can be faster than rankItemStruct because it moves only pointers, but not the whole data structures
void rankItemStruct(ItemStruct* items, int len) {
  int i=0;
  qsort(items, len, sizeof(ItemStruct), compareItemStruct);
  for(i=0;i<len;++i)
    (items[i].index)++;
  
}

void rankItem(Item* items, int len) {
  int i=0;
  qsort(items, len, sizeof(Item), compareItem);
  for(i=0;i<len;++i)
    (items[i]->index)++;
}

extern int Ndim; 
extern double* values; 

void useItemStruct() {
  int i;
  puts("---------- Using ItemStruct ----------");
  ItemStruct *ilist=(ItemStruct*)malloc(Ndim*sizeof(ItemStruct));

  puts("Before sorting");
  for(i=0;i<Ndim;++i) {
    ilist[i]=createItemStruct(values[i], i);
    printf("ilist[%d]=%.2f, index=%d, rank=%.1f\n", 
	   i, ilist[i].value, ilist[i].index, ilist[i].rank);
  }
  rankItemStruct(ilist, Ndim);
  puts("After sorting");
  for(i=0;i<Ndim;++i) {
    printf("ilist[%d]=%.2f, order=%d, rank=%.1f\n", 
	   i, ilist[i].value, ilist[i].index, ilist[i].rank);
  }
}
