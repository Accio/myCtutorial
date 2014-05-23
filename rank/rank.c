
#include <stdio.h>

#include "rank-private.h"
#include "rank.h"

int compareItem (const void* a, const void* b) // dereference void pointer: *((T*)ptr)
{
  // const Item *ap=(Item*)a;
  // const Item *bp=(Item*)b;
  //return ((*ap)->value-(*bp)->value);
  return ((*(Item*)a)->value-(*(Item*)b)->value);

}

double values[]={2.5, 1.5, 3.5, 1.5 ,4.5 ,4.5, 7.5, 7.5, 0, 4.5, 4.5};
int Ndim=11;

ItemList createItemList(const double* array, int len) {
  int i;
  Item *ilist=(Item*)malloc(len*sizeof(Item));
  for(i=0;i<len;++i) {
    ilist[i]=createItem(array[i], i);
  }
  ItemList res=(ItemList)malloc(sizeof(ItemList));
  res->list=ilist;
  res->len=len;
  res->ulen=-1;
  return(res);
}


void printItemList(const ItemList list) {
  int i=0;
  printf("--ItemList (Len=%d, UniqLen=%d)--\n",
	 list->len, list->ulen);
  for(i=0;i<list->len;i++)
    printf("ilist[%d]=%.2f, index=%d, rank=%.1f\n",
	   i, 
	   list->list[i]->value, 
	   list->list[i]->index,
	   list->list[i]->rank);
}

void rankItemList(ItemList list) {
  Item* ll=list->list;
  int len=list->len;
  int i, j, k;
  int ucount=0;
  double *backup=(double*)malloc(len * sizeof(double));
  for(i=0;i<len; ++i)
    backup[i]=ll[i]->value;

  qsort(ll, len, sizeof(Item), compareItem);

  for(i=0; i<len;i=j+1) {
    j=i;
#ifdef DEBUG
    if(j<len-1)
      printf("i=%d, j=%d, ind1=%d, ind2=%d, val1=%.1f, val2=%.1f\n", 
	     i, j, 
	     ll[j]->index, ll[j+1]->index, 
	     backup[ll[j]->index],
	     backup[ll[j+1]->index]);
#endif

    while((j<len-1) && backup[ll[j]->index] == backup[ll[j+1]->index]) {
      j++;
    }
    for(k=i;k<=j;k++)
      ll[k]->rank=(i+j+2)/2.;
    ucount++;
  }
  for(i=0;i<len;++i) {
    (ll[i]->index)++; // index starts from 1
  }
  free(backup);
  list->ulen=ucount;
}

void useItem() {
  int i;
  puts("---------- Using Item ----------");

  ItemList ilist=createItemList(values, Ndim);

  puts("Before sorting");
  printItemList(ilist);

  rankItemList(ilist);
  puts("After sorting");
  printItemList(ilist);
}

int main(int argc, char** argv) {
  //useItemStruct();
  useItem();
  // puts("Information");
  //printf("Size of Item:%d\n", sizeof(Item));
  //printf("Size of ItemStruct:%d\n", sizeof(ItemStruct));
  return(0);
}
