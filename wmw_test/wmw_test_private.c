/*! \file private functions that are not public interface of wmw_test
  *
  */

/*! \brief rank an array of double values and fill in ranks
 * the function comes from http://nathsaharia.blogspot.ch/2012/09/implement-rank-sort-in-c.html 
 * Unfortunately it can be slow when the input array is large. The complexity is O(n^2)
*/
void rank(const dArray values, iArray ranks) {
  double* v=values->value;
  int* r=ranks->value;
  int len=values->len;
  int i,j;
  for(i=0;i<len;++i) r[i]=1; // rank starts from 1
  for(i=0;i<len;++i) {
    for(j=0;j<i;++j) { /* O(n2) */
      v[j]<=v[i] ? r[i]++ : r[j]++;
    }
  }
}

