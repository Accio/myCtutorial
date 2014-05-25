#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MATHLIB_STANDALONE
#include <Rmath.h>

#include "stat_rank.h"

// Implementation follows limma::rankSumTestWithCorrelation
typedef struct  {
  size_t len;
  int* value;
} intArrayStruct, *iArray;

iArray iArrayCreate(int n) {
  iArray res=(iArray)malloc(sizeof(intArrayStruct));
  res->len=n;
  res->value=(int*)malloc(n*sizeof(int));
  return(res);
}
iArray iArrayCreateDef(int n, int val) {
  int i;
  iArray res=iArrayCreate(n);
  for(i=0;i<n;i++)
    res->value[i]=val;
  return(res);
}

void iArrayDestroy(iArray array) {
  array->len=0;
  free(array->value);
  free(array);
}
void iArrayPrint(const iArray array) {
  int i=0;
  for(i=0;i<array->len;++i) {
    printf("%d", array->value[i]);
    if(i!=array->len) {
      printf(" ");
    }
  }
  puts("");
}

typedef struct {
  size_t len;
  double* value;
} doubleArrayStruct , *dArray;

dArray dArrayCreate(int n) {
  dArray res=(dArray)malloc(sizeof(doubleArrayStruct));
  res->len=n;
  res->value=(double*)malloc(n*sizeof(double));
  return(res);
}
void dArrayDestroy(dArray array) {
  array->len=0;
  free(array->value);
  free(array);
}
void dArrayPrint(const dArray array) {
  int i=0;
  for(i=0;i<array->len;++i) {
    printf("%g", array->value[i]);
    if(i!=array->len) {
      printf(" ");
    }
  }
  puts("");
}

typedef struct {
  double U; // U statistic
  double ltP; // lower tail P value
  double gtP; // higher tail P value
} wmwResStruct, *wmwRes;

wmwRes wmwResCreate(double u, double ltp, double utp) {
  wmwRes res=(wmwRes)malloc(sizeof(wmwResStruct));
  res->U=u;
  res->ltP=ltp;
  res->gtP=utp;
  return(res);
}

void wmwResDestroy(wmwRes res) {
  free(res);
}

wmwRes wmwTest(const iArray index,
	       const dArray stat,
	       const double cor,
	       const int df) {
  int i,j;
  int n=stat->len;
  int n1=index->len;
  int n2=n-n1;
  double irsum=0; // sum of rank of index
  double U, mu, sigma2;
  double zlt, zut; // z lower/upper tail (normal distribution approximation)
  double plt, put, tmp;
  int ulen=0;
 
  DRankList list=createDRankList(stat->value, n);

  rankDRankList(list);

  // sum of the ranks of indexed elements
  for(i=0;i<n1;++i)
    irsum+=list->list[ index->value[i] ]->rank;
  ulen=list->ulen;
  
  U=n1*n2+n1*(n1+1.0)/2-irsum; 
  mu=(double)n1*n2/2;
  if(cor==0 || n1==1) {
    sigma2=n1*n2*(n+1.0)/12;
  } else {
    sigma2=(asin(1)*n1*n2+asin(0.5)*n1*n2*(n2-1.0)+\
	    asin(cor/2)*n1*(n1-1.0)*n2*(n2-1.0)+ \
	    asin((cor+1)/2)*n1*(n1-1)*n2)/2/M_PI;
  }
  
  if(ulen!=n) { // has ties
    int* tbl=(int*)malloc(ulen * sizeof(int));
    int ncount=0;
    double prod=0;
    sortDRankList(list);
    for(i=0;i<n;i=j+1) {
      j=i;
      while(j<n-1 && (list->list[j+1]->value==list->list[j]->value)) ++j;
      tbl[ncount++]=j-i+1;
    }
    for(i=0;i<ulen;++i)
      prod+=tbl[i]*(tbl[i]+1)*(tbl[i]-1);
    sigma2*=(1-prod/(n*(n+1)*(n-1)));
    free(tbl);
  }
  zlt=(U+0.5-mu)/sqrt(sigma2);
  zut=(U-0.5-mu)/sqrt(sigma2);
  
#ifdef WMWDEBUG
  printf("sum(r1)=%f, mu=%f, n=%d, n1=%d, n2=%d, sigma=%2.3f\n"
	 "zlt=%f, zut=%f\n",
  	 irsum, mu, n, n1, n2, sigma2, zlt, zut);
#endif

  pnorm_both(zut, &tmp, &plt, 1, 0); // upper tail p of upper-tail z 
  pnorm_both(zlt, &put, &tmp, 0, 0); // lower tail p of lower-tail z

  wmwRes res=wmwResCreate(U, plt, put);
  return(res);
}

#define EPSILON 1E-6
#define qequal(x,y) abs((x)-(y))<EPSILON

int main(int argc, char** argv) {
  time_t seed=time(NULL);
  srand(seed);
  int i;
  int Nlen;
  int IndLen;
  double cor;

  if(argc!=4) {
    printf("usage: %s TOTAL_LENGTH VAR_LENTH COR\n",argv[0]);
    return(-1);
  }

  Nlen=atoi(argv[1]);
  IndLen=atoi(argv[2]);
  cor=atof(argv[3]);

  if(IndLen>Nlen || Nlen<0 || IndLen<0) {
    puts("Error: TOTAL_LENGH must be no less than VAR_LENGTH, and both must be positive");
    return(-2);
  } else if (cor>1 | cor<0) {
    puts("Error: COR must be between 0 and 1");
    return(-3);
  }

  dArray stats=dArrayCreate(Nlen);
  //iArray ranks=iArrayCreate(Nlen);
  wmwRes res;
  iArray myInd=iArrayCreate(IndLen);;

  for(i=0;i<Nlen;++i)
    stats->value[i]=rand() % Nlen + 1.25;

  //It appears rank is very slow when Nlen is large (=40000). Why?
  //rank(stats, ranks);

#ifdef DEBUG
  //printf("Values: ");
  //dArrayPrint(stats);
  //printf("Ranks: ");
  //iArrayPrint(ranks);
#endif
  
  for(i=0;i<IndLen;i++)
    myInd->value[i]=rand() % Nlen;
  res=wmwTest(myInd, stats, cor, 0);
  printf("U=%.2f, ltP=%.4f, gtP=%.4f\n",
	 res->U, res->ltP, res->gtP);

  dArrayDestroy(stats);
  //iArrayDestroy(ranks);
  return(0);
}
