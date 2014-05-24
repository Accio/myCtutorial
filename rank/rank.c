#include <stdio.h>
#include <stdlib.h>

#include "rank.h"

/*! \brief Create a Item object
 * 
 * A item object holds a double value, its original index, and its rank.
 *
 * The rank is initialized with -1, and changed to a positive one (starting from 1) by sortRankItemList. This is used to check whether that function has been run or not, so please do not change the initial value of rank.
 */

Item createItem(double value, int index) {
  Item it=(Item)malloc(sizeof(ItemStruct)); // TAKE CARE: use sizeof(Item) here will produce bugs that are very difficult to debug
  it->index=index;
  it->value=value;
  it->rank=-1.0;
  return(it);
}

/*! \brief destroy an item object */
void destroyItem(Item it) {
  free(it);
}

/*! \brief compare item objects by value */
int compareItem (const void* a, const void* b) // dereference void pointer: *((T*)ptr)
{
  // const Item *ap=(Item*)a;
  // const Item *bp=(Item*)b;
  //return ((*ap)->value-(*bp)->value);
  return ((*(Item*)a)->value-(*(Item*)b)->value);
}

/*! \brief compare item objects by input index */
int compareItemIndex (const void* a, const void* b) // dereference void pointer: *((T*)ptr)
{
  // const Item *ap=(Item*)a;
  // const Item *bp=(Item*)b;
  //return ((*ap)->value-(*bp)->value);
  return ((*(Item*)a)->index-(*(Item*)b)->index);

}

/*! \brief create an ItemList object 
 \param array: a double array
 \param len: the length of the double array
*/
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

/*! \brief print an ItemList object
*/
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

/*! \brief test whether the ItemList has been ranked 
 *
 * if sortRankItemList has been run, the value will be 1, otherwise 0.
 */
int isRanked(const ItemList list) {return(list->list[0]->rank>0);}

/*! \brief: sort and gives rank to a ItemList
 *
 *  sortRankItemList sorts and gives statistical (fractional) rank to a ItemList.
 * 
 *  sortRankItemList runs once and only once (controlled by isRanked):
 *  Once the ranks have been set (i.e. ranks>0), the function will exit
 *  without doing anything.
 */ 
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

/*! \brief: rankItemList
 * \param list An ItemList
 * It calls sortRankItemList if the ItemList has not been ranked before
 * The items in the list are sorted by input index
 */
void rankItemList(ItemList list) {
  if(!isRanked(list))
    sortRankItemList(list);
  Item* ll=list->list;
  int len=list->len;
  qsort(ll, len, sizeof(Item), compareItemIndex);
}

/*! \brief: sortItemList
 * \param list An ItemList
 * It calls sortRankItemList if the ItemList has not been ranked before
 * The items in the list are sorted by ascending order of the values.
 */
void sortItemList(ItemList list) {
  if(!isRanked(list))
    sortRankItemList(list);
  Item* ll=list->list;
  int len=list->len;
  qsort(ll, len, sizeof(Item), compareItem);
}
