all:rank

rank:rank.c rank.h rank-private.c rank-private.h
	$(CC) rank.c rank-private.c -o rank

clean:
	rm -f core.* *~ *.o
	rm -f rank