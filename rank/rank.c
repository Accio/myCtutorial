#include <stdio.h>
#include <stdlib.h>

#include "rank.h"

Item createItem(double value, int index) {
  Item it=(Item)malloc(sizeof(ItemStruct)); // TAKE CARE: use sizeof(Item) here will produce bugs that are very difficult to debug
  it->index=index;
  it->value=value;
  it->order=0;
  it->rank=-1.0;
  return(it);
}

void destroyItem(Item it) {
  free(it);
}

int compareItem (const void* a, const void* b) // dereference void pointer: *((T*)ptr)
{
  // const Item *ap=(Item*)a;
  // const Item *bp=(Item*)b;
  //return ((*ap)->value-(*bp)->value);
  return ((*(Item*)a)->value-(*(Item*)b)->value);
}

int compareItemIndex (const void* a, const void* b) // dereference void pointer: *((T*)ptr)
{
  // const Item *ap=(Item*)a;
  // const Item *bp=(Item*)b;
  //return ((*ap)->value-(*bp)->value);
  return ((*(Item*)a)->index-(*(Item*)b)->index);

}



ItemList createItemList(const double* array, int len) {
  int i;
  Item *ilist=(Item*)malloc(len*sizeof(Item));
  for(i=0;i<len;++i) {
    ilist[i]=createItem(array[i], i);
  }
  ItemList res=(ItemList)malloc(sizeof(ItemListStruct));
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

/* sortRankItemList: first sort and gives rank */
void sortRankItemList(ItemList list) {
  if(isRanked(list)) return; // make sure that this function runs only once
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
      printf("[DEBUG] i=%d, j=%d, ind1=%d, ind2=%d, val1=%.1f, val2=%.1f\n", 
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


/* rankItemList: only rank, do not sort (the input sequence remain unchanged) */
int isRanked(const ItemList list) {return(list->list[0]->rank>0);}

void rankItemList(ItemList list) {
  if(!isRanked(list))
    sortRankItemList(list);
  Item* ll=list->list;
  int len=list->len;
  qsort(ll, len, sizeof(Item), compareItemIndex);
}

void sortItemList(ItemList list) {
  if(!isRanked(list))
    sortRankItemList(list);
  Item* ll=list->list;
  int len=list->len;
  qsort(ll, len, sizeof(Item), compareItem);
}
