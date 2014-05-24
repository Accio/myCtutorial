#ifndef _STAT_RANK_H_
#define _STAT_RANK_H_

typedef struct {
  int index;
  double value;
  int order;
  double rank;
} ItemStruct, *Item;

typedef struct {
  Item* list;
  int len;
  int ulen;
} ItemListStruct, *ItemList;

int isRanked(const ItemList list);

int compareItem(const void* a, const void* b);
int compareItemIndex(const void* a, const void* b);

ItemList createItemList(const double* array, int len);
void printItemList(const ItemList list);
void sortRankItemList(ItemList list);
void rankItemList(ItemList list);
void sortItemList(ItemList list);

/* private */
Item createItem(double, int);
void destroyItem(Item it);
#endif /* _STAT_RANK_H_ */
