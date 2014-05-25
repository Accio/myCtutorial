include $(BIOINFOCONFDIR)/prpidefs.make
RMATH_HOME=$(BIOSEXTLIBLOC)/Rmath

## Make sure that you have compiled the Rmath standalone library
## include directory should contain Rmath.h
RMATH_INC_DIR=${RMATH_HOME}/include
RMATH_LIB_DIR=${RMATH_HOME}/lib

RANKDIR=../stat_rank/
CFLAGSL = $(CFLAGS) -I${RMATH_INC_DIR} -L${RMATH_LIB_DIR} -I${RANKDIR}

wmw_test:wmw_test.c ${RANKDIR}/stat_rank.h
	$(CC) -Wl,-rpath ${RMATH_LIB_DIR} ${CFLAGSL} ${RANKDIR}/stat_rank.c  wmw_test.c -o wmw_test -lRmath -lm  

clean:
	rm -f *.o *.so core.* *~
	rm -f wmw_test
