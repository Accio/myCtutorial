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
} *ItemList;

#endif /* RANK_H_ */
