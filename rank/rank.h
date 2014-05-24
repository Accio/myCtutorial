/*! \file rank.h
    \brief Header for statistical ranking
    
    Details.
*/
#ifndef _STAT_RANK_H_
#define _STAT_RANK_H_

/*! \struct "*Item"
 *  \struct ItemStruct
 *  \brief A class used to sort/rank double values
 *
 *  ItemStruct is synonym to *Item
 */
typedef struct {
  int index; /*!< Input index (starting from 0) */
  double value; /*!< Value of the number */
  double rank; /*!< Fractional ranking (starting from 1) */
} ItemStruct, *Item;

/*! \struct *ItemList
 *  \brief A dynamic array of Items, with length and unique length
 *
 *  ItemListStruct is synonym to ItemList
 */
typedef struct {
  Item* list; /*!< Dynamic array of Items */
  int len; /*!< Length of the array */
  int ulen; /*!< Length of unique elements */
} ItemListStruct, *ItemList;

/*! \brief compare Item by value */
int compareItem(const void* a, const void* b);
/*! \brief compare Item by index */
int compareItemIndex(const void* a, const void* b);

/*! \brief initialize an ItemList 
 * \param array an array of double values
 * \param len the length of the array
 */
ItemList createItemList(const double* array, int len);
/*! \brief print an ItemList */
void printItemList(const ItemList list);
/*! \brief perform sorting and ranking at once */
void sortRankItemList(ItemList list);
/*! \brief rank the ItemList and keeping the input order */
void rankItemList(ItemList list);
/*! \brief sort the ItemList */
void sortItemList(ItemList list);

/* private */
Item createItem(double, int);
void destroyItem(Item it);
int isRanked(const ItemList list);

#endif /* _STAT_RANK_H_ */
