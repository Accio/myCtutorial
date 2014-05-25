#include <stdio.h>

#include "stat_rank.h"

double values[]={2.5, 1.5, 3.5, 1.5 ,4.5 ,4.5, 7.5, 7.5, 0, 4.5, 4.5};
int Ndim=11;

void useDRank() {
  puts("---------- Using DRank ----------");

  DRankList ilist=createDRankList(values, Ndim);

  puts("Before sorting");
  printDRankList(ilist);

  sortDRankList(ilist);
  puts("Only sorting (ranked implicitly)");
  printDRankList(ilist);

  rankDRankList(ilist);
  puts("Only ranking (sorted implicitly)");
  printDRankList(ilist);

  sortRankDRankList(ilist);
  puts("After sorting and ranking");
  printDRankList(ilist);







}


int main(int argc, char** argv) {
  useDRank();
  //useDRankStruct();
  // puts("Information");
  //printf("Size of DRank:%d\n", sizeof(DRank));
  //printf("Size of DRankStruct:%d\n", sizeof(DRankStruct));
  return(0);
}
