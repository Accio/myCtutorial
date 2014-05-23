#ifndef RANK_H_
#define RANK_H_

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

int compareItem(const void* a, const void* b);

ItemList createItemList(const double* array, int len);
void printItemList(const ItemList list);
void rankItemList(ItemList list);

/* private */
Item createItem(double, int);
void destroyItem(Item it);
#endif /* RANK_H_ */
