all:rank

rank:rank.c rank.h rank-main.c rank-learnStruct.c 
	$(CC) rank.c rank-learnStruct.c rank-main.c -o rank

clean:
	rm -f core.* *~ *.o
	rm -f rank