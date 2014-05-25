
DOXYGEN=doxygen

all:rank

rank:stat_rank.c stat_rank.h rank-main.c rank-learnStruct.c 
	$(CC) $(DDEBUG) -Wall stat_rank.c rank-learnStruct.c rank-main.c -o rank

clean:
	rm -f core.* *~ *.o
	rm -f rank

.PHONY=doc clean