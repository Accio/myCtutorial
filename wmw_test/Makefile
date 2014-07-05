HOST=`hostname`
ifeq ($(HOST), montale.bas.roche.com)
  include $(BIOINFOCONFDIR)/prpidefs.make
  RMATH_HOME=$(BIOSEXTLIBLOC)/Rmath

  ## Make sure that you have compiled the Rmath standalone library
  ## include directory should contain Rmath.h
  RMATH_INC_DIR=${RMATH_HOME}/include
  RMATH_LIB_DIR=${RMATH_HOME}/lib
  RMATH_FLAGS=-DRMATH_STANDALONE -I${RMATH_INC_DIR} -L${RMATH_LIB_DIR}
  RMATH_LD_FLAGS=-lRmath
else 
  R=R
  RHOME=`R RHOME`
  RMATH_INC_DIR=${RHOME}/include
  RMATH_LIB_DIR=${RHOME}/lib
  RMATH_FLAGS=-I${RMATH_INC_DIR} -L${RMATH_LIB_DIR}
  RMATH_LD_FLAGS=-lR
endif

RANKDIR=../stat_rank/
CFLAGSL = $(CFLAGS) -I${RANKDIR} ${RMATH_FLAGS}

wmw_test:wmw_test.c wmw_test.h ${RANKDIR}/stat_rank.h
	$(CC) -Wl,-rpath ${RMATH_LIB_DIR} ${CFLAGSL} ${RANKDIR}/stat_rank.c  wmw_test.c -o wmw_test ${RMATH_LD_FLAGS} -lm  

clean:
	rm -f *.o *.so core.* *~
	rm -f wmw_test
