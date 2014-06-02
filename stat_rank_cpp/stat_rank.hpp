/*! \file Generic statistical rank
 *
 *  zhangj83, 07.05.2014
 *
 *  Data structures and function declaration for statistical rank which can be applied to generic data types
 *  It is a C++ implementation of the algorithm originally written in C.
 *  The C implementation, which only applied to double values, can be found at https://github.com/Accio/myCtutorial/tree/master/wmw_test
 */

#ifndef _STAT_RANK_H_
#define _STAT_RANK_H_

template <class T> class Rank {
 private:
  int index; /*!< Input index (starting from 0) */
  double rank; /*!< Fractional ranking (starting from 1) */
  T value; /*!< Value of the number */

  bool isRanked();

 public:
  bool compVal(Rank const &a, Rank const &b);
  bool compInd(Rank const &a, Rank const &b);
}

template <class T> class DRankList {
 private:
  std::vector<Rank<T>> list;
  int ulen;

 public:
  RankList(int len);
  
  void print(RankList const &a);
  void sortRank(RankList list);
  void rank(RankList list);
  void sort(RankList list);
}

#endif /* _STAT_RANK_H_ */
