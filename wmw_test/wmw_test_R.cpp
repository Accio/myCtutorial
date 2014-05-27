/*! \file wmw_test_R.c
    R interface to wmw_test
*/

#include <Rcpp.h>
using namespace Rcpp;
#extern "C" {
  #include <rank.h>
  #include <wmw_test.h>
}
/*! \brief rank sum test with correlation
 *
 * Wilcoxon-Mann-Whitney test with correction for correlation
 * \param indList: an list of integer indices (starting from 1 by R convention)
 * \param matrix: an expression matrix with features in rows and samples in columns
 * \param type: return value type: 1=U stat, 2=ltP, 3=gtP, 4=-log10(ltP), 5=-log10(gtP)
 */
RcppExport SEXP wilcoxon_mann_whitney(SEXP indlist, SEXP matrix, SEXP type) {
  NumericVector ip(indlist)
  NumericMatrix mp(matrix);
  int i=0;
  int nr=ip.size();
  int nc=mp.ncol();
  NumericMatrix res(nr, nc);
  return(res);
}
