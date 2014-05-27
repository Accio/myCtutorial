DOXYGEN=doxygen

.PHONY=doc
all:
	$(MAKE) -C fork
	$(MAKE) -C malloc
	$(MAKE) -C sizeof
	$(MAKE) -C stat_rank
	$(MAKE) -C wmw_test

doc:
	$(DOXYGEN) Doxyfile

