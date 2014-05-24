
DOXYGEN=doxygen

all:rank

rank:rank.c rank.h rank-main.c rank-learnStruct.c 
	$(CC) $(DDEBUG) -Wall rank.c rank-learnStruct.c rank-main.c -o rank

clean:
	rm -f core.* *~ *.o
	rm -f rank

.PHONY=doc clean