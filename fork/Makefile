all:fork exec-example

fork:fork.c
	${CC} fork.c -o fork

exec-example:fork
	${CC} exec-example.c -o exec-example

.PHONY=test-exec

test-exec: exec-example
	./exec-example 2