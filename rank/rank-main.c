#include <stdio.h>

#include "rank.h"

double values[]={2.5, 1.5, 3.5, 1.5 ,4.5 ,4.5, 7.5, 7.5, 0, 4.5, 4.5};
int Ndim=11;

void useItem() {
  puts("---------- Using Item ----------");

  ItemList ilist=createItemList(values, Ndim);

  puts("Before sorting");
  printItemList(ilist);

  sortRankItemList(ilist);
  puts("After sorting");
  printItemList(ilist);

  rankItemList(ilist);
  puts("Only ranking, no sorting");
  printItemList(ilist);
}


int main(int argc, char** argv) {
  useItem();
  //useItemStruct();
  // puts("Information");
  //printf("Size of Item:%d\n", sizeof(Item));
  //printf("Size of ItemStruct:%d\n", sizeof(ItemStruct));
  return(0);
}
